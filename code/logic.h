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

/* $Header: /CounterStrike/LOGIC.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : LOGIC.H                                                      *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : May 29, 1994                                                 *
 *                                                                                             *
 *                  Last Update : May 29, 1994   [JLB]                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "layer.h"


class AbstractClass;
class MonoClass;

/***********************************************************************************************
**	Game logic processing is controlled by this class. The graphic and AI logic is handled
**	separately so that on slower machines, the graphic display is least affected.
*/
class LogicClass : public LayerClass
{
		typedef LayerClass BASECLASS;

	public:
		void AI(void);
		bool Submit(ObjectClass const * object, bool sort=false);
		void Remove(ObjectClass * object);
		void Detach(AbstractClass const * target, bool all=true);
#ifdef _DEBUG
		void Debug_Dump(MonoClass *mono) const;
#endif
		void Environment_AI(void);
};

extern unsigned FramesThisSecond;
extern unsigned TotalFrames;
extern unsigned LastFramesPerSecond;
extern unsigned SecondsPassed;
