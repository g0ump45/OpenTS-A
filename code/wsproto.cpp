/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /Sun/WSProto.cpp                                            $*
 *                                                                                             *
 *                      $Author:: Joe_b                                                       $*
 *                                                                                             *
 *                     $Modtime:: 8/20/97 10:54a                                              $*
 *                                                                                             *
 *                    $Revision:: 5                                                           $*
 *                                                                                             *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 *                                                                                             *
 *  WSProto.CPP WinsockInterfaceClass to provide an interface to Winsock protocols             *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 *                                                                                             *
 * Functions:                                                                                  *
 *                                                                                             *
 * WIC::WinsockInterfaceClass -- constructor for the WinsockInterfaceClass                     *
 * WIC::~WinsockInterfaceClass -- destructor for the WinsockInterfaceClass                     *
 * WIC::Close -- Releases any currently in use Winsock resources.                              *
 * WIC::Close_Socket -- Close the communication socket if its open                             *
 * WIC::Start_Listening -- Enable callbacks for read/write events on our socket                *
 * WIC::Stop_Listening -- Disable the winsock event callback                                   *
 * WIC::Discard_In_Buffers -- Discard any packets in our incoming packet holding buffers       *
 * WIC::Discard_In_Buffers -- Discard any packets in our outgoing packet holding buffers       *
 * WIC::Init -- Initialised Winsock and this class for use.                                    *
 * WIC::Read -- read any pending input from the communications socket                          *
 * WIC::WriteTo -- Send data via the Winsock socket                                            *
 * WIC::Broadcast -- Send data via the Winsock socket                                          *
 * WIC::Clear_Socket_Error -- Clear any outstanding erros on the socket                        *
 * WIC::Set_Socket_Options -- Sets default socket options for Winsock buffer sizes             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "wsproto.h"

#include "dbgprint.h"
#include "netadmit.h"
#include "vector.h"

#include <cassert>
#include <cstdio>
#include <cstring>

namespace {

/// <summary>Names a stable transport rejection reason.</summary>
char const * Packet_Drop_Name(WinsockInterfaceClass::PacketDropReasonType reason)
{
	switch (reason) {
		case WinsockInterfaceClass::WS_DROP_RECEIVE_TOO_SHORT: return("udp-too-short");
		case WinsockInterfaceClass::WS_DROP_RECEIVE_TOO_LARGE: return("udp-too-large");
		case WinsockInterfaceClass::WS_DROP_BAD_CRC: return("udp-bad-crc");
		case WinsockInterfaceClass::WS_DROP_READ_BUFFER_TOO_SMALL: return("transport-output-too-small");
		case WinsockInterfaceClass::WS_DROP_SEND_LENGTH: return("transport-send-length");
		case WinsockInterfaceClass::WS_DROP_SEND_ADDRESS: return("transport-send-address");
		default: return("transport-unknown");
	}
}

}

/***********************************************************************************************
 * WIC::WinsockInterfaceClass -- constructor for the WinsockInterfaceClass                     *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    3/20/96 2:51PM ST : Created                                                              *
 *=============================================================================================*/
WinsockInterfaceClass::WinsockInterfaceClass(void) :
Socket(Socket_Create_Platform_Socket()),
Listening(false)
{
	WinsockInitialised = false;

	for (int i = 0; i < WS_MAX_STATIC_BUFFERS; i++) {
		StaticInBuffers[i].InUse = false;
		StaticInBuffers[i].IsAllocated = false;

		StaticOutBuffers[i].InUse = false;
		StaticOutBuffers[i].IsAllocated = false;
	}

	InBuffersUsed = 0;
	OutBuffersUsed = 0;

	InBufferArrayPos = 0;
	OutBufferArrayPos = 0;
	memset(PacketDrops, 0, sizeof(PacketDrops));

	DebugString("WinsockInterface constructed\n");

}


/***********************************************************************************************
 * WIC::~WinsockInterfaceClass -- destructor for the WinsockInterfaceClass                     *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    3/20/96 2:52PM ST : Created                                                              *
 *=============================================================================================*/
WinsockInterfaceClass::~WinsockInterfaceClass(void)
{
	Close();
}


/***********************************************************************************************
 * WIC::Close -- Releases any currently in use Winsock resources.                              *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    3/20/96 2:52PM ST : Created                                                              *
 *=============================================================================================*/
void WinsockInterfaceClass::Close(void)
{
	/*
	**	If we never initialised the class in the first place then just return
	*/
	if (!WinsockInitialised) return;

	Stop_Listening();

	/*
	**	Close any open sockets
	*/
	Close_Socket();

	WinsockInitialised = false;
}


/***********************************************************************************************
 * WIC::Close_Socket -- Close the communication socket if its open                             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    8/5/97 11:53AM ST : Created                                                              *
 *=============================================================================================*/
