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

/**********************************************************************
**	Damage, as inflicted by projectiles, has different characteristics.
**	These are the different "warhead" types that can be assigned to the
**	various projectiles in the game.
*/
enum WarheadType {
	WARHEAD_NONE=-1,

	WARHEAD_EMPULS,
	WARHEAD_SONIC_WARHEAD,
	WARHEAD_TANK_O_GAS,
	WARHEAD_SA,					// Small arms -- good against infantry.
	WARHEAD_HE,					// High explosive -- good against buildings & infantry.
	WARHEAD_AP,					// Armor piercing -- good against armor.
	WARHEAD_GAS,
	WARHEAD_FIRE,				// Incendiary -- Good against flammables.
	WARHEAD_HOLLOW_POINT,		// Sniper bullet type.
	WARHEAD_SUPER,
	WARHEAD_ORGANIC,
	WARHEAD_SLIMER,
	WARHEAD_FIRESTORM_WH,
	WARHEAD_ION_CANNON_WH,
	WARHEAD_RAIL_SHOT,
	WARHEAD_MECHANICAL,			/// Repair weapon for vehicles
	WARHEAD_VEINHOLE_WH,
	WARHEAD_ION_WH,
	WARHEAD_ARTYHE,
	WARHEAD_PLASMA_WH,
	WARHEAD_SAMWH,
	WARHEAD_ORCAAP,
	WARHEAD_RAIL_SHOT2,
	WARHEAD_ORCAHE,

	/*
	 * Firestorm additions start here
	 */
	WARHEAD_METEORITE,
	WARHEAD_RPG,
	WARHEAD_SHARD,
	WARHEAD_FIRE2,
	WARHEAD_NUKE,				// Nuclear missile
	WARHEAD_WEBMASS,
	WARHEAD_LIMPY,
	WARHEAD_COREDEFPLASMAWH,
	WARHEAD_STINGER,
	WARHEAD_SUPER2,
	WARHEAD_MOBILEEMPULSE,

	WARHEAD_COUNT,
	WARHEAD_FIRST=0
};
