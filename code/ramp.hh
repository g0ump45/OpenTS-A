/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once


/// Enumeration for the slope type.
/// Each ramp is named for the map direction its ground descends toward, so RAMP_WEST is the
/// ramp you drive down heading west. The map compass sits 45 degrees off the screen, so map
/// north is the upper right of the display. See slope##.tem for image reference.
enum RampType
{
	RAMP_NONE = 0, /// A flat tile (i.e. no ramp).

	/// Standard (two corners high).
	RAMP_WEST = 1, /// Descends west; the two eastern corners are raised.
	RAMP_NORTH = 2, /// Descends north; the two southern corners are raised.
	RAMP_EAST = 3, /// Descends east; the two western corners are raised.
	RAMP_SOUTH = 4, /// Descends south; the two northern corners are raised.

	/// Tile outside corners (one corner high).
	RAMP_CORNER_NW = 5,
	RAMP_CORNER_NE = 6,
	RAMP_CORNER_SE = 7,
	RAMP_CORNER_SW = 8,

	/// Tile inside corners (three corners high).
	RAMP_MID_NW = 9,
	RAMP_MID_NE = 10,
	RAMP_MID_SE = 11,
	RAMP_MID_SW = 12,

	/// Steep (two corners high, one corner double high).
	RAMP_STEEP_NW = 13,
	RAMP_STEEP_NE = 14,
	RAMP_STEEP_SE = 15,
	RAMP_STEEP_SW = 16,

	/// Double ramps (two corners high, alternating). The height and tilt tables treat all four
	/// as flat ground half a level up, so only the artwork slopes.
	RAMP_DOUBLE_UP_SW_NE = 17, /// Double ramp tile that slopes up, faces SW-NE (in the game world).
	RAMP_DOUBLE_DOWN_SW_NE = 18, /// Double ramp tile that slopes down, faces SW-NE (in the game world).
	RAMP_DOUBLE_UP_NW_SE = 19, /// Double ramp tile that slopes up, faces NW-SE (in the game world).
	RAMP_DOUBLE_DOWN_NW_SE = 20, /// Double ramp tile that slopes down, faces NW-SE (in the game world).

	RAMP_COUNT
};
