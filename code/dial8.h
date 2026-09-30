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

/* $Header: /CounterStrike/DIAL8.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : DIAL8.H                                                      *
 *                                                                                             *
 *                   Programmer : Bill Randolph                                                *
 *                                                                                             *
 *                   Start Date : 02/06/95                                                     *
 *                                                                                             *
 *                  Last Update : February 6, 1995 [BR]                                        *
 *                                                                                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "control.h"
#include "face.h"

#include "facing.hh"

class Dial8Class : public ControlClass
{
		typedef ControlClass BASECLASS;

	public:
		/*
		**	Constructor/Destructor
		*/
		Dial8Class(int id, int x, int y, int w, int h, Dir256 dir);

		/*
		**	Get/Set the direction the dial is currently pointing
		*/
		Dir256 Get_Direction(void) const;
		void Set_Direction(Dir256 dir);

		/*
		**	Overloaded draw routine
		*/
		virtual int Draw_Me(int forced = false) override;

	protected:
		/*
		**	Overloaded event processing routine
		*/
		virtual int Action(unsigned flags, KeyNumType &key) override;

	private:
		int FaceX;                       // x-coord of center of face
		int FaceY;                       // y-coord of center of face
		int FacePoint[FACING_COUNT][2];  // coords of the little dial decorations
		int FaceLine[FACING_COUNT][2];   // coords for drawing the dial hand
		Dir256 Direction;                // 0-255 numerical direction of dial
		FacingType Facing;               // numerical facing direction of dial (0 - 7)
		FacingType OldFacing;            // previous Facing value

};
