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
**	When objects are manipulated on the map that are marked as being
**	removed (up), placed down (down), or just to be redrawn (change);
**	or when an object's rendering (not logical) size changes, due to
**	its being selected or having an animation attached (overlap up/down).
*/
enum MarkType {
	MARK_UP,				// Removed from the map.
	MARK_DOWN,				// Placed on the map.
	MARK_CHANGE,			// Altered in place on the map.
	MARK_DOWN_FORCED,		/// Added in TS.
};
