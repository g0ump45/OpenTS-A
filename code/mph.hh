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
**	Units that move can move at different speeds. These enumerate the
**	different speeds that a unit can move.
*/
enum MPHType {
	MPH_IMMOBILE=0,
	MPH_VERY_SLOW=5,        // 2
	MPH_KINDA_SLOW=6,       // 3
	MPH_SLOW=8,             // 4
	MPH_SLOW_ISH=10,        // 5
	MPH_MEDIUM_SLOW=12,     // 6
	MPH_MEDIUM=18,          // 9
	MPH_MEDIUM_FAST=30,     // 12
	MPH_MEDIUM_FASTER=35,   // 14
	MPH_FAST=40,            // 16
	MPH_ROCKET=60,          // 24
	MPH_VERY_FAST=100,      // 40
	MPH_LIGHT_SPEED=255     // 100
};
