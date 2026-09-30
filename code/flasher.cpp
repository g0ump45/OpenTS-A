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

/* $Header: /CounterStrike/FLASHER.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : FLASHER.CPP                                                  *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : May 28, 1994                                                 *
 *                                                                                             *
 *                  Last Update : October 17, 1994   [JLB]                                     *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   FlasherClass::Debug_Dump -- Displays current status to the monochrome screen.             *
 *   FlasherClass::Process -- Performs the logic processing for the flashing ability.          *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "flasher.h"

#include "mono.h"


#ifdef _DEBUG
/***********************************************************************************************
 * FlasherClass::Debug_Dump -- Displays current status to the monochrome screen.               *
 *                                                                                             *
 *    This utility function will output the current status of the FlasherClass to the mono     *
 *    screen. It is through this display that bugs may be fixed or detected.                   *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/31/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
void FlasherClass::Debug_Dump(MonoClass * mono) const
{
	mono->Set_Cursor(50, 7);
	mono->Printf("%2d", FlashCount);
}
#endif


/***********************************************************************************************
 * FlasherClass::Process -- Performs the logic processing for the flashing ability.            *
 *                                                                                             *
 *    The ability for an object to flash is controlled by this logic processing routine. It    *
 *    should be called once per game tick per unit.                                            *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  bool; Should the associated object be redrawn?                                     *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/28/1994 JLB : Created.                                                                 *
 *   06/20/1994 JLB : Is now independent of object it represents.                              *
 *=============================================================================================*/
bool FlasherClass::Process(void)
{
	if (FlashCount) {
		FlashCount--;
		IsBlushing = false;

		if (FlashCount & 0x01) {
			IsBlushing = true;
		}
		return(true);
	}
	return(false);
}
