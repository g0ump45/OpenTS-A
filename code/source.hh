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
**	Game reinforcements are each controlled by the following structure. The
**	data originates in the scenario INI file but is then carried throughout
**	any saved games.
*/
enum SourceType {
	SOURCE_NONE=-1,				// No defined source (error condition).

	SOURCE_NORTH,					// From north edge.
	SOURCE_EAST,					// From east edge.
	SOURCE_SOUTH,					// From south edge.
	SOURCE_WEST,					// From west edge.
	SOURCE_AIR,						// Dropped by air (someplace).

	SOURCE_COUNT,
	SOURCE_FIRST=0
};
