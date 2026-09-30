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
**	This specifies the infantry in the game. The "E" designation is
**	similar to the army classification of enlisted soldiers.
*/
enum InfantryType {
	INFANTRY_NONE=-1,

	INFANTRY_E1,
	INFANTRY_E2,
	INFANTRY_E3,
	INFANTRY_MEDIC,
	INFANTRY_WEEDGUY,
	INFANTRY_ENGINEER,
	INFANTRY_MUTANT,
	INFANTRY_CIV1,
	INFANTRY_CIV2,
	INFANTRY_CIV3,
	INFANTRY_JUMPJET,
	INFANTRY_DOGGIE,
	INFANTRY_CYC2,
	INFANTRY_UMAGON,
	INFANTRY_GHOST,
	INFANTRY_MHIJACK,
	INFANTRY_SLAV,
	INFANTRY_CHAMSPY,
	INFANTRY_MWMN,
	INFANTRY_MUTANT3,
	INFANTRY_OXANNA,
	INFANTRY_TRATOS,
	INFANTRY_CYBORG,
	INFANTRY_CTECH,

	/*
	 * Firestorm additions start here
	 */
	INFANTRY_HUEY,
	INFANTRY_CIV4,
	INFANTRY_CIV5,
	INFANTRY_CIV6,
	INFANTRY_ELCAD,

	INFANTRY_COUNT,
	INFANTRY_FIRST=0
};
