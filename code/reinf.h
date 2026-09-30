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

#include "types.h"

#include "aircraft.hh"
#include "infantry.hh"
#include "mission.hh"
#include "tmission.hh"

class TeamTypeClass;
class HouseClass;
class TechnoTypeClass;
class AbstractClass;
class FootClass;
class Cell;

bool Do_Reinforcements(TeamTypeClass const * team, WAYPOINT wp=-1);
bool Create_Reinforcement(TeamTypeClass const * teamtype, FootClass * object, Cell const & cell, bool atwaypoint);
bool Create_Special_Reinforcement(HouseClass * house, TechnoTypeClass const * type, TechnoTypeClass const * another, TeamMissionType mission = TMISSION_NONE, int argument =0);
int Create_Air_Reinforcement(HouseClass *house, AircraftType air, int number, MissionType mission, AbstractClass * tarcom, AbstractClass * navcom, InfantryType passenger=INFANTRY_NONE);
