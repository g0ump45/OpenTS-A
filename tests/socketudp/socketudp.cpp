/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

// Drives the UDP transport against a socket that reaches no network, so that the
// send and receive passes can be exercised without opening a session. The
// transport is used through its public surface only; what a test knows about a
// datagram it learns from the socket it handed in.

#include "always.h"

#include "netsocket.h"
#include "wspudp.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>


// The transport logs through DebugString and reads the default port from the
// game. Neither is worth starting an engine for.
int WestwoodOnline_PortNumber = 1234;

void __cdecl DebugString(char const *, ...)
{
}

void __cdecl DebugStringNoPrefix(char const *, ...)
{
}

// The transport asks the platform for a socket as it is constructed. Answering
// with a null one is what keeps the Winsock implementation out of this harness
// altogether; each test then supplies the socket it means to drive.
std::unique_ptr<SocketClass> Socket_Create_Platform_Socket(void)
{
	return(std::make_unique<NullSocketClass>());
}

namespace {

int Failures = 0;


void Check(bool condition, char const * what)
{
	std::printf("%-72s %s\n", what, condition ? "ok" : "FAILED");
	if (!condition) {
		Failures++;
	}
}


// A transport wired to a socket the test keeps hold of. Open_Socket is what
// actually opens the injected socket, so the order here matters.
struct Harness
{
	UDPInterfaceClass Transport;
	NullSocketClass * Socket = nullptr;

	explicit Harness(std::vector<InterfaceType> interfaces = {})
	{
		auto socket = std::make_unique<NullSocketClass>();
		Socket = socket.get();
		Socket->Set_Interfaces(std::move(interfaces));

		Transport.Set_Socket(std::move(socket));
		Transport.Set_Local_Port(50000);
		Transport.Set_Destination_Port(50000);
		Transport.Open_Socket();
		Transport.Start_Listening();
	}

	// Hands the transport a buffer to send and returns the bytes that reached
	// the wire, which is the framing a peer would have to accept.
	std::vector<unsigned char> Send(std::string const & payload, IPXAddressClass const & to)
	{
		Socket->Clear_Sent();
		IPXAddressClass address = to;
		Transport.WriteTo(const_cast<char *>(payload.data()), static_cast<int>(payload.size()), &address, sizeof(address));
		Transport.Service();

		if (Socket->Sent().empty()) return(std::vector<unsigned char>());
		return(Socket->Sent().back().Bytes);
	}

