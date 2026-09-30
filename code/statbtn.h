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

/* $Header: /CounterStrike/STATBTN.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : STATBTN.H                                                    *
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

#include "buff.h"
#include "gadget.h"

#include "dialog.hh"

class StaticButtonClass : public GadgetClass
{
		typedef GadgetClass BASECLASS;

	public:
		StaticButtonClass(void);
		StaticButtonClass(unsigned id, char const * text, TextPrintType style, int x, int y, int w=-1, int h=-1);
		virtual ~StaticButtonClass(void) override;
		virtual int Draw_Me(int forced=false) override;
		virtual void Set_Text(char const * text, bool resize = false);

	protected:

		virtual void Draw_Background(void);
		virtual void Draw_Text(char const * text);

		/*
		**	If a background is to be preserved for this button, then this will point to
		**	a buffer that holds a pristine background image.
		*/
		Buffer Background;

		/*
		**	This points to a copy of the string that is used for the button's text.
		*/
		char * String;

		/*
		**	This is the print flags to use when rendering this button's text.
		*/
		TextPrintType PrintFlags;
};
