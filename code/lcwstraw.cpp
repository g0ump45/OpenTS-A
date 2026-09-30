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

/* $Header: /CounterStrike/LCWSTRAW.CPP 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : LCWSTRAW.CPP                                                 *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 07/02/96                                                     *
 *                                                                                             *
 *                  Last Update : July 4, 1996 [JLB]                                           *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   LCWStraw::Get -- Fetch data through the LCW processor.                                    *
 *   LCWStraw::LCWStraw -- Constructor for LCW straw object.                                   *
 *   LCWStraw::~LCWStraw -- Destructor for the LCW straw.                                      *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "lcwstraw.h"

#include "lcw.h"

#include <cassert>
#include <cstring>


/***********************************************************************************************
 * LCWStraw::LCWStraw -- Constructor for LCW straw object.                                     *
 *                                                                                             *
 *    This will initialize the LCW straw object. Whether the object is to compress or          *
 *    decompress and the block size to use is specified. The data is compressed in blocks      *
 *    that are sized to be quick to compress and yet still yield good compression ratios.      *
 *                                                                                             *
 * INPUT:   decrypt  -- Should the data be decompressed?                                       *
 *                                                                                             *
 *          blocksize-- The size of the blocks to process.                                     *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   It takes two buffers of the blocksize specified if compression is to be         *
 *             performed.                                                                      *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/04/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
LCWStraw::LCWStraw(CompControl control, int blocksize) :
		Control(control),
		Counter(0),
		Buffer(NULL),
		Buffer2(NULL),
		BlockSize(blocksize)
{
	SafetyMargin = LCW_Comp_Bound(BlockSize) - BlockSize;
	Buffer = new char[BlockSize+SafetyMargin];
	if (control == COMPRESS) {
		Buffer2 = new char[BlockSize+SafetyMargin+sizeof(BlockHeader)];
	}
}


/***********************************************************************************************
 * LCWStraw::~LCWStraw -- Destructor for the LCW straw.                                        *
 *                                                                                             *
 *    The destructor will free up the allocated buffers that it allocated in the constructor.  *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/04/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
LCWStraw::~LCWStraw(void)
{
	delete [] Buffer;
	Buffer = NULL;

	delete [] Buffer2;
	Buffer2 = NULL;
}


/***********************************************************************************************
 * LCWStraw::Get -- Fetch data through the LCW processor.                                      *
 *                                                                                             *
 *    This routine will fetch the data bytes specified. It does this by first accumulating     *
 *    a full block of data and then compressing or decompressing it as indicated. Subsequent   *
 *    requests for data will draw from this buffer of processed data until it is exhausted     *
 *    and another block must be fetched.                                                       *
 *                                                                                             *
 * INPUT:   destbuf  -- Pointer to the buffer to hold the data requested.                      *
 *                                                                                             *
 *          length   -- The number of data bytes requested.                                    *
 *                                                                                             *
 * OUTPUT:  Returns with the actual number of bytes stored into the buffer. If this number     *
 *          is less than that requested, then this indicates that the data source has been     *
 *          exhausted.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/04/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int LCWStraw::Get(void * destbuf, int slen)
{
	assert(Buffer != NULL);

	int total = 0;

	/*
	**	Verify parameters for legality.
	*/
	if (destbuf == NULL || slen < 1) {
		return(0);
	}

	while (slen > 0) {

		/*
		**	Copy as much data is requested and available into the desired
		**	destination buffer.
		*/
		if (Counter > 0) {
			int len = (slen < Counter) ? slen : Counter;
			if (Control == DECOMPRESS) {
				memmove(destbuf, &Buffer[BlockHeader.UncompCount-Counter], len);
			} else {
				memmove(destbuf, &Buffer2[(BlockHeader.CompCount+sizeof(BlockHeader))-Counter], len);
			}
			destbuf = ((char *)destbuf) + len;
			slen -= len;
			Counter -= len;
			total += len;
		}
		if (slen == 0) break;

		if (Control == DECOMPRESS) {
			int incount = BASECLASS::Get(&BlockHeader, sizeof(BlockHeader));
			if (incount != sizeof(BlockHeader)) break;

			// The counts are stream data; a block the compressor could not have written
			// would start before the buffer or expand past it.
			if (BlockHeader.CompCount == 0 || BlockHeader.CompCount > BlockSize+SafetyMargin) break;
			if (BlockHeader.UncompCount == 0 || BlockHeader.UncompCount > BlockSize) break;

			void * ptr = &Buffer[(BlockSize+SafetyMargin) - BlockHeader.CompCount];
			incount = BASECLASS::Get(ptr, BlockHeader.CompCount);
			if (incount != BlockHeader.CompCount) break;

			LCW_Uncomp(ptr, Buffer, BlockHeader.UncompCount);
			Counter = BlockHeader.UncompCount;
		} else {
			BlockHeader.UncompCount = (unsigned short)BASECLASS::Get(Buffer, BlockSize);
			if (BlockHeader.UncompCount == 0) break;
			BlockHeader.CompCount = (unsigned short)LCW_Comp(Buffer, &Buffer2[sizeof(BlockHeader)], BlockHeader.UncompCount);
			memmove(Buffer2, &BlockHeader, sizeof(BlockHeader));
			Counter = BlockHeader.CompCount+sizeof(BlockHeader);
		}
	}

	return(total);
}
