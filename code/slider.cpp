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

/* $Header: /CounterStrike/SLIDER.CPP 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : SLIDER.CPP                                                   *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 01/15/95                                                     *
 *                                                                                             *
 *                  Last Update : September 20, 1995 [JLB]                                     *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   SliderClass::Action -- Handles input processing for the slider.                           *
 *   SliderClass::Bump -- Bumps the slider one "thumb size" up or down.                        *
 *   SliderClass::Recalc_Thumb -- Recalculates the thumb pixel size and starting offset.       *
 *   SliderClass::Set_Maximum -- Sets the maximum value for this slider.                       *
 *   SliderClass::Set_Thumb_Size -- Sets the size of the thumb in "slider units".              *
 *   SliderClass::Set_Value -- Sets the current thumb position for the slider.                 *
 *   SliderClass::SliderClass -- Normal constructor for a slider (with thumb) gadget.          *
 *   SliderClass::Step -- Steps the slider one value up or down.                               *
 *   SliderClass::Draw_Thumb -- Draws the "thumb" for this slider.                             *
 *   SliderClass::~SliderClass -- Destructor for slider object.                                *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "slider.h"

#include "_mixfile.h"
#include "control.h"
#include "dialog.h"
#include "gauge.h"
#include "mixfile.h"
#include "shapebtn.h"
#include "xmouse.h"

#include "dialog.hh"

#include <algorithm>


/***********************************************************************************************
 * SliderClass::SliderClass -- Normal constructor for a slider (with thumb) gadget.            *
 *                                                                                             *
 *    This is the normal constructor for the slider gadget.                                    *
 *                                                                                             *
 * INPUT:   id    -- The ID number to assign to this gadget.                                   *
 *          x,y   -- The pixel coordinate of the upper left corner for this gadget.            *
 *          w,h   -- The width and height of the slider gadget. The slider automatically       *
 *                   adapts for horizontal or vertical operation depending on which of these   *
 *                   dimensions is greater.                                                    *
 * OUTPUT:     none                                                                            *
 * WARNINGS:   none                                                                            *
 * HISTORY:    01/15/1995 JLB : Created.                                                       *
 *=============================================================================================*/
SliderClass::SliderClass(unsigned id, int x, int y, int w, int h, int belong_to_list)
	: BASECLASS(id, x, y, w, h)
{
	BelongToList = belong_to_list ? true : false;

	PlusGadget = 0;
	MinusGadget = 0;
	if (!BelongToList) {
		PlusGadget  = new ShapeButtonClass(id, (const ShapeSet *)MFCD::Retrieve("BTN-PLUS.SHP"), X+Width+2, Y);
		MinusGadget = new ShapeButtonClass(id, (const ShapeSet *)MFCD::Retrieve("BTN-MINS.SHP"), X-6, Y);

		if (PlusGadget) {
			PlusGadget->Make_Peer(*this);
			PlusGadget->Add(*this);
			PlusGadget->Flag_To_Redraw();
		}
		if (MinusGadget) {
			MinusGadget->Make_Peer(*this);
			MinusGadget->Add(*this);
			MinusGadget->Flag_To_Redraw();
		}
	}
	Set_Thumb_Size(1);
	Recalc_Thumb();

	/*
	**	Gauges have at least 2 colors, but sliders should only have one.
	*/
	IsColorized = 0;
}


/***********************************************************************************************
 * SliderClass::~SliderClass -- Destructor for slider object.                                  *
 *                                                                                             *
 *    This cleans up the slider object in preparation for deletion.                            *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/20/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
SliderClass::~SliderClass(void)
{
	if (PlusGadget) {
		delete PlusGadget;
		PlusGadget = 0;
	}
	if (MinusGadget) {
		delete MinusGadget;
		MinusGadget = 0;
	}
}


/***********************************************************************************************
 * SliderClass::Set_Maximum -- Sets the maximum value for this slider.                         *
 *                                                                                             *
 *    This sets the maximum value that the slider can be set at. The maximum value controls    *
 *    the size of the thumb and the resolution of the thumb's movement.                        *
 *                                                                                             *
 * INPUT:   value -- The value to set for the slider's maximum.                                *
 * OUTPUT:  bool; Was the maximum value changed? A false indicates a set to the value it       *
 *                is currently set to already.                                                 *
 * WARNINGS:   none                                                                            *
 * HISTORY:    01/15/1995 JLB : Created.                                                       *
 *=============================================================================================*/
int SliderClass::Set_Maximum(int value)
{
	if (BASECLASS::Set_Maximum(value)) {
		Recalc_Thumb();
		return(true);
	}
	return(false);
}


