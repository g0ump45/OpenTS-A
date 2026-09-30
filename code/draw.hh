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

/*
**	Flags used to fetch the appropriate blitter object.
*/
enum ShapeFlags_Type {
	SHAPE_NORMAL,									// Standard shape (which is transparent)
	SHAPE_DARKEN			= 1 << 0,				// Force all pixels to darken the destination.
	SHAPE_TRANSLUCENT25		= 1 << 1,				// Translucent to destination (25%).
	SHAPE_TRANSLUCENT50		= 1 << 2,				// Translucent to destination (50%).
	SHAPE_TRANSLUCENT75		= ((1 << 1)|(1 << 2)),	// Translucent to destination (75%).
	SHAPE_PREDATOR 			= 1 << 3,				// Predator effect
	SHAPE_REMAP				= 1 << 4,				// Simple remap
	SHAPE_NOTRANS			= 1 << 5,				// A non transparent but otherwise standard shape
	SHAPE_ALPHA_BLEND		= 1 << 6,				/// Blend src into dest by per-pixel weights read from the alpha buffer.
	SHAPE_80				= 1 << 7,				/// Unused/reserved. Never tested in blitter selection.
	SHAPE_ALPHA_WRITE_MULT	= 1 << 8,				/// Write the alpha buffer (draws no color), scaled by the intensity argument.
	SHAPE_CENTER			= 1 << 9,				// Coords are based on shape's center pt
	SHAPE_WIN_REL			= 1 << 10,				// Coordinates are window relative instead of absolute.
	SHAPE_ALPHA				= 1 << 11,				/// Light pixels through the alpha-lighting remap read from the alpha buffer.
	SHAPE_ZREAD				= 1 << 12,				/// Depth-test against the z-buffer, flat depth.
	SHAPE_ZGRAD				= 1 << 13,				/// Depth-test against the z-buffer, gradient depth (see ZGradientType).
	SHAPE_ZWRITE			= 1 << 14,				/// Depth-test AND write the z-buffer (occluders).
	SHAPE_ALPHA_WRITE		= 1 << 15,				/// Write the alpha buffer (draws no color), unscaled.
	SHAPE_ZERO_ALPHA		= 1 << 16,				/// Draw only where the alpha buffer is zero.
	SHAPE_NONZERO_ALPHA		= 1 << 17,				/// Draw only where the alpha buffer is nonzero.
};
