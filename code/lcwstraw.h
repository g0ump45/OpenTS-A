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

/* $Header: /CounterStrike/LCWSTRAW.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : LCWSTRAW.H                                                   *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 07/02/96                                                     *
 *                                                                                             *
 *                  Last Update : July 2, 1996 [JLB]                                           *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once


#include "straw.h"

/*
**	This class handles LCW compression/decompression to the data stream that is drawn through
**	this class. Note that for compression, two internal buffers are required. For decompression
**	only one buffer is required. This changes the memory footprint of this class depending on
**	the process desired.
*/
class LCWStraw : public Straw
{
		typedef Straw BASECLASS;

	public:
		enum CompControl {
			COMPRESS,
			DECOMPRESS
		};

		LCWStraw(CompControl control, int blocksize=1024*8);
		virtual ~LCWStraw(void) override;

		virtual int Get(void * source, int slen) override;

	private:

		/*
		**	This tells the pipe if it should be decompressing or compressing the data stream.
		*/
		CompControl Control;

		/*
		**	The number of bytes accumulated into the staging buffer.
		*/
		int Counter;

		/*
		**	Pointer to the working buffer that compression/decompression will use.
		*/
		char * Buffer;
		char * Buffer2;

		/*
		**	The working block size. Data will be compressed in chunks of this size.
		*/
		int BlockSize;

		/*
		**	LCW compression requires a safety margin when decompressing over itself. This
		**	margin is only for the worst case situation (very rare).
		*/
		int SafetyMargin;

		/*
		**	Each block has a header of this format.
		*/
		struct {
			unsigned short CompCount;   // Size of data block (compressed).
			unsigned short UncompCount; // Bytes of uncompressed data it represents.
		} BlockHeader;

		LCWStraw(LCWStraw & rvalue);
		LCWStraw & operator = (LCWStraw const & pipe);
};