void WinsockInterfaceClass::Close_Socket (void)
{
	if (Socket != nullptr) {
		Socket->Close();
	}
}


/// <summary>
/// Replaces the socket this transport sends through, closing whatever it held.
/// </summary>
void WinsockInterfaceClass::Set_Socket(std::unique_ptr<SocketClass> socket)
{
	Close_Socket();
	Socket = std::move(socket);
}


/// <summary>
/// Lets Service poll the socket. Nothing is received until this succeeds; the
/// socket is already non-blocking, since Open leaves it that way.
/// </summary>
/// <returns>bool; Is the socket ready to be polled?</returns>
bool WinsockInterfaceClass::Start_Listening (void)
{
	if (Socket == nullptr || !Socket->Is_Open()) {
		DebugString("Cannot listen on a socket that is not open.\n");
		assert (false);
		return(false);
	}
	Listening = true;
	return(true);
}


/// <summary>
/// Stops Service polling the socket, leaving the socket itself open. WriteTo and
/// Broadcast still send what they are given.
/// </summary>
void WinsockInterfaceClass::Stop_Listening (void)
{
	Listening = false;
}


/// <summary>
/// Moves pending packets between the socket and the holding buffers, so
/// that Read finds what has arrived and what WriteTo queued has gone out.
/// </summary>
void WinsockInterfaceClass::Service(void)
{
	if (!Listening) return;

	Receive_Pending();
	Send_Pending();
}


/***********************************************************************************************
 * WIC::Discard_In_Buffers -- Discard any packets in our incoming packet holding buffers       *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    8/5/97 11:55AM ST : Created                                                              *
 *=============================================================================================*/
void WinsockInterfaceClass::Discard_In_Buffers(void)
{
	WinsockBufferType *packet;

	while (InBuffers.Count()) {
		packet = InBuffers[0];
		if (packet->IsAllocated) {
			delete packet;
		} else {
			packet->InUse = false;
			InBuffersUsed--;
		}
		InBuffers.Delete_Index(0);
	}
	InBuffersUsed = 0;
	InBufferArrayPos = 0;
}


/***********************************************************************************************
 * WIC::Discard_In_Buffers -- Discard any packets in our outgoing packet holding buffers       *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    8/5/97 11:55AM ST : Created                                                              *
 *=============================================================================================*/
void WinsockInterfaceClass::Discard_Out_Buffers(void)
{
	WinsockBufferType *packet;

	while (OutBuffers.Count()) {
		packet = OutBuffers[0];
		if (packet->IsAllocated) {
			delete packet;
		} else {
			packet->InUse = false;
			OutBuffersUsed--;
		}
		OutBuffers.Delete_Index(0);
	}
	OutBuffersUsed = 0;
	OutBufferArrayPos = 0;
}


/***********************************************************************************************
 * WIC::Init -- Initialised Winsock and this class for use.                                    *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   true if Winsock is available and was initialised                                  *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    3/20/96 2:54PM ST : Created                                                              *
 *=============================================================================================*/
bool WinsockInterfaceClass::Init(void)
{
	DebugString("WinsockInterface init.\n");

	/*
	**	Just return true if we are already set up
	*/
	if (WinsockInitialised) {
		DebugString("WinsockInterface already initialised\n");
		return(true);
	}

	// The platform's socket library is started by the socket itself, on the
	// first Open, so there is nothing left to bring up here.
	if (Socket == nullptr) {
		DebugString("No socket is available on this platform.\n");
		return(false);
	}

	Discard_In_Buffers();
	Discard_Out_Buffers();

	WinsockInitialised = true;

	return(true);
}


/***********************************************************************************************
 * WIC::Build_Packet_CRC -- Create a CRC value for a packet.                                   *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    ptr to packet                                                                     *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   10/5/99 1:26PM ST : Created                                                               *
 *=============================================================================================*/
void WinsockInterfaceClass::Build_Packet_CRC(WinsockBufferType * packet)
{
	assert (packet->InUse);
	assert (packet->BufferLen);

	packet->CRC = Calculate_Packet_CRC(packet->Buffer, packet->BufferLen);
}


/// <summary>Calculates the transport checksum.</summary>
unsigned int WinsockInterfaceClass::Calculate_Packet_CRC(void const * buffer, int buffer_len) const
{
	if (buffer == NULL || buffer_len <= 0) {
		return(0);
	}
	return(NetAdmission::Calculate_Datagram_CRC(std::span<std::byte const>(static_cast<std::byte const *>(buffer), static_cast<std::size_t>(buffer_len))));
}


