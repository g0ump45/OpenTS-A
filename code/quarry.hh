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

/****************************************************************************
**	There are various target types that teams and special weapons can be
**	assigned to attack. These are general target categories since the actual
**	disposition of potential targets cannot be precisely predicted -- thus these
**	serve as guidelines for the computer AI.
*/
enum QuarryType {
	QUARRY_NONE,

	QUARRY_ANYTHING,    // Attack any enemy (same as "hunt").
	QUARRY_BUILDINGS,   // Attack buildings (in general).
	QUARRY_HARVESTERS,  // Attack harvesters or refineries.
	QUARRY_INFANTRY,    // Attack infantry.
	QUARRY_VEHICLES,    // Attack combat vehicles.
	QUARRY_FACTORIES,   // Attack factories (all types).
	QUARRY_DEFENSE,     // Attack base defense buildings.
	QUARRY_THREAT,      // Attack enemies near friendly base.
	QUARRY_POWER,       // Attack power facilities.

	QUARRY_COUNT,
	QUARRY_FIRST=0
};
