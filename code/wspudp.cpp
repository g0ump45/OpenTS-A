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
 *                     $Archive:: /Sun/WSPUDP.cpp                                             $*
 *                                                                                             *
 *                      $Author:: Joe_b                                                       $*
 *                                                                                             *
 *                     $Modtime:: 8/05/97 6:45p                                               $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 *                                                                                             *
 *  WSProto.CPP WinsockInterfaceClass to provide an interface to Winsock protocols             *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 *                                                                                             *
 * Functions:                                                                                  *
 * UDPInterfaceClass::UDPInterfaceClass -- Class constructor.                                  *
 * UDPInterfaceClass::Set_Broadcast_Address -- Sets the address to send broadcast packets to   *
 * UDPInterfaceClass::Open_Socket -- Opens a socket for communications via the UDP protocol    *
 * TMC::Message_Handler -- Message handler function for Winsock related messages               *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "wspudp.h"

#include "dbgprint.h"
#include "netadmit.h"
#include "vector.h"

#include <cstdio>
#include <cstring>


extern int WestwoodOnline_PortNumber;

// A tunnelled datagram leads with the sender's and the recipient's tunnel IDs, which is
// all the tunnel server reads in order to forward it.
#define TUNNEL_HEADER_SIZE 4

/***********************************************************************************************
 * UDPInterfaceClass::UDPInterfaceClass -- Class constructor.                                  *
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
 *    8/5/97 12:11PM ST : Created                                                              *
 *=============================================================================================*/
UDPInterfaceClass::UDPInterfaceClass (void) :
	BASECLASS(),
	LocalPort(0),
	DestinationPort(0),
	LocalPortSet(false),
	DestinationPortSet(false),
	UseBroadcast(false),
	TunnelID(0),
	TunnelIP(0),
	TunnelPort(0)
{}


/// <summary>
/// Sets the port to listen on.
/// </summary>
/// <param name="port">Port in host order. Zero binds a port of Winsock's choosing.</param>
void UDPInterfaceClass::Set_Local_Port(unsigned short port)
{
	LocalPort = port;
	LocalPortSet = true;
}


/// <summary>
/// Sets the port that outgoing packets are addressed to.
/// </summary>
/// <param name="port">Port in host order.</param>
void UDPInterfaceClass::Set_Destination_Port(unsigned short port)
{
	DestinationPort = port;
	DestinationPortSet = true;
}


/// <summary>
/// Allows this socket to broadcast, so that a game can be found without knowing who is
/// out there. The broadcast addresses themselves are worked out when the socket opens.
/// </summary>
void UDPInterfaceClass::Enable_Broadcast(bool enable)
{
	UseBroadcast = enable;
}


/// <summary>
/// Sends everything by way of a CnCNet tunnel server, for players who have no route to
/// each other. Each player is known only by a tunnel ID from here on.
/// </summary>
/// <param name="local_id">The ID the tunnel server knows us by.</param>
/// <param name="tunnel_ip">Address of the tunnel server.</param>
/// <param name="tunnel_port">Port of the tunnel server. Zero turns tunnelling off.</param>
void UDPInterfaceClass::Configure_Tunnel(unsigned short local_id, unsigned long tunnel_ip, unsigned short tunnel_port)
{
	TunnelID = local_id;
	TunnelIP = tunnel_ip;
	TunnelPort = tunnel_port;
}


/// <summary>
/// Hands a datagram to the socket, routing it through the tunnel server when one is
/// in use.
/// </summary>
/// <param name="to">Where the packet is bound. In tunnel mode the port carries the
/// recipient's tunnel ID rather than a real port.</param>
/// <returns>The socket's answer, counting only the payload.</returns>
TransferResult UDPInterfaceClass::Send_To(void const * buffer, int length, IPXAddressClass const & to)
{
	if (Socket == nullptr) return(TransferResult{SocketError::OTHER, 0});

	if (TunnelPort == 0) {
		return(Socket->Send_To(buffer, length, to));
	}

	// The tunnel server routes on the header alone, so it has to lead the datagram,
	// outside the packet's own framing.
	char tunnelled[TUNNEL_HEADER_SIZE + WS_RECEIVE_BUFFER_LEN];
	if (length > (int)sizeof(tunnelled) - TUNNEL_HEADER_SIZE) {
		return(TransferResult{SocketError::MESSAGE_SIZE, 0});
	}

	unsigned short header[] = { TunnelID, to.Get_Port() };
	std::memcpy(tunnelled, header, sizeof(header));
	std::memcpy(tunnelled + TUNNEL_HEADER_SIZE, buffer, length);

	IPXAddressClass const server(TunnelIP, TunnelPort);
	TransferResult result = Socket->Send_To(tunnelled, length + TUNNEL_HEADER_SIZE, server);

	if (result.Error == SocketError::NONE && result.Length > 0) {
		result.Length -= TUNNEL_HEADER_SIZE;
	}

	return(result);
}


