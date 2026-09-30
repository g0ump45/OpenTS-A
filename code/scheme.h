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

#include "hsv.h"
#include "palette.h"

#include "scheme.hh"

class Surface;
template<class T> class DynamicVectorClass;
class ConvertClass;
class LightConvertClass;


class ColorScheme
{
	public:
		ColorScheme(void);
		ColorScheme(char const * name, HSVClass &hsv, const PaletteClass & base, const PaletteClass & screenpalette, int intensity_levels);
		~ColorScheme(void);

		void Build_Light_Converters(const PaletteClass & base, const PaletteClass & screenpalette, int r = 1000, int g = 1000, int b = 1000);

		bool operator==(const ColorScheme &that);
		bool operator!=(const ColorScheme &that);

		static int Find_Or_Make(char const * name, HSVClass &hsv, const PaletteClass & base, const PaletteClass & screenpalette, int intensity_levels);

	public:
		/*
		 * This is the number given to the scheme as it joins the global scheme list. The
		 * user interface code passes it about in place of a pointer to the scheme itself.
		 */
		int ID;

		/*
		 * This is the palette holding the scheme's sixteen entry remap ramp, shaded from
		 * the base palette at the time the converter was built.
		 */
		PaletteClass Palette;

		/*
		 * This is the name that the scheme is looked up by, usually the house color it
		 * stands for. Two schemes are told apart by this alone, ignoring case.
		 */
		char * Name;

		/*
		 * This is the color that the scheme's remap ramp is shaded from. It is kept so
		 * that the converter can be rebuilt whenever the ambient lighting changes.
		 */
		HSVClass HSV;

		/*
		 * This points to the converter that draws the scheme's ramp at whichever lighting
		 * level is asked for. It is thrown away and built afresh whenever the map's
		 * lighting or tinting changes.
		 */
		LightConvertClass * Converter;

		/*
		 * This is the number of lighting levels that the converter was built with. It is
		 * part of the scheme's identity, so the same name built for a different number of
		 * levels is a different scheme.
		 */
		int IntensityLevels;

		/****************************************************************************
		**	This entry defines a complete color scheme, with the player's remap table,
		**	the font remap table, and a color scheme for dialog boxes and buttons.
		*/
		//struct RemapControlType
		//{
		int Color;					// Normal color index.
		int BrightColor;			// Highlight (bright) color index.
		//unsigned char RemapTable[256];	// Actual remap table.
		//unsigned char FontRemap[16];		// Remap table for gradient font.
		int Shadow;                 // Color of shadowed edge of a raised button.
		int Background;             // Background fill color for buttons.
		int Corners;                // Transition color between shadow and highlight.
		int Highlight;              // Bright edge of raised button.
		int Box;                    // Color for dialog box border.
		int Bright;                 // Color used for highlighted text.
		int Underline;              // Color for underlining dialog box titles.
		int Bar;                    // Selected entry list box background color.
		//};
};

ConvertClass *Build_Converter(HSVClass & hsv, const PaletteClass & base, const PaletteClass & screenpalette, Surface const & typicalsurface, PaletteClass *remapped);
ConvertClass *Build_Light_Converter(HSVClass & hsv, const PaletteClass & base, const PaletteClass & screenpalette, PaletteClass *remapped, Surface const & typicalsurface, int intensity_levels, int r, int g, int b, bool *indexes);

ColorScheme * Fetch_Scheme_By_Name(const char * name, int intensity_levels = 1);
int Fetch_Scheme_Index_By_Name(char const * name, int intensity_levels = 1);

extern DynamicVectorClass<ColorScheme *> ColorSchemes;
