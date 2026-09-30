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
 *                     $Archive:: /Commando/Library/SHASTRAW.CPP                              $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   SHAStraw::Get -- Fetch data from the straw and process the SHA with the data.             *
 *   SHAStraw::Result -- Fetches the current SHA digest.                                       *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "shastraw.h"


/***********************************************************************************************
 * SHAStraw::Get -- Fetch data from the straw and process the SHA with the data.               *
 *                                                                                             *
 *    This routine will fetch the requested data and as it passes through this straw it will   *
 *    submit it to the SHA processor. The data that passes through is unmodified by this       *
 *    straw segment.                                                                           *
 *                                                                                             *
 * INPUT:   source   -- Pointer to the buffer that will hold the requested data.               *
 *                                                                                             *
 *          length   -- The length of the data requested.                                      *
 *                                                                                             *
 * OUTPUT:  Returns with the number of bytes stored in the buffer. If this number is less      *
 *          than the number requested, then this indicates that the data stream has been       *
 *          exhausted.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int SHAStraw::Get(void * source, int slen)
{
	if (source == NULL || slen < 1) {
		return(0);
	}

	int counter = BASECLASS::Get(source, slen);
	if (!IsDisabled) {
		SHA.Hash(source, counter);
	}
	return(counter);
}


/***********************************************************************************************
 * SHAStraw::Result -- Fetches the current SHA digest.                                         *
 *                                                                                             *
 *    Use this routine to fetch the current SHA digest from the straw. It will return the      *
 *    digest of the data that has passed through this straw segment.                           *
 *                                                                                             *
 * INPUT:   result   -- Pointer to the buffer to hold the message digest. The buffer must be   *
 *                      20 bytes long.                                                         *
 *                                                                                             *
 * OUTPUT:  Returns with the number of bytes stored into the digest buffer. This will always   *
 *          be 20.                                                                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int SHAStraw::Result(void * result) const
{
	return(SHA.Result(result));
}
