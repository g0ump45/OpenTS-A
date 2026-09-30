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
**	This structure is used to control the box relief style drawn by
**	the Draw_Box() function.
*/
struct BoxStyleType {
	int	Filler;		// Center box fill color.
	int	Shadow;		// Shadow color (darker).
	int	Highlight;	// Highlight color (lighter).
	int	Corner;		// Corner color (transition).
};

enum BoxStyleEnum {
	BOXSTYLE_DOWN,          // Typical depressed edge border.
	BOXSTYLE_RAISED,        // Typical raised edge border.
	BOXSTYLE_DIS_DOWN,      // Disabled but depressed.
	BOXSTYLE_DIS_RAISED,    // Disabled but raised.
	BOXSTYLE_BOX,           // list box.
	BOXSTYLE_BORDER,        // main dialog box.

	BOXSTYLE_COUNT
};


/**********************************************************************
**	These are the control flags for Fancy_Text_Print function.
*/
enum TextPrintType {
	TPF_LASTPOINT		=0x0000,        // Use previous font point value.
	TPF_6POINT			=0x0001,        // Use 6 point font.
	TPF_8POINT			=0x0002,        // Use 8 point font.
	TPF_3POINT			=0x0003,        // Use 3 point font.
	TPF_LED				=0x0004,        // Use LED font.
	TPF_VCR				=0x0005,        // Use VCR font.
	TPF_6PT_GRAD		=0x0006,        // Use 6 point gradient font.
	TPF_MAP				=0x0007,        // Font used for popup help text.
	TPF_METAL12			=0x0008,        // Use 12 point tab font
	TPF_EFNT				=0x0009,    // Use scenario editor font.
	TPF_TYPE				=0x000A,    // Use teletype font
	TPF_SCORE			=0x000B,        // Use score screen font.
	TPF_LASTSHADOW		=0x0000,        // Use previous font palette.
	TPF_NOSHADOW		=0x0010,        // Don't have any shadow.
	TPF_DROPSHADOW		=0x0020,        // Use a simple drop shadow.
	TPF_FULLSHADOW		=0x0040,        // Use a full outline shadow.
	TPF_LIGHTSHADOW	=0x0080,            // Use engraved drop 'shadow' color.
	TPF_CENTER			=0x0100,        // Center about the X axis.
	TPF_RIGHT			=0x0200,        // Right justify text.
	TPF_MEDIUM_COLOR	=0x1000,        // Use medium color for all text gradient
	TPF_BRIGHT_COLOR	=0x2000,        // Use bright color for all text gradient
	TPF_USE_GRAD_PAL	=0x4000,        // Use a gradient palette based on fore color

	// Standard button text print flags.
	TPF_TEXT			=(TPF_6PT_GRAD|TPF_NOSHADOW),
	TPF_BUTTON			=(TPF_CENTER|TPF_6PT_GRAD|TPF_NOSHADOW),
	TPF_EBUTTON			=(TPF_CENTER|TPF_EFNT|TPF_NOSHADOW),
};
