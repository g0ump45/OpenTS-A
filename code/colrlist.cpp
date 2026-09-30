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

/* $Header: /CounterStrike/COLRLIST.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : COLRLIST.CPP                                                 *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 01/15/95                                                     *
 *                                                                                             *
 *                  Last Update : April 19, 1995 [BRR]                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   ColorListClass::Add_Item -- Adds an item to the list                                      *
 *   ColorListClass::ColorListClass -- Class constructor                                       *
 *   ColorListClass::Draw_Entry -- Draws one text line                                         *
 *   ColorListClass::Remove_Item -- Removes an item from the list                              *
 *   ColorListClass::Set_Selected_Style -- tells how to draw selected item                     *
 *   ColorListClass::~ColorListClass -- Class destructor                                       *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "colrlist.h"

#include "_convert.h"
#include "_surface.h"
#include "convert.h"
#include "dialog.h"
#include "dsurface.h"
#include "globals.h"
#include "scheme.h"
#include "vector.h"

#include "color.hh"


/***************************************************************************
 * ColorListClass::ColorListClass -- class constructor                     *
 *                                                                         *
 * INPUT:                                                                  *
 *      id               button ID                                         *
 *      x,y            upper-left corner, in pixels                        *
 *      w,h            width, height, in pixels                            *
 *      list            ptr to array of char strings to list               *
 *    flags          flags for mouse, style of listbox                     *
 *      up,down         pointers to shapes for up/down buttons             *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:          01/05/1995 MML : Created.                             *
 *=========================================================================*/
ColorListClass::ColorListClass (int id, int x, int y, int w, int h,
	TextPrintType flags, ShapeSet const * up, ShapeSet const * down) :
	BASECLASS (id, x, y, w, h, flags, up, down),
	Style(SELECT_HIGHLIGHT),
	SelectColor(0)
{
}


/***************************************************************************
 * ColorListClass::~ColorListClass -- Class destructor                     *
 *                                                                         *
 * INPUT:                                                                  *
 *      none.                                                              *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
ColorListClass::~ColorListClass(void)
{
	Colors.Clear();
	SelectColor = 0;
}


/***************************************************************************
 * ColorListClass::Add_Item -- Adds an item to the list                    *
 *                                                                         *
 * INPUT:                                                                  *
 *      text      text to add to list                                      *
 *      color      color for item                                          *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      position of item in the list                                       *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
int ColorListClass::Add_Item(char const * text, int color)
{
	Colors.Add(color);
	return(BASECLASS::Add_Item(text));
}


/***************************************************************************
 * ColorListClass::Add_Item -- Adds an item to the list                    *
 *                                                                         *
 * INPUT:                                                                  *
 *      text      text to add to list                                      *
 *      color      color for item                                          *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      position of item in the list                                       *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
int ColorListClass::Add_Item(int text, int color)
{
	Colors.Add(color);
	return(BASECLASS::Add_Item(text));
}


/***************************************************************************
 * ColorListClass::Remove_Item -- Removes an item from the list            *
 *                                                                         *
 * INPUT:                                                                  *
 *      text      ptr to item to remove                                    *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
void ColorListClass::Remove_Item(char const * text)
{
	int index = List.ID(text);
	if (index != -1) {
		Colors.Delete_Index(index);
		BASECLASS::Remove_Item(text);
	}
}


/// <summary>
/// Removes the specified entry from the list.
/// This routine will discard the color assigned to the entry as well, so that the color
/// list stays in step with the text list.
/// </summary>
void ColorListClass::Remove_Item(int index)
{
	if (index != -1) {
		Colors.Delete_Index(index);
		BASECLASS::Remove_Item(index);
	}
}

/***************************************************************************
 * ColorListClass::Set_Selected_Style -- tells how to draw selected item   *
 *                                                                         *
 * INPUT:                                                                  *
 *      style      style to draw                                           *
 *      color      color to draw the special style in; -1 = use item's color*
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
void ColorListClass::Set_Selected_Style(SelectStyleType style, int color)
{
	Style = style;
	SelectColor = color;
}


/***************************************************************************
 * ColorListClass::Draw_Entry -- Draws one text line                       *
 *                                                                         *
 * INPUT:                                                                  *
 *      index         index into List of item to draw                      *
 *      x,y         x,y coords to draw at                                  *
 *      width         maximum width allowed for text                       *
 *      selected      true = this item is selected                         *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   04/19/1995 BRR : Created.                                             *
 *=========================================================================*/
