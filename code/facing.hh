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
**	For every cell there are 8 adjacent cells. Use these direction numbers
**	when referring to adjacent cells. This comes into play when moving
**	between cells and in the Desired_Facing() algorithm.
*/
enum FacingType {
	FACING_NONE=-1,

	FACING_N,			// North
	FACING_NE,			// North-East
	FACING_E,			// East
	FACING_SE,			// South-East
	FACING_S,			// South
	FACING_SW,			// South-West
	FACING_W,			// West
	FACING_NW,			// North-West

	FACING_COUNT,			// Total of 8 directions (0..7).
	FACING_FIRST=0,

	FACING_0=FACING_N,
	FACING_45=FACING_NE,
	FACING_90=FACING_E,
	FACING_135=FACING_SE,
	FACING_180=FACING_S,
	FACING_225=FACING_SW,
	FACING_270=FACING_W,
	FACING_315=FACING_NW
};

#define MG_FACINGF_N   (1 << 7)
#define MG_FACINGF_NE  (1 << 0)
#define MG_FACINGF_E   (1 << 1)
#define MG_FACINGF_SE  (1 << 2)
#define MG_FACINGF_S   (1 << 3)
#define MG_FACINGF_SW  (1 << 4)
#define MG_FACINGF_W   (1 << 5)
#define MG_FACINGF_NW  (1 << 6)

#define MASK_FACINGF_N   (1 << 7)
#define MASK_FACINGF_NE  (1 << 0)
#define MASK_FACINGF_E   (1 << 5)
#define MASK_FACINGF_SE  (1 << 2)
#define MASK_FACINGF_S   (1 << 3)
#define MASK_FACINGF_SW  (1 << 4)
#define MASK_FACINGF_W   (1 << 1)
#define MASK_FACINGF_NW  (1 << 6)
