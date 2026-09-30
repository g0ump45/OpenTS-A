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

/* $Header: /CounterStrike/MAPEDIT.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : MAPEDIT.H                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : May 14, 1994                                                 *
 *                                                                                             *
 *                  Last Update : May 14, 1994   [JLB]                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * This class is derived from the normal display map class. It exists                          *
 * only to allow editing and adding items to the map.                                          *
 *---------------------------------------------------------------------------------------------*
 * House-setting functions: The editor contains several house maintenance routines:            *
 * Verify_House: tells if the given ObjectType can be owned by the given HousesType            *
 * Cycle_House: Finds the next valid house for the given ObjectType; used when a new object    *
 *              can't be owned by the current editor HousesType.                               *
 * Change_House: attempts to change the owner of the currently-selected object                 *
 * Toggle_House: cycles the HousesType of a pending placement object                           *
 * Set_House_Buttons: sets house buttons in accordance with the given HousesType               *
 *---------------------------------------------------------------------------------------------*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#ifdef _DEBUG

#include "mouse.h"

class ObjectTypeClass;

class MapEditClass: public MouseClass
{
		typedef MouseClass BASECLASS;

	/*
	**	Public Interface
	*/
	public:
		MapEditClass(void) {};
		virtual ~MapEditClass(void) override {};

		bool Add_To_List(ObjectTypeClass const *object);

	/*
	**	Private Interface
	*/
	private:
};

#endif
