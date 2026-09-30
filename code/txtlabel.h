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

/* $Header: /CounterStrike/TXTLABEL.H 1     3/03/97 10:26a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : TXTLABEL.H                                                   *
 *                                                                                             *
 *                   Programmer : Bill Randolph                                                *
 *                                                                                             *
 *                   Start Date : 02/06/95                                                     *
 *                                                                                             *
 *                  Last Update : February 6, 1995 [BR]                                        *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "gadget.h"

#include "dialog.hh"

class TextLabelClass : public GadgetClass
{
		typedef GadgetClass BASECLASS;

	public:
		/*
		**	Constructor/Destructor
		*/
		TextLabelClass(char *txt, int x, int y, int color, TextPrintType style);

		/*
		**	Overloaded draw routine
		*/
		virtual int Draw_Me(int forced = false) override;

		/*
		**	Sets the displayed text of the label
		*/
		virtual void Set_Text(char *txt) {Text = txt;};

		/*
		**	General-purpose data fields
		*/
		unsigned int UserData1;
		unsigned int UserData2;
		TextPrintType Style;
		char *Text;
		int Color;
		int PixWidth;
};
