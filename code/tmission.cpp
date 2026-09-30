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

#include "tmission.h"

#include "globals.h"
#include "mission.h"
#include "quarry.h"
#include "teamtype.h"

#include "need.hh"
#include "target.hh"
#include "tmission.hh"
#include "unload.hh"

#include <cstdio>

#ifdef _DEBUG
/*
********************************** Globals **********************************
*/
char const * const TMissions[TMISSION_COUNT] = {
	"Attack...",
	"Attack Waypoint...",
	"Go Berzerk",
	"Move to waypoint...",
	"Move to Cell...",
	"Guard area (timer ticks)...",
	"Jump to line #...",
	"Player wins",
	"Unload...",
	"Deploy",
	"Follow friendlies",
	"Do this...",
	"Set global...",
	"Idle Anim...",
	"Load onto Transport",
	"Spy on bldg @ waypt...",
	"Patrol to waypoint...",
	"Change script...",
	"Change team...",
	"Panic",
	"Change house...",
	"Scatter",
	"Goto nearby shroud",
	"Player loses",
	"Play speech...",
	"Play sound...",
	"Play movie...",
	"Play music...",
	"Reduce tiberium",
	"Begin production",
	"Fire sale",
	"Self destruct",
	"Ion storm start in...",
	"Ion storn end",
	"Center view on team (speed)...",
	"Reshroud map",
	"Reveal map",
	"Delete team members",
	"Clear global...",
	"Set local...",
	"Clear local...",
	"Unpanic",
	"Force facing...",
	"Wait till fully loaded",
	"Truck unload",
	"Truck load",
	"Attack enemy building",
	"Moveto enemy building",
	"Scout",
	"Success",
	"Flash",
	"Play Anim",
	"Talk Bubble",
};

char const * const TMissionsHelp[TMISSION_COUNT] = {
	"Attack some general target",
	"Attack anything nearby the specified waypoint",
	"Cyborg members of the team will go berzerk.",
	"Orders the team to move to a waypoint on the map",
	"Orders the team to move to a specific cell on the map",
	"Guard an area for a specified amount of time",
	"Move to a new line number in the script.  Used for loops.",
	"Duh",
	"Unloads all loaded units.  The command parameter specifies which units should stay a part of the team, and which should be severed from the team.",
	"Causes all deployable units in the team to deploy",
	"Causes the team to follow the nearest friendly unit",
	"Give all team members the specified mission",
	"Sets a global variable",
	"Causes team members to enter their idle animation",
	"Causes all units to load into transports, if able",
	"**OBSOLETE**",
	"Move to a waypoint while scanning for enemies",
	"Causes the team to start using a new script",
	"Causes the team to switch team types",
	"Causes all units in the team to panic",
	"All units in the team switch houses",
	"Tells all units to scatter",
	"Causes units to flee to a shrouded cell",
	"Causes the player to lose",
	"Plays the specified voice file",
	"Plays the specified sound file",
	"Plays the specified movie file",
	"Plays the specified theme",
	"Reduces the amount of tiberium around team members",
	"Signals the owning house to begin production",
	"Causes an AI house to sell all of its buildings and do a Braveheart",
	"Causes all team members to self destruct",
	"Causes an ion storm to begin at the specified time",
	"Causes an ion storm to end",
	"Center view on team (speed)...",
	"Reshrouds the map",
	"Reveals the map",
	"Delete all members from the team",
	"Clears the specified global variable",
	"Sets the specified local variable",
	"Clears the specified local variable",
	"Causes all team members to stop panicking",
	"Forces team members to face a certain direction",
	"Waits until all transports are full",
	"Causes all trucks to unload their crates (ie, change imagery)",
	"Causes all trucks to load crates (ie, change imagery)",
	"Attack a specific type of building with the specified property",
	"Move to a specific type of building with the specified property",
	"The team will scout the bases of the players that have not been scouted",
	"Record a team as having successfully accomplished its mission.  Used for AI trigger weighting.  Put this at the end of every AITrigger script.",
	"Flashes a team for a period of team.",
	"Plays an anim over every unit in the team.",
	"Displays talk bubble over first unit in the team.",
};

char const * const TargetProperties[TPROPERTY_COUNT] = {
	"Least Threat",
	"Greatest Threat",
	"Nearest",
	"Farthest",
};

char const * const UnloadTypeNames[UNLOAD_COUNT] = {
	"Keep Transports, Keep Units",
	"Keep Transports, Lose Units",
	"Lose Transports, Keep Units",
	"Lose Transports, Lose Units",
};
#endif


