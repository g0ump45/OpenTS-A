/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

// The Winsock implementation of SocketClass. This is the only file in the
// transport that includes a socket header, so it is also the only one that has
// to keep winsock2.h ahead of anything that would pull the older winsock.h in.

#include "always.h"

#if defined(_WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include "netsocket.h"

#include "dbgprint.h"

namespace {

// WSAStartup and WSACleanup are per-process and reference counted by Winsock
// itself, so the sockets only have to agree on how many of them are open.
int OpenSockets = 0;


bool Start_Winsock(void)
{
	if (OpenSockets > 0) {
		OpenSockets++;
		return(true);
	}

	WSADATA info = {};
	int const rc = WSAStartup(MAKEWORD(2, 2), &info);
	if (rc != 0) {
		DebugString("Winsock failed to initialise - error code %d.\n", rc);
		return(false);
	}

	DebugString("Winsock %d.%d initialised OK\n", LOBYTE(info.wVersion), HIBYTE(info.wVersion));
	OpenSockets++;
	return(true);
}


void Stop_Winsock(void)
{
	if (OpenSockets == 0) return;

	OpenSockets--;
	if (OpenSockets == 0) {
		WSACleanup();
	}
}


SocketError Translate_Error(int error)
{
	switch (error) {
		case WSAEWOULDBLOCK: return(SocketError::WOULD_BLOCK);
		case WSAECONNRESET: return(SocketError::RESET);
		case WSAEMSGSIZE: return(SocketError::MESSAGE_SIZE);
		default: return(SocketError::OTHER);
	}
}


class WinsockSocketClass : public SocketClass
{
	public:
		~WinsockSocketClass(void) override;

		bool Open(unsigned short port) override;
		void Close(void) override;
		bool Is_Open(void) const override { return(Socket != INVALID_SOCKET); }

		bool Set_Broadcast(bool enable) override;
		bool Set_Buffer_Sizes(int receive, int send) override;
		void Clear_Error(void) override;

		TransferResult Send_To(void const * buffer, int length, IPXAddressClass const & to) override;
		TransferResult Receive_From(void * buffer, int length, IPXAddressClass & from) override;

		bool Local_Interfaces(std::vector<InterfaceType> & interfaces) override;

