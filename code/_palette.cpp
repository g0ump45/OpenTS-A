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

#include "always.h"

#include "palette.h"


/***************************************************************************
**	Special palettes for MCGA mode goes here. These palette buffers are used
**	for pictures that do not use the game palette or are used for fading to
**	black.
*/
PaletteClass CCPalette;
PaletteClass GamePalette;
//PaletteClass InGamePalette;
PaletteClass SchemePalette;
PaletteClass BlackPalette(RGBClass(0, 0, 0));
PaletteClass WhitePalette(RGBClass(RGBClass::MAX_VALUE, RGBClass::MAX_VALUE, RGBClass::MAX_VALUE));
PaletteClass OriginalPalette;
PaletteClass ScorePalette;
PaletteClass VoxelPalette;
PaletteClass WaypointPalette;
