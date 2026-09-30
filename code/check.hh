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
**	When performing a landing operation, the aircraft must pass through
**	navigation checkpoints. These enumerations specify the check points.
*/
enum CheckPointType {
	CHECK_STACK,    // Holding area far away from airfield.
	CHECK_DOWNWIND, // Downwind leg of approach.
	CHECK_CROSSWIND // Crosswind leg of approach.
};