/// <summary>
/// Takes a datagram from the socket, unwrapping it when a tunnel is in use. A tunnelled
/// packet reports its sender by tunnel ID, since the server is the only endpoint the
/// socket ever sees.
/// </summary>
/// <returns>The payload received. A length of zero with no error means the datagram was
/// not for this client, which leaves the drain free to try the next one.</returns>
TransferResult UDPInterfaceClass::Receive_From(void * buffer, int length, IPXAddressClass & from)
{
	if (Socket == nullptr) return(TransferResult{SocketError::OTHER, 0});

	if (TunnelPort == 0) {
		return(Socket->Receive_From(buffer, length, from));
	}

	char tunnelled[TUNNEL_HEADER_SIZE + WS_RECEIVE_BUFFER_LEN];
	TransferResult const result = Socket->Receive_From(tunnelled, sizeof(tunnelled), from);

	if (result.Error != SocketError::NONE) return(result);

	int rc = result.Length;

	// Anything too short to carry a header, or addressed to somebody else, is not ours.
	unsigned short header[2];
	if (rc <= TUNNEL_HEADER_SIZE) return(TransferResult{SocketError::NONE, 0});
	std::memcpy(header, tunnelled, sizeof(header));

	if (header[1] != TunnelID) return(TransferResult{SocketError::NONE, 0});

	rc -= TUNNEL_HEADER_SIZE;
	if (rc > length) return(TransferResult{SocketError::NONE, 0});

	std::memcpy(buffer, tunnelled + TUNNEL_HEADER_SIZE, rc);

	// The server is the only endpoint we see, so the sender is named by tunnel ID.
	from.Set_Address(0, header[0]);

	return(TransferResult{SocketError::NONE, rc});
}



/***********************************************************************************************
 * UDPIC::~UDPInterfaceClass -- UDPInterface class destructor                                  *
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
 *    10/9/97 12:17PM ST : Created                                                             *
 *=============================================================================================*/
UDPInterfaceClass::~UDPInterfaceClass (void)
{
	Clear_Broadcast_Addresses();

	while ( LocalAddresses.Count() ) {
		delete LocalAddresses[0];
		LocalAddresses.Delete_Index(0);
	}

	Close();
}


/// <summary>
/// Discards every broadcast address the interface knows about.
/// This routine is used to forget the addresses handed over by Set_Broadcast_Address,
/// so that a later broadcast will not reach a stale set of destinations.
/// </summary>
void UDPInterfaceClass::Clear_Broadcast_Addresses(void)
{
	while ( BroadcastAddresses.Count() ) {
		delete BroadcastAddresses[0];
		BroadcastAddresses.Delete_Index(0);
	}
}


/***********************************************************************************************
 * UDPInterfaceClass::Set_Broadcast_Address -- Sets the address to send broadcast packets to   *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Address to add to the broadcast list                                              *
 *                                                                                             *
 * OUTPUT:   Nothing                                                                           *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    8/5/97 12:12PM ST : Created                                                              *
 *=============================================================================================*/
void UDPInterfaceClass::Set_Broadcast_Address (const IPXAddressClass &address)
{
	BroadcastAddresses.Add (new IPXAddressClass(address));
}


/***********************************************************************************************
 * UDPInterfaceClass::Open_Socket -- Opens a socket for communications via the UDP protocol    *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Socket number to use. Not required for this protocol.                             *
 *                                                                                             *
 * OUTPUT:   True if socket was opened OK                                                      *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    8/5/97 12:13PM ST : Created                                                              *
 *=============================================================================================*/
