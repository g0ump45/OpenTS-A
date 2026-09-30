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

/// TS names derived from FA2/FS

/*
**	TeamMissionType: the various missions that a team can have.
*/
enum TeamMissionType {
	TMISSION_NONE=-1,

	TMISSION_ATTACK,						// Attack specified quarry type.
	TMISSION_ATT_WAYPT,						// Attack specified waypoint
	TMISSION_BERZERK,						/// Cyborg team members go berzerk.
	TMISSION_MOVE,							// moves to waypoint specified.
	TMISSION_MOVECELL,						// moves to cell # specified.
	TMISSION_GUARD,							// works like an infantry's guard mission
	TMISSION_LOOP,							// loop back to start of mission list
	TMISSION_WIN,							/// Player wins.
	TMISSION_UNLOAD,						// Unload at current location.
	TMISSION_DEPLOY,						// Deploy mobile building type.
	TMISSION_HOUND_DOG,						// Follow nearest friendly unit.
	TMISSION_DO,							// Do guard, sticky, area guard (mission sticks on this).
	TMISSION_SET_GLOBAL,					// Set global variable.
	TMISSION_IDLE_ANIM,						/// Team members enter their idle animation.
	TMISSION_LOAD,							// Load onto transport member of team.
	TMISSION_SPY,							// Spy enter the building at specified waypoint
	TMISSION_PATROL,						// Move but look for enemies as well.
	TMISSION_SCRIPT,						/// Start using a new script.
	TMISSION_TEAMCHANGE,					/// Switch to a new team type.
	TMISSION_PANIC,							/// All units in the team panic.
	TMISSION_CHANGE_HOUSE,					/// All units in the team switch houses.
	TMISSION_SCATTER,						/// Tell all units to scatter.
	TMISSION_GOTO_SHROUD,					/// Flee to a shrouded cell.
	TMISSION_LOSE,							/// Player loses.
	TMISSION_PLAY_SPEECH,					/// Play the specified voice file.
	TMISSION_PLAY_SOUND,					/// Play the specified sound file.
	TMISSION_PLAY_MOVIE,					/// Play the specified movie file.
	TMISSION_PLAY_MUSIC,					/// Play the specified theme.
	TMISSION_REDUCE_TIBERIUM,				/// Reduce Tiberium around team members.
	TMISSION_BEGIN_PRODUCTION,				/// Signal the owning house to begin production.
	TMISSION_FIRE_SALE,						/// AI house sells all buildings and attacks.
	TMISSION_SELF_DESTRUCT,					/// All team members self destruct.
	TMISSION_ION_STORM_START,				/// Start an ion storm at the specified time.
	TMISSION_ION_STORM_END,					/// End the ion storm.
	TMISSION_CENTER_VIEWPOINT,				/// Center view on team at given speed.
	TMISSION_RESHROUD,						/// Reshroud the map.
	TMISSION_REVEAL,						/// Reveal the map.
	TMISSION_DESTROY_MEMBERS,				/// Delete all members from the team.
	TMISSION_CLEAR_GLOBAL,					/// Clear global variable.
	TMISSION_SET_LOCAL,						/// Set local variable.
	TMISSION_CLEAR_LOCAL,					/// Clear local variable.
	TMISSION_UNPANIC,						/// All team members stop panicking.
	TMISSION_FORCE_FACING,					/// Force team members to face a direction.
	TMISSION_FULLY_LOADED,					/// Wait until all transports are full.
	TMISSION_UNLOAD_TRUCK,					/// Trucks unload their crates.
	TMISSION_LOAD_TRUCK,					/// Trucks load crates.
	TMISSION_ATTACK_BUILDING_WITH_PROPERTY,	/// Attack building type with specified property.
	TMISSION_MOVETO_BUILDING_WITH_PROPERTY,	/// Move to building type with specified property.
	TMISSION_SCOUT,							/// Scout unscouted player bases.
	TMISSION_SUCCESS,						/// Record team mission success for AI trigger weighting.
	TMISSION_FLASH,							/// Flash team for a period of time.
	TMISSION_PLAY_ANIM,						/// Play anim over every team member.
	TMISSION_TALK_BUBBLE,					/// Talk bubble over first unit in team.

	TMISSION_COUNT,
	TMISSION_FIRST=0
};
