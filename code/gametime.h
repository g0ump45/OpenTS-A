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

/***************************************************************************
 **     C O N F I D E N T I A L --- W E S T W O O D   S T U D I O S       **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : VQAVIEW                                  *
 *                                                                         *
 *                    File Name : GAMETIME.H                               *
 *                                                                         *
 *                   Programmer : Michael Grayford                         *
 *                                                                         *
 *                   Start Date :                                          *
 *                                                                         *
 *                  Last Update : Nov 22, 1995   [MG]                      *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

//==========================================================================
// PUBLIC FUNCTIONS
//==========================================================================

extern unsigned int Get_Game_Time(void);
extern unsigned int Get_Game_Time_50(void);

//==========================================================================
// PUBLIC DEFINES
//==========================================================================

#define MAX_ULONG				0xFFFFFFFF

//==========================================================================
// CLASSES
//==========================================================================

class GameTimeClass {
	private:
		unsigned int game_start_time;

	public:
		GameTimeClass( void );
		unsigned int Get_Time( void );

}; /* VQAClass */


//==========================================================================
// PUBLIC DATA
//==========================================================================

extern GameTimeClass Game_Time;
