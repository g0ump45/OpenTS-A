/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "_zbuffer.h"

#include "zbuffer.h"

ZGradStruct ZGradients[ZGRAD_COUNT] = {
	{+1, +1, +1, +1, -1, true},	 /// ZGRAD_GROUND
	{+2, +3, +2, +3, -1, true},	 /// ZGRAD_45DEG
	{+1, +3, +1, +3, +1, false}, /// ZGRAD_90DEG
	{+1, +1, -1, -1, -1, true}	 /// ZGRAD_135DEG
};

ZBuffer *DepthBuffer;