/***********************************************************************************************
 * SliderClass::Set_Thumb_Size -- Sets the size of the thumb in "slider units".                *
 *                                                                                             *
 *    This routine will set the size of the thumb as it relates to the maximum value the       *
 *    slider can achieve. This serves to display a proportionally sized thumb as well as       *
 *    control how the slider "bumps" up or down.                                               *
 *                                                                                             *
 * INPUT:   value -- The new value of the thumb. It should never be larger than the slider     *
 *                   maximum.                                                                  *
 * OUTPUT:     none                                                                            *
 * WARNINGS:   none                                                                            *
 * HISTORY:    01/15/1995 JLB : Created.                                                       *
 *=============================================================================================*/
void SliderClass::Set_Thumb_Size(int value)
{
	Thumb = std::min(value, MaxValue);
	Thumb = std::max(Thumb, 1);
	Flag_To_Redraw();
	Recalc_Thumb();
}


/***********************************************************************************************
 * SliderClass::Set_Value -- Sets the current thumb position for the slider.                   *
 *                                                                                             *
 *    This routine will set the thumb position for the slider.                                 *
 *                                                                                             *
 * INPUT:   value -- The position to set the slider. This position is relative to the maximum  *
 *                   value for the slider.                                                     *
 *                                                                                             *
 * OUTPUT:  bool; Was the slider thumb position changed at all?                                *
 * WARNINGS:  none                                                                             *
 * HISTORY:   01/15/1995 JLB : Created.                                                        *
 *=============================================================================================*/
int SliderClass::Set_Value(int value)
{
	value = std::min(value, MaxValue-Thumb);

	if (BASECLASS::Set_Value(value)) {
		Recalc_Thumb();
		return(true);
	}
	return(false);
}


/***********************************************************************************************
 * SliderClass::Recalc_Thumb -- Recalculates the thumb pixel size and starting offset.         *
 *                                                                                             *
 *    This takes the current thumb logical size and starting value and calculates the pixel    *
 *    size and starting offset accordingly. This function should be called whenever one of     *
 *    these elements has changed.                                                              *
 *                                                                                             *
 * INPUT:      none                                                                            *
 * OUTPUT:     none                                                                            *
 * WARNINGS:   none                                                                            *
 * HISTORY:    01/15/1995 JLB : Created.                                                       *
 *=============================================================================================*/
void SliderClass::Recalc_Thumb(void)
{
	int length = IsHorizontal ? Width : Height;
	int size   = int(length * ((double)Thumb / MaxValue));
	ThumbSize  = std::max(size, 4);
	int start  = int(length * ((double)CurValue / MaxValue));
	ThumbStart = std::min(start, length-ThumbSize);
}


/***********************************************************************************************
 * SliderClass::Action -- Handles input processing for the slider.                             *
 *                                                                                             *
 *    This routine is called when a qualifying input event has occurred. This routine will     *
 *    process that event and make any adjustments to the slider as necessary.                  *
 *                                                                                             *
 * INPUT:   flags -- Flag bits that tell the input event that caused this function to          *
 *                   be called.                                                                *
 *          key   -- Reference to the key that caused the input event.                         *
 * OUTPUT:  bool; Was the event consumed and further processing of the gadget list should be   *
 *                aborted?                                                                     *
 * WARNINGS:   none                                                                            *
 * HISTORY:    01/15/1995 JLB : Created.                                                       *
 *=============================================================================================*/
int SliderClass::Action(unsigned flags, KeyNumType &key)
{
	/*
	**	Handle the mouse click in a special way. If the click was not on the thumb, then
	**	jump the thumb position one "step" in the appropriate direction. Otherwise, let normal
	**	processing take place -- the slider then "sticks" and the thumb moves according to
	**	mouse position.
	*/
	if (flags & LEFTPRESS) {
		int mouse;		// Mouse pixel position.
		int edge;		// Edge of slider.

		if (IsHorizontal) {
			mouse = Get_Mouse_X();
			edge = X;
		} else {
			mouse = Get_Mouse_Y();
			edge = Y;
		}
		edge += 1;

		/*
		**	Clicking outside the thumb: invoke parent's Action to process flags etc,
		**	but turn off the event & return true so processing stops at this button.
		*/
		if (mouse < edge+ThumbStart) {
			Bump(true);
			BASECLASS::Action(0, key);
			key = KN_NONE;
			return(true);
		} else {
			if (mouse > edge+ThumbStart+ThumbSize) {
				Bump(false);
				BASECLASS::Action(0, key);
				key = KN_NONE;
				return(true);
			} else {
				BASECLASS::Action(flags, key);
				key = KN_NONE;
				return(true);
			}
		}
	}

	/*
	**	CHANGE GAUGECLASS::ACTION -- REMOVE (LEFTRELEASE) FROM IF STMT
	*/
	return(BASECLASS::Action(flags, key));
}


