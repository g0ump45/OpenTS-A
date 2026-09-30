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
 *                     $Archive:: /G/wwlib/RNDSTRAW.H                                         $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 12:00p                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once


#include "random.h"
#include "straw.h"

/*
**	This is a straw terminator class. It will generate random numbers to fill the data request.
**	Unlike regular straw terminators, this class will never run out of "data".
*/
class RandomStraw : public Straw
{
		typedef Straw BASECLASS;

	public:
		RandomStraw(void);
		virtual ~RandomStraw(void) override;

		virtual int Get(void * source, int slen) override;

		void Reset(void);
		void Seed_Bit(int seed);
		void Seed_Byte(char seed);
		void Seed_Short(short seed);
		void Seed_Long(int seed);

		int Seed_Bits_Needed(void) const;

	private:
		/*
		**	Counter of the number of seed bits stored to this random number
		**	generator.
		*/
		int SeedBits;

		/*
		**	The current random generator to use when fetching the next random
		**	byte of data.
		*/
		int Current;

		/*
		**	Array of generators. There must be at least 448 bits of random number seed
		**	in order to be reasonably secure, however, using 1024 bits would be best.
		*/
		Random3Class Random[32];

		void Scramble_Seed(void);

		RandomStraw(RandomStraw & rvalue);
		RandomStraw & operator = (RandomStraw const & pipe);
};


extern RandomStraw CryptRandom;