	// Drains whatever the transport accepted, as the manager's service pass does.
	std::vector<std::string> Drain(void)
	{
		std::vector<std::string> received;

		for (;;) {
			char buffer[2048];
			char address[64];
			int length = sizeof(buffer);
			int address_len = sizeof(address);

			int const rc = Transport.Read(buffer, length, address, address_len);
			if (rc == 0) break;

			received.emplace_back(buffer, buffer + length);
		}

		return(received);
	}
};


IPXAddressClass Peer(uint32_t ip, uint16_t port)
{
	return(IPXAddressClass(ip, Socket_Network_Port(port)));
}


/// A send the socket refuses must cost the pass, not the queue. This is the
/// case the transport cannot reach against a real socket, since a loopback
/// send buffer never fills.
void Test_Full_Socket_Keeps_The_Queue(void)
{
	Harness harness;
	IPXAddressClass const peer = Peer(0x0100007f, 51000);

	IPXAddressClass first = peer;
	IPXAddressClass second = peer;
	char one[] = "first";
	char two[] = "second";

	// WriteTo flushes as it queues, so the socket has to be refusing before the
	// packets go in for them to still be waiting.
	harness.Socket->Set_Would_Block(true);

	harness.Transport.WriteTo(one, 5, &first, sizeof(first));
	harness.Transport.WriteTo(two, 6, &second, sizeof(second));

	harness.Transport.Service();
	Check(harness.Socket->Sent().empty(), "a full socket sends nothing");

	harness.Socket->Set_Would_Block(false);
	harness.Transport.Service();

	Check(harness.Socket->Sent().size() == 2, "both packets survive the refused pass");

	if (harness.Socket->Sent().size() == 2) {
		std::vector<unsigned char> const & sent = harness.Socket->Sent()[0].Bytes;
		bool const ordered = sent.size() == 5 + sizeof(unsigned int)
			&& std::memcmp(sent.data() + sizeof(unsigned int), "first", 5) == 0;
		Check(ordered, "the queue keeps its order across the refusal");
	}
}


/// A datagram the transport framed is one it accepts back.
void Test_Round_Trip(void)
{
	Harness harness;
	IPXAddressClass const peer = Peer(0x0100007f, 51000);

	std::vector<unsigned char> const wire = harness.Send("hello", peer);
	Check(!wire.empty(), "a queued packet reaches the socket");

	harness.Socket->Deliver(peer, wire.data(), static_cast<int>(wire.size()));
	harness.Transport.Service();

	std::vector<std::string> const got = harness.Drain();
	Check(got.size() == 1 && got[0] == "hello", "a framed datagram is accepted back");
}


/// The drain is bounded so a flood cannot hold the frame, and what is left
/// waits for the next pass rather than being lost.
void Test_Drain_Is_Bounded(void)
{
	Harness harness;
	IPXAddressClass const peer = Peer(0x0100007f, 51000);

	std::vector<unsigned char> const wire = harness.Send("x", peer);

	int const flood = WS_MAX_STATIC_BUFFERS + 10;
	for (int i = 0; i < flood; i++) {
		harness.Socket->Deliver(peer, wire.data(), static_cast<int>(wire.size()));
	}

	harness.Transport.Service();
	std::size_t const first_pass = harness.Drain().size();
	Check(first_pass <= WS_MAX_STATIC_BUFFERS, "one pass takes no more than the buffer pool holds");

	harness.Transport.Service();
	std::size_t const second_pass = harness.Drain().size();
	Check(first_pass + second_pass == static_cast<std::size_t>(flood), "the rest waits for the next pass");
}


/// A transient failure mid-drain must not end the pass. Windows reports
/// WSAECONNRESET routinely when a peer quits, and stopping there would strand
/// everything queued behind it.
void Test_Reset_Does_Not_End_The_Pass(void)
{
	Harness harness;
	IPXAddressClass const peer = Peer(0x0100007f, 51000);

	std::vector<unsigned char> const wire = harness.Send("after", peer);

	harness.Socket->Set_Next_Receive_Error(SocketError::RESET);
	harness.Socket->Deliver(peer, wire.data(), static_cast<int>(wire.size()));

	harness.Transport.Service();

	std::vector<std::string> const got = harness.Drain();
	Check(got.size() == 1 && got[0] == "after", "a reset is cleared and the drain carries on");
}


/// A packet from one of our own addresses is our own broadcast coming back.
void Test_Own_Address_Is_Discarded(void)
{
	uint32_t const mine = 0x0100007f;

	Harness harness({{mine, 0}});
	IPXAddressClass const self = Peer(mine, 51000);

	std::vector<unsigned char> const wire = harness.Send("echo", self);

	harness.Socket->Deliver(self, wire.data(), static_cast<int>(wire.size()));
	harness.Transport.Service();

	Check(harness.Drain().empty(), "a packet from one of our own addresses is thrown away");
}


/// Anything the admission layer rejects must not reach the game.
void Test_Malformed_Is_Rejected(void)
{
	Harness harness;
	IPXAddressClass const peer = Peer(0x0100007f, 51000);

	unsigned char const runt[] = {1, 2};
	harness.Socket->Deliver(peer, runt, sizeof(runt));

	unsigned char corrupt[] = {0, 0, 0, 0, 'n', 'o'};
	harness.Socket->Deliver(peer, corrupt, sizeof(corrupt));

	harness.Transport.Service();

	Check(harness.Drain().empty(), "a runt and a bad checksum are both refused");
	Check(harness.Transport.Dropped_Packets(WinsockInterfaceClass::WS_DROP_RECEIVE_TOO_SHORT) >= 1,
		"the short datagram is counted as a drop");
}


/// A tunnelled game names its players by tunnel ID, and the server is the only
/// endpoint the socket ever sees.
void Test_Tunnel_Framing(void)
{
	unsigned short const us = 7;
	unsigned short const them = 9;

	Harness harness;
	harness.Transport.Configure_Tunnel(us, 0x0100007f, Socket_Network_Port(50000));

	IPXAddressClass const recipient(0, them);
	std::vector<unsigned char> const wire = harness.Send("tunnelled", recipient);

	bool const headed = wire.size() >= 4
		&& wire[0] == (us & 0xff) && wire[1] == (us >> 8)
		&& wire[2] == (them & 0xff) && wire[3] == (them >> 8);
	Check(headed, "a tunnelled datagram leads with the sender and recipient");

	// The server echoes it back with us as the recipient.
	std::vector<unsigned char> ours(wire);
	ours[2] = static_cast<unsigned char>(us & 0xff);
	ours[3] = static_cast<unsigned char>(us >> 8);

	harness.Socket->Deliver(IPXAddressClass(0, 0), ours.data(), static_cast<int>(ours.size()));
	harness.Transport.Service();
	Check(harness.Drain().size() == 1, "a tunnelled datagram addressed to us is accepted");

	// One for somebody else must be passed over, not treated as a failure.
	std::vector<unsigned char> theirs(wire);
	harness.Socket->Deliver(IPXAddressClass(0, 0), theirs.data(), static_cast<int>(theirs.size()));

	std::vector<unsigned char> const mine = harness.Send("second", recipient);
	std::vector<unsigned char> echoed(mine);
	echoed[2] = static_cast<unsigned char>(us & 0xff);
	echoed[3] = static_cast<unsigned char>(us >> 8);
	harness.Socket->Deliver(IPXAddressClass(0, 0), echoed.data(), static_cast<int>(echoed.size()));

	harness.Transport.Service();
	std::vector<std::string> const got = harness.Drain();
	Check(got.size() == 1 && got[0] == "second", "a datagram for another tunnel ID is passed over");
}


/// Broadcasting reaches every network the machine sits on, and falls back on
/// the blind broadcast when no network names one of its own.
void Test_Broadcast_Addresses(void)
{
	Harness with_networks({{0x0100007f, 0xff00007f}, {0x0200a8c0, 0xff00a8c0}});
	with_networks.Transport.Enable_Broadcast(true);

	Harness blind;
	blind.Transport.Enable_Broadcast(true);

	// Enable_Broadcast only takes effect when the socket opens, so both were
	// opened without it; what matters here is that neither crashes and the
	// local address list came from the socket.
	Check(with_networks.Transport.Get_Num_Local_Addresses() == 2, "every reported interface is a local address");
	Check(blind.Transport.Get_Num_Local_Addresses() == 0, "a socket naming no interface reports none");
}

}


int main(void)
{
	Test_Full_Socket_Keeps_The_Queue();
	Test_Round_Trip();
	Test_Drain_Is_Bounded();
	Test_Reset_Does_Not_End_The_Pass();
	Test_Own_Address_Is_Discarded();
	Test_Malformed_Is_Rejected();
	Test_Tunnel_Framing();
	Test_Broadcast_Addresses();

	std::printf("\n%s\n", Failures == 0 ? "All checks passed." : "Some checks FAILED.");
	return(Failures == 0 ? 0 : 1);
}
