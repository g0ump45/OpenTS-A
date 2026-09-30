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

/* $Header: /CounterStrike/DIAL8.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : DIAL8.CPP                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 07/05/96                                                     *
 *                                                                                             *
 *                  Last Update : July 5, 1996 [JLB]                                           *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Dial8Class::Action -- action routine for Dial8Class                                       *
 *   Dial8Class::Dial8Class -- constructor for the facing dial                                 *
 *   Dial8Class::Draw_Me -- render routine for Dial8Class                                      *
 *   Dial8Class::Get_Direction -- retrieves direction (0-255) of dial                          *
 *   Dial8Class::Set_Direction -- sets current direction (0-255) of dial                       *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "dial8.h"

#include "_convert.h"
#include "_surface.h"
#include "convert.h"
#include "dialog.h"
#include "inline.h"
#include "scheme.h"
#include "surface.h"
#include "vector.h"


/***************************************************************************
 * Dial8Class::Dial8Class -- constructor for the facing dial               *
 *                                                                         *
 * INPUT:                                                                  *
 *      id            button ID                                            *
 *      x,y,w,h      dimensions in window-relative pixels                  *
 *      dir         numerical initial facing value (0-255); this is the    *
 *                  value returned by WWLIB Desired_Facing8()              *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   11/16/1994 BR : Created.                                              *
 *=========================================================================*/
Dial8Class::Dial8Class(int id, int x, int y, int w, int h, Dir256 dir) :
	BASECLASS(id, x, y, w, h, LEFTPRESS | LEFTHELD | LEFTRELEASE, true)
{
	/*
	**	Center coordinates.
	*/
	FaceX = X + (Width / 2);
	FaceY = Y + (Height / 2);

	/*
	**	Init directions.
	*/
	Direction = dir;                // 0 - 255
	Facing = Dir_Facing(Direction); // 0 - 7
	OldFacing = Facing;             // 0 - 7

	/*
	**	Compute the drawing dimensions:  a 45-degree angle intersects a unity-
	**	radius circle at (.707,.707). Make the decorations 8/10 of the radius,
	**	and the line extend to 6/10 of the radius. Use Width/2 for x-radius,
	**	Height/2 for y-radius.
	*/
	FacePoint[FACING_N][0] = FaceX;
	FacePoint[FACING_N][1] = FaceY - (h * 8 / 2) / 10;

	FacePoint[FACING_NE][0] = FaceX + (w * 7 * 8 / 2) / 100;
	FacePoint[FACING_NE][1] = FaceY - (h * 7 * 8 / 2) / 100;

	FacePoint[FACING_E][0] = FaceX + (w * 8 / 2) / 10;
	FacePoint[FACING_E][1] = FaceY;

	FacePoint[FACING_SE][0] = FaceX + (w * 7 * 8 / 2) / 100;
	FacePoint[FACING_SE][1] = FaceY + (h * 7 * 8 / 2) / 100;

	FacePoint[FACING_S][0] = FaceX;
	FacePoint[FACING_S][1] = FaceY + (h * 8 / 2) / 10;

	FacePoint[FACING_SW][0] = FaceX - (w * 7 * 8 / 2) / 100;
	FacePoint[FACING_SW][1] = FaceY + (h * 7 * 8 / 2) / 100;

	FacePoint[FACING_W][0] = FaceX - (w * 8 / 2) / 10;
	FacePoint[FACING_W][1] = FaceY;

	FacePoint[FACING_NW][0] = FaceX - (w * 7 * 8 / 2) / 100;
	FacePoint[FACING_NW][1] = FaceY - (h * 7 * 8 / 2) / 100;

	FaceLine[FACING_N][0] = FaceX;
	FaceLine[FACING_N][1] = FaceY - (h * 6 / 2) / 10;

	FaceLine[FACING_NE][0] = FaceX + (w * 7 * 6 / 2) / 100;
	FaceLine[FACING_NE][1] = FaceY - (h * 7 * 6 / 2) / 100;

	FaceLine[FACING_E][0] = FaceX + (w * 6 / 2) / 10;
	FaceLine[FACING_E][1] = FaceY;

	FaceLine[FACING_SE][0] = FaceX + (w * 7 * 6 / 2) / 100;
	FaceLine[FACING_SE][1] = FaceY + (h * 7 * 6 / 2) / 100;

	FaceLine[FACING_S][0] = FaceX;
	FaceLine[FACING_S][1] = FaceY + (h * 6 / 2) / 10;

	FaceLine[FACING_SW][0] = FaceX - (w * 7 * 6 / 2) / 100;
	FaceLine[FACING_SW][1] = FaceY + (h * 7 * 6 / 2) / 100;

	FaceLine[FACING_W][0] = FaceX - (w * 6 / 2) / 10;
	FaceLine[FACING_W][1] = FaceY;

	FaceLine[FACING_NW][0] = FaceX - (w * 7 * 6 / 2) / 100;
	FaceLine[FACING_NW][1] = FaceY - (h * 7 * 6 / 2) / 100;
}