/// <summary>
/// Fills in this team mission from its INI text form.
/// This routine is used while a team type is being read from the scenario file. The
/// entry carries the mission and its associated data value as a comma separated pair.
/// A cell stated in the old narrow encoding is converted as it is read, because the
/// scenario's format is not itself carried into a save game.
/// </summary>
/// <param name="entry">The INI text to parse. A NULL pointer leaves this mission
/// untouched.</param>
void TeamMissionClass::Fill_In(char const * entry)
{
	if (entry != NULL) {

		TeamMissionType tmission;
		int value;

		sscanf(entry, "%d,%d", &tmission, &value);

		if (tmission == TMISSION_MOVECELL && NewINIFormat < 4) {
			value = (value % 128) + ((value / 128) * 1000);
		}

		Mission = tmission;
		Data.Value = value;
	}
}


/// <summary>
/// Builds the INI text form of this team mission.
/// This routine is the counterpart to Fill_In and is used when a team type is written
/// back out to the scenario file.
/// </summary>
/// <param name="ptr">Buffer to build the entry into. A NULL pointer builds nothing.</param>
/// <returns>Returns with the number of characters placed into the buffer.</returns>
/// <remarks>Be sure that the destination buffer is big enough to hold the entry.</remarks>
int TeamMissionClass::Build_INI_Entry(char * ptr) const
{
	if (ptr != NULL) {
		sprintf(ptr, "%d,%d", Mission, Data.Value);
		return(strlen(ptr));
	}

	return(0);
}

/***********************************************************************************************
 * TeamMission_Needs -- Determines what extra data is needed by team mission.                  *
 *                                                                                             *
 *    This routine will return the required extra data that the specified team mission will    *
 *    need.                                                                                    *
 *                                                                                             *
 * INPUT:   tmtype   -- The team mission type to check.                                        *
 *                                                                                             *
 * OUTPUT:  Returns with the data type needed for this team mission.                           *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   01/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
NeedType TeamMission_Needs(TeamMissionType tmtype)
{
	switch (tmtype) {
		/*
		**	Requires a formation type.
		*/
//		case TMISSION_FORMATION:
//			return(NEED_FORMATION);

		/*
		**	Team mission requires a target quarry value.
		*/
		case TMISSION_ATTACK:
			return(NEED_QUARRY);

		/*
		**	Team mission requires a data value.
		*/
		case TMISSION_MOVECELL:
			return(NEED_HEX_NUMBER);

		/*
		 * Team mission requires a velocity type.
		 */
		case TMISSION_CENTER_VIEWPOINT:
			return(NEED_VELOCITY);

		/*
		 * Team mission requires a global.
		 */
		case TMISSION_SET_GLOBAL:
		case TMISSION_CLEAR_GLOBAL:
			return(NEED_GLOBAL);

		/*
		 * Team mission requires a local.
		 */
		case TMISSION_SET_LOCAL:
		case TMISSION_CLEAR_LOCAL:
			return(NEED_LOCAL);

		case TMISSION_GUARD:
		case TMISSION_LOOP:
		case TMISSION_IDLE_ANIM:
		case TMISSION_ION_STORM_START:
		case TMISSION_FORCE_FACING:
		case TMISSION_FLASH:
			return(NEED_NUMBER);

		/*
		**	Team mission requires a waypoint.
		*/
		case TMISSION_PATROL:
		case TMISSION_MOVE:
		case TMISSION_ATT_WAYPT:
		case TMISSION_SPY:
			return(NEED_WAYPOINT);

		/*
		 * Team mission requires a house.
		 */
		case TMISSION_CHANGE_HOUSE:
			return(NEED_HOUSE);

		/*
		**	Team mission requires a general mission type.
		*/
		case TMISSION_DO:
			return(NEED_MISSION);

		/*
		 * Team mission requires a script.
		 */
		case TMISSION_SCRIPT:
			return(NEED_SCRIPT);

		/*
		 * Team mission requires a team.
		 */
		case TMISSION_TEAMCHANGE:
			return(NEED_TEAM);

		/*
		 * Team mission requires a speech.
		 */
		case TMISSION_PLAY_SPEECH:
			return(NEED_SPEECH);

		/*
		 * Team mission requires a sound.
		 */
		case TMISSION_PLAY_SOUND:
			return(NEED_SOUND);

		/*
		 * Team mission requires a movie.
		 */
		case TMISSION_PLAY_MOVIE:
			return(NEED_MOVIE);

		/*
		 * Team mission requires a theme.
		 */
		case TMISSION_PLAY_MUSIC:
			return(NEED_THEME);

		/*
		 * Team mission requires a building with a property.
		 */
		case TMISSION_ATTACK_BUILDING_WITH_PROPERTY:
		case TMISSION_MOVETO_BUILDING_WITH_PROPERTY:
			return(NEED_BUILDING_ATTACK);

		/*
		 * Team mission requires a unload type.
		 */
		case TMISSION_UNLOAD:
			return(NEED_SPLIT);

		/*
		 * Team mission requires a animation.
		 */
		case TMISSION_PLAY_ANIM:
			return(NEED_ANIM);

		/*
		 * Team mission requires a talk bubble type.
		 */
		case TMISSION_TALK_BUBBLE:
			return(NEED_TALK_BUBBLE);

		default:
			break;
	}
	return(NEED_NONE);
}
