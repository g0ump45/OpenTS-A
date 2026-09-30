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

/* $Header: /CounterStrike/IPXCONN.H 1     3/03/97 10:24a Joe_bostic $ */
/***************************************************************************
 **   C O N F I D E N T I A L --- W E S T W O O D    S T U D I O S        **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : Command & Conquer                        *
 *                                                                         *
 *                    File Name : IPXCONN.H                                *
 *                                                                         *
 *                   Programmer : Bill Randolph                            *
 *                                                                         *
 *                   Start Date : December 19, 1994                        *
 *                                                                         *
 *                  Last Update : April 9, 1995   [BR]                     *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *                                                                         *
 * This is the Connection Class for IPX communications.  It inherits       *
 * a Queue, PacketBuf, timeout variables from ConnectionClass.  It         *
 * inherits its Send_/Receive_/Get_Packet functions, and the sequenced     *
 * ACK/Retry logic in Service_Send_Queue & Service_Receive_Queue from      *
 * SequencedConnClass.  It guarantees order of delivery of packets.        *
 *                                                                         *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once


/*
********************************* Includes **********************************
*/
#include "connect.h"
#include "ipxaddr.h"


/*
***************************** Class Declaration *****************************
*/
class IPXConnClass : public ConnectionClass
{
		typedef ConnectionClass BASECLASS;

	/*
	---------------------------- Public Interface ----------------------------
	*/
	public:
		/*.....................................................................
		Various useful enums:
		.....................................................................*/
		enum IPXConnTag {
			CONN_NAME_MAX = 40			// max # chars allowed for connection name
		};

		/*.....................................................................
		Constructor/destructor.
		.....................................................................*/
		IPXConnClass(int numsend, int numrecieve, int maxlen,
			unsigned short magicnum, IPXAddressClass *address, int id, char const *name,
			int extralen = 0);
		virtual ~IPXConnClass () override {};

		/*.....................................................................
		Initialization.
		.....................................................................*/
		virtual void Init (void) override;

		/*.....................................................................
		The Configure function is for configuring all connections at once.
		It's static because it doesn't apply to any specific connection, but
		all of them.
		.....................................................................*/
		static void Configure(int conn_num);

		/*.....................................................................
		These routines tell IPX to start listening for packets, and to stop
		listening for packets.  They're static because they affect all
		connections at once (there's no way to turn listening on for only one
		connection; it's all or nothing).
		.....................................................................*/
		static int Start_Listening (void);
		static int Stop_Listening (void);

		/*.....................................................................
		The Destination address for this connection
		.....................................................................*/
		IPXAddressClass Address;

		/*.....................................................................
		Each Connection can have a Name & Unique numerical ID
		.....................................................................*/
		int ID;
		char Name[CONN_NAME_MAX];

	/*
	-------------------------- Protected Interface ---------------------------
	*/
	protected:

		/*.....................................................................
		This is the overloaded Send routine declared in ConnectionClass, and
		used in SequencedConnClass.
		.....................................................................*/
		virtual int Send (char *buf, int buflen, void *extrabuf, int extralen) override;

		/*.....................................................................
		These are the routines that access the transport.  Open_Socket &
		Close_Socket are static because they're called by Start_Listening &
		Stop_Listening.  Send_To & Broadcast are static since they're direct
		interfaces to the transport, and there's only one instance running.
		.....................................................................*/
		static int Open_Socket(void);
		static void Close_Socket(void);
		static int Send_To(char *buf, int buflen, IPXAddressClass *address);
		static int Broadcast(char *buf, int buflen);

		/*.....................................................................
		User's local Connection # (0 = not logged in)
		.....................................................................*/
		static int ConnectionNum;

		/*.....................................................................
		This status flag tells us if Configure() has been called or not.
		.....................................................................*/
		static int Configured;

		/*.....................................................................
		This status flag tells us if the socket has been opened or not.
		.....................................................................*/
		static int SocketOpen;

		/*.....................................................................
		This status flag tells us if Start_Listening() has been called or not.
		.....................................................................*/
		static int Listening;
};


/*************************** end of ipxconn.h ******************************/
