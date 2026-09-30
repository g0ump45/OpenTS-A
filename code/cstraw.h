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
 *                     $Archive:: /G/wwlib/cstraw.h                                           $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 11:59a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "buff.h"
#include "straw.h"

/*
**	This class handles transfer of data by perform regulated requests for data from the next
**	class in the chain. It performs no translation on the data. By using this segment in a
**	straw chain, data throughput can be regulated. This can yield great performance increases
**	when dealing with a file source.
*/
class CacheStraw : public Straw
{
		typedef Straw BASECLASS;

	public:
		CacheStraw(Buffer const & buffer) : BufferPtr(buffer), Index(0), Length(0) {}
		CacheStraw(int length=4096) : BufferPtr(length), Index(0), Length(0) {}
		virtual int Get(void * source, int slen) override;

	private:
		Buffer BufferPtr;
		int Index;
		int Length;

		bool Is_Valid(void) {return(BufferPtr.Is_Valid());}
		CacheStraw(CacheStraw & rvalue);
		CacheStraw & operator = (CacheStraw const & pipe);
};
