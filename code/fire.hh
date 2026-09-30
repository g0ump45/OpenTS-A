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
**	These return values are used when determine if firing is legal.
**	By examining this value it can be determined what should be done
**	to fix the reason why firing wasn't allowed.
*/
enum FireErrorType {
	FIRE_OK,			// Weapon is allowed to fire.
	FIRE_AMMO,			// No ammo available to fire?
	FIRE_FACING,		// Not correctly facing target?
	FIRE_REARM,			// It is busy rearming?
	FIRE_ROTATING,		// Is it in process of rotating?
	FIRE_ILLEGAL,		// Is it targeting something illegal?
	FIRE_CANT,			// Is this unit one that cannot fire anything?
	FIRE_MOVING,		// Is it moving and not allowed to fire while moving?
	FIRE_RANGE,			// Is the target out of range?
	FIRE_CLOAKED,		// Is the shooter currently cloaked?
	FIRE_BUSY,			// Is shooter currently doing something else?
	FIRE_MUST_DEPLOY,	/// Must deploy before firing?
};
