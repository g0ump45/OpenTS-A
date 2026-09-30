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
 *                     $Archive:: /Commando/Library/PKSTRAW.H                                 $*
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

#include "blwstraw.h"
#include "pk.h"
#include "pkstraw.h"
#include "rndstraw.h"

class PKStraw : public Straw
{
		typedef Straw BASECLASS;
	public:
		enum CryptControl {
			ENCRYPT,
			DECRYPT
		};

		PKStraw(CryptControl control, RandomStraw & rnd);
		~PKStraw(void) override;

		virtual void Get_From(Straw * straw) override;
		virtual void Get_From(Straw & straw) {Get_From(&straw);}

		virtual int Get(void * source, int slen) override;

		// Submit key to be used for encryption/decryption.
		void Key(PKey const * key);

	private:
		enum {
			BLOWFISH_KEY_SIZE=BlowfishEngine::MAX_KEY_LENGTH,
			MAX_KEY_BLOCK_SIZE=256		// Maximum size of pk encrypted blowfish key.
		};

		/*
		**	This flag indicates whether the PK (fetch blowfish key) phase is
		**	in progress or not.
		*/
		bool IsGettingKey;

		/*
		**	This is the random straw that is needed to generate the
		**	blowfish key.
		*/
		RandomStraw & Rand;

		/*
		**	This is the attached blowfish pipe. After the blowfish key has been
		**	decrypted, then the PK processor goes dormant and the blowfish processor
		**	takes over the data flow.
		*/
		BlowStraw BF;

		/*
		**	This control member tells what method (encryption or decryption) that should
		**	be performed on the data stream.
		*/
		CryptControl Control;

		/*
		**	Pointer to the key to use for encryption or decryption. If this pointer is NULL, then
		**	the data passing through this segment will not be modified.
		*/
		PKey const * CipherKey;

		/*
		**	This is the staging buffer for the block of data. This block must be as large as
		**	the largest possible key size or the largest blowfish key size (whichever is
		**	greater).
		*/
		char Buffer[256];

		int Counter;

		/*
		**	This records the number of bytes remaining in the current block. This
		**	will be the number of bytes left to accumulate before the block can be
		**	processed either for encryption or decryption.
		*/
		int BytesLeft;

		int Encrypted_Key_Length(void) const;
		int Plain_Key_Length(void) const;

		PKStraw(PKStraw & rvalue);
		PKStraw & operator = (PKStraw const & straw);
};
