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

/* $Header: /CounterStrike/GAUGE.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : GAUGE.H                                                      *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic, Maria del Mar McCready Legg                   *
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

class GaugeClass : public ControlClass
{
		typedef ControlClass BASECLASS;

	public:

		GaugeClass(unsigned id, int x, int y, int w, int h);

		virtual int Draw_Me(int forced=false) override;
		virtual int Set_Maximum(int value);
		virtual int Set_Value(int value);
		virtual int Get_Value(void) const {return(CurValue);};
		virtual void Use_Thumb(int value) { HasThumb = value ? true : false; };

		virtual int Thumb_Pixels(void) { return(4);}

		/*
		**	If this gauge has a color to the left of the current setting, then this
		**	flag will be true.
		*/
		bool IsColorized;

	protected:

		/*
		**	If a thumb is desired, set to true.
		*/
		bool HasThumb;

		/*
		**	Is this a horizontal slider?
		*/
		bool IsHorizontal;

		int MaxValue;				// maximum value (in application units)
		int CurValue;				// index of 1st displayed string in box
										//  (in application units)

		/*
		**	This value records the difference between where the user clicked
		**	and the edge of the thumb, so that the thumb follows the mouse
		**	with the proper offset.
		*/
		int ClickDiff;

	protected:
		virtual void Draw_Thumb(void);
		virtual int  Action(unsigned flags, KeyNumType &key) override;
		virtual int  Pixel_To_Value(int pixel);
		virtual int  Value_To_Pixel(int value);
};



class TriColorGaugeClass : public GaugeClass
{
		typedef GaugeClass BASECLASS;

	public:
		TriColorGaugeClass(unsigned id, int x, int y, int w, int h);
		virtual int Draw_Me(int forced) override;
		virtual int Set_Red_Limit(int value);
		virtual int Set_Yellow_Limit(int value);

	protected:
		int RedLimit;				// maximum value for red
		int YellowLimit;			// maximum value for yellow
};
