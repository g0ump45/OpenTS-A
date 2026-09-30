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
 *                     $Archive:: /Commando/Library/LOAD.CPP                                  $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Load_Uncompress -- Load and uncompress the given file.                                    *
 *   Uncompress_Data -- Uncompress standard CPS buffer.                                        *
 *   Load_Data -- Loads a data file from disk.                                                 *
 *   Load_Alloc_Data -- Loads and allocates buffer for a file.                                 *
 *   Write_Data -- Writes a block of data as a file to disk.                                   *
 *   Uncompress_Data -- Uncompresses data from one buffer to another.                          *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "iff.h"
#include "lcw.h"

#include <cstring>


/***************************************************************************
 * Uncompress_Data -- Uncompresses data from one buffer to another.        *
 *                                                                         *
 *    This routine takes data from a compressed file (sans the first two   *
 *    size bytes) and uncompresses it to a destination buffer.  The source *
 *    data MUST have the CompHeaderType at its start.                      *
 *                                                                         *
 * INPUT:   src   -- Source compressed data pointer.                       *
 *                                                                         *
 *          dst   -- Destination (paragraph aligned) pointer.              *
 *                                                                         *
 * OUTPUT:  Returns with the size of the uncompressed data.                *
 *                                                                         *
 * WARNINGS:   If LCW compression is used, the destination buffer must     *
 *             be paragraph aligned.                                       *
 *                                                                         *
 * HISTORY:                                                                *
 *   09/17/1993 JLB : Created.                                             *
 *=========================================================================*/
unsigned int Uncompress_Data(void const *src, void *dst)
{
	unsigned int					skip;   // Number of leading data to skip.
	CompressionType	method;                 // Compression method used.
	unsigned int					uncomp_size=NULL;

	if (!src || !dst) return(NULL);

	/*
	**	Interpret the data block header structure to determine
	**	compression method, size, and skip data amount.
	*/
	uncomp_size = ((CompHeaderType*)src)->Size;
	#if (AMIGA)
		uncomp_size = Reverse_Long(uncomp_size);
	#endif
	skip = ((CompHeaderType*)src)->Skip;
	#if (AMIGA)
		skip = Reverse_Word(skip);
	#endif
	method = (CompressionType) ((CompHeaderType*)src)->Method;
	src = ((char*)src) + (int)sizeof(CompHeaderType) + (int)skip;
//	src = Add_Long_To_Pointer((void *)src, (long)sizeof(CompHeaderType) + (long)skip);

	switch (method) {

		default:
		case NOCOMPRESS:
			memmove(dst, (void *) src, uncomp_size);
//			Mem_Copy((void *) src, dst, uncomp_size);
			break;

		case HORIZONTAL:
#if LIB_EXTERNS_RESOLVED
			RLE_Uncompress((void *) src, dst, uncomp_size);
#endif
			break;

		case LCW:
			LCW_Uncomp((void *) src, (void *) dst, (unsigned int) uncomp_size);
			break;

	}

	return(uncomp_size);
}
