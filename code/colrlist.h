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

/* $Header: /CounterStrike/COLRLIST.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : COLRLIST.H                                                   *
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

#include "list.h"
#include "vector.h"

#include "scheme.hh"

class ShapeSet;

/***************************************************************************
**	This class adds the ability for every list item to have a different color.
*/
class ColorListClass : public ListClass
{
		typedef ListClass BASECLASS;

	public:
		/*********************************************************************
		**	These enums are the ways a selected item can be drawn
		*/
		//lint -esym(578,SELECT_NONE)
		enum SelectStyleType {
			SELECT_NORMAL,				// selected items aren't drawn differently
			SELECT_HIGHLIGHT,			// item is highlighted
			SELECT_BOX,					// draw a box around the item
			SELECT_BAR,					// draw a bar behind the item
			SELECT_INVERT				// draw the string inverted
		};

		ColorListClass(int id, int x, int y, int w, int h, TextPrintType flags, ShapeSet const * up, ShapeSet const * down);
		virtual ~ColorListClass(void) override;

		virtual int  Add_Item(char const * text, int color = 0);
		virtual int  Add_Item(int text, int color = 0);
		virtual void Remove_Item(char const * text) override;
		virtual void Remove_Item(int) override;

		virtual void Set_Selected_Style(SelectStyleType style, int color = 0);

		virtual int Add_Item(char const * text) override { return(Add_Item(text, 0)); }
		virtual int Add_Item(int text) override { return(Add_Item(text, 0)); }

		/*
		**	This is the list of colors for each item.
		*/
		DynamicVectorClass<int> Colors;

	protected:
		virtual void Draw_Entry(int index, int x, int y, int width, int selected) override;

		/*
		**	This tells how to draw the selected item.
		*/
		SelectStyleType Style;
		int SelectColor;

};
