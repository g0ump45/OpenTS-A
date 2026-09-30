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
**	Each building has a predetermined size. These are the size numbers.
**	The trailing number is this define is the width and height (respectively)
**	of the building in cells.
*/
enum BSizeType {
	BSIZE_NONE=-1,

	BSIZE_11,
	BSIZE_21,
	BSIZE_12,
	BSIZE_22,
	BSIZE_23,
	BSIZE_32,
	BSIZE_33,
	BSIZE_35,
	BSIZE_42,
	BSIZE_33_REF,
	BSIZE_13,
	BSIZE_31,
	BSIZE_43,
	BSIZE_14,
	BSIZE_15,
	BSIZE_26,
	BSIZE_25,
	BSIZE_53,
	BSIZE_44,
	BSIZE_34,
	BSIZE_64,
	BSIZE_00,

	BSIZE_COUNT,
	BSIZE_FIRST = 0,
};
