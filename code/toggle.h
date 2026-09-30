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

/* $Header: /CounterStrike/TOGGLE.H 1     3/03/97 10:26a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : TOGGLE.H                                                     *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 01/15/95                                                     *
 *                                                                                             *
 *                  Last Update : January 15, 1995 [JLB]                                       *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "control.h"

/*
**	This class handles gadgets that behave like the Windows buttons. That is, once the mouse
**	button is clicked over them, they capture the focus until the mouse button is released.
**	They have a different imagery for the pressed and released states. They only recognize
**	a valid selection when the mouse button is release while over the button.
*/
class ToggleClass : public ControlClass
{
		typedef ControlClass BASECLASS;

	public:
		ToggleClass(unsigned id, int x, int y, int w, int h);
		void Turn_On(void);
		void Turn_Off(void);

		/*
		**	Is this button in a pressed down state? This occurs when the mouse is clicked on the
		**	button and the mouse is still being held down.
		*/
		bool IsPressed;

		/*
		**	This is the button on/off state. Sometimes a button that is "on" has a different
		**	imagery than one that is "off". If the on/off state is not necessary, then just
		**	ignore this flag.
		*/
		bool IsOn;

		/*
		**	If this button can be turned "on" or "off", then this flag should be set to
		**	true. Sometimes a button needs to display its on/off state. In the render routine,
		**	examine the IsOn flag and display accordingly. If this flag is false, then the
		**	IsOn flag will not be changed, regardless of button clicking.
		*/
		bool IsToggleType;

	protected:

		virtual int Action(unsigned flags, KeyNumType &key) override;
};