/***********************************************************************************************
 * SliderClass::Bump -- Bumps the slider one "thumb size" up or down.                          *
 *                                                                                             *
 *    This support function will bump the slider one "step" or the size of the thumb up or     *
 *    down as specified. It is typically called when the slider is clicked outside of the      *
 *    thumb region but still inside of the slider.                                             *
 *                                                                                             *
 * INPUT:   up -- Should the bump be to increase the current position?                         *
 * OUTPUT:  bool; Was the slider changed at all? A false indicates that the slider is already  *
 *                at one end or the other.                                                     *
 * WARNINGS:   none                                                                            *
 * HISTORY:    01/15/1995 JLB : Created.                                                       *
 *=============================================================================================*/
int SliderClass::Bump(int up)
{
	if (up) {
		return(Set_Value(CurValue - Thumb));
	}
	return(Set_Value(CurValue + Thumb));
}


/***********************************************************************************************
 * SliderClass::Step -- Steps the slider one value up or down.                                 *
 *                                                                                             *
 *    This routine will move the slider thumb one step in the direction specified.             *
 *                                                                                             *
 * INPUT:   up -- Should the step be up (i.e., forward)?                                       *
 * OUTPUT:  bool; Was the slider changed at all? A false indicates that the slider is already  *
 *                at one end or the other.                                                     *
 * WARNINGS:   none                                                                            *
 * HISTORY:    01/15/1995 JLB : Created.                                                       *
 *=============================================================================================*/
int SliderClass::Step(int up)
{
	if (up) {
		return(Set_Value(CurValue - 1));
	}
	return(Set_Value(CurValue + 1));
}


/***********************************************************************************************
 * SliderClass::Draw_Thumb -- Draws the "thumb" for this slider.                               *
 *                                                                                             *
 *    This will draw the thumb graphic for this slider. Sometimes the thumb requires special   *
 *    drawing, thus the need for this function separate from the normal Draw_Me function.      *
 *                                                                                             *
 * INPUT:   none                                                                               *
 * OUTPUT:  none                                                                               *
 * WARNINGS:   The mouse is guaranteed to be hidden when this routine is called.               *
 * HISTORY:    01/16/1995 JLB : Created.                                                       *
 *=============================================================================================*/
void SliderClass::Draw_Thumb(void)
{
	if (IsHorizontal) {
		Draw_Box(Rect(X+ThumbStart, Y, ThumbSize, Height), BOXSTYLE_RAISED, true);
	} else {
		Draw_Box(Rect(X, Y+ThumbStart, Width, ThumbSize), BOXSTYLE_RAISED, true);
	}
}


/***********************************************************************************************
 * SliderClass::Draw_Me -- Draws the body of the gauge.                                        *
 *                                                                                             *
 *    This routine will draw the body of the gauge if necessary.                               *
 *                                                                                             *
 * INPUT:   forced   -- Should the gauge be redrawn regardless of the current redraw flag?     *
 * OUTPUT:  bool; Was the gauge redrawn?                                                       *
 * WARNINGS:   none                                                                            *
 * HISTORY:    01/16/1995 JLB : Created.                                                       *
 *=============================================================================================*/
int SliderClass::Draw_Me(int forced)
{
	if (BelongToList) {
		if (ControlClass::Draw_Me(forced)) {

			/*
			**	Draw the body & set text color.
			*/
			Draw_Box (Rect(X, Y, Width, Height), BOXSTYLE_DOWN, true);
			Draw_Thumb();

			return(true);
		}
	}

	/*
	**	If it does not belong to a listbox...
	*/
	return(BASECLASS::Draw_Me(forced));
}


/***********************************************************************************************
 * SliderClass::Peer_To_Peer -- A peer gadget was touched -- make adjustments.                 *
 *                                                                                             *
 *    This routine is called when one of the peer gadgets (the scroll arrows or the slider)    *
 *    was touched in some fashion. This routine will sort out whom and why and then make       *
 *    any necessary adjustments to the list box.                                               *
 *                                                                                             *
 * INPUT:   flags    -- The event flags that affected the peer gadget.                         *
 *          key      -- The key value at the time of the event.                                *
 *          whom     -- Which gadget is being touched.                                         *
 * OUTPUT:  none                                                                               *
 * WARNINGS:   none                                                                            *
 * HISTORY:    01/16/1995 JLB : Created.                                                       *
 *=============================================================================================*/
void SliderClass::Peer_To_Peer(unsigned flags, KeyNumType & , ControlClass & whom)
{
	if (flags & LEFTRELEASE) {
		if (&whom == PlusGadget) {
			Step(false);
		}
		if (&whom == MinusGadget) {
			Step(true);
		}
	}
}
