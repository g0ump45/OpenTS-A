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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /G/wwlib/_mono.h                                            $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 11:58a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

class MonoClass;

/**********************************************************************
**	These are the identifiers for the various monochrome debug screens.
*/
enum DMonoType {
	DMONO_OBJECT,
	DMONO_HOUSE,
	DMONO_STRESS,
	DMONO_EVENTS,

	DMONO_COUNT,
	DMONO_FIRST=0
};


/*
**	This externs the global mono object. There can be only one.
*/
extern MonoClass Mono;

#define Mono_Clear_Screen Mono.Clear
#define Mono_Printf Mono.Printf
#define Mono_Set_Cursor Mono.Set_Cursor
