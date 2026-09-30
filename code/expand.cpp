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

/* $Header: /CounterStrike/EXPAND.CPP 7     3/17/97 1:05a Steve_tall $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : EXPAND.CPP                                                   *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 11/03/95                                                     *
 *                                                                                             *
 *                  Last Update : Mar 01, 1997 [V.Grippi]                                      *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   EListClass::Draw_Entry -- Draws entry for expansion scenario.                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "expand.h"

#include "ccfile.h"

/***********************************************************************************************
 * Expansion_CS_Present -- Is the Counterstrike expansion available?                           *
 *                                                                                             *
 *                                                                                             *
 *                                                                                             *
 * INPUT:    Nothing                                                                           *
 *                                                                                             *
 * OUTPUT:   true if counterstrike installed                                                   *
 *                                                                                             *
 * WARNINGS: None                                                                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *    3/5/97 1:59PM ST : Fixed to check for EXPAND.MIX                                         *
 *=============================================================================================*/
bool Expansion_Present(void)
{
	CCFileClass file("EXPAND.DAT");
	return(file.Is_Available());
}


/// <summary>
/// Handles the expansion scenario selection.
/// This routine is called by the main menu when the player elects to start a new
/// scenario game. No expansion scenarios are offered, so the selection always succeeds.
/// </summary>
bool Expansion_Dialog(void)
{
	bool okval = true;
	return(okval);
}
