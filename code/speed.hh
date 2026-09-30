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
**	Each vehicle is give a speed rating. This is a combination of not only
**	its physical speed, but the means by which it travels (wheels, tracks,
**	wings, etc). This is used to determine the movement table.
*/
enum SpeedType {
	SPEED_NONE=-1,

	SPEED_FOOT,					// Bipedal.
	SPEED_TRACK,				// Tracked locomotion.
	SPEED_WHEEL,				// Balloon tires.
	SPEED_HOVER,
	SPEED_WINGED,				// Lifter's, 'thopters, and rockets.
	SPEED_FLOAT,				// Ships.
	SPEED_AMPHIBIOUS,
	SPEED_CREEP,

	SPEED_COUNT,
	SPEED_FIRST=SPEED_FOOT
};
