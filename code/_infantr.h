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

#include "facing.hh"

/*
**	This structure is associated with each maneuver type. It tells whether the
**	maneuver can be interrupted and the frame rate.
*/
struct DoStruct {
	bool Interrupt;     // Can it be interrupted?
	bool IsMobile;      // Can it move while doing this?
	bool RandomStart;   // Should animation be "randomized"?
	unsigned char Rate; // Frame rate.
};

struct DoInfoStruct {
	int Frame;			// Starting frame of the animation.
	int Count;			// Number of frames of animation.
	int Jump;			// Frames to jump between facings.
	FacingType Facing;
};
