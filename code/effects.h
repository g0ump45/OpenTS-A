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

class PaletteClass;


struct TLucentType {
	unsigned char	SourceColor;
	unsigned char	DestColor;
	unsigned char	Fading;
	unsigned char	reserved;
};


void * Conquer_Build_Fading_Table(PaletteClass const & palette, void * dest, int color, int frac);
void * Conquer_Build_Translucent_Table(PaletteClass const & palette, TLucentType const * control, int count, void * buffer);

void * Build_Fading_Table(PaletteClass const & palette, void * dest, int color, int frac);
void * Build_Fading_Table(PaletteClass const & palette, void * dest, int color, int frac);
void * Build_Translucent_Table(PaletteClass const & palette, TLucentType const * control, int count, void * buffer);

void * Make_Fading_Table(PaletteClass const & palette, void * dest, int color, int frac);

int Translucent_Table_Size(int count);
