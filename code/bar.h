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

/* $Header: /CounterStrike/BAR.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : BAR.H                                                        *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 08/16/96                                                     *
 *                                                                                             *
 *                  Last Update : August 16, 1996 [JLB]                                        *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once


/*
**	This is a manager for a progress (or other) bargraph. Such a graph consists of a fill
**	and a background region. The fill percentage of the bargraph is controlled by an
**	update value. The bargraph can be optionally outlined.
*/
class ProgressBarClass
{
	public:
		ProgressBarClass(int x, int y, int width, int height, int forecolor, int backcolor, int bordercolor=0);

		bool Update(double value);
		void Redraw(void) const;

	private:

		void Outline(void) const;
		bool Is_Horizontal(void) const;
		bool Is_Outlined(void) const {return(BorderColor != 0);}

		/*
		**	This is the upper left coordinates of the bargraph.
		*/
		int X,Y;

		/*
		**	This is the dimensions of the bargraph.
		*/
		int Width, Height;

		/*
		**	These are the colors to use when drawing the progress bar.
		*/
		int BarColor;
		int BackColor;
		int BorderColor;

		/*
		**	This is the current value of the bargraph.
		*/
		double CurrentValue;

		/*
		**	This is the current value as of the last time the bargraph was rendered.
		*/
		double LastDisplayCurrent;

		/*
		**	If the bargraph has been drawn at least once, then this flag will
		**	be true.
		*/
		bool IsDrawn;
};
