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
**	Selected units have a special selected unit box around them. These are the
**	defines for the two types of selected unit boxes. One is for infantry and
**	the other is for regular units.
*/
enum SelectEnum {
	SELECT_NONE=-1,
	SELECT_INFANTRY,                // Small infantry selection box.
	SELECT_UNIT,                    // Big unit selection box.
	SELECT_BUILDING=SELECT_UNIT,    // Custom box for buildings.
	SELECT_TERRAIN=SELECT_UNIT,     // Custom box for terrain objects.
	SELECT_WRENCH,                  // A building is repairing overlay graphic.

	SELECT_COUNT
};
