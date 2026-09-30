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
 *                     $Archive:: /G/wwlib/b64straw.h                                         $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 11:58a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "straw.h"

/*
**	Performs Base 64 encoding/decoding on the data that is drawn through the straw. Note that
**	encoding increases the data size by about 30%. The reverse occurs when decoding.
*/
class Base64Straw : public Straw
{
		typedef Straw BASECLASS;

	public:
		enum CodeControl {
			ENCODE,
			DECODE
		};

		Base64Straw(CodeControl control) : Control(control), Counter(0) {}
		virtual int Get(void * source, int slen) override;

	private:

		/*
		**	Indicates if this is for encoding or decoding of Base64 data.
		*/
		CodeControl Control;

		/*
		**	The counter of the number of accumulated bytes pending for processing.
		*/
		int Counter;

		/*
		**	Buffer that holds the Base64 coded bytes. This will be the staging buffer if
		**	this is for a decoding process. Otherwise, it will be used as a scratch buffer.
		*/
		char CBuffer[4];

		/*
		**	Buffer that holds the plain bytes. This will be the staging buffer if this
		**	is for an encoding process. Otherwise, it will be used as a scratch buffer.
		*/
		char PBuffer[3];

		/*
		**	Explicitly disable the copy constructor and the assignment operator.
		*/
		Base64Straw(Base64Straw & rvalue);
		Base64Straw & operator = (Base64Straw const & pipe);
};
