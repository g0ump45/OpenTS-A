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
**	The objects to be drawn on the map are grouped into layers. These
**	enumerated values specify those layers. The ground layer is sorted
**	from back to front.
*/
enum LayerType {
	LAYER_NONE=-1,

	LAYER_UNDERGROUND,
	LAYER_SURFACE,		// Flat on the ground (no sorting or apparent vertical height).
	LAYER_GROUND,		// Touching the ground type object (units & buildings).
	LAYER_AIR,			// Flying above the ground (explosions & flames).
	LAYER_TOP,			// Topmost layer (aircraft & bullets).

	LAYER_COUNT,
	LAYER_FIRST=0
};
