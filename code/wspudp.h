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
 *                     $Archive:: /Sun/WSPUDP.h                                               $*
 *                                                                                             *
 *                      $Author:: Joe_b                                                       $*
 *                                                                                             *
 *                     $Modtime:: 8/05/97 6:45p                                               $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "wsproto.h"


/*
**	Class to allow access to UDP specific portions of the Winsock interface.
**
*/
class UDPInterfaceClass : public WinsockInterfaceClass {
		typedef WinsockInterfaceClass BASECLASS;

	public:

		UDPInterfaceClass (void);
		virtual ~UDPInterfaceClass(void) override;

		virtual bool Open_Socket(void) override;
		virtual void Set_Broadcast_Address ( const IPXAddressClass &address ) override;
		virtual void Clear_Broadcast_Addresses(void) override;
		virtual void Broadcast (void *buffer, int buffer_len) override;

		/*
		 * Ports are in host order. Left unset, both follow WestwoodOnline_PortNumber; a
		 * local port of zero binds whatever port Winsock hands out.
		 */
		void Set_Local_Port(unsigned short port);
		void Set_Destination_Port(unsigned short port);

		void Enable_Broadcast(bool enable);

		/*
		 * Route everything through a CnCNet tunnel server, which forwards between players
		 * that cannot reach each other directly. Every datagram gains a routing header
		 * naming the sender and the recipient by their tunnel ID; a player is addressed by
		 * that ID in place of a real endpoint. All arguments are in network order.
		 */
		void Configure_Tunnel(unsigned short local_id, unsigned long tunnel_ip, unsigned short tunnel_port);

		virtual ProtocolEnum Get_Protocol (void) override {
			return(PROTOCOL_UDP);
		};

		virtual int Get_Num_Local_Addresses(void) override {
			return(LocalAddresses.Count());
		};

		virtual unsigned char *Get_Local_Address(int index) override {
			return(LocalAddresses[index]);
		};

	protected:

		virtual void Receive_Pending(void) override;
		virtual void Send_Pending(void) override;

	private:

		void Register_Local_Addresses();

		// Wrappers around the socket that add and strip the tunnel routing header. A
		// receive that answers NONE with a length of zero delivered nothing this client
		// should see, which a caller draining the socket passes over.
		TransferResult Send_To(void const * buffer, int length, IPXAddressClass const & to);
		TransferResult Receive_From(void * buffer, int length, IPXAddressClass & from);

		/*
		**	Addresses to send to when broadcasting a packet.
		*/
		DynamicVectorClass <IPXAddressClass *> BroadcastAddresses;

		/*
		**	List of local addresses.
		*/
		DynamicVectorClass <unsigned char *> LocalAddresses;

		unsigned short LocalPort;
		unsigned short DestinationPort;
		bool LocalPortSet;
		bool DestinationPortSet;
		bool UseBroadcast;

		// A tunnel is in use when TunnelPort is non-zero.
		unsigned short TunnelID;
		unsigned long TunnelIP;
		unsigned short TunnelPort;
};
