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
 *                     $Archive:: /Commando/Library/CRCSTRAW.CPP                              $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   CRCStraw::Get -- Fetch the data requested and calculate CRC on it.                        *
 *   CRCStraw::Result -- Returns with the CRC of all data passed through the straw.            *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "crcstraw.h"


/***********************************************************************************************
 * CRCStraw::Get -- Fetch the data requested and calculate CRC on it.                          *
 *                                                                                             *
 *    This routine will fetch the number of bytes requested. The data will not be modified     *
 *    by this straw segment, but the CRC engine will examine the data so as to keep an         *
 *    accurate CRC value.                                                                      *
 *                                                                                             *
 * INPUT:   source   -- Pointer to the buffer to hold the data requested.                      *
 *                                                                                             *
 *          length   -- The number of bytes requested.                                         *
 *                                                                                             *
 * OUTPUT:  Returns with the actual number of bytes stored in the buffer. If this number is    *
 *          less than that requested, then this indicates that the data stream has been        *
 *          exhausted.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int CRCStraw::Get(void * source, int slen)
{
	if (source == NULL || slen < 1) {
		return(0);
	}

	int counter = BASECLASS::Get(source, slen);
	CRC(source, counter);
	return(counter);
}


/***********************************************************************************************
 * CRCStraw::Result -- Returns with the CRC of all data passed through the straw.              *
 *                                                                                             *
 *    This routine will return the CRC value of the data that has passed through this straw    *
 *    segment.                                                                                 *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the CRC value of the data this straw segment has seen.                *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int CRCStraw::Result(void) const
{
	return(CRC());
}
