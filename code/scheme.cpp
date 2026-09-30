/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "scheme.h"

#include "_surface.h"
#include "lightcon.h"
#include "sun.h"
#include "vector.h"

#include <cmath>
#include <cstring>

bool _indexes[256] =
{
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	1
};

DynamicVectorClass<ColorScheme *> ColorSchemes;


/// <summary>
/// Builds a lighting aware converter for a color scheme's ramp.
/// This routine shades the sixteen entry remap ramp from the color specified and hands back a
/// converter that can draw it at any of the lighting levels requested. Color schemes use this
/// routine for everything the player sees tinted by the map's lighting.
/// </summary>
/// <param name="hsv">The hue, saturation and value that the ramp is shaded from.</param>
/// <param name="base">The palette that the remapped ramp is derived from.</param>
/// <param name="screenpalette">The palette that the converter must remap into.</param>
/// <param name="remapped">Palette to receive the shaded ramp.</param>
/// <param name="typicalsurface">A surface of the pixel format the converter must feed.</param>
/// <param name="intensity_levels">The number of lighting levels the converter must
/// support.</param>
/// <param name="r">The red tint level to shade the converter with.</param>
/// <param name="g">The green tint level to shade the converter with.</param>
/// <param name="b">The blue tint level to shade the converter with.</param>
/// <param name="indexes">Flags marking which palette entries take part in the remap.</param>
/// <returns>Returns with a pointer to the newly created converter.</returns>
ConvertClass *Build_Light_Converter(HSVClass & hsv, const PaletteClass & base, const PaletteClass & screenpalette, PaletteClass * remapped, Surface const & typicalsurface, int intensity_levels, int r, int g, int b, bool *indexes)
{
	int hue = hsv.Get_Hue();
	int saturation = hsv.Get_Saturation();
	int value = hsv.Get_Value();

	*remapped = base;

	double cos_step = DEG_TO_RAD(14.0 / 3.0);
	double sin_step = DEG_TO_RAD(8.0 / 3.0);

	for (int i = 0; i < 16; i++) {
		double cosval = DEG_TO_RAD(20) + (i * cos_step);
		double sinval = DEG_TO_RAD(50) + (i * sin_step);
		if (i == 0) {
			cosval = DEG_TO_RAD(360.0/32.0); /// 11.25 degrees, expressed in radians.
		}

		int sat = int(std::sin(sinval) * saturation);
		int val = int(std::cos(cosval) * value);

		(*remapped)[i + 16] = HSVClass(hue, sat, val);
	}

	return(new LightConvertClass(*remapped, screenpalette, typicalsurface, r, g, b, false, indexes, intensity_levels));
}


/// <summary>
/// Builds a plain converter for a color scheme's ramp.
/// This routine shades the sixteen entry remap ramp from the color specified and hands back a
/// converter that maps it onto the screen palette. It is the unlit counterpart of
/// Build_Light_Converter.
/// </summary>
/// <param name="hsv">The hue, saturation and value that the ramp is shaded from.</param>
/// <param name="base">The palette that the remapped ramp is derived from.</param>
/// <param name="screenpalette">The palette that the converter must remap into.</param>
/// <param name="typicalsurface">A surface of the pixel format the converter must feed.</param>
/// <param name="remapped">Optional palette to receive the shaded ramp. May be NULL.</param>
/// <returns>Returns with a pointer to the newly created converter.</returns>
ConvertClass *Build_Converter(HSVClass & hsv, const PaletteClass & base, const PaletteClass & screenpalette, Surface const & typicalsurface, PaletteClass *remapped)
{
	int hue = hsv.Get_Hue();
	int saturation = hsv.Get_Saturation();
	int value = hsv.Get_Value();

	PaletteClass pal = base;

	double cos_step = DEG_TO_RAD(14.0 / 3.0);
	double sin_step = DEG_TO_RAD(8.0 / 3.0);

	for (int i = 0; i < 16; i++) {
		double cosval = DEG_TO_RAD(20) + (i * cos_step);
		double sinval = DEG_TO_RAD(50) + (i * sin_step);
		if (i == 0) {
			cosval = DEG_TO_RAD(360.0/32.0); /// 11.25 degrees, expressed in radians.
		}

		int sat = int(std::sin(sinval) * saturation);
		int val = int(std::cos(cosval) * value);

		pal[i + 16] = HSVClass(hue, sat, val);
	}

	if (remapped != NULL) {
		*remapped = pal;
	}

	return(new ConvertClass(pal, screenpalette, typicalsurface));
}


