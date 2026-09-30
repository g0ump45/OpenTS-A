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

/* $Header: /CounterStrike/SLIDER.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : SLIDER.H                                                     *
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

#include "gauge.h"

class ShapeButtonClass;

/***************************************************************************
 * SliderClass -- Like a Windows ListBox structure                         *
 *                                                                         *
 * INPUT:      int id-- id of gadget                                       *
 *               int x -- x position of gadget                             *
 *               int y -- y position of gadget                             *
 *               int w -- width of gadget                                  *
 *               int h -- height of gadget                                 *
 *               int belong_to_list -- does this slider go with a listclass?*
 *                                                                         *
 * OUTPUT:     none.                                                       *
 * WARNINGS:                                                               *
 * HISTORY:    01/03/1995 MML : Created.                                   *
 *=========================================================================*/
class SliderClass : public GaugeClass
{
		typedef GaugeClass BASECLASS;

	public:
		SliderClass(unsigned id, int x, int y, int w, int h, int belong_to_list=false);
		virtual ~SliderClass(void) override;

		virtual void Set_Thumb_Size(int value);
		virtual int  Set_Maximum(int value) override;
		virtual int  Set_Value(int) override;
		virtual int  Bump(int up);
		virtual int  Step(int up);
		virtual int  Draw_Me(int forced) override;
		virtual void Peer_To_Peer(unsigned flags, KeyNumType & key, ControlClass & whom) override;

		virtual int Thumb_Pixels(void) override { return(ThumbSize);}

	protected:

		/*
		**	If the slider bar has been created, these point to the respective gadgets
		**	that it is composed of.
		*/
		ShapeButtonClass * PlusGadget;
		ShapeButtonClass * MinusGadget;

		/*
		**	If I belong to a listbox, I have to draw myself differently...
		**/
		bool BelongToList;

		/*
		**	This is the logical size of the thumb. This value is used when drawing
		**	the thumb imagery. It is also the amount that is bumped when the
		**	Bump() function is called.  (This value is in application units.)
		*/
		int Thumb;

		/*
		**	This is the current thumb pixel size and starting offset from beginning
		**	of slider region.  (These values are in pixels.)
		*/
		int ThumbSize;
		int ThumbStart;			// x or y position for the thumb

		virtual int  Action(unsigned flags, KeyNumType &key) override;
		virtual void Draw_Thumb(void) override;

	private:
		void Recalc_Thumb(void);
};
