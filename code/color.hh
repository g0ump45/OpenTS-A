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

enum ColorType {
	TBLACK,
	PURPLE,
	CYAN,
	GREEN,
	LTGREEN,
	YELLOW,
	PINK,
	BROWN,
	RED,
	LTCYAN,
	LTBLUE,
	BLUE,
	BLACK,
	GREY,
	LTGREY,
	WHITE,
	COLOR_PADDING=0x1000
};


/* These defines handle the various names given to the same color. */
#define	DKGREEN	GREEN
#define	DKBLUE	BLUE
#define	GRAY	GREY
#define	DKGREY	GREY
#define	DKGRAY	GREY
#define	LTGRAY	LTGREY

