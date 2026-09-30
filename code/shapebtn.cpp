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

/* $Header: /CounterStrike/SHAPEBTN.CPP 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : SHAPEBTN.CPP                                                 *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 01/15/95                                                     *
 *                                                                                             *
 *                  Last Update : September 20, 1995 [JLB]                                     *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   ShapeButtonClass::Draw_Me -- Renders the shape button's imagery.                          *
 *   ShapeButtonClass::Set_Shape -- Assigns a shape to this shape button.                      *
 *   ShapeButtonClass::ShapeButtonClass -- Constructor for a shape type button.                *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "shapebtn.h"

#include "_convert.h"
#include "_surface.h"
#include "convert.h"
#include "dbgprint.h"
#include "draw.h"
#include "shapeset.h"


/***********************************************************************************************
 * ShapeButtonClass::ShapeButtonClass -- Default Constructor for a shape type button.          *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   You must call Set_Shape() before using a button constructed with this function, *
 *             and you must set X & Y, and ID.                                                 *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/15/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
ShapeButtonClass::ShapeButtonClass(void) :
	BASECLASS(0, 0, 0, 0, 0),
	ReflectButtonState(false),
	DrawOffsetX(0),
	DrawOffsetY(0),
	DrawOnSidebar(0),
	DrawFaded(0),
	ShapeDrawer(NormalDrawer)
{
}


/***********************************************************************************************
 * ShapeButtonClass::ShapeButtonClass -- Constructor for a shape type button.                  *
 *                                                                                             *
 *    This is the normal constructor for a shape type button. Shape buttons are ones that      *
 *    have their imagery controlled by a shape file. The various states of the button are      *
 *    given a visual form as one of these shapes. Button dimensions are controlled by the      *
 *    first shape.                                                                             *
 *                                                                                             *
 * INPUT:   id    -- The button ID.                                                            *
 *                                                                                             *
 *          shape -- Pointer to the shape file that controls the button's display.             *
 *                                                                                             *
 *          x,y   -- The pixel coordinate of the upper left corner of the button.              *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   The width and height of the shape is controlled by the first shape in the       *
 *             shape file provided. This means that all the shapes in the shape file must be   *
 *             the same size.                                                                  *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/15/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
ShapeButtonClass::ShapeButtonClass(unsigned id, ShapeSet const * shape, int x, int y, int override_width, int override_height, bool faded) :
	BASECLASS(id, x, y, 0, 0),
	ReflectButtonState(false),
	DrawOffsetX(0),
	DrawOffsetY(0),
	DrawOnSidebar(0),
	ShapeDrawer(NormalDrawer),
	DrawFaded(faded)
{
	Set_Shape(shape, override_width, override_height);
}


/***********************************************************************************************
 * ShapeButtonClass::Set_Shape -- Assigns a shape to this shape button.                        *
 *                                                                                             *
 *    This routine will assign the specified shape to this shape object.                       *
 *                                                                                             *
 * INPUT:   data  -- Pointer to the shape to assign.                                           *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/20/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
void ShapeButtonClass::Set_Shape(ShapeSet const * data, int override_width, int override_height)
{
	ShapeData = data;
	if (ShapeData) {
		Width = ShapeData->Get_Width();
		Height = ShapeData->Get_Height();
	}
	if (override_width != 0) {
		Width = override_width;
	}
	if (override_height != 0) {
		Height = override_height;
	}
}


/***********************************************************************************************
 * ShapeButtonClass::Draw_Me -- Renders the shape button's imagery.                            *
 *                                                                                             *
 *    This function is called when the button detects that it must be redrawn. The actual      *
 *    shape to use is controled by the button's state and the shape file provided when then    *
 *    button was constructed.                                                                  *
 *                                                                                             *
 * INPUT:   forced   -- Should the button be redrawn regardless of the redraw flag?            *
 *                                                                                             *
 * OUTPUT:  bool; Was the shape redrawn?                                                       *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/15/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int ShapeButtonClass::Draw_Me(int forced)
{
	if (ControlClass::Draw_Me(forced) && ShapeData) {
		/*
		**	Draw the body & set text color.
		*/
		int shapenum = 0;
		if (IsDisabled) {
			shapenum = DISABLED_SHAPE;
		} else {

			if (!ReflectButtonState) {

				if (IsPressed) {
					shapenum = DOWN_SHAPE;
				} else {
					shapenum = UP_SHAPE;
				}
			} else {
				shapenum = IsOn;
			}
		}
		Surface *surf = SidebarSurface;
		if (!DrawOnSidebar) {
			surf = LogicalSurface;
		}

		Draw_Shape(*surf, *ShapeDrawer, ShapeData, shapenum, Point2D(DrawOffsetX + X, DrawOffsetY + Y), VisibleRect, DrawFaded != 0 ? SHAPE_ALPHA : SHAPE_NORMAL);
		IsDrawn = true;
		return(true);
	}
	return(false);
}
