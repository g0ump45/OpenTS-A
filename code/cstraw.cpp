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
 *                     $Archive:: /Commando/Library/CSTRAW.CPP                                $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   CacheStraw::Get -- Fetch data from the data source.                                       *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "cstraw.h"

#include <cstring>


/***********************************************************************************************
 * CacheStraw::Get -- Fetch data from the data source.                                         *
 *                                                                                             *
 *    This will supply the data quantity requested. It performs a regulating influence on the  *
 *    data requests passed through it. The data is requested from the next straw in the        *
 *    chain such that the data stream is requested in chunks. This serves to lessen the        *
 *    impact of multiple small data requests.                                                  *
 *                                                                                             *
 * INPUT:   source   -- Pointer to the buffer to hold the data.                                *
 *                                                                                             *
 *          slen     -- The number of data bytes requested.                                    *
 *                                                                                             *
 * OUTPUT:  Returns with the number of data bytes stored into the buffer specified. If this    *
 *          number is less than that requested, it indicates that the data source has been     *
 *          exhausted.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/10/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int CacheStraw::Get(void * source, int slen)
{
	int total = 0;

	if (Is_Valid() && source != NULL && slen > 0) {

		/*
		**	Keep processing the data request until there is no more data to supply or the request
		**	has been fulfilled.
		*/
		while (slen > 0) {

			/*
			**	First try to fetch the data from data previously loaded into the buffer.
			*/
			if (Length > 0) {
				int tocopy = (Length < slen) ? Length : slen;
				memmove(source, ((char *)BufferPtr.Get_Buffer()) + Index, tocopy);
				slen -= tocopy;
				Index += tocopy;
				total += tocopy;
				Length -= tocopy;
				source = (char*)source + tocopy;
			}
			if (slen == 0) break;

			/*
			**	Since there is more to be fulfilled yet the holding buffer is empty,
			**	refill the buffer with a fresh block of data from the source.
			*/
			Length = BASECLASS::Get(BufferPtr, BufferPtr.Get_Size());
			Index = 0;
			if (Length == 0) break;
		}
	}
	return(total);
}