void ColorListClass::Draw_Entry(int index, int x, int y, int width, int selected)
{
	int color;

	/*
	**	Draw a non-selected item in its color
	*/
	if (!selected) {
		Conquer_Clip_Text_Print(List[index], *LogicalSurface, LogicalSurface->Get_Rect(), Point2D(x, y), ColorSchemes[Colors[index]], TBLACK, TextFlags, width, Tabs);
		return;
	}

	/*
	**	For selected items, choose the right color & style:
	*/
	if (SelectColor == NULL) {
		color = int(index);
	} else {
		color = SelectColor;
	}

	switch (Style) {
		/*
		**	NONE: Just print the string in its native color
		*/
		case SELECT_NORMAL:
			Conquer_Clip_Text_Print(List[index], *LogicalSurface, LogicalSurface->Get_Rect(), Point2D(x, y), ColorSchemes[Colors[index]], TBLACK,
				TextFlags, width, Tabs);
			break;

		/*
		**	HIGHLIGHT: Draw the string in the highlight color (SelectColor must
		**	be set)
		*/
		case SELECT_HIGHLIGHT:
			if (TextFlags & TPF_6PT_GRAD) {
				Conquer_Clip_Text_Print(List[index], *LogicalSurface, LogicalSurface->Get_Rect(), Point2D(x, y), ColorSchemes[color], TBLACK, TextPrintType(TextFlags | TPF_BRIGHT_COLOR), width, Tabs);
			} else {
				Conquer_Clip_Text_Print(List[index], *LogicalSurface, LogicalSurface->Get_Rect(), Point2D(x, y), ColorSchemes[color], TBLACK, TextFlags, width, Tabs);
			}
			break;

		/*
		**	BOX: Draw a box around the item in the current select color
		*/
		case SELECT_BOX:
			LogicalSurface->Draw_Rect (Rect(x, y, x + width - 2, y + LineHeight - 2), NormalDrawer->Convert_Pixel(ColorSchemes[color]->Color));
			Conquer_Clip_Text_Print(List[index], *LogicalSurface, LogicalSurface->Get_Rect(), Point2D(x, y), ColorSchemes[Colors[index]], TBLACK, TextFlags, width, Tabs);
			break;

		/*
		**	BAR: draw a color bar under the text
		*/
		case SELECT_BAR:
			if (TextFlags & TPF_6PT_GRAD) {
				LogicalSurface->Fill_Rect(Rect(x, y, width, LineHeight), NormalDrawer->Convert_Pixel(ColorSchemes[color]->Color));
				Conquer_Clip_Text_Print(List[index], *LogicalSurface, LogicalSurface->Get_Rect(), Point2D(x, y), ColorSchemes[Colors[index]], TBLACK, TextPrintType(TextFlags | TPF_BRIGHT_COLOR), width, Tabs);
			} else {
				LogicalSurface->Fill_Rect(Rect(x, y, width - 1, LineHeight - 1), NormalDrawer->Convert_Pixel(ColorSchemes[color]->Color));
				Conquer_Clip_Text_Print(List[index], *LogicalSurface, LogicalSurface->Get_Rect(), Point2D(x, y), ColorSchemes[Colors[index]], TBLACK, TextFlags, width, Tabs);
			}
			break;

		/*
		**	INVERT: Draw text as the background color on foreground color
		*/
		case SELECT_INVERT:
			LogicalSurface->Fill_Rect (Rect(x, y, width, LineHeight), NormalDrawer->Convert_Pixel(ColorSchemes[Colors[index]]->Color));
			break;
	}
}
