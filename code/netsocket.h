/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

// The datagram socket the transport sends and receives through, behind an
// interface small enough that a platform other than Winsock can stand in
// without the transport knowing. Addresses cross as IPXAddressClass, and a
// failure is reported as a SocketError rather than through a thread-global,
// so no platform header reaches the transport. Everything here runs on the
// game thread.

#pragma once

#include "ipxaddr.h"

#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>


// What went wrong with a transfer. WOULD_BLOCK is the ordinary "nothing more
// to do" answer from a non-blocking socket, not a failure.
enum class SocketError
{
	NONE,
	WOULD_BLOCK,
	RESET,
	MESSAGE_SIZE,
	OTHER
};


struct TransferResult
{
	SocketError Error;
	int Length;             // Bytes moved. Meaningful only when Error is NONE.
};


// One address the machine answers on, and the broadcast that reaches its
// network. Both in network order; Broadcast is zero when the platform cannot
// work one out.
struct InterfaceType
{
	uint32_t Address;
	uint32_t Broadcast;
};


// Ports are configured in host order but addressed in network order. Building
// the byte pair by hand is what lets this live in a header no socket library
// reaches, and it is correct whichever way round the host stores an integer.
inline uint16_t Socket_Network_Port(uint16_t port)
{
	unsigned char const bytes[2] = {
		static_cast<unsigned char>(port >> 8),
		static_cast<unsigned char>(port & 0xff)
	};

	uint16_t network = 0;
	std::memcpy(&network, bytes, sizeof(network));
	return(network);
}


class SocketClass
{
	public:
		virtual ~SocketClass(void) = default;

		// Binds a non-blocking datagram socket to the port, starting the
		// platform's socket library on first use. The transport only ever
		// polls, so there is no blocking mode to ask for.
		virtual bool Open(unsigned short port) = 0;
		virtual void Close(void) = 0;
		virtual bool Is_Open(void) const = 0;

		virtual bool Set_Broadcast(bool enable) = 0;
		virtual bool Set_Buffer_Sizes(int receive, int send) = 0;

		// Discards a pending error the socket is holding, so that the next
		// transfer is not failed by the last one.
		virtual void Clear_Error(void) = 0;

		virtual TransferResult Send_To(void const * buffer, int length, IPXAddressClass const & to) = 0;
		virtual TransferResult Receive_From(void * buffer, int length, IPXAddressClass & from) = 0;

		// Answers the addresses this machine holds. False leaves the list
		// untouched and the caller to fall back on a blind broadcast.
		virtual bool Local_Interfaces(std::vector<InterfaceType> & interfaces) = 0;
};


// A socket that reaches no network. Tests drive the transport through it by
// queueing what should arrive and reading back what was sent.
class NullSocketClass : public SocketClass
{
	public:
		struct Datagram
		{
			IPXAddressClass Address;
			std::vector<unsigned char> Bytes;
		};

		bool Open(unsigned short port) override;
		void Close(void) override;
		bool Is_Open(void) const override { return(Opened); }

		bool Set_Broadcast(bool enable) override { Broadcast = enable; return(true); }
		bool Set_Buffer_Sizes(int receive, int send) override;
		void Clear_Error(void) override { PendingError = SocketError::NONE; }

		TransferResult Send_To(void const * buffer, int length, IPXAddressClass const & to) override;
		TransferResult Receive_From(void * buffer, int length, IPXAddressClass & from) override;

		bool Local_Interfaces(std::vector<InterfaceType> & interfaces) override;

		// Queues a datagram for the next Receive_From, as if it had arrived.
		void Deliver(IPXAddressClass const & from, void const * bytes, int length);

		// What Send_To was given, oldest first.
		std::vector<Datagram> const & Sent(void) const { return(Outbound); }
		void Clear_Sent(void) { Outbound.clear(); }

		// Refuses every send until it is cleared, standing in for a socket
		// whose send buffer is full.
		void Set_Would_Block(bool block) { WouldBlock = block; }

		// Fails the next receive with this error, once.
		void Set_Next_Receive_Error(SocketError error) { PendingError = error; }

		void Set_Interfaces(std::vector<InterfaceType> interfaces) { Interfaces = std::move(interfaces); }

		unsigned short Bound_Port(void) const { return(Port); }

	private:
		std::vector<Datagram> Inbound;
		std::vector<Datagram> Outbound;
		std::vector<InterfaceType> Interfaces;
		std::size_t NextInbound = 0;
		SocketError PendingError = SocketError::NONE;
		unsigned short Port = 0;
		bool Opened = false;
		bool Broadcast = false;
		bool WouldBlock = false;
};


// Creates the socket this platform provides. Returns null when the platform
// has none, which leaves the transport unable to open a session.
std::unique_ptr<SocketClass> Socket_Create_Platform_Socket(void);
