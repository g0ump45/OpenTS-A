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

/* $Header: /CounterStrike/CHECKBOX.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : CHECKBOX.CPP                                                 *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 05/26/95                                                     *
 *                                                                                             *
 *                  Last Update : July 6, 1996 [JLB]                                           *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   CheckBoxClass::Action -- Handles a button action on a checkbox object.                    *
 *   CheckBoxClass::Draw_Me -- Draws the checkbox imagery.                                     *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "checkbox.h"

#include "_convert.h"
#include "_surface.h"
#include "convert.h"
#include "dialog.h"
#include "dsurface.h"
#include "xmouse.h"

#include "color.hh"


/***********************************************************************************************
 * CheckBoxClass::Draw_Me -- Draws the checkbox imagery.                                       *
 *                                                                                             *
 *    This routine will draw the checkbox either filled or empty as necessary.                 *
 *                                                                                             *
 * INPUT:   forced   -- Should the check box be drawn even if it doesn't think it needs to?    *
 *                                                                                             *
 * OUTPUT:  Was the check box rendered?                                                        *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/01/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int CheckBoxClass::Draw_Me(int forced)
{
	if (BASECLASS::Draw_Me(forced)) {

		Hide_Mouse();
		Draw_Box(Rect(X, Y, Width, Height), BOXSTYLE_DOWN, false);
		LogicalSurface->Fill_Rect(Rect(X+1, Y+1, Width-1, Height-1), NormalDrawer->Convert_Pixel(GREY));
		if (IsOn) {
			LogicalSurface->Fill_Rect(Rect(X+1, Y+1, Width-1, Height-1), NormalDrawer->Convert_Pixel(LTGREEN));
		}
		Show_Mouse();
		return(true);
	}
	return(false);
}


/***********************************************************************************************
 * CheckBoxClass::Action -- Handles a button action on a checkbox object.                      *
 *                                                                                             *
 *    This routine will detect if the mouse has been clicked on the checkbox object. If so,    *
 *    the check box state will be toggled.                                                     *
 *                                                                                             *
 * INPUT:   flags -- The event flags that resulted in this routine being called.               *
 *                                                                                             *
 *          key   -- The key that resulted in this routine being called.                       *
 *                                                                                             *
 * OUTPUT:  bool; Should normal processing occur?                                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int CheckBoxClass::Action(unsigned flags, KeyNumType & key)
{
	if (flags & LEFTRELEASE) {
		if (IsOn) {
			Turn_Off();
		} else {
			Turn_On();
		}
	}
	return(BASECLASS::Action(flags, key));
}
