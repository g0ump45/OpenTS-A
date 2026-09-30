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
**	Terrain can be of these different classes. At any point in the game
**	a particular piece of ground must fall under one of these classifications.
**	This is true, even if it is undergoing a temporary transition.
*/
enum LandType {
	LAND_NONE=-1,

	LAND_CLEAR,		// "Clear" terrain.
	LAND_ROAD,		// Road terrain.
	LAND_WATER,		// Water.
	LAND_ROCK,		// Impassable rock.
	LAND_WALL,		// Wall (blocks movement).
	LAND_TIBERIUM,	// Tiberium field.
	LAND_BEACH,		// Beach terrain.
	LAND_ROUGH,		// Rocky terrain.
	LAND_ICE,		/// Ice frozen solid.
	LAND_RAILROAD,	/// Rail tracks.
	LAND_TUNNEL,	/// Tunnel.
	LAND_WEEDS,		/// Weeds.

	LAND_COUNT,
	LAND_FIRST=0
};
