/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "netsocket.h"

#include <cstring>


bool NullSocketClass::Open(unsigned short port)
{
	Port = port;
	Opened = true;
	return(true);
}


void NullSocketClass::Close(void)
{
	Opened = false;
	Inbound.clear();
	NextInbound = 0;
}


bool NullSocketClass::Set_Buffer_Sizes(int, int)
{
	return(true);
}


void NullSocketClass::Deliver(IPXAddressClass const & from, void const * bytes, int length)
{
	Datagram datagram;
	datagram.Address = from;
	datagram.Bytes.assign(static_cast<unsigned char const *>(bytes), static_cast<unsigned char const *>(bytes) + length);
	Inbound.push_back(std::move(datagram));
}


/// <summary>
/// Records the datagram instead of sending it, unless the socket has been told
/// to refuse, in which case it answers WOULD_BLOCK and keeps nothing.
/// </summary>
TransferResult NullSocketClass::Send_To(void const * buffer, int length, IPXAddressClass const & to)
{
	if (!Opened) return(TransferResult{SocketError::OTHER, 0});
	if (WouldBlock) return(TransferResult{SocketError::WOULD_BLOCK, 0});

	Datagram datagram;
	datagram.Address = to;
	datagram.Bytes.assign(static_cast<unsigned char const *>(buffer), static_cast<unsigned char const *>(buffer) + length);
	Outbound.push_back(std::move(datagram));

	return(TransferResult{SocketError::NONE, length});
}


/// <summary>
/// Hands back the next queued datagram, or WOULD_BLOCK once they run out. A
/// datagram longer than the buffer is dropped and reported as MESSAGE_SIZE,
/// which is what a real socket does with an oversized one.
/// </summary>
TransferResult NullSocketClass::Receive_From(void * buffer, int length, IPXAddressClass & from)
{
	if (!Opened) return(TransferResult{SocketError::OTHER, 0});

	if (PendingError != SocketError::NONE) {
		SocketError const error = PendingError;
		PendingError = SocketError::NONE;
		return(TransferResult{error, 0});
	}

	if (NextInbound >= Inbound.size()) {
		Inbound.clear();
		NextInbound = 0;
		return(TransferResult{SocketError::WOULD_BLOCK, 0});
	}

	Datagram const & datagram = Inbound[NextInbound++];
	from = datagram.Address;

	int const size = static_cast<int>(datagram.Bytes.size());
	if (size > length) return(TransferResult{SocketError::MESSAGE_SIZE, 0});

	std::memcpy(buffer, datagram.Bytes.data(), datagram.Bytes.size());
	return(TransferResult{SocketError::NONE, size});
}


bool NullSocketClass::Local_Interfaces(std::vector<InterfaceType> & interfaces)
{
	if (Interfaces.empty()) return(false);

	interfaces = Interfaces;
	return(true);
}
