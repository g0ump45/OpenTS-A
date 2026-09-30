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
 *                     $Archive:: /Commando/Library/SHASTRAW.H                                $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once


#include "sha.h"
#include "straw.h"

/*
**	This class serves as a straw that generates a Secure Hash from the data stream that flows
**	through it. It doesn't modify the data stream in any fashion.
*/
class SHAStraw : public Straw
{
		typedef Straw BASECLASS;

	public:
		SHAStraw(void) : IsDisabled(false) {}
		virtual int Get(void * source, int slen) override;

		void Disable(void) {IsDisabled = true;}
		void Enable(void) {IsDisabled = false;}

		// Fetch the SHA hash value (stored in result buffer -- 20 bytes long).
		int Result(void * result) const;

	protected:
		bool IsDisabled;

		SHAEngine SHA;

	private:
		SHAStraw(SHAStraw & rvalue);
		SHAStraw & operator = (SHAStraw const & straw);
};
