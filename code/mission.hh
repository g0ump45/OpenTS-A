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

#pragma once

#include <cassert>

/**********************************************************************
**	These missions enumerate the various state machines that can apply to
**	a game object. Only one of these state machines is active at any one
**	time.
*/
enum MissionType {
	MISSION_NONE=-1,

	MISSION_SLEEP,          // Do nothing whatsoever.
	MISSION_ATTACK,         // Attack nearest enemy.
	MISSION_MOVE,           // Guard location or unit.
	MISSION_QMOVE,          // A queue list movement mission.
	MISSION_RETREAT,        // Return home for R & R.
	MISSION_GUARD,          // Stay still.
	MISSION_STICKY,         // Stay still -- never recruit.
	MISSION_ENTER,          // Move into object cooperatively.
	MISSION_CAPTURE,        // Move into in order to capture.
	MISSION_HARVEST,        // Hunt for and collect nearby Tiberium.
	MISSION_GUARD_AREA,     // Active guard of area.
	MISSION_RETURN,         // Head back to refinery.
	MISSION_STOP,           // Sit still.
	MISSION_AMBUSH,         // Wait until discovered.
	MISSION_HUNT,           // Active search and destroy.
	MISSION_UNLOAD,         // Search for and deliver cargo.
	MISSION_SABOTAGE,       // Move into in order to destroy.
	MISSION_CONSTRUCTION,   // Building buildup operation.
	MISSION_DECONSTRUCTION, // Building builddown operation.
	MISSION_REPAIR,         // Repair process mission.
	MISSION_RESCUE,
	MISSION_MISSILE,
	MISSION_HARMLESS,       // Sit around and don't appear like a threat.
	MISSION_OPEN,
	MISSION_PATROL,

	MISSION_COUNT,
	MISSION_FIRST=0
};

inline MissionType operator++(MissionType & mission)
{
	mission = MissionType(int(mission) + 1);
	assert(mission >= MISSION_FIRST && mission <= MISSION_COUNT);
	return(mission);
}

MissionType MissionType_From_Name(char const * name);
char const * MissionType_To_Name(MissionType mission);
