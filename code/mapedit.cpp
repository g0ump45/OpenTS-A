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

/* $Header: /CounterStrike/MAPEDIT.CPP 2     3/13/97 2:05p Steve_tall $ */
/***************************************************************************
 **   C O N F I D E N T I A L --- W E S T W O O D    S T U D I O S        **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : Command & Conquer                        *
 *                                                                         *
 *                    File Name : MAPEDIT.CPP                              *
 *                                                                         *
 *                   Programmer : Bill Randolph                            *
 *                                                                         *
 *                   Start Date : October 20, 1994                         *
 *                                                                         *
 *                  Last Update : February 2, 1995   [BR]                  *
 *                                                                         *
 *-------------------------------------------------------------------------*
 *   Map Editor overloaded routines & utility routines                     *
 *-------------------------------------------------------------------------*
 * Map Editor modules:                                                     *
 * (Yes, they're all one huge class.)                                      *
 *      mapedit.cpp:   overloaded routines, utility routines               *
 *      mapeddlg.cpp:   map editor dialogs, most of the main menu options  *
 *      mapedplc.cpp:   object-placing routines                            *
 *      mapedsel.cpp:   object-selection & manipulation routines           *
 *      mapedtm.cpp:   team-editing routines                               *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 *   MapEditClass::AI -- The map editor's main logic                       *
 *   MapEditClass::Read_INI -- overloaded Read_INI function                *
 *   MapEditClass::AI_Menu -- menu of AI options                           *
 *   MapEditClass::Add_To_List -- adds a TypeClass to the chooseable list  *
 *   MapEditClass::Clear_List -- clears the internal chooseable object list*
 *   MapEditClass::Cycle_House -- finds next valid house for object type   *
 *   MapEditClass::Draw_It -- overloaded Redraw routine                    *
 *   MapEditClass::Fatal -- exits with error message                       *
 *   MapEditClass::Main_Menu -- main menu processor for map editor         *
 *   MapEditClass::MapEditClass -- class constructor                       *
 *   MapEditClass::Mouse_Moved -- checks for mouse motion                  *
 *   MapEditClass::One_Time -- one-time initialization                     *
 *   MapEditClass::Verify_House -- sees if given house can own given obj   *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "mapedit.h"

#include "objtype.h"

#ifdef _DEBUG

/***************************************************************************
 * MapEditClass::Add_To_List -- adds a TypeClass to the chooseable list    *
 *                                                                         *
 * Use this routine to add an object to the game object selection list.    *
 * This list is used by the Add_Object function. All items located in the  *
 * list will appear and be chooseable by that function. Make sure to       *
 * clear the list before adding a sequence of items to it. Clearing        *
 * the list is accomplished by the Clear_List() function.                  *
 *                                                                         *
 * INPUT:                                                                  *
 *      object      ptr to ObjectTypeClass to add                          *
 *                                                                         *
 * OUTPUT:                                                                 *
 *      bool: was the object added to the list?  A failure could occur if  *
 *      NULL were passed in or the list is full.                           *
 *                                                                         *
 * WARNINGS:                                                               *
 *      none.                                                              *
 *                                                                         *
 * HISTORY:                                                                *
 *   06/04/1994 JLB : Created.                                             *
 *=========================================================================*/
bool MapEditClass::Add_To_List(ObjectTypeClass const * object)
{
	/*
	**	Add the object if there's room.
	*/
	if (object /*&& ObjCount < MAX_EDIT_OBJECTS*/) {
//		Objects[ObjCount++] = object;

		/*
		**	Update type counters.
		*/
		switch (object->What_Am_I()) {
//			case RTTI_TEMPLATETYPE:
//				NumType[0]++;
//				break;

			case RTTI_OVERLAYTYPE:
//				NumType[1]++;
				break;

			case RTTI_SMUDGETYPE:
//				NumType[2]++;
				break;

			case RTTI_TERRAINTYPE:
//				NumType[3]++;
				break;

			case RTTI_UNITTYPE:
//				NumType[4]++;
				break;

			case RTTI_INFANTRYTYPE:
//				NumType[5]++;
				break;

//			case RTTI_VESSELTYPE:
//				NumType[6]++;
//				break;

			case RTTI_BUILDINGTYPE:
//				NumType[7]++;
				break;

			case RTTI_AIRCRAFTTYPE:
//				NumType[8]++;
				break;
		}
		return(true);
	}

	return(false);
}

#endif
