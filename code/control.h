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

/* $Header: /CounterStrike/CONTROL.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : CONTROL.H                                                    *
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

#include "gadget.h"

/***************************************************************************
 * ControlClass -- Region tracking class                                   *
 *                                                                         *
 * INPUT:      int x -- x position of gadget                               *
 *               int y -- y position of gadget                             *
 *               int w -- width of gadget                                  *
 *               int h -- height of gadget                                 *
 *               UWORD flags -- see enumeration choices                    *
 *                                                                         *
 * OUTPUT:     0 = new scenario created, -1 = not                          *
 * WARNINGS:   This class is Abstract (cannot make an instance of it)      *
 *                                                                         *
 * HISTORY:                                                                *
 *   01/03/1995 MML : Created.                                             *
 *=========================================================================*/
class ControlClass : public GadgetClass
{
		typedef GadgetClass BASECLASS;

	public:
		ControlClass(unsigned id, int x, int y, int w, int h, unsigned flags=LEFTPRESS|RIGHTPRESS, bool sticky=false);
		ControlClass(ControlClass const & control);

		virtual void Make_Peer(GadgetClass & gadget);

		/*
		**	Render support function.
		*/
		virtual int Draw_Me(int forced=false) override;

		/*
		**	This is the ID number for this control gadget. This number is used to generate
		**	a special pseudo-key when the gadget detects valid input.
		*/
		unsigned ID;

	protected:
		virtual unsigned Get_ID(void) const override;
		virtual int Action(unsigned flags, KeyNumType & key) override;

		/*
		**	This points to the peer button to inform when something happens to this
		**	gadget.
		*/
		GadgetClass * Peer;
};
