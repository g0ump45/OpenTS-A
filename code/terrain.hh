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
**	The three dimensional terrain objects are enumerated here. These
**	objects function similar to buildings in that they can be driven
**	behind and can take damage on an individual basis.
*/
enum TerrainType {
	TERRAIN_NONE=-1,

	/// TERRAIN_MINE,
	TERRAIN_BOXES01,
	TERRAIN_BOXES02,
	TERRAIN_BOXES03,
	TERRAIN_BOXES04,
	TERRAIN_BOXES05,
	TERRAIN_BOXES06,
	TERRAIN_BOXES07,
	TERRAIN_BOXES08,
	TERRAIN_BOXES09,
	TERRAIN_ICE01,
	TERRAIN_ICE02,
	TERRAIN_ICE03,
	TERRAIN_ICE04,
	TERRAIN_ICE05,
	TERRAIN_TREE01,
	TERRAIN_TREE02,
	TERRAIN_TREE03,
	TERRAIN_TREE04,
	TERRAIN_TREE05,
	TERRAIN_TREE06,
	TERRAIN_TREE07,
	TERRAIN_TREE08,
	TERRAIN_TREE09,
	TERRAIN_TREE10,
	TERRAIN_TREE11,
	TERRAIN_TREE12,
	TERRAIN_TREE13,
	TERRAIN_TREE14,
	TERRAIN_TREE15,
	TERRAIN_TREE16,
	TERRAIN_TREE17,
	TERRAIN_TREE18,
	TERRAIN_TREE19,
	TERRAIN_TREE20,
	TERRAIN_TREE21,
	TERRAIN_TREE22,
	TERRAIN_TREE23,
	TERRAIN_TREE24,
	TERRAIN_TREE25,
	TERRAIN_TIBTRE01,
	TERRAIN_TIBTRE02,
	TERRAIN_TIBTRE03,
	TERRAIN_VEINTREE,

	/*
	 * Firestorm additions start here
	 */
	TERRAIN_FONA01,
	TERRAIN_FONA02,
	TERRAIN_FONA03,
	TERRAIN_FONA04,
	TERRAIN_FONA05,
	TERRAIN_FONA06,
	TERRAIN_FONA07,
	TERRAIN_FONA08,
	TERRAIN_FONA09,
	TERRAIN_FONA10,
	TERRAIN_FONA11,
	TERRAIN_FONA12,
	TERRAIN_FONA13,
	TERRAIN_FONA14,
	TERRAIN_FONA15,
	TERRAIN_BIGBLUE3,
	TERRAIN_GAWALL,
	TERRAIN_NAWALL,

	TERRAIN_COUNT,
	TERRAIN_FIRST=0
};
