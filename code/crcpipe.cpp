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
 *                     $Archive:: /Commando/Library/CRCPIPE.CPP                               $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   CRCPipe::Result -- Fetches the current CRC of the data.                                   *
 *   CRCPipe::Put -- Retrieves the data bytes specified and calculates CRC on it.              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "crcpipe.h"


/***********************************************************************************************
 * CRCPipe::Put -- Retrieves the data bytes specified and calculates CRC on it.                *
 *                                                                                             *
 *    This routine will fetch the number of bytes requested from the straw. The data is        *
 *    not modified by this straw segment, but it is examined by the CRC engine in order to     *
 *    keep an accurate CRC of the data that passes through this routine.                       *
 *                                                                                             *
 * INPUT:   source   -- Pointer to the buffer that will hold the data requested.               *
 *                                                                                             *
 *          length   -- The number of bytes requested.                                         *
 *                                                                                             *
 * OUTPUT:  Returns with the actual number of bytes stored into the buffer. If this number is  *
 *          less than the number requested, then this indicates that the data stream has been  *
 *          exhausted.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int CRCPipe::Put(void const * source, int slen)
{
	CRC(source, slen);
	return(BASECLASS::Put(source, slen));
}


/***********************************************************************************************
 * CRCPipe::Result -- Fetches the current CRC of the data.                                     *
 *                                                                                             *
 *    This routine will return the CRC of the data that has passed through the pipe up to      *
 *    this time.                                                                               *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the CRC value.                                                        *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int CRCPipe::Result(void) const
{
	return(CRC());
}
