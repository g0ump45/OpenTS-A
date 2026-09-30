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

/* $Header: /CounterStrike/IPXADDR.H 1     3/03/97 10:24a Joe_bostic $ */
/***************************************************************************
 **   C O N F I D E N T I A L --- W E S T W O O D    S T U D I O S        **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : Command & Conquer                        *
 *                                                                         *
 *                    File Name : IPXADDR.H                                *
 *                                                                         *
 *                   Programmer : Bill Randolph                            *
 *                                                                         *
 *                   Start Date : December 19, 1994                        *
 *                                                                         *
 *                  Last Update : December 19, 1994   [BR]                 *
 *                                                                         *
 * This class is useful for any IPX-related code.  It's just a utility     *
 * to help manage those annoying IPX address fields.  This class lets you  *
 * compare addresses, copy addresses to & from the IPX header, etc.        *
 *                                                                         *
 * The class has no virtual functions, so you can treat this class just    *
 * like a data structure; it can be loaded & saved, and even transmitted   *
 * across the net.                                                         *
 *                                                                         *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include <cstdint>


/*
***************************** Class Declaration *****************************
*/
class IPXAddressClass
{
	/*
	---------------------------- Public Interface ----------------------------
	*/
	public:
		/*.....................................................................
		Constructors. The default one is the broadcast address.
		.....................................................................*/
		IPXAddressClass(void);
		IPXAddressClass(uint32_t ip, uint16_t port);

		/*
		 * The address, in network byte order. A port of zero means the transport should
		 * send to whichever port it was configured with; a tunnelled game names its
		 * players by tunnel ID in the port, with the IP left at zero.
		 */
		void Set_Address(uint32_t ip, uint16_t port);
		uint32_t Get_IP(void) const {return(IP);}
		uint16_t Get_Port(void) const {return(Port);}
		void Set_Port(uint16_t port) {Port = port;}

		/*.....................................................................
		Tells if this address is a broadcast address
		.....................................................................*/
		int Is_Broadcast(void) const;

		/*.....................................................................
		Overloaded operators:
		.....................................................................*/
		bool operator == (IPXAddressClass & addr);
		bool operator != (IPXAddressClass & addr);

		/*.....................................................................
		Convert address to human readable string
		.....................................................................*/
		const char *As_String(void);

	/*
	-------------------------- Protected Interface ---------------------------
	*/
	protected:
	/*
	--------------------------- Private Interface ----------------------------
	*/
	private:
		uint32_t IP;
		uint16_t Port;
};


/**************************** end of ipxaddr.h *****************************/