/// <summary>Returns the number of transport packets rejected for one stable reason.</summary>
unsigned int WinsockInterfaceClass::Dropped_Packets(PacketDropReasonType reason) const
{
	if (reason < 0 || reason >= WS_DROP_COUNT) {
		return(0);
	}

	return(PacketDrops[reason]);
}


/// <summary>Records a transport rejection and rate-limits its diagnostic.</summary>
void WinsockInterfaceClass::Record_Packet_Drop(PacketDropReasonType reason)
{
	if (reason < 0 || reason >= WS_DROP_COUNT) {
		return;
	}

	unsigned int count = ++PacketDrops[reason];
	if (count == 1 || (count & (count - 1)) == 0) {
		DebugString("Network packet drop [%s]: %u\n", Packet_Drop_Name(reason), count);
	}
}


/***********************************************************************************************
 * WIC::Get_New_Out_Buffer -- Get a holding buffer for an outgoing packet                      *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   ptr to out buffer                                                                 *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/00 12:39PM ST : Created                                                               *
 *=============================================================================================*/
void *WinsockInterfaceClass::Get_New_Out_Buffer(void)
{
	WinsockBufferType *buffer = NULL;
	int pos;

	assert (OutBuffersUsed <= WS_MAX_STATIC_BUFFERS);

	/*
	**	If there are no more free buffers in the heap then allocate one.
	*/
	if (OutBuffersUsed == WS_MAX_STATIC_BUFFERS) {
		buffer = new WinsockBufferType;
		buffer->IsAllocated = true;
		buffer->InUse = true;
	}else{
		/*
		**	Find the next free buffer in the heap.
		*/
		for (int i=0 ; i<WS_MAX_STATIC_BUFFERS ; i++) {

			pos = OutBufferArrayPos++;
			if (OutBufferArrayPos > WS_MAX_STATIC_BUFFERS-1) {
				OutBufferArrayPos = 0;
			}

			if (StaticOutBuffers[pos].InUse == false) {
				buffer = &StaticOutBuffers[pos];
				buffer->InUse = true;
				OutBuffersUsed++;
				break;
			}
		}
	}

	assert (buffer != NULL);
	return(buffer);
}


/***********************************************************************************************
 * WIC::Get_New_In_Buffer -- Get a holding buffer for an incoming packet                       *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   ptr to in buffer                                                                  *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   3/2/00 12:39PM ST : Created                                                               *
 *=============================================================================================*/
void *WinsockInterfaceClass::Get_New_In_Buffer(void)
{
	WinsockBufferType *buffer = NULL;
	int pos;

	assert (InBuffersUsed <= WS_MAX_STATIC_BUFFERS);

	/*
	**	If there are no more free buffers in the heap then allocate one.
	*/
	if (InBuffersUsed == WS_MAX_STATIC_BUFFERS) {
		buffer = new WinsockBufferType;
		buffer->IsAllocated = true;
		buffer->InUse = true;
	}else{
		/*
		**	Find the next free buffer in the heap.
		*/
		for (int i=0 ; i<WS_MAX_STATIC_BUFFERS ; i++) {

			pos = InBufferArrayPos++;
			if (InBufferArrayPos > WS_MAX_STATIC_BUFFERS-1) {
				InBufferArrayPos = 0;
			}

			if (StaticInBuffers[pos].InUse == false) {
				buffer = &StaticInBuffers[pos];
				buffer->InUse = true;
				InBuffersUsed++;
				break;
			}
		}
	}

	assert (buffer != NULL);
	return(buffer);
}


/***********************************************************************************************
 * WIC::Read -- read any pending input from the communications socket                          *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    ptr to buffer to receive input                                                    *
 *           length of buffer                                                                  *
 *           ptr to address to fill with address that packet was sent from                     *
 *           length of address buffer                                                          *
 *                                                                                             *
 * OUTPUT:   number of bytes transfered to buffer                                              *
 *                                                                                             *
 * WARNINGS: The format of the address is dependent on the protocol in use.                    *
 *                                                                                             *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    3/20/96 2:58PM ST : Created                                                              *
 *=============================================================================================*/