bool UDPInterfaceClass::Open_Socket(void)
{
	/*
	**	If Winsock is not initialised then do it now.
	*/
	if ( !WinsockInitialised ) {
		if ( !Init()) return( false );
	}

	DebugString("About to open a UDP socket\n");

	/*
	**	Create our UDP socket and bind it to our UDP port number
	*/
	unsigned short const port = LocalPortSet ? LocalPort : (unsigned short) WestwoodOnline_PortNumber;

	if (!Socket->Open(port)) {
		return(false);
	}

	// Winsock refuses a broadcast on a socket that never asked for one.
	if ( UseBroadcast ) {
		Socket->Set_Broadcast(true);
	}

	/*
	**	Clear out any old local addresses from the local address list.
	*/
	while ( LocalAddresses.Count() ) {
		delete LocalAddresses[0];
		LocalAddresses.Delete_Index(0);
	}

	Register_Local_Addresses();

	/*
	**	Set options for the UDP socket
	*/
	BASECLASS::Set_Socket_Options();

	DebugString("UDP Socket init complete\n");

	return(true);
}


/// <summary>
/// Collects the addresses this machine can be reached at.
/// Every adapter's address goes into the local address list, which is what lets an incoming
/// packet be recognized as one of our own and thrown away. When broadcasting is enabled,
/// each adapter's network also contributes a directed broadcast address, so that a broadcast
/// reaches every network this machine sits on rather than only the first.
/// </summary>
/// <remarks>
/// A platform that cannot work out a network's broadcast address reports none for that
/// entry, which leaves the blind broadcast below as the only way onto the local wire.
/// </remarks>
void UDPInterfaceClass::Register_Local_Addresses()
{
	std::vector<InterfaceType> interfaces;

	if (Socket != nullptr && Socket->Local_Interfaces(interfaces)) {

		for (InterfaceType const & found : interfaces) {

			unsigned char * local = new unsigned char[4];
			*reinterpret_cast<uint32_t *>(local) = found.Address;
			LocalAddresses.Add(local);

			if (!UseBroadcast || found.Broadcast == 0) continue;

			// A port of zero leaves the send path to use the port this socket was given.
			IPXAddressClass * broadcast = new IPXAddressClass(found.Broadcast, 0);
			BroadcastAddresses.Add(broadcast);

			DebugString("Added broadcast address: %s\n", broadcast->As_String());
		}
	}

	// Nothing named a network of its own, so settle for a broadcast that goes no
	// further than the local wire. A default address is that blind broadcast.
	if (UseBroadcast && BroadcastAddresses.Count() == 0) {
		BroadcastAddresses.Add(new IPXAddressClass());
	}
}


/***********************************************************************************************
 * UDPIC::Broadcast -- Send data via the Winsock socket                                        *
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
void UDPInterfaceClass::Broadcast (void *buffer, int buffer_len)
{
	if (buffer == NULL || buffer_len <= 0 || buffer_len > WS_INTERNET_BUFFER_LEN) {
		Record_Packet_Drop(WS_DROP_SEND_LENGTH);
		return;
	}

	for ( int i=0 ; i<BroadcastAddresses.Count() ; i++ ) {

		/*
		**	Create a temporary holding area for the packet.
		*/
		WinsockBufferType *packet = (WinsockBufferType *)Get_New_Out_Buffer();
		if (packet == NULL) {
			return;
		}

		/*
		**	Copy the packet into the holding buffer.
		*/
		memcpy ( packet->Buffer, buffer, buffer_len );
		packet->BufferLen = buffer_len;

		/*
		**	Indicate that this packet should be broadcast.
		*/
		packet->IsBroadcast = true;

		/*
		**	Set up the send address for this packet.
		*/
		memset (packet->Address, 0, sizeof (packet->Address));
		memcpy (packet->Address, BroadcastAddresses[i], sizeof (IPXAddressClass));

		Build_Packet_CRC(packet);

		/*
		**	Add it to our out list.
		*/
		OutBuffers.Add ( packet );

		Send_Pending();
	}
}


