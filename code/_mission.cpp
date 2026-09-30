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

#include "always.h"

#include "_mission.h"

/***********************************************************************************************
**	Unit order names. These names correspond to the player selectable orders
**	a unit can have. The system initiated orders have no use for the ASCII name
**	associated, but they are listed here for completeness sake.
*/
char const * Missions[MISSION_COUNT] = {
	"Sleep",
	"Attack",
	"Move",
	"QMove",
	"Retreat",
	"Guard",
	"Sticky",
	"Enter",
	"Capture",
	"Harvest",
	"Area Guard",
	"Return",
	"Stop",
	"Ambush",
	"Hunt",
	"Unload",
	"Sabotage",
	"Construction",
	"Selling",
	"Repair",
	"Rescue",
	"Missile",
	"Harmless",
	"Open",
	"Patrol",
};
