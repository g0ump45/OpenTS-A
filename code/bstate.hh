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
**	These are the enumerated animation sequences that a building may
**	be processing. These serve to control the way that a building
**	appears.
*/
enum BStateType {
	BSTATE_NONE=-1,

	BSTATE_CONSTRUCTION,		// Construction animation.
	BSTATE_IDLE,				// Idle animation.
	BSTATE_ACTIVE,				// Animation when building is "doing its thing".
	BSTATE_FULL,				// Special alternate active state.
	BSTATE_AUX1,				// Auxiliary animation.
	BSTATE_AUX2,				// Auxiliary animation.

	BSTATE_COUNT,
	BSTATE_FIRST=0
};