/// <summary>
/// Takes every datagram the socket holds into the in buffers. A pass is
/// bounded so that a flood cannot hold the frame; what is left waits for the
/// next one.
/// </summary>
void UDPInterfaceClass::Receive_Pending(void)
{
	for (int taken = 0; taken < WS_MAX_STATIC_BUFFERS; taken++) {
		IPXAddressClass source;

		TransferResult const received = Receive_From(ReceiveBuffer, sizeof (ReceiveBuffer), source);

		if (received.Error != SocketError::NONE) {
			// Would-block means the socket is empty; anything else is cleared
			// and the drain carries on.
			if (received.Error == SocketError::WOULD_BLOCK) return;
			Clear_Error();
			continue;
		}

		// Nothing this client should see, such as a tunnelled datagram bound
		// for somebody else.
		if (received.Length == 0) continue;

		int const rc = received.Length;

		std::span<std::byte const> const datagram(reinterpret_cast<std::byte const *>(ReceiveBuffer), static_cast<std::size_t>(rc));
		NetAdmission::DatagramResult const admission = NetAdmission::Admit_Datagram(datagram, WS_INTERNET_BUFFER_LEN);
		if (!admission.Succeeded()) {
			switch (admission.ErrorCode) {
				case NetAdmission::Error::DATAGRAM_TOO_LARGE:
					Record_Packet_Drop(WS_DROP_RECEIVE_TOO_LARGE);
					break;
				case NetAdmission::Error::BAD_CRC:
					Record_Packet_Drop(WS_DROP_BAD_CRC);
					break;
				default:
					Record_Packet_Drop(WS_DROP_RECEIVE_TOO_SHORT);
					break;
			}
			continue;
		}

		/*
		**	Make sure this packet didn't come from us. If it did then throw it away.
		*/
		bool ours = false;
		uint32_t const from_ip = source.Get_IP();
		for ( int i=0 ; i<LocalAddresses.Count() ; i++ ) {
			if ( ! memcmp (LocalAddresses[i], &from_ip, 4) ) {
				ours = true;
				break;
			}
		}
		if (ours) continue;

		/*
		**	Create a new buffer and store this packet in it.
		*/
		WinsockBufferType * packet = (WinsockBufferType *)Get_New_In_Buffer();
		if (packet == NULL) {
			return;
		}
		packet->BufferLen = static_cast<int>(admission.Payload.size());
		packet->CRC = admission.WireCRC;
		memcpy(packet->Buffer, admission.Payload.data(), admission.Payload.size());

		/*
		**	Copy the address data into the holding buffer address area.
		*/
		memset ( packet->Address, 0, sizeof (packet->Address) );
		memcpy ( packet->Address, &source, sizeof (source) );

		/*
		**	Add the holding buffer to the packet list.
		*/
		InBuffers.Add (packet);
	}
}


/// <summary>
/// Sends the out buffers in order until they are empty or the socket will take
/// no more. A send that fails leaves its packet at the head for the next pass.
/// </summary>
void UDPInterfaceClass::Send_Pending(void)
{
	while (OutBuffers.Count() > 0) {
		WinsockBufferType * packet = OutBuffers[0];

		/*
		**	Set up the address structure of the outgoing packet
		*/
		IPXAddressClass destination;
		memcpy (&destination, packet->Address, sizeof (destination));

		// An address without a port of its own goes to the port this socket was given.
		if (destination.Get_Port() == 0) {
			unsigned short const port = DestinationPortSet ? DestinationPort : (unsigned short)WestwoodOnline_PortNumber;
			destination.Set_Port(Socket_Network_Port(port));
		}

		TransferResult const sent = Send_To ( ((char const *)packet->Buffer) - sizeof(packet->CRC), packet->BufferLen + sizeof(packet->CRC), destination );

		if (sent.Error != SocketError::NONE) {
			if (sent.Error != SocketError::WOULD_BLOCK) {
				Clear_Error();
			}
			break;
		}

		OutBuffers.Delete_Index(0);
		if (packet->IsAllocated) {
			delete packet;
		} else {
			packet->InUse = false;
			OutBuffersUsed--;
		}
	}
}
