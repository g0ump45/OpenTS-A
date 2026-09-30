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
 *                     $Archive:: /Commando/Library/crcstraw.h                                $*
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

#include "crc.h"
#include "straw.h"

/*
**	This class will build a CRC value from the data stream that is drawn through this class.
**	The data is not modified, but it is examined as it passes through.
*/
class CRCStraw : public Straw
{
		typedef Straw BASECLASS;

	public:
		CRCStraw(void) {}
		virtual int Get(void * source, int slen) override;

		// Calculate and return the CRC value.
		int Result(void) const;

	protected:
		CRCEngine CRC;

	private:
		CRCStraw(CRCStraw & rvalue);
		CRCStraw & operator = (CRCStraw const & pipe);
};