/// <summary>
/// Constructs a blank color scheme.
/// The scheme has no name and no converter yet; it merely takes its place in the global color
/// scheme list. Use Build_Light_Converters to give it a converter.
/// </summary>
ColorScheme::ColorScheme(void) :
	Name(NULL),
	HSV(0,0,0),
	Converter(NULL),
	IntensityLevels(1)
{
	ColorSchemes.Add(this);
	ID = ColorSchemes.Count();
}


/// <summary>
/// Builds a named color scheme.
/// This routine creates the scheme's remapped palette and light converter from the color
/// supplied, fills in the default user interface colors, and adds the scheme to the global
/// color scheme list.
/// </summary>
/// <param name="name">The name that this scheme will be looked up by.</param>
/// <param name="hsv">The hue, saturation and value that the scheme's color ramp is shaded
/// from.</param>
/// <param name="base">The palette that the scheme's remapped ramp is derived from.</param>
/// <param name="screenpalette">The palette that the converter must remap into.</param>
/// <param name="intensity_levels">The number of lighting levels to build the converter
/// with.</param>
ColorScheme::ColorScheme(const char *name, HSVClass &hsv, const PaletteClass & base, const PaletteClass & screenpalette, int intensity_levels) :
	Name(strdup(name)),
	HSV(hsv),
	Converter(NULL),
	IntensityLevels(intensity_levels),
	Color(16),
	BrightColor(15),
	Shadow(25),
	Background(24),
	Corners(22),
	Highlight(16),
	Box(19),
	Bright(16),
	Underline(16),
	Bar(21)

{
#ifdef __ANDROID__
	if (VisibleSurface == NULL) {
		Palette = base;
		double cos_step = DEG_TO_RAD(14.0 / 3.0);
		double sin_step = DEG_TO_RAD(8.0 / 3.0);
		for (int i = 0; i < 16; i++) {
			double cosval = DEG_TO_RAD(20) + (i * cos_step);
			double sinval = DEG_TO_RAD(50) + (i * sin_step);
			if (i == 0) cosval = DEG_TO_RAD(360.0 / 32.0);
			int sat = int(std::sin(sinval) * hsv.Get_Saturation());
			int val = int(std::cos(cosval) * hsv.Get_Value());
			Palette[i + 16] = HSVClass(hsv.Get_Hue(), sat, val);
		}
	} else {
		Converter = (LightConvertClass *)Build_Light_Converter(HSV, base, screenpalette, &Palette, *VisibleSurface, intensity_levels, NORMAL_LIGHT, NORMAL_LIGHT, NORMAL_LIGHT, _indexes);
	}
#else
    Converter = (LightConvertClass *)Build_Light_Converter(HSV, base, screenpalette, &Palette, *VisibleSurface, intensity_levels, NORMAL_LIGHT, NORMAL_LIGHT, NORMAL_LIGHT, _indexes);
#endif

	ColorSchemes.Add(this);
	ID = ColorSchemes.Count();
}


/// <summary>
/// Rebuilds the scheme's light converter with a new tint.
/// Use this routine when the ambient lighting changes; any converter built earlier is thrown
/// away first.
/// </summary>
/// <param name="base">The palette that the scheme's remapped ramp is derived from.</param>
/// <param name="screenpalette">The palette that the converter must remap into.</param>
/// <param name="r">The red tint level to shade the converter with.</param>
/// <param name="g">The green tint level to shade the converter with.</param>
/// <param name="b">The blue tint level to shade the converter with.</param>
void ColorScheme::Build_Light_Converters(const PaletteClass & base, const PaletteClass & screenpalette, int r, int g, int b)
{
	if (Converter != NULL) {
		delete Converter;
		Converter = NULL;
	}

#ifdef __ANDROID__
	if (VisibleSurface == NULL) {
		// Android can load scenarios before a display surface exists.
		Palette = base;
		double cos_step = DEG_TO_RAD(14.0 / 3.0);
		double sin_step = DEG_TO_RAD(8.0 / 3.0);
		for (int i = 0; i < 16; i++) {
			double cosval = DEG_TO_RAD(20) + (i * cos_step);
			double sinval = DEG_TO_RAD(50) + (i * sin_step);
			if (i == 0) {
				cosval = DEG_TO_RAD(360.0/32.0);
			}
			int sat = int(std::sin(sinval) * HSV.Get_Saturation());
			int val = int(std::cos(cosval) * HSV.Get_Value());
			Palette[i + 16] = HSVClass(HSV.Get_Hue(), sat, val);
		}
		return;
	}
#endif

	Converter = (LightConvertClass *)Build_Light_Converter(HSV, base, screenpalette, &Palette, *VisibleSurface, IntensityLevels, r, g, b, _indexes);
}


