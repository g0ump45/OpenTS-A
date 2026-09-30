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

/* $Header: /CounterStrike/BAR.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : BAR.CPP                                                      *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 08/16/96                                                     *
 *                                                                                             *
 *                  Last Update : August 16, 1996 [JLB]                                        *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   ProgressBarClass::Is_Horizontal -- Determines if the bargraph is horizontal or not.       *
 *   ProgressBarClass::Outline -- Draw an outline around the bargraph if supposed to.          *
 *   ProgressBarClass::ProgressBarClass -- Constructor for the bargraph object.                *
 *   ProgressBarClass::Redraw -- Redraw the bargraph.                                          *
 *   ProgressBarClass::Set_Limit -- Set the logic tracking value.                              *
 *   ProgressBarClass::Update -- Update the value and redraw as necessary.                     *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "bar.h"

#include "_convert.h"
#include "_surface.h"
#include "_xmouse.h"
#include "convert.h"
#include "dsurface.h"
#include "xmouse.h"


/***********************************************************************************************
 * ProgressBarClass::ProgressBarClass -- Constructor for the bargraph object.                  *
 *                                                                                             *
 *    This is the constructor for the bargraph object. It establishes the dimensions and       *
 *    coordinate of the bargraph as well as the colors it will use when drawn.                 *
 *                                                                                             *
 * INPUT:   w,y      -- Pixel coordinate of the upper left corner of the bargraph.             *
 *                                                                                             *
 *          width,height   -- Dimensions of the bargraph.                                      *
 *                                                                                             *
 *          forecolor   -- The color to use for the filled portion of the bargraph.            *
 *                                                                                             *
 *          backcolor   -- The color to use for the non-filled portion of the bargraph.        *
 *                                                                                             *
 *          bordercolor -- Optional border color. If not zero, then the bargraph will be       *
 *                         outlined with this color.                                           *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/16/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
ProgressBarClass::ProgressBarClass(int x, int y, int width, int height, int forecolor, int backcolor, int bordercolor) :
	X(x),
	Y(y),
	Width(width),
	Height(height),
	BarColor(forecolor),
	BackColor(backcolor),
	BorderColor(bordercolor),
	CurrentValue(0),
	LastDisplayCurrent(0),
	IsDrawn(false)
{
}


/***********************************************************************************************
 * ProgressBarClass::Is_Horizontal -- Determines if the bargraph is horizontal or not.         *
 *                                                                                             *
 *    If the bargraph is oriented horizontally, then this function will return TRUE.           *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  bool; Is this bargraph horizontal?                                                 *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/16/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool ProgressBarClass::Is_Horizontal(void) const
{
	if (Width > Height) return(true);
	return(false);
}


/***********************************************************************************************
 * ProgressBarClass::Update -- Update the value and redraw as necessary.                       *
 *                                                                                             *
 *    This will update the value of the bargraph to the fill ratio specified and then          *
 *    redraw it if required. Very small changes to the bargraph value might not result in a    *
 *    visual change.                                                                           *
 *                                                                                             *
 * INPUT:   value -- The new value to assign to this bargraph.                                 *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   bool; Did this update result in a redraw?                                       *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/16/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool ProgressBarClass::Update(double value)
{
	CurrentValue = value;

	if (!IsDrawn || value - LastDisplayCurrent >= .1) {
		Redraw();
		return(true);
	}
	return(false);
}


/***********************************************************************************************
 * ProgressBarClass::Outline -- Draw an outline around the bargraph if supposed to.            *
 *                                                                                             *
 *    This routine will draw a border around the bargraph if this bargraph has a color         *
 *    specified for the border.                                                                *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/16/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void ProgressBarClass::Outline(void) const
{
	if (Is_Outlined()) {
		LogicalSurface->Draw_Rect(Rect(X, Y, Width, Height), NormalDrawer->Convert_Pixel(BorderColor));
	}
}


/***********************************************************************************************
 * ProgressBarClass::Redraw -- Redraw the bargraph.                                            *
 *                                                                                             *
 *    This will redraw the entire bargraph.                                                    *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/16/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void ProgressBarClass::Redraw(void) const
{
	Hide_Mouse();

	Outline();

	/*
	**	Determine the inner dimensions of the bargraph. This will be
	**	somewhat smaller than indicated if it has a border.
	*/
	int x = X;
	int y = Y;
	int w = Width;
	int h = Height;
	if (Is_Outlined()) {
		x += 1;
		y += 1;
		w -= 2;
		h -= 2;
	}

	/*
	**	The working "length" of the bargraph is dependant on whether the
	**	bargraph is horizontal or vertical.
	*/
	int size = Is_Horizontal() ? w : h;

	/*
	**	Determine the number of pixels to fill in the bargraph depending on the
	**	size of the internal value. The larger the internal value the more
	**	filled the bargraph becomes.
	*/
	int fill = CurrentValue * size;

	/*
	**	Draw the filled portion of the bargraph if there is any pixels to draw.
	*/
	if (fill > 0) {
		if (Is_Horizontal()) {
			LogicalSurface->Fill_Rect(Rect(x, y, fill, h), NormalDrawer->Convert_Pixel(BarColor));
		} else {
			LogicalSurface->Fill_Rect(Rect(x, y+fill, w, h), NormalDrawer->Convert_Pixel(BarColor));
		}
	}

	/*
	**	Draw the unfilled portion of the bargraph if there are any pixels to
	**	draw of it.
	*/
	if (w-fill > 0) {
		if (Is_Horizontal()) {
			LogicalSurface->Fill_Rect(Rect(x+fill, y, w, h), NormalDrawer->Convert_Pixel(BackColor));
		} else {
			LogicalSurface->Fill_Rect(Rect(x, y, w, fill-1), NormalDrawer->Convert_Pixel(BackColor));
		}
	}

	Show_Mouse();

	ProgressBarClass * bar = (ProgressBarClass *)this;
	bar->LastDisplayCurrent = CurrentValue;
	bar->IsDrawn = true;
}
