/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

enum IsometricTileType {
	ISOTILE_CLEAR = 0,

	ISOTILE_NONE = 0xFFFF, // -1
	TILE_NONE = ISOTILE_NONE,

	/*
	 * Tiberian Dawn's TEMPLATE_NONE, from when the tile index was a byte. The index
	 * has widened since, but the old value is still checked for.
	 */
	ISOTILE_NONE_LEGACY = 0xFF,

	ISOTILE_INVALID = -1,
	ISOTILE_INVALID_CLIFF = -2,

	ISOTILE_FIRST = 0
};

#define ICE_LAT 1
#define ICE_CRACKED 16
#define ICE_EDGE 17
#define ICE_SHORE_COUNT 48
#define ICE_COUNT 64

#define PAVE_TILE_COUNT				16
#define MISC_PAVE_TILE_COUNT		14
//#define CLEAR_TO_PAVE_LAT_COUNT		16
#define RAMP_BASE_COUNT				20
//#define MM_RAMP_BASE_COUNT			20
#define RAMP_SMOOTH_COUNT			12
//#define CLEAR_TILE_COUNT			1
//#define ROUGH_TILE_COUNT			1
//#define CLEAR_TO_ROUGH_LAT_COUNT	16
//#define HEIGHT_BASE_COUNT			15
#define CLIFF_COUNT					40
#define SHORE_PIECES_COUNT			42
#define WATER_COUNT					14
#define ICE1_COUNT					ICE_COUNT
#define ICE2_COUNT					ICE_COUNT
#define ICE3_COUNT					ICE_COUNT
//#define ICE_SHORE_COUNT				48
//#define BLACK_TILE_COUNT			1
#define BRIDGE_COUNT				16
#define TRAIN_BRIDGE_COUNT			16
#define SLOPE_COUNT					10
//#define SLOPE_PIECES_COUNT			10
//#define SLOPE_PIECES2_COUNT			10
//#define MONORAIL_SLOPES_COUNT		4
//#define TUNNELS_COUNT				4
//#define TRACK_TUNNELS_COUNT			4
//#define DIRT_TUNNELS_COUNT			4
//#define DIRT_TRACK_TUNNELS_COUNT	4
#define WATERFALL_EAST_COUNT		4
#define WATERFALL_WEST_COUNT		4
#define WATERFALL_SOUTH_COUNT		4
#define WATERFALL_NORTH_COUNT		4
#define CLIFF_RAMPS_COUNT			20
#define PAVED_ROAD_COUNT			15
#define PAVED_ROAD_ENDS_COUNT		4
#define PAVED_ROAD_SLOPES_COUNT		4
#define DIRT_ROAD_JUNCTION_COUNT	11
#define DIRT_ROAD_CURVE_COUNT		24
#define DIRT_ROAD_STRAIGHT_COUNT	66
//#define ROUGH_GROUND_COUNT			10
#define WATER_CLIFFS_COUNT			28
#define DIRT_ROAD_SLOPES_COUNT		8
#define DESTROYABLE_CLIFFS_COUNT	2
//#define SAND_TILE_COUNT				1
//#define CLEAR_TO_SAND_LAT_COUNT		16
//#define GREEN_TILE_COUNT			1
//#define CLEAR_TO_GREEN_LAT_COUNT	16
//#define ROCKS_COUNT					1
#define WATER_CAVES_COUNT			8
#define SWAMP_COUNT					9

#define DIRT_ROAD_TILE_TOTAL		(DIRT_ROAD_STRAIGHT_COUNT+DIRT_ROAD_CURVE_COUNT+DIRT_ROAD_JUNCTION_COUNT)