/// <summary>
/// Destroys the color scheme.
/// The scheme's name and light converter are released and the scheme drops itself from the
/// global color scheme list.
/// </summary>
ColorScheme::~ColorScheme(void)
{
	if (Name != NULL) {
		free(Name);
	}
	Name = NULL;

	if (Converter != NULL) {
		delete Converter;
	}
	Converter = NULL;

	ColorSchemes.Delete(this);
}


/// <summary>
/// Determines if two color schemes are the same.
/// Schemes are told apart by name alone, and the comparison ignores case.
/// </summary>
/// <returns>bool; Do the two schemes share a name?</returns>
bool ColorScheme::operator==(ColorScheme const & that)
{
	return(stricmp(Name, that.Name) == 0);
}


/// <summary>
/// Determines if two color schemes are different.
/// Schemes are told apart by name alone, and the comparison ignores case.
/// </summary>
/// <returns>bool; Are the two schemes named differently?</returns>
bool ColorScheme::operator!=(ColorScheme const & that)
{
	return(stricmp(Name, that.Name) != 0);
}


/// <summary>
/// Finds a color scheme by name, creating it if it does not exist yet.
/// This routine is used to fetch the house and player color schemes on demand. A scheme that
/// has not been built yet is constructed from the palettes supplied and then looked up again.
/// </summary>
/// <param name="hsv">The hue, saturation and value that the scheme's color ramp is shaded
/// from.</param>
/// <param name="base">The palette that the scheme's remapped ramp is derived from.</param>
/// <param name="screenpalette">The palette that the converter must remap into.</param>
/// <param name="intensity_levels">The number of lighting levels to build the converter
/// with.</param>
/// <returns>Returns with the index into the color scheme list.</returns>
int ColorScheme::Find_Or_Make(char const * name, HSVClass & hsv, const PaletteClass & base, const PaletteClass & screenpalette, int intensity_levels)
{
	while (true) {
		for (int i = 0; i < ColorSchemes.Count(); i++) {
			if (stricmp(name, ColorSchemes[i]->Name) == 0 && ColorSchemes[i]->IntensityLevels == intensity_levels) {
				return(i);
			}
		}
		new ColorScheme(name, hsv, base, screenpalette, intensity_levels);
	}
}


/// <summary>
/// Fetches a named color scheme.
/// This routine is the convenience form of Fetch_Scheme_Index_By_Name for callers that want
/// the scheme itself rather than its index.
/// </summary>
/// <param name="intensity_levels">The number of lighting levels the scheme must have been
/// built with.</param>
/// <returns>Returns with a pointer to the scheme. Otherwise, NULL is returned.</returns>
ColorScheme * Fetch_Scheme_By_Name(char const * name, int intensity_levels)
{
	int id = Fetch_Scheme_Index_By_Name(name, intensity_levels);

	if (id >= 0) {
		return(ColorSchemes[id]);
	}

	return(NULL);
}


/// <summary>
/// Finds the index of a named color scheme.
/// This routine is used by the dialog and text drawing code to look up a scheme it only
/// knows the name of. The intensity level count is part of the identity, so the same name
/// built for a different number of levels will not match.
/// </summary>
/// <param name="intensity_levels">The number of lighting levels the scheme must have been
/// built with.</param>
/// <returns>Returns with the index into the color scheme list, or -1 if there is no
/// match.</returns>
int Fetch_Scheme_Index_By_Name(char const * name, int intensity_levels)
{
	for (int i = 0; i < ColorSchemes.Count(); i++) {
		if (stricmp(name, ColorSchemes[i]->Name) == 0 && ColorSchemes[i]->IntensityLevels == intensity_levels) {
			return(i);
		}
	}
	return(-1);
}
