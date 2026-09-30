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
**	These are the themes that the game can play. They must be in exact
**	same order as specified in the CONQUER.TXT file as well as the filename
**	list located in the ThemeClass.
*/
enum ThemeType {
	THEME_QUIET=-3,
	THEME_PICK_ANOTHER=-2,

	THEME_NONE=-1,

	THEME_INTRO,
	THEME_VALVES1B,
	THEME_DUSKHOUR,
	THEME_FLURRY,
	THEME_MUTANTS,
	THEME_APPROACH,
	THEME_GLOOM,
	THEME_INFRARED,
	THEME_MADRAP,
	THEME_REDSKY,
	THEME_STORM,
	THEME_TIMEBOMB,
	THEME_WHATLURK,
	THEME_DEFENSE,
	THEME_HEROISM,
	THEME_LONETROP,
	THEME_NODCRUSH,
	THEME_PHAROTEK,
	THEME_SCOUT,
	THEME_SCORE,
	THEME_MAPS,
	THEME_IONSTORM,

	THEME_COUNT,
	THEME_FIRST=0
};
