/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "zgrad.hh"

class ZBuffer;

extern ZBuffer *DepthBuffer;

struct ZGradStruct {
	int BaseIncrement;     /// Z delta per pixel (horizontal step across a scanline)
	int LineIncrement;     /// Z delta per scanline (vertical step between rows)
	int StepDenominator;   /// Fractional step denominator for fine-grained vertical interpolation
	int StepNumerator;     /// Fractional step numerator controlling wrap frequency
	int WrapIncrement;     /// Z delta applied each time the fractional counter wraps
	bool IsTopDown;        /// True if Z increases linearly top-to-bottom; false if using fractional stepping (bottom-up)
};

extern ZGradStruct ZGradients[ZGRAD_COUNT];
