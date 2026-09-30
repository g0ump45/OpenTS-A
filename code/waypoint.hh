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
**	These are special indices into the Waypoint array; slots 0-25 are
**	reserved for letter-designated Waypoints, the others are special.
*/
enum WaypointType {
	WAYPT_HOME = 98,				// Home-cell for this scenario
	WAYPT_REINF,					// cell where reinforcements arrive
	WAYPT_SPECIAL,					// Used by special airdrop reinforcements.

	WAYPT_COUNT
};
