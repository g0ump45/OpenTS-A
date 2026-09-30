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
**	These are the response values when checking to see if an object
**	can enter or exist at a specified location. By examining this
**	return value, appropriate action may be chosen.
**	NOTE: If this changes, update the static array in Find_Path module.
*/
enum MoveType {
	MOVE_OK, 					// No blockage.
	MOVE_CLOAK,					// A cloaked blocking enemy object.
	MOVE_MOVING_BLOCK,			// Blocked, but only temporarily.
	MOVE_CLOSED_GATE,
	MOVE_FRIENDLY_DESTROYABLE,
	MOVE_DESTROYABLE,			// Enemy unit or building is blocking.
	MOVE_TEMP,					// Blocked by friendly unit.
	MOVE_NO,					// Strictly prohibited terrain.

	MOVE_COUNT
};
