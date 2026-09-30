/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

// The BSD sockets implementation of SocketClass, for the platforms that have no
// Winsock. It mirrors netsocket_win32.cpp; where the two differ it is because
// the platform does, not because the transport asked for anything else.

#include "always.h"

#if !defined(_WIN32)

#include "netsocket.h"

#include "dbgprint.h"

#include <arpa/inet.h>
#include <errno.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

namespace {

SocketError Translate_Error(int error)
{
	switch (error) {
		case EWOULDBLOCK:
			return(SocketError::WOULD_BLOCK);
#if EAGAIN != EWOULDBLOCK
		case EAGAIN:
			return(SocketError::WOULD_BLOCK);
#endif
		// A datagram socket reports a refused peer on the receive that follows
		// the send, which is where Winsock reports a reset.
		case ECONNREFUSED:
		case ECONNRESET:
			return(SocketError::RESET);
		case EMSGSIZE:
			return(SocketError::MESSAGE_SIZE);
		default:
			return(SocketError::OTHER);
	}
}


class PosixSocketClass : public SocketClass
{
	public:
		~PosixSocketClass(void) override;

		bool Open(unsigned short port) override;
		void Close(void) override;
		bool Is_Open(void) const override { return(Socket >= 0); }

		bool Set_Broadcast(bool enable) override;
		bool Set_Buffer_Sizes(int receive, int send) override;
		void Clear_Error(void) override;

		TransferResult Send_To(void const * buffer, int length, IPXAddressClass const & to) override;
		TransferResult Receive_From(void * buffer, int length, IPXAddressClass & from) override;

		bool Local_Interfaces(std::vector<InterfaceType> & interfaces) override;

	private:
		int Socket = -1;
};


PosixSocketClass::~PosixSocketClass(void)
{
	Close();
}


bool PosixSocketClass::Open(unsigned short port)
{
	Close();

	/*
	**	Create our UDP socket
	*/
	Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (Socket < 0) {
		DebugString("Failed to create the UDP socket - error code %d\n", errno);
		return(false);
	}

	/*
	**	Bind our UDP socket to our UDP port number
	*/
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	DebugString("About to bind the UDP socket to port %d\n", port);

	if (bind(Socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
		DebugString("Failed to bind the UDP socket - error code %d\n", errno);
		Close();
		return(false);
	}

	// The transport polls, so the socket must never wait on a call.
	int nonblocking = 1;
	if (ioctl(Socket, FIONBIO, &nonblocking) < 0) {
		DebugString("Failed to make the socket non-blocking - error code %d\n", errno);
		Close();
		return(false);
	}

	/*
	**	Set options for the UDP socket
	*/
	linger ling = {};
	ling.l_onoff = 0;   // linger off
	ling.l_linger = 0;  // timeout in seconds (ie close now)
	setsockopt(Socket, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));

	return(true);
}


void PosixSocketClass::Close(void)
{
	if (Socket >= 0) {
		close(Socket);
		Socket = -1;
	}
}


bool PosixSocketClass::Set_Broadcast(bool enable)
{
	if (Socket < 0) return(false);

	int optval = enable ? 1 : 0;
	if (setsockopt(Socket, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) < 0) {
		DebugString("Failed to set UDP socket option SO_BROADCAST - error code %d.\n", errno);
		return(false);
	}
	return(true);
}


bool PosixSocketClass::Set_Buffer_Sizes(int receive, int send)
{
	if (Socket < 0) return(false);

	bool ok = true;

	/*
	**	Specify the size of the receive buffer.
	*/
	if (setsockopt(Socket, SOL_SOCKET, SO_RCVBUF, &receive, sizeof(receive)) < 0) {
		DebugString("Failed to set socket option SO_RCVBUF - error code %d.\n", errno);
		ok = false;
	}

	/*
	**	Specify the size of the send buffer.
	*/
	if (setsockopt(Socket, SOL_SOCKET, SO_SNDBUF, &send, sizeof(send)) < 0) {
		DebugString("Failed to set socket option SO_SNDBUF - error code %d.\n", errno);
		ok = false;
	}

	return(ok);
}


void PosixSocketClass::Clear_Error(void)
{
	if (Socket < 0) return;

	int error_code = 0;
	socklen_t length = sizeof(error_code);

	getsockopt(Socket, SOL_SOCKET, SO_ERROR, &error_code, &length);
}


TransferResult PosixSocketClass::Send_To(void const * buffer, int length, IPXAddressClass const & to)
{
	if (Socket < 0) return(TransferResult{SocketError::OTHER, 0});

	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = to.Get_IP();
	addr.sin_port = to.Get_Port();

	ssize_t const rc = sendto(Socket, buffer, static_cast<size_t>(length), 0,
		reinterpret_cast<sockaddr const *>(&addr), sizeof(addr));

	if (rc < 0) return(TransferResult{Translate_Error(errno), 0});

	return(TransferResult{SocketError::NONE, static_cast<int>(rc)});
}


TransferResult PosixSocketClass::Receive_From(void * buffer, int length, IPXAddressClass & from)
{
	if (Socket < 0) return(TransferResult{SocketError::OTHER, 0});

	sockaddr_in addr = {};
	socklen_t address_len = sizeof(addr);

	ssize_t const rc = recvfrom(Socket, buffer, static_cast<size_t>(length), 0,
		reinterpret_cast<sockaddr *>(&addr), &address_len);

	if (rc < 0) return(TransferResult{Translate_Error(errno), 0});

	from.Set_Address(addr.sin_addr.s_addr, addr.sin_port);
	return(TransferResult{SocketError::NONE, static_cast<int>(rc)});
}


/// <summary>
/// Reports every address the machine answers on. The interface list carries a
/// broadcast address of its own, so unlike the Windows side there is no netmask
/// arithmetic to do here.
/// </summary>
bool PosixSocketClass::Local_Interfaces(std::vector<InterfaceType> & interfaces)
{
	ifaddrs * addresses = nullptr;

	if (getifaddrs(&addresses) != 0) {
		DebugString("getifaddrs failed - error code %d\n", errno);
		return(false);
	}

	for (ifaddrs * entry = addresses; entry != nullptr; entry = entry->ifa_next) {

		if (entry->ifa_addr == nullptr) continue;
		if (entry->ifa_addr->sa_family != AF_INET) continue;

		InterfaceType found = {};
		found.Address = reinterpret_cast<sockaddr_in const *>(entry->ifa_addr)->sin_addr.s_addr;
		if (found.Address == 0) continue;

		if ((entry->ifa_flags & IFF_BROADCAST) != 0 && entry->ifa_broadaddr != nullptr) {
			found.Broadcast = reinterpret_cast<sockaddr_in const *>(entry->ifa_broadaddr)->sin_addr.s_addr;
		}

		interfaces.push_back(found);
	}

	freeifaddrs(addresses);

	return(!interfaces.empty());
}

}


std::unique_ptr<SocketClass> Socket_Create_Platform_Socket(void)
{
	return(std::make_unique<PosixSocketClass>());
}

#endif
