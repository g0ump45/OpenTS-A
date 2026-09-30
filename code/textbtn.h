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

/* $Header: /CounterStrike/TEXTBTN.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : TEXTBTN.H                                                    *
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

#include "toggle.h"

#include "dialog.hh"


class TextButtonClass : public ToggleClass
{
		typedef ToggleClass BASECLASS;

	public:
		TextButtonClass(void);
		TextButtonClass(unsigned id, char const * text, TextPrintType style, int x, int y, int w=-1, int h=-1, bool blackborder=false, bool nobackground=false);
		TextButtonClass(unsigned id, int text, TextPrintType style, int x, int y, int w=-1, int h=-1, bool blackborder=false, bool nobackground=false);
		virtual int Draw_Me(int forced=false) override;
		virtual void Set_Text(char const *text, bool resize = false);
		virtual void Set_Text(int text, bool resize = false);
		virtual void Set_Style (TextPrintType style) {PrintFlags = style;}

	protected:

		virtual void Draw_Background(void);
		virtual void Draw_Text(char const * text);

		bool IsBlackBorder;

		/*
		 * If this button is to be drawn as bare text, with no box or border behind it, then
		 * this flag will be true.
		 */
		bool IsNoBackground;

		/*
		**	This points to a constant string that is used for the button's text.
		*/
		char const * String;

		/*
		**	This is the print flags to use when rendering this button's text.
		*/
		TextPrintType PrintFlags;
};