	private:
		SOCKET Socket = INVALID_SOCKET;
		bool Started = false;
};


WinsockSocketClass::~WinsockSocketClass(void)
{
	Close();
	if (Started) {
		Stop_Winsock();
		Started = false;
	}
}


bool WinsockSocketClass::Open(unsigned short port)
{
	if (!Started) {
		if (!Start_Winsock()) return(false);
		Started = true;
	}

	Close();

	/*
	**	Create our UDP socket
	*/
	Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (Socket == INVALID_SOCKET) {
		DebugString("Failed to create the UDP socket - error code %d\n", WSAGetLastError());
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

	if (bind(Socket, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) == SOCKET_ERROR) {
		DebugString("Failed to bind the UDP socket - error code %d\n", WSAGetLastError());
		Close();
		return(false);
	}

	// The transport polls, so the socket must never wait on a call.
	u_long nonblocking = 1;
	if (ioctlsocket(Socket, FIONBIO, &nonblocking) == SOCKET_ERROR) {
		DebugString("Failed to make the socket non-blocking - error code %d\n", WSAGetLastError());
		Close();
		return(false);
	}

	/*
	**	Set options for the UDP socket
	*/
	linger ling = {};
	ling.l_onoff = 0;   // linger off
	ling.l_linger = 0;  // timeout in seconds (ie close now)
	setsockopt(Socket, SOL_SOCKET, SO_LINGER, reinterpret_cast<char *>(&ling), sizeof(ling));

	return(true);
}


void WinsockSocketClass::Close(void)
{
	if (Socket != INVALID_SOCKET) {
		closesocket(Socket);
		Socket = INVALID_SOCKET;
	}
}


bool WinsockSocketClass::Set_Broadcast(bool enable)
{
	if (Socket == INVALID_SOCKET) return(false);

	int optval = enable ? 1 : 0;
	if (setsockopt(Socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char *>(&optval), sizeof(optval)) == SOCKET_ERROR) {
		DebugString("Failed to set UDP socket option SO_BROADCAST - error code %d.\n", WSAGetLastError());
		return(false);
	}
	return(true);
}


bool WinsockSocketClass::Set_Buffer_Sizes(int receive, int send)
{
	if (Socket == INVALID_SOCKET) return(false);

	bool ok = true;

	/*
	**	Specify the size of the receive buffer.
	*/
	if (setsockopt(Socket, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char *>(&receive), sizeof(receive)) == SOCKET_ERROR) {
		DebugString("Failed to set socket option SO_RCVBUF - error code %d.\n", WSAGetLastError());
		ok = false;
	}

	/*
	**	Specify the size of the send buffer.
	*/
	if (setsockopt(Socket, SOL_SOCKET, SO_SNDBUF, reinterpret_cast<char *>(&send), sizeof(send)) == SOCKET_ERROR) {
		DebugString("Failed to set socket option SO_SNDBUF - error code %d.\n", WSAGetLastError());
		ok = false;
	}

	return(ok);
}


void WinsockSocketClass::Clear_Error(void)
{
	if (Socket == INVALID_SOCKET) return;

	unsigned int error_code = 0;
	int length = sizeof(error_code);

	getsockopt(Socket, SOL_SOCKET, SO_ERROR, reinterpret_cast<char *>(&error_code), &length);
	error_code = 0;
	setsockopt(Socket, SOL_SOCKET, SO_ERROR, reinterpret_cast<char *>(&error_code), length);
}


TransferResult WinsockSocketClass::Send_To(void const * buffer, int length, IPXAddressClass const & to)
{
	if (Socket == INVALID_SOCKET) return(TransferResult{SocketError::OTHER, 0});

	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = to.Get_IP();
	addr.sin_port = to.Get_Port();

	int const rc = sendto(Socket, static_cast<char const *>(buffer), length, 0,
		reinterpret_cast<sockaddr const *>(&addr), sizeof(addr));

	if (rc == SOCKET_ERROR) return(TransferResult{Translate_Error(WSAGetLastError()), 0});

	return(TransferResult{SocketError::NONE, rc});
}


TransferResult WinsockSocketClass::Receive_From(void * buffer, int length, IPXAddressClass & from)
{
	if (Socket == INVALID_SOCKET) return(TransferResult{SocketError::OTHER, 0});

	sockaddr_in addr = {};
	int address_len = sizeof(addr);

	int const rc = recvfrom(Socket, static_cast<char *>(buffer), length, 0,
		reinterpret_cast<sockaddr *>(&addr), &address_len);

	if (rc == SOCKET_ERROR) return(TransferResult{Translate_Error(WSAGetLastError()), 0});

	from.Set_Address(addr.sin_addr.s_addr, addr.sin_port);
	return(TransferResult{SocketError::NONE, rc});
}


/// <summary>
/// Reports every address the machine answers on, with the directed broadcast
/// derived from each netmask. Falls back on the host lookup, which reports no
/// netmask, so those entries carry a zero broadcast.
/// </summary>
bool WinsockSocketClass::Local_Interfaces(std::vector<InterfaceType> & interfaces)
{
	ULONG size = 0;

	if (GetAdaptersInfo(nullptr, &size) == ERROR_BUFFER_OVERFLOW) {

		IP_ADAPTER_INFO * adapters = reinterpret_cast<IP_ADAPTER_INFO *>(new char[size]);
		bool enumerated = false;

		if (GetAdaptersInfo(adapters, &size) == NO_ERROR) {

			for (IP_ADAPTER_INFO * adapter = adapters; adapter != nullptr; adapter = adapter->Next) {
				for (IP_ADDR_STRING * entry = &adapter->IpAddressList; entry != nullptr; entry = entry->Next) {

					uint32_t address = 0;
					if (inet_pton(AF_INET, entry->IpAddress.String, &address) != 1) continue;
					if (address == 0) continue;

					DebugString("Found local address: %s\n", entry->IpAddress.String);

					InterfaceType found = {address, 0};

					uint32_t mask = 0;
					if (inet_pton(AF_INET, entry->IpMask.String, &mask) == 1) {
						// Every host bit set reaches the whole of that network.
						found.Broadcast = address | ~mask;
					}

					interfaces.push_back(found);
					enumerated = true;
				}
			}
		}

		delete[] reinterpret_cast<char *>(adapters);

		if (enumerated) return(true);
	}

	DebugString("GetAdaptersInfo failed - falling back on the host lookup\n");

	char hostname[128];
	if (gethostname(hostname, sizeof(hostname)) != 0) return(false);

	addrinfo hints = {};
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	addrinfo * found = nullptr;
	if (getaddrinfo(hostname, nullptr, &hints, &found) != 0) {
		DebugString("getaddrinfo failed! Error code %d\n", WSAGetLastError());
		return(false);
	}

	for (addrinfo * entry = found; entry != nullptr; entry = entry->ai_next) {
		if (entry->ai_family != AF_INET) continue;

		sockaddr_in const * addr = reinterpret_cast<sockaddr_in const *>(entry->ai_addr);
		interfaces.push_back({addr->sin_addr.s_addr, 0});
	}

	freeaddrinfo(found);

	return(!interfaces.empty());
}

}


std::unique_ptr<SocketClass> Socket_Create_Platform_Socket(void)
{
	return(std::make_unique<WinsockSocketClass>());
}

#endif
