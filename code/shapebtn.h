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

/* $Header: /CounterStrike/SHAPEBTN.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : SHAPEBTN.H                                                   *
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

#include "toggle.h"

class ConvertClass;
class ShapeSet;

class ShapeButtonClass : public ToggleClass
{
		typedef ToggleClass BASECLASS;

	public:
		ShapeButtonClass(void);
		ShapeButtonClass(unsigned id, ShapeSet const * shapes, int x, int y, int override_width = 0, int override_height = 0, bool faded = false);
		virtual int Draw_Me(int forced=false) override;
		virtual void Set_Shape(ShapeSet const * data, int override_width = 0, int override_height = 0);
		ShapeSet const * Get_Shape_Data(void) {return(ShapeData);};

		enum ShapeButtonClassEnums {
			UP_SHAPE,				// Shape to use when button is "up".
			DOWN_SHAPE,				// Shape to use when button is "down".
			DISABLED_SHAPE			// Shape to use when button is disabled.
		};

		bool ReflectButtonState;

		/*
		 * These are the pixel offsets added to the button's position when its shape is
		 * drawn. The sidebar uses them to shift a button out of screen space and into the
		 * coordinate space of the surface it actually renders onto.
		 */
		int DrawOffsetX;
		int DrawOffsetY;

		/*
		 * If this button renders onto the sidebar surface rather than the logical surface,
		 * then this flag will be true.
		 */
		bool DrawOnSidebar;

		/*
		 * This is the converter that translates the shape's palette indices into screen
		 * pixels. Sidebar and cameo buttons substitute their own for the NormalDrawer default.
		 */
		ConvertClass *ShapeDrawer;

		/*
		 * Whenever this button actually renders its shape, this flag is set true. The sidebar
		 * polls and clears it to learn that its surface has changed and must be copied to the
		 * visible page.
		 */
		bool IsDrawn;

		/*
		 * If the button's shape is to be drawn translucently rather than solid, then this flag
		 * will be true.
		 */
		bool DrawFaded;

	protected:

		/*
		**	This points to the shape data file. This file contains the appropriate shapes
		**	for this button in the offsets specified above.
		*/
		ShapeSet const * ShapeData;
};
