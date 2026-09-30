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
**	For units that are cloaking, these value specify the visual character
**	of the object.
*/
enum VisualType {
	VISUAL_NORMAL,      // Completely visible -- normal.
	VISUAL_INDISTINCT,  // The edges shimmer and become indistinct.
	VISUAL_DARKEN,      // Color and texture is muted along with shimmering.
	VISUAL_SHADOWY,     // Body is translucent in addition to shimmering.
	VISUAL_RIPPLE,      // Just a ripple (true predator effect).
	VISUAL_HIDDEN       // Nothing at all is visible.
};