int WinsockInterfaceClass::Read(void *buffer, int &buffer_len, void *address, int &address_len)
{
	/*
	**	If there are no available packets then return 0
	*/
	if ( InBuffers.Count() == 0 ) return(0);

	/*
	**	Get the oldest packet for reading
	*/
	int packetnum = 0;
	WinsockBufferType *packet = InBuffers[packetnum];
	assert(packet != NULL);
	if (packet == NULL) {
		return(0);
	}

	assert(packet->InUse);

	int buffer_capacity = buffer_len;
	int address_capacity = address_len;
	if (buffer == NULL || address == NULL || packet->BufferLen <= 0 || packet->BufferLen > WS_INTERNET_BUFFER_LEN ||
		buffer_capacity < packet->BufferLen || address_capacity < (int)sizeof(packet->Address)) {
		InBuffers.Delete_Index(packetnum);
		if (packet->IsAllocated) {
			delete packet;
		} else {
			packet->InUse = false;
			InBuffersUsed--;
		}
		buffer_len = 0;
		address_len = 0;
		Record_Packet_Drop(WS_DROP_READ_BUFFER_TOO_SMALL);
		return(0);
	}

	/*
	**	Copy the data and the address it came from into the supplied buffers.
	*/
	memcpy(buffer, packet->Buffer, packet->BufferLen);
	memcpy(address, packet->Address, sizeof (packet->Address));

	/*
	**	Return the length of the packet in buffer_len.
	*/
	buffer_len = packet->BufferLen;
	address_len = sizeof(packet->Address);

	/*
	**	Delete the temporary storage for the packet now that it is being passed to the game.
	*/
	InBuffers.Delete_Index(packetnum);
	if (packet->IsAllocated) {
		delete packet;
	}else{
		packet->InUse = false;
		InBuffersUsed--;
	}

	return(buffer_len);
}


/***********************************************************************************************
 * WIC::WriteTo -- Send data via the Winsock socket                                            *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    ptr to buffer containing data to send                                             *
 *           length of data to send                                                            *
 *           address to send data to.                                                          *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: The format of the address is dependent on the protocol in use.                    *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    3/20/96 3:00PM ST : Created                                                              *
 *=============================================================================================*/
void WinsockInterfaceClass::WriteTo(void *buffer, int buffer_len, void *address, int address_len)
{
	if (buffer == NULL || buffer_len <= 0 || buffer_len > WS_INTERNET_BUFFER_LEN) {
		Record_Packet_Drop(WS_DROP_SEND_LENGTH);
		return;
	}
	if (address == NULL || address_len <= 0 || address_len > (int)sizeof(WinsockBufferType::Address)) {
		Record_Packet_Drop(WS_DROP_SEND_ADDRESS);
		return;
	}

	/*
	**	Create a temporary holding area for the packet.
	*/
	WinsockBufferType *packet = (WinsockBufferType*) Get_New_Out_Buffer();
	assert (packet != NULL);
	if (packet == NULL) {
		return;
	}

	/*
	**	Copy the packet into the holding buffer.
	*/
	memcpy ( packet->Buffer, buffer, buffer_len );
	packet->BufferLen = buffer_len;
	packet->IsBroadcast = false;
//	memcpy ( packet->Address, address, sizeof (packet->Address) );
	memcpy ( packet->Address, address, address_len );

	Build_Packet_CRC(packet);

	/*
	**	Add it to our out list.
	*/
	OutBuffers.Add ( packet );

	Send_Pending();
}


/***********************************************************************************************
 * WIC::Broadcast -- Send data via the Winsock socket                                          *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    ptr to buffer containing data to send                                             *
 *           length of data to send                                                            *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    3/20/96 3:00PM ST : Created                                                              *
 *=============================================================================================*/
void WinsockInterfaceClass::Broadcast (void *buffer, int buffer_len)
{
	if (buffer == NULL || buffer_len <= 0 || buffer_len > WS_INTERNET_BUFFER_LEN) {
		Record_Packet_Drop(WS_DROP_SEND_LENGTH);
		return;
	}

	/*
	**	Create a temporary holding area for the packet.
	*/
	WinsockBufferType *packet = (WinsockBufferType*) Get_New_Out_Buffer();
	assert(packet != NULL);
	if (packet == NULL) {
		return;
	}

	/*
	**	Copy the packet into the holding buffer.
	*/
	memcpy ( packet->Buffer, buffer, buffer_len );
	packet->BufferLen = buffer_len;
	Build_Packet_CRC(packet);

	/*
	**	Indicate that this packet should be broadcast.
	*/
	packet->IsBroadcast = true;

	/*
	**	Add it to our out list.
	*/
	OutBuffers.Add ( packet );

	Send_Pending();
}


/***********************************************************************************************
 * WIC::Clear_Error -- Clear any outstanding erros on the socket                               *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    8/5/97 12:05PM ST : Created                                                              *
 *=============================================================================================*/
void WinsockInterfaceClass::Clear_Error(void)
{
	if (Socket != nullptr) {
		Socket->Clear_Error();
	}
}


/***********************************************************************************************
 * WIC::Set_Socket_Options -- Sets default socket options for Winsock buffer sizes             *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    8/5/97 12:07PM ST : Created                                                              *
 *=============================================================================================*/
bool WinsockInterfaceClass::Set_Socket_Options ( void )
{
	if (Socket == nullptr) return(false);

	return(Socket->Set_Buffer_Sizes(SOCKET_BUFFER_SIZE, SOCKET_BUFFER_SIZE));
}


