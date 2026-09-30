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
 *                     $Archive:: /Commando/Library/BLWSTRAW.H                                $*
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

#include "blowfish.h"
#include "straw.h"


/*
**	Performs Blowfish encryption/decryption to the data that is drawn through this straw. The
**	process is controlled by the key which must be submitted to the class before any data
**	manipulation will occur. The Blowfish algorithm is symmetric, thus the same key is used
**	for encryption as is for decryption.
*/
class BlowStraw : public Straw
{
		typedef Straw BASECLASS;

	public:
		enum CryptControl {
			ENCRYPT,
			DECRYPT
		};

		BlowStraw(CryptControl control) : BF(NULL), Counter(0), Control(control) {}
		virtual ~BlowStraw(void) override {delete BF;BF = NULL;}

		virtual int Get(void * source, int slen) override;

		// Submit key for blowfish engine.
		void Key(void const * key, int length);

	protected:
		/*
		**	The Blowfish engine used for encryption/decryption. If this pointer is
		**	NULL, then this indicates that the blowfish engine is not active and no
		**	key has been submitted. All data would pass through this straw unchanged
		**	in that case.
		*/
		BlowfishEngine * BF;

	private:
		char Buffer[8];
		int Counter;
		CryptControl Control;

		BlowStraw(BlowStraw & rvalue);
		BlowStraw & operator = (BlowStraw const & straw);
};
