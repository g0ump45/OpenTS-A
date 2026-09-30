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

#include "_font.h"


/***************************************************************************
**	Most of the text in the game will use the six point font. These are the
**	pointers to the fonts. If it is NULL, then the font hasn't been loaded
**	yet.
*/
FontClass * /*const*/ Metal12FontPtr;	// Font for use on in-game tabs in hires
FontClass * /*const*/ MapFontPtr;		// Standard very small font.
FontClass * /*const*/ Font6Ptr;			// Standard small font.
FontClass * /*const*/ EditorFont;		// Font used for scenario editor.
FontClass * /*const*/ Font8Ptr;			// 8 point proportional.
FontClass * /*const*/ GradFont6Ptr;		// gradient 6 point font pointer.
FontClass * /*const*/ SmallFontPtr;
