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

/* $Header: /CounterStrike/CONST.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : CONST.CPP                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : September 20, 1993                                           *
 *                                                                                             *
 *                  Last Update : September 20, 1993   [JLB]                                   *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "coord.h"
#include "globals.h"

#include "anim.hh"


char const * LandName[LAND_COUNT] = {
	"Clear",
	"Road",
	"Water",
	"Rock",
	"Wall",
	"Tiberium",
	"Beach",
	"Rough",
	"Ice",
	"Railroad",
	"Tunnel",
	"Weeds"
};


char const * SpeedName[SPEED_COUNT] = {
	"Foot",
	"Track",
	"Wheel",
	"Hover",
	"Winged",
	"Float",
	"Amphibious",
	"Creep"
};


/***************************************************************************
**	These are the text names for the various armor types a unit may possess.
*/
char const * const ArmorName[ARMOR_COUNT] = {
	"none",
	"wood",
	"light",
	"heavy",
	"concrete"
};


/***************************************************************************
**	Relative coordinate offsets from the center of a cell for each
**	of the legal positions that an object in a cell may stop at. Only infantry
**	are allowed to stop at other than the center of the cell.
*/
Coord const StoppingCoordAbs[5] = {
	Coord(CELL_LEPTON_W / 2,     CELL_LEPTON_H / 2, 0),     // center
	Coord(CELL_LEPTON_W / 4,     CELL_LEPTON_H / 4, 0),     // upper left
	Coord(3 * CELL_LEPTON_W / 4, CELL_LEPTON_H / 4, 0),     // upper right
	Coord(CELL_LEPTON_W / 4,     3 * CELL_LEPTON_H / 4, 0), // lower left
	Coord(3 * CELL_LEPTON_W / 4, 3 * CELL_LEPTON_H / 4, 0)  // lower right
};


/***************************************************************************
**	This specifies the odds of receiving the various random crate power
**	ups. The odds are expressed as "shares" of 100 percent.
*/
int CrateShares[CRATE_COUNT] = {
	50,     // CRATE_MONEY
	20,     // CRATE_UNIT
	1,      // CRATE_HEAL_BASE
	3,      // CRATE_CLOAK
	5,      // CRATE_EXPLOSION
	5,      // CRATE_NAPALM
	20,     // CRATE_SQUAD
	1,      // CRATE_DARKNESS
	1,      // CRATE_REVEAL
	10,     // CRATE_ARMOR
	10,     // CRATE_SPEED
	10,     // CRATE_FIREPOWER
	1,      // CRATE_ICBM
	3,      // CRATE_INVULN
	1,      /// CRATE_VETERAN
	1,      /// CRATE_ION_STORM
	1,      /// CRATE_GAS
	1,      /// CRATE_TIBERIUM
	1       /// CRATE_POD
};

AnimType CrateAnims[CRATE_COUNT] = {
	ANIM_NONE,  // CRATE_MONEY
	ANIM_NONE,  // CRATE_UNIT
	ANIM_NONE,  // CRATE_HEAL_BASE
	ANIM_NONE,  // CRATE_CLOAK
	ANIM_NONE,  // CRATE_EXPLOSION
	ANIM_NONE,  // CRATE_NAPALM
	ANIM_NONE,  // CRATE_SQUAD
	ANIM_NONE,  // CRATE_DARKNESS
	ANIM_NONE,  // CRATE_REVEAL
	ANIM_NONE,  // CRATE_ARMOR
	ANIM_NONE,  // CRATE_SPEED
	ANIM_NONE,  // CRATE_FIREPOWER
	ANIM_NONE,  // CRATE_ICBM
	ANIM_NONE,  // CRATE_INVULN
	ANIM_NONE,  /// CRATE_VETERAN
	ANIM_NONE,  /// CRATE_ION_STORM
	ANIM_NONE,  /// CRATE_GAS
	ANIM_NONE,  /// CRATE_TIBERIUM
	ANIM_NONE   /// CRATE_POD
};

double CrateData[CRATE_COUNT] = {
	0,      // CRATE_MONEY
	0,      // CRATE_UNIT
	0,      // CRATE_HEAL_BASE
	0,      // CRATE_CLOAK
	0,      // CRATE_EXPLOSION
	0,      // CRATE_NAPALM
	0,      // CRATE_SQUAD
	0,      // CRATE_DARKNESS
	0,      // CRATE_REVEAL
	0,      // CRATE_ARMOR
	0,      // CRATE_SPEED
	0,      // CRATE_FIREPOWER
	0,      // CRATE_ICBM
	0,      // CRATE_INVULN
	0,      /// CRATE_VETERAN
	0,      /// CRATE_ION_STORM
	0,      /// CRATE_GAS
	0,      /// CRATE_TIBERIUM
	0       /// CRATE_POD
};

char const * const CrateNames[CRATE_COUNT] = {
	"Money",
	"Unit",
	"HealBase",
	"Cloak",
	"Explosion",
	"Napalm",
	"Squad",
	"Darkness",
	"Reveal",
	"Armor",
	"Speed",
	"Firepower",
	"ICBM",
	"Invulnerability",
	"Veteran",
	"IonStorm",
	"Gas",
	"Tiberium",
	"Pod"
};

GroundType Ground[LAND_COUNT];