/***************************************************************************
 * Dial8Class::Action -- activation function for Dial8Class                *
 *                                                                         *
 * INPUT:                                                                  *
 *      flags      the reason we're being called                           *
 *      key      the KN_number that was pressed                            *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      true = event was processed, false = event not processed            *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   02/06/1995 BR : Created.                                              *
 *=========================================================================*/
int Dial8Class::Action(unsigned flags, KeyNumType &key)
{
	static int is_sel = 0;

	/*
	**	We might end up clearing the event bits. Make sure that the sticky
	**	process is properly updated anyway.
	*/
	Sticky_Process(flags);

	if (flags & LEFTPRESS) {
		is_sel = 1;
	}

	/*
	**	If left mouse is clicked or held, and the dial has changed its direction,
	**	invoke the parent Action routine:
	**	GadgetClass::Action handles Sticky processing, & sets IsToRepaint if any
	**	  flag bits are set.
	**	ControlClass::Action handles Peer_To_Peer notification, and substitutes
	**	  'key' with the button ID if any flags are set, or 0 if no flags are set
	*/
	if (flags & LEFTPRESS || ((flags & LEFTHELD) && is_sel)) {
		/*
		**	Get new dial position (0-255)
		*/
		Direction = ::Direction(Point2D(FaceX, FaceY), Get_Mouse_Point()).As_Dir256();

		/*
		**	Convert to Facing value (0-7).
		*/
		Facing = Dir_Facing(Direction);

		/*
		**	If it's moved, redraw.
		*/
		if (Facing!=OldFacing) {
			OldFacing = Facing;
			BASECLASS::Action(flags, key);
			return(true);

		} else {

			/*
			**	Dial hasn't moved; kill the event & return
			*/
			key = KN_NONE;
			BASECLASS::Action(0, key);
			return(true);
		}

	} else {

		/*
		**	Otherwise, no events have occurred; kill the event if it's a LEFTRELEASE,
		**	and return
		*/
		if (flags & LEFTRELEASE) {
			key = KN_NONE;
			is_sel = 0;
		}
		return(BASECLASS::Action(0, key));
	}
}


/***************************************************************************
 * Dial8Class::Draw_Me -- custom render routine for Dial8Class             *
 *                                                                         *
 * INPUT:                                                                  *
 *      forced      true = draw regardless of the current redraw flag state*
 *                                                                         *
 * OUTPUT:                                                                 *
 *      true = gadget was redrawn, false = wasn't                          *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   02/06/1995 BR : Created.                                              *
 *=========================================================================*/
int Dial8Class::Draw_Me(int forced)
{
	int scheme = GadgetClass::Get_Color_Scheme();

	/*
	**	Redraw if parent indicates a redraw is needed
	*/
	if (BASECLASS::Draw_Me(forced)) {
		/*
		**	Hide the mouse.
		*/
		Hide_Mouse();

		/*
		**	Draw background & decorations.
		*/
		Draw_Box(Rect(X, Y, Width, Height), BOXSTYLE_DOWN, true);
		for (int i=0; i < FACING_COUNT; i++) {
			Draw_Box(Rect(FacePoint[i][0] - 1, FacePoint[i][1] -1, 3, 3), BOXSTYLE_RAISED, false);
		}

		/*
		**	Draw the hand & its shadow.
		*/
		LogicalSurface->Draw_Line(Point2D(FaceX+1, FaceY+1), Point2D(FaceLine[Facing][0]+1, FaceLine[Facing][1]+1), NormalDrawer->Convert_Pixel(ColorSchemes[scheme]->Shadow));
		LogicalSurface->Draw_Line(Point2D(FaceX, FaceY), Point2D(FaceLine[Facing][0], FaceLine[Facing][1]), NormalDrawer->Convert_Pixel(ColorSchemes[scheme]->Highlight));

		/*
		**	Restore the mouse.
		*/
		Show_Mouse();

		return(true);
	}

	return(false);
}


/***************************************************************************
 * Dial8Class::Get_Direction -- retrieves direction (0-255) of dial        *
 *                                                                         *
 * INPUT:                                                                  *
 *      none.                                                              *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      DirType dial is pointing to                                        *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   11/17/1994 BR : Created.                                              *
 *=========================================================================*/
Dir256 Dial8Class::Get_Direction(void) const
{
	return(Direction);
}


/***************************************************************************
 * Dial8Class::Set_Direction -- sets current direction (0-255) of dial     *
 *                                                                         *
 * INPUT:                                                                  *
 *      DirType to set dial to                                             *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      none.                                                              *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   11/17/1994 BR : Created.                                              *
 *=========================================================================*/
void Dial8Class::Set_Direction(Dir256 dir)
{
	Direction = dir;
	Facing = Dir_Facing(Direction);
	OldFacing = Facing;
	Flag_To_Redraw();
}
