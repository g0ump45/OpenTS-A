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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /G/wwlib/Convert.cpp                                        $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 2/19/99 11:51a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "convert.h"

#include "blitblit.h"
#include "dsurface.h"
#include "hsv.h"
#include "rlerle.h"
#include "vector.h"


DynamicVectorClass<ConvertClass *> ConvertClass::Drawers;


/// <summary>
/// Constructs a drawer that maps art onto the display.
/// This routine builds the tables that convert the source artwork's palette into the
/// pixel form the display wants, at every brightness level requested, along with the
/// shadow table used to darken a color. The drawer adds itself to the list of drawers so
/// that it can be rebuilt if the display pixel format later changes.
/// </summary>
/// <param name="artpalette">The palette the source artwork was drawn with.</param>
/// <param name="screenpalette">The palette the display is currently showing.</param>
/// <param name="surface">The surface whose pixel format the drawer must match.</param>
/// <param name="intensity_levels">Number of brightness levels to build translations for.</param>
/// <param name="quick_init">Should the table and blitter building be put off until the
/// drawer is first used?</param>
ConvertClass::ConvertClass(PaletteClass const & artpalette, PaletteClass const & screenpalette, Surface const & surface, int intensity_levels, bool quick_init) :
	BBP(surface.Bytes_Per_Pixel()),
	PlainBlitter(NULL),
	TransBlitter(NULL),
	ShadowBlitter(NULL),
	RemapBlitter(NULL),
	Translucent1Blitter(NULL),
	Translucent2Blitter(NULL),
	Translucent3Blitter(NULL),
	BlitPlainXlatZReadPtr(NULL),
	BlitTransXlatZReadPtr(NULL),
	BlitTransDarkenZReadPtr(NULL),
	BlitTransZRemapXlatZReadPtr(NULL),
	BlitTransLucent75ZReadPtr(NULL),
	BlitTransLucent50ZReadPtr(NULL),
	BlitTransLucent25ZReadPtr(NULL),
	BlitTransLucent75ZReadWarpPtr(NULL),
	BlitTransLucent50ZReadWarpPtr(NULL),
	BlitTransLucent25ZReadWarpPtr(NULL),
	BlitPlainXlatZReadWritePtr(NULL),
	BlitTransXlatZReadWritePtr(NULL),
	BlitTransDarkenZReadWritePtr(NULL),
	BlitTransZRemapXlatZReadWritePtr(NULL),
	BlitTransLucent75ZReadWritePtr(NULL),
	BlitTransLucent50ZReadWritePtr(NULL),
	BlitTransLucent25ZReadWritePtr(NULL),
	BlitPlainXlatAlphaPtr(NULL),
	BlitTransXlatAlphaPtr(NULL),
	BlitTransZRemapXlatAlphaPtr(NULL),
	BlitTransLucent75AlphaPtr(NULL),
	BlitTransLucent50AlphaPtr(NULL),
	BlitTransLucent25AlphaPtr(NULL),
	BlitTransXlatWriteAlphaPtr(NULL),
	BlitTransXlatMultWriteAlphaPtr(NULL),
	BlitTranslucentWriteAlphaPtr(NULL),
	BlitTranslucent50NonzeroAlphaPtr(NULL),
	BlitTranslucent50ZeroAlphaPtr(NULL),
	BlitTranslucent75NonzeroAlphaPtr(NULL),
	BlitTranslucent75ZeroAlphaPtr(NULL),
	BlitPlainXlatAlphaZReadPtr(NULL),
	BlitTransXlatAlphaZReadPtr(NULL),
	BlitTransZRemapXlatAlphaZReadPtr(NULL),
	BlitTransLucent75AlphaZReadPtr(NULL),
	BlitTransLucent50AlphaZReadPtr(NULL),
	BlitTransLucent25AlphaZReadPtr(NULL),
	BlitTransLucent75AlphaZReadWarpPtr(NULL),
	BlitTransLucent50AlphaZReadWarpPtr(NULL),
	BlitTransLucent25AlphaZReadWarpPtr(NULL),
	BlitPlainXlatAlphaZReadWritePtr(NULL),
	BlitTransXlatAlphaZReadWritePtr(NULL),
	BlitTransZRemapXlatAlphaZReadWritePtr(NULL),
	BlitTransLucent75AlphaZReadWritePtr(NULL),
	BlitTransLucent50AlphaZReadWritePtr(NULL),
	BlitTransLucent25AlphaZReadWritePtr(NULL),
	RLETransBlitter(NULL),
	RLEShadowBlitter(NULL),
	RLERemapBlitter(NULL),
	RLETranslucent1Blitter(NULL),
	RLETranslucent2Blitter(NULL),
	RLETranslucent3Blitter(NULL),
	RLEBlitTransXlatZReadPtr(NULL),
	RLEBlitTransZRemapXlatZReadPtr(NULL),
	RLEBlitTransDarkenZReadPtr(NULL),
	RLEBlitTransLucent75ZReadPtr(NULL),
	RLEBlitTransLucent50ZReadPtr(NULL),
	RLEBlitTransLucent25ZReadPtr(NULL),
	RLEBlitTransLucent75ZReadWarpPtr(NULL),
	RLEBlitTransLucent50ZReadWarpPtr(NULL),
	RLEBlitTransLucent25ZReadWarpPtr(NULL),
	RLEBlitTransXlatZReadWritePtr(NULL),
	RLEBlitTransZRemapXlatZReadWritePtr(NULL),
	RLEBlitTransDarkenZReadWritePtr(NULL),
	RLEBlitTransLucent75ZReadWritePtr(NULL),
	RLEBlitTransLucent50ZReadWritePtr(NULL),
	RLEBlitTransLucent25ZReadWritePtr(NULL),
	RLEBlitTransXlatAlphaPtr(NULL),
	RLEBlitTransZRemapXlatAlphaPtr(NULL),
	RLEBlitTransLucent75AlphaPtr(NULL),
	RLEBlitTransLucent50AlphaPtr(NULL),
	RLEBlitTransLucent25AlphaPtr(NULL),
	RLEBlitTransXlatAlphaZReadPtr(NULL),
	RLEBlitTransZRemapXlatAlphaZReadPtr(NULL),
	RLEBlitTransLucent75AlphaZReadPtr(NULL),
	RLEBlitTransLucent50AlphaZReadPtr(NULL),
	RLEBlitTransLucent25AlphaZReadPtr(NULL),
	RLEBlitTransLucent75AlphaZReadWarpPtr(NULL),
	RLEBlitTransLucent50AlphaZReadWarpPtr(NULL),
	RLEBlitTransLucent25AlphaZReadWarpPtr(NULL),
	RLEBlitTransXlatAlphaZReadWritePtr(NULL),
	RLEBlitTransZRemapXlatAlphaZReadWritePtr(NULL),
	RLEBlitTransLucent75AlphaZReadWritePtr(NULL),
	RLEBlitTransLucent50AlphaZReadWritePtr(NULL),
	RLEBlitTransLucent25AlphaZReadWritePtr(NULL),
	IntensityLevels(intensity_levels),
	IntensityTranslator(NULL),
	Translator(NULL),
	ShadowTable(NULL),
	RemapTable(NULL)
	//HalfbrightMask(0),
	//QuarterbrightMask(0)
{
	if (IntensityLevels < 1) {
		IntensityLevels = 1;
	}

	/*
	**	The draw data initialization is greatly dependant upon the pixel format
	**	of the display surface. Check the pixel format and set the values accordingly.
	*/
	if (BBP == 1) {

		/*
		**	Build the shadow table by creating a slightly darker version of
		**	the color and then finding the closest match to it.
		*/
		ShadowTable = new unsigned char [256];
		ShadowTable[0] = 0;
		for (int shadow = 1; shadow < 256; shadow++) {
			HSVClass hsv = artpalette[shadow];
			hsv.Set_Value((unsigned char)(hsv.Get_Value() / 2));
			ShadowTable[shadow] = (unsigned char)artpalette.Closest_Color(hsv);
		}

		/*
		**	The translator table is created by finding the closest color
		**	in the display palette from each color in the source art
		**	palette.
		*/
		IntensityTranslator = new unsigned char [256 * IntensityLevels];
		unsigned char * trans = (unsigned char *)IntensityTranslator;
		Translator = &trans[256 * ((IntensityLevels - 1) >> 1)];

		if (IntensityLevels == 1) {
			trans[0] = 0;
			trans++;
			for (int index = 1; index < 256; index++) {
				trans[0] = (unsigned char)screenpalette.Closest_Color(artpalette[index]);
				trans++;
			}
		} else {
			for (int t = 0; t <= IntensityLevels - 1; t++) {
				trans[0] = 0;
				trans++;
				for (int index = 1; index < 256; index++) {
					HSVClass hsv = artpalette[index];
					hsv.Set_Value((unsigned char)((t * hsv.Get_Value() * 2) / (IntensityLevels - 1)));
					trans[0] = (unsigned char)screenpalette.Closest_Color(hsv);
					trans++;
				}
			}
		}

	} else {

		/*
		**	The hicolor translation table is constructed according to the pixel
		**	format of the display and the source art palette.
		*/
		//assert(surface.Is_Direct_Draw());
		IntensityTranslator = new unsigned short [256 * IntensityLevels];
		unsigned short * trans = (unsigned short *)IntensityTranslator;
		Translator = &trans[256 * ((IntensityLevels - 1) >> 1)];

		if (!quick_init) {
			((DSurface &)surface).Build_Remap_Table((unsigned short *)trans, IntensityLevels, artpalette);
		}

		/*
		**	Fetch the pixel mask values to be used for the various algorithmic
		**	pixel processing performed for hicolor displays.
		*/
		HalfbrightMask = ((DSurface &)surface).Get_Halfbright_Mask();
		QuarterbrightMask = ((DSurface &)surface).Get_Quarterbright_Mask();
	}

	if (!quick_init) {
		Create_Blitters();
	}

	Drawers.Add(this);
}


/// <summary>
/// Creates the blitters this drawer will hand out.
/// This routine builds one blitter for every supported combination of remapping,
/// translucency, alpha and depth buffer handling, in both plain and RLE flavors, and in
/// the form appropriate to the display's pixel depth. The blitter lookup routines call
/// this routine on demand, so there is no need to call it directly.
/// </summary>
void ConvertClass::Create_Blitters(void)
{
	if (BBP == 1) {

		/*
		**	Construct all the blitter objects necessary to support the functionality
		**	required for the draw permutations.
		*/
		PlainBlitter = new BlitPlainXlat<unsigned char>((unsigned char const *)Translator);
		TransBlitter = new BlitTransXlat<unsigned char>((unsigned char const *)Translator);
		RemapBlitter = new BlitTransZRemapXlat<unsigned char>(&RemapTable, (unsigned char const *)Translator);
		ShadowBlitter = new BlitTransRemapDest<unsigned char>(ShadowTable);
		Translucent1Blitter = new BlitTransRemapXlat<unsigned char>(ShadowTable, (unsigned char const *)Translator);
		Translucent2Blitter = new BlitTransRemapXlat<unsigned char>(ShadowTable, (unsigned char const *)Translator);
		Translucent3Blitter = new BlitTransRemapXlat<unsigned char>(ShadowTable, (unsigned char const *)Translator);

		/*
		**	Create the RLE aware blitter objects.
		*/
		RLETransBlitter = new RLEBlitTransXlat<unsigned char>((unsigned char const *)Translator);
		RLERemapBlitter = new RLEBlitTransZRemapXlat<unsigned char>(&RemapTable, (unsigned char const *)Translator);
		RLEShadowBlitter = new RLEBlitTransRemapDest<unsigned char>(ShadowTable);
		RLETranslucent1Blitter = new RLEBlitTransRemapXlat<unsigned char>(ShadowTable, (unsigned char const *)Translator);
		RLETranslucent2Blitter = new RLEBlitTransRemapXlat<unsigned char>(ShadowTable, (unsigned char const *)Translator);
		RLETranslucent3Blitter = new RLEBlitTransRemapXlat<unsigned char>(ShadowTable, (unsigned char const *)Translator);

		RLEBlitTransXlatZReadPtr = new RLEBlitTransXlatZRead<unsigned char>((unsigned char const *)Translator);
		RLEBlitTransZRemapXlatZReadPtr = new RLEBlitTransZRemapXlatZRead<unsigned char>(&RemapTable, (unsigned char const*)Translator);
		RLEBlitTransDarkenZReadPtr = new RLEBlitTransRemapDestZRead<unsigned char>(ShadowTable);
		RLEBlitTransLucent75ZReadPtr = new RLEBlitTransRemapXlatZRead<unsigned char>(ShadowTable, (unsigned char const *)Translator);
		RLEBlitTransLucent50ZReadPtr = new RLEBlitTransRemapXlatZRead<unsigned char>(ShadowTable, (unsigned char const *)Translator);
		RLEBlitTransLucent25ZReadPtr = new RLEBlitTransRemapXlatZRead<unsigned char>(ShadowTable, (unsigned char const *)Translator);

		RLEBlitTransXlatZReadWritePtr = new RLEBlitTransXlatZReadWrite<unsigned char>((unsigned char const *)Translator);
		RLEBlitTransZRemapXlatZReadWritePtr = new RLEBlitTransZRemapXlatZReadWrite<unsigned char>(&RemapTable, (unsigned char const*)Translator);
		RLEBlitTransDarkenZReadWritePtr = new RLEBlitTransRemapDestZReadWrite<unsigned char>(ShadowTable);
		RLEBlitTransLucent75ZReadWritePtr = new RLEBlitTransRemapXlatZReadWrite<unsigned char>(ShadowTable, (unsigned char const *)Translator);
		RLEBlitTransLucent50ZReadWritePtr = new RLEBlitTransRemapXlatZReadWrite<unsigned char>(ShadowTable, (unsigned char const *)Translator);
		RLEBlitTransLucent25ZReadWritePtr = new RLEBlitTransRemapXlatZReadWrite<unsigned char>(ShadowTable, (unsigned char const *)Translator);

	} else {

		/*
		**	Construct all the blitter objects necessary to support the functionality
		**	required for the draw permutations.
		*/
		PlainBlitter = new BlitPlainXlat<unsigned short>((unsigned short const *)Translator);
		TransBlitter = new BlitTransXlat<unsigned short>((unsigned short const *)Translator);
		RemapBlitter = new BlitTransZRemapXlat<unsigned short>(&RemapTable, (unsigned short const *)Translator);
		ShadowBlitter = new BlitTransDarken<unsigned short>((unsigned short)HalfbrightMask);
		Translucent1Blitter = new BlitTransLucent75<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		Translucent2Blitter = new BlitTransLucent50<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		Translucent3Blitter = new BlitTransLucent25<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);

		BlitPlainXlatZReadPtr = new BlitPlainXlatZRead<unsigned short>((unsigned short const *)Translator);
		BlitTransXlatZReadPtr = new BlitTransXlatZRead<unsigned short>((unsigned short const *)Translator);
		BlitTransZRemapXlatZReadPtr = new BlitTransZRemapXlatZRead<unsigned short>(&RemapTable, (unsigned short const*)Translator);
		BlitTransDarkenZReadPtr = new BlitTransDarkenZRead<unsigned short>((unsigned short)HalfbrightMask);
		BlitTransLucent75ZReadPtr = new BlitTransLucent75ZRead<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		BlitTransLucent50ZReadPtr = new BlitTransLucent50ZRead<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		BlitTransLucent25ZReadPtr = new BlitTransLucent25ZRead<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		BlitTransLucent75ZReadWarpPtr = new BlitTransLucent75ZReadWarp<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		BlitTransLucent50ZReadWarpPtr = new BlitTransLucent50ZReadWarp<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		BlitTransLucent25ZReadWarpPtr = new BlitTransLucent25ZReadWarp<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);

		BlitPlainXlatZReadWritePtr = new BlitPlainXlatZReadWrite<unsigned short>((unsigned short const *)Translator);
		BlitTransXlatZReadWritePtr = new BlitTransXlatZReadWrite<unsigned short>((unsigned short const *)Translator);
		BlitTransZRemapXlatZReadWritePtr = new BlitTransZRemapXlatZReadWrite<unsigned short>(&RemapTable, (unsigned short const*)Translator);
		BlitTransDarkenZReadWritePtr = new BlitTransDarkenZReadWrite<unsigned short>((unsigned short)HalfbrightMask);
		BlitTransLucent75ZReadWritePtr = new BlitTransLucent75ZReadWrite<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		BlitTransLucent50ZReadWritePtr = new BlitTransLucent50ZReadWrite<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		BlitTransLucent25ZReadWritePtr = new BlitTransLucent25ZReadWrite<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);

		BlitPlainXlatAlphaPtr = new BlitPlainXlatAlpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels);
		BlitTransXlatAlphaPtr = new BlitTransXlatAlpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels);
		BlitTransZRemapXlatAlphaPtr = new BlitTransZRemapXlatAlpha<unsigned short>(&RemapTable, (unsigned short const *)IntensityTranslator, IntensityLevels);
		BlitTransLucent75AlphaPtr = new BlitTransLucent75Alpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		BlitTransLucent50AlphaPtr = new BlitTransLucent50Alpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)HalfbrightMask);
		BlitTransLucent25AlphaPtr = new BlitTransLucent25Alpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);

		BlitTransXlatWriteAlphaPtr = new BlitTransXlatWriteAlpha<unsigned short>(/*no args*/);
		BlitTransXlatMultWriteAlphaPtr = new BlitTransXlatMultWriteAlpha<unsigned short>(/*no args*/);
		BlitTranslucentWriteAlphaPtr = new BlitTranslucentWriteAlpha<unsigned short>((unsigned short const *)IntensityTranslator);
		BlitTranslucent50NonzeroAlphaPtr = new BlitTranslucent50NonzeroAlpha<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		BlitTranslucent50ZeroAlphaPtr = new BlitTranslucent50ZeroAlpha<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		BlitTranslucent75NonzeroAlphaPtr = new BlitTranslucent75NonzeroAlpha<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		BlitTranslucent75ZeroAlphaPtr = new BlitTranslucent75ZeroAlpha<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);

		BlitPlainXlatAlphaZReadPtr = new BlitPlainXlatAlpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels);
		BlitTransXlatAlphaZReadPtr = new BlitTransXlatAlphaZRead<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels);
		BlitTransZRemapXlatAlphaZReadPtr = new BlitTransZRemapXlatAlphaZRead<unsigned short>(&RemapTable, (unsigned short const *)IntensityTranslator, IntensityLevels);
		BlitTransLucent75AlphaZReadPtr = new BlitTransLucent75AlphaZRead<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		BlitTransLucent50AlphaZReadPtr = new BlitTransLucent50AlphaZRead<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)HalfbrightMask);
		BlitTransLucent25AlphaZReadPtr = new BlitTransLucent25AlphaZRead<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		BlitTransLucent75AlphaZReadWarpPtr = new BlitTransLucent75AlphaZReadWarp<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		BlitTransLucent50AlphaZReadWarpPtr = new BlitTransLucent50AlphaZReadWarp<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)HalfbrightMask);
		BlitTransLucent25AlphaZReadWarpPtr = new BlitTransLucent25AlphaZReadWarp<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);

		BlitPlainXlatAlphaZReadWritePtr = new BlitPlainXlatAlpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels);
		BlitTransXlatAlphaZReadWritePtr = new BlitTransXlatAlphaZReadWrite<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels);
		BlitTransZRemapXlatAlphaZReadWritePtr = new BlitTransZRemapXlatAlphaZReadWrite<unsigned short>(&RemapTable, (unsigned short const *)IntensityTranslator, IntensityLevels);
		BlitTransLucent75AlphaZReadWritePtr = new BlitTransLucent75AlphaZReadWrite<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		BlitTransLucent50AlphaZReadWritePtr = new BlitTransLucent50AlphaZReadWrite<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)HalfbrightMask);
		BlitTransLucent25AlphaZReadWritePtr = new BlitTransLucent25AlphaZReadWrite<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);

		/*
		**	Create the RLE aware blitter objects.
		*/
		RLETransBlitter = new RLEBlitTransXlat<unsigned short>((unsigned short const *)Translator);
		RLERemapBlitter = new RLEBlitTransZRemapXlat<unsigned short>(&RemapTable, (unsigned short const *)Translator);
		RLEShadowBlitter = new RLEBlitTransDarken<unsigned short>((unsigned short)HalfbrightMask);
		RLETranslucent1Blitter = new RLEBlitTransLucent75<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		RLETranslucent2Blitter = new RLEBlitTransLucent50<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		RLETranslucent3Blitter = new RLEBlitTransLucent25<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);

		RLEBlitTransXlatZReadPtr = new RLEBlitTransXlatZRead<unsigned short>((unsigned short const *)Translator);
		RLEBlitTransZRemapXlatZReadPtr = new RLEBlitTransZRemapXlatZRead<unsigned short>(&RemapTable, (unsigned short const*)Translator);
		RLEBlitTransDarkenZReadPtr = new RLEBlitTransDarkenZRead<unsigned short>((unsigned short)HalfbrightMask);
		RLEBlitTransLucent75ZReadPtr = new RLEBlitTransLucent75ZRead<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		RLEBlitTransLucent50ZReadPtr = new RLEBlitTransLucent50ZRead<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		RLEBlitTransLucent25ZReadPtr = new RLEBlitTransLucent25ZRead<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		RLEBlitTransLucent75ZReadWarpPtr = new RLEBlitTransLucent75ZReadWarp<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		RLEBlitTransLucent50ZReadWarpPtr = new RLEBlitTransLucent50ZReadWarp<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		RLEBlitTransLucent25ZReadWarpPtr = new RLEBlitTransLucent25ZReadWarp<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);

		RLEBlitTransXlatZReadWritePtr = new RLEBlitTransXlatZReadWrite<unsigned short>((unsigned short const *)Translator);
		RLEBlitTransZRemapXlatZReadWritePtr = new RLEBlitTransZRemapXlatZReadWrite<unsigned short>(&RemapTable, (unsigned short const*)Translator);
		RLEBlitTransDarkenZReadWritePtr = new RLEBlitTransDarkenZReadWrite<unsigned short>((unsigned short)HalfbrightMask);
		RLEBlitTransLucent75ZReadWritePtr = new RLEBlitTransLucent75ZReadWrite<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);
		RLEBlitTransLucent50ZReadWritePtr = new RLEBlitTransLucent50ZReadWrite<unsigned short>((unsigned short const *)Translator, (unsigned short)HalfbrightMask);
		RLEBlitTransLucent25ZReadWritePtr = new RLEBlitTransLucent25ZReadWrite<unsigned short>((unsigned short const *)Translator, (unsigned short)QuarterbrightMask);

		RLEBlitTransXlatAlphaPtr = new RLEBlitTransXlatAlpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels);
		RLEBlitTransZRemapXlatAlphaPtr = new RLEBlitTransZRemapXlatAlpha<unsigned short>(&RemapTable, (unsigned short const *)IntensityTranslator, IntensityLevels);
		RLEBlitTransLucent75AlphaPtr = new RLEBlitTransLucent75Alpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		RLEBlitTransLucent50AlphaPtr = new RLEBlitTransLucent50Alpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)HalfbrightMask);
		RLEBlitTransLucent25AlphaPtr = new RLEBlitTransLucent25Alpha<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);

		RLEBlitTransXlatAlphaZReadPtr = new RLEBlitTransXlatAlphaZRead<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels);
		RLEBlitTransZRemapXlatAlphaZReadPtr = new RLEBlitTransZRemapXlatAlphaZRead<unsigned short>(&RemapTable, (unsigned short const *)IntensityTranslator, IntensityLevels);
		RLEBlitTransLucent75AlphaZReadPtr = new RLEBlitTransLucent75AlphaZRead<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		RLEBlitTransLucent50AlphaZReadPtr = new RLEBlitTransLucent50AlphaZRead<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)HalfbrightMask);
		RLEBlitTransLucent25AlphaZReadPtr = new RLEBlitTransLucent25AlphaZRead<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		RLEBlitTransLucent75AlphaZReadWarpPtr = new RLEBlitTransLucent75AlphaZReadWarp<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		RLEBlitTransLucent50AlphaZReadWarpPtr = new RLEBlitTransLucent50AlphaZReadWarp<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)HalfbrightMask);
		RLEBlitTransLucent25AlphaZReadWarpPtr = new RLEBlitTransLucent25AlphaZReadWarp<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);

		RLEBlitTransXlatAlphaZReadWritePtr = new RLEBlitTransXlatAlphaZReadWrite<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels);
		RLEBlitTransZRemapXlatAlphaZReadWritePtr = new RLEBlitTransZRemapXlatAlphaZReadWrite<unsigned short>(&RemapTable, (unsigned short const *)IntensityTranslator, IntensityLevels);
		RLEBlitTransLucent75AlphaZReadWritePtr = new RLEBlitTransLucent75AlphaZReadWrite<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
		RLEBlitTransLucent50AlphaZReadWritePtr = new RLEBlitTransLucent50AlphaZReadWrite<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)HalfbrightMask);
		RLEBlitTransLucent25AlphaZReadWritePtr = new RLEBlitTransLucent25AlphaZReadWrite<unsigned short>((unsigned short const *)IntensityTranslator, IntensityLevels, (unsigned short)QuarterbrightMask);
	}
}


/// <summary>
/// Destroys this drawer object.
/// The blitters and the translation tables are freed and the drawer takes itself off the
/// list of drawers, so that a later display format change will not try to rebuild it.
/// </summary>
ConvertClass::~ConvertClass(void)
{
	Destroy_Blitters();

	delete [] IntensityTranslator;
	IntensityTranslator = NULL;

	delete [] ShadowTable;
	ShadowTable = NULL;

	Drawers.Delete(this);
}


/// <summary>
/// Destroys the blitters this drawer owns.
/// This routine is used when the drawer is being torn down, and when the display pixel
/// format has changed so that the blitters must be built afresh. The drawer is left in
/// a usable state -- the next request for a blitter will simply build them again.
/// </summary>
void ConvertClass::Destroy_Blitters(void)
{
	delete PlainBlitter;
	PlainBlitter = NULL;

	delete TransBlitter;
	TransBlitter = NULL;

	delete ShadowBlitter;
	ShadowBlitter = NULL;

	delete RemapBlitter;
	RemapBlitter = NULL;

	delete Translucent1Blitter;
	Translucent1Blitter = NULL;

	delete Translucent2Blitter;
	Translucent2Blitter = NULL;

	delete Translucent3Blitter;
	Translucent3Blitter = NULL;

	delete BlitPlainXlatZReadPtr;
	BlitPlainXlatZReadPtr = NULL;

	delete BlitTransXlatZReadPtr;
	BlitTransXlatZReadPtr = NULL;

	delete BlitTransDarkenZReadPtr;
	BlitTransDarkenZReadPtr = NULL;

	delete BlitTransZRemapXlatZReadPtr;
	BlitTransZRemapXlatZReadPtr = NULL;

	delete BlitTransLucent75ZReadPtr;
	BlitTransLucent75ZReadPtr = NULL;

	delete BlitTransLucent50ZReadPtr;
	BlitTransLucent50ZReadPtr = NULL;

	delete BlitTransLucent25ZReadPtr;
	BlitTransLucent25ZReadPtr = NULL;

	delete BlitTransLucent75ZReadWarpPtr;
	BlitTransLucent75ZReadWarpPtr = NULL;

	delete BlitTransLucent50ZReadWarpPtr;
	BlitTransLucent50ZReadWarpPtr = NULL;

	delete BlitTransLucent25ZReadWarpPtr;
	BlitTransLucent25ZReadWarpPtr = NULL;

	delete BlitPlainXlatZReadWritePtr;
	BlitPlainXlatZReadWritePtr = NULL;

	delete BlitTransXlatZReadWritePtr;
	BlitTransXlatZReadWritePtr = NULL;

	delete BlitTransDarkenZReadWritePtr;
	BlitTransDarkenZReadWritePtr = NULL;

	delete BlitTransZRemapXlatZReadWritePtr;
	BlitTransZRemapXlatZReadWritePtr = NULL;

	delete BlitTransLucent75ZReadWritePtr;
	BlitTransLucent75ZReadWritePtr = NULL;

	delete BlitTransLucent50ZReadWritePtr;
	BlitTransLucent50ZReadWritePtr = NULL;

	delete BlitTransLucent25ZReadWritePtr;
	BlitTransLucent25ZReadWritePtr = NULL;

	delete BlitPlainXlatAlphaPtr;
	BlitPlainXlatAlphaPtr = NULL;

	delete BlitTransXlatAlphaPtr;
	BlitTransXlatAlphaPtr = NULL;

	delete BlitTransZRemapXlatAlphaPtr;
	BlitTransZRemapXlatAlphaPtr = NULL;

	delete BlitTransLucent75AlphaPtr;
	BlitTransLucent75AlphaPtr = NULL;

	delete BlitTransLucent50AlphaPtr;
	BlitTransLucent50AlphaPtr = NULL;

	delete BlitTransLucent25AlphaPtr;
	BlitTransLucent25AlphaPtr = NULL;

	delete BlitTranslucent50NonzeroAlphaPtr;
	BlitTranslucent50NonzeroAlphaPtr = NULL;

	delete BlitTranslucent50ZeroAlphaPtr;
	BlitTranslucent50ZeroAlphaPtr = NULL;

	delete BlitTranslucent75NonzeroAlphaPtr;
	BlitTranslucent75NonzeroAlphaPtr = NULL;

	delete BlitTranslucent75ZeroAlphaPtr;
	BlitTranslucent75ZeroAlphaPtr = NULL;

	delete BlitTransXlatWriteAlphaPtr;
	BlitTransXlatWriteAlphaPtr = NULL;

	delete BlitTransXlatMultWriteAlphaPtr;
	BlitTransXlatMultWriteAlphaPtr = NULL;

	delete BlitTranslucentWriteAlphaPtr;
	BlitTranslucentWriteAlphaPtr = NULL;

	delete BlitPlainXlatAlphaZReadPtr;
	BlitPlainXlatAlphaZReadPtr = NULL;

	delete BlitTransXlatAlphaZReadPtr;
	BlitTransXlatAlphaZReadPtr = NULL;

	delete BlitTransZRemapXlatAlphaZReadPtr;
	BlitTransZRemapXlatAlphaZReadPtr = NULL;

	delete BlitTransLucent75AlphaZReadPtr;
	BlitTransLucent75AlphaZReadPtr = NULL;

	delete BlitTransLucent50AlphaZReadPtr;
	BlitTransLucent50AlphaZReadPtr = NULL;

	delete BlitTransLucent25AlphaZReadPtr;
	BlitTransLucent25AlphaZReadPtr = NULL;

	delete BlitTransLucent75AlphaZReadWarpPtr;
	BlitTransLucent75AlphaZReadWarpPtr = NULL;

	delete BlitTransLucent50AlphaZReadWarpPtr;
	BlitTransLucent50AlphaZReadWarpPtr = NULL;

	delete BlitTransLucent25AlphaZReadWarpPtr;
	BlitTransLucent25AlphaZReadWarpPtr = NULL;

	delete BlitPlainXlatAlphaZReadWritePtr;
	BlitPlainXlatAlphaZReadWritePtr = NULL;

	delete BlitTransXlatAlphaZReadWritePtr;
	BlitTransXlatAlphaZReadWritePtr = NULL;

	delete BlitTransZRemapXlatAlphaZReadWritePtr;
	BlitTransZRemapXlatAlphaZReadWritePtr = NULL;

	delete BlitTransLucent75AlphaZReadWritePtr;
	BlitTransLucent75AlphaZReadWritePtr = NULL;

	delete BlitTransLucent50AlphaZReadWritePtr;
	BlitTransLucent50AlphaZReadWritePtr = NULL;

	delete BlitTransLucent25AlphaZReadWritePtr;
	BlitTransLucent25AlphaZReadWritePtr = NULL;

	delete RLETransBlitter;
	RLETransBlitter = NULL;

	delete RLEShadowBlitter;
	RLEShadowBlitter = NULL;

	delete RLERemapBlitter;
	RLERemapBlitter = NULL;

	delete RLETranslucent1Blitter;
	RLETranslucent1Blitter = NULL;

	delete RLETranslucent2Blitter;
	RLETranslucent2Blitter = NULL;

	delete RLETranslucent3Blitter;
	RLETranslucent3Blitter = NULL;

	delete RLEBlitTransXlatZReadPtr;
	RLEBlitTransXlatZReadPtr = NULL;

	delete RLEBlitTransZRemapXlatZReadPtr;
	RLEBlitTransZRemapXlatZReadPtr = NULL;

	delete RLEBlitTransDarkenZReadPtr;
	RLEBlitTransDarkenZReadPtr = NULL;

	delete RLEBlitTransLucent75ZReadPtr;
	RLEBlitTransLucent75ZReadPtr = NULL;

	delete RLEBlitTransLucent50ZReadPtr;
	RLEBlitTransLucent50ZReadPtr = NULL;

	delete RLEBlitTransLucent25ZReadPtr;
	RLEBlitTransLucent25ZReadPtr = NULL;

	delete RLEBlitTransLucent75ZReadWarpPtr;
	RLEBlitTransLucent75ZReadWarpPtr = NULL;

	delete RLEBlitTransLucent50ZReadWarpPtr;
	RLEBlitTransLucent50ZReadWarpPtr = NULL;

	delete RLEBlitTransLucent25ZReadWarpPtr;
	RLEBlitTransLucent25ZReadWarpPtr = NULL;

	delete RLEBlitTransXlatZReadWritePtr;
	RLEBlitTransXlatZReadWritePtr = NULL;

	delete RLEBlitTransZRemapXlatZReadWritePtr;
	RLEBlitTransZRemapXlatZReadWritePtr = NULL;

	delete RLEBlitTransDarkenZReadWritePtr;
	RLEBlitTransDarkenZReadWritePtr = NULL;

	delete RLEBlitTransLucent75ZReadWritePtr;
	RLEBlitTransLucent75ZReadWritePtr = NULL;

	delete RLEBlitTransLucent50ZReadWritePtr;
	RLEBlitTransLucent50ZReadWritePtr = NULL;

	delete RLEBlitTransLucent25ZReadWritePtr;
	RLEBlitTransLucent25ZReadWritePtr = NULL;

	delete RLEBlitTransXlatAlphaPtr;
	RLEBlitTransXlatAlphaPtr = NULL;

	delete RLEBlitTransZRemapXlatAlphaPtr;
	RLEBlitTransZRemapXlatAlphaPtr = NULL;

	delete RLEBlitTransLucent75AlphaPtr;
	RLEBlitTransLucent75AlphaPtr = NULL;

	delete RLEBlitTransLucent50AlphaPtr;
	RLEBlitTransLucent50AlphaPtr = NULL;

	delete RLEBlitTransLucent25AlphaPtr;
	RLEBlitTransLucent25AlphaPtr = NULL;

	delete RLEBlitTransXlatAlphaZReadPtr;
	RLEBlitTransXlatAlphaZReadPtr = NULL;

	delete RLEBlitTransZRemapXlatAlphaZReadPtr;
	RLEBlitTransZRemapXlatAlphaZReadPtr = NULL;

	delete RLEBlitTransLucent75AlphaZReadPtr;
	RLEBlitTransLucent75AlphaZReadPtr = NULL;

	delete RLEBlitTransLucent50AlphaZReadPtr;
	RLEBlitTransLucent50AlphaZReadPtr = NULL;

	delete RLEBlitTransLucent25AlphaZReadPtr;
	RLEBlitTransLucent25AlphaZReadPtr = NULL;

	delete RLEBlitTransLucent75AlphaZReadWarpPtr;
	RLEBlitTransLucent75AlphaZReadWarpPtr = NULL;

	delete RLEBlitTransLucent50AlphaZReadWarpPtr;
	RLEBlitTransLucent50AlphaZReadWarpPtr = NULL;

	delete RLEBlitTransLucent25AlphaZReadWarpPtr;
	RLEBlitTransLucent25AlphaZReadWarpPtr = NULL;

	delete RLEBlitTransXlatAlphaZReadWritePtr;
	RLEBlitTransXlatAlphaZReadWritePtr = NULL;

	delete RLEBlitTransZRemapXlatAlphaZReadWritePtr;
	RLEBlitTransZRemapXlatAlphaZReadWritePtr = NULL;

	delete RLEBlitTransLucent75AlphaZReadWritePtr;
	RLEBlitTransLucent75AlphaZReadWritePtr = NULL;

	delete RLEBlitTransLucent50AlphaZReadWritePtr;
	RLEBlitTransLucent50AlphaZReadWritePtr = NULL;

	delete RLEBlitTransLucent25AlphaZReadWritePtr;
	RLEBlitTransLucent25AlphaZReadWritePtr = NULL;
}


/// <summary>
/// Fetches the blitter that satisfies the drawing flags.
/// This routine is used by the shape drawing routines to pick the blitter that performs
/// the requested combination of remapping, translucency, alpha and depth buffer work on
/// an uncompressed shape. If this drawer has no blitters yet, they are created first.
/// </summary>
/// <returns>Returns with a pointer to the blitter to draw with.</returns>
Blitter const * ConvertClass::Blitter_From_Flags(ShapeFlags_Type flags) const
{
	static ShapeFlags_Type z_read_flags = ShapeFlags_Type(SHAPE_ZREAD|SHAPE_ZGRAD);

	if (PlainBlitter == NULL) {
		((ConvertClass *)this)->Create_Blitters();
	}

	if (flags & SHAPE_REMAP) {

		if (flags & SHAPE_ZWRITE) {

			if (flags & SHAPE_ALPHA) {
				return(BlitTransZRemapXlatAlphaZReadWritePtr);
			}

			return(BlitTransZRemapXlatZReadWritePtr);
		}

		if (flags & z_read_flags) {

			if (flags & SHAPE_ALPHA) {
				return(BlitTransZRemapXlatAlphaZReadPtr);
			}

			return(BlitTransZRemapXlatZReadPtr);
		}

		if (flags & SHAPE_ALPHA) {
			return(BlitTransZRemapXlatAlphaPtr);
		}

		return(RemapBlitter);
	}

	/*
	**	Quick check to see if this is a translucent operation. If so, then no
	**	further examination of the flags is necessary.
	*/
	switch (flags & (SHAPE_TRANSLUCENT25 | SHAPE_TRANSLUCENT50 | SHAPE_TRANSLUCENT75)) {
		case SHAPE_TRANSLUCENT25:

			if (flags & SHAPE_ZWRITE) {

				if (flags & SHAPE_ALPHA) {
					return(BlitTransLucent25AlphaZReadWritePtr);
				}

				return(BlitTransLucent25ZReadWritePtr);
			}

			if (flags & z_read_flags) {

				if (flags & SHAPE_PREDATOR) {

					if (flags & SHAPE_ALPHA) {
						return(BlitTransLucent25AlphaZReadWarpPtr);
					}

					return(BlitTransLucent25ZReadWarpPtr);
				}

				if (flags & SHAPE_ALPHA) {
					return(BlitTransLucent25AlphaZReadPtr);
				}

				return(BlitTransLucent25ZReadPtr);
			}

			if (flags & SHAPE_ALPHA) {
				return(BlitTransLucent25AlphaPtr);
			}

			return(Translucent3Blitter);

		case SHAPE_TRANSLUCENT50:

			if (flags & SHAPE_ZWRITE) {

				if (flags & SHAPE_ALPHA) {
					return(BlitTransLucent50AlphaZReadWritePtr);
				}

				return(BlitTransLucent50ZReadWritePtr);
			}

			if (flags & z_read_flags) {

				if (flags & SHAPE_PREDATOR) {

					if (flags & SHAPE_ALPHA) {
						return(BlitTransLucent50AlphaZReadWarpPtr);
					}

					return(BlitTransLucent50ZReadWarpPtr);
				}

				if (flags & SHAPE_ALPHA) {
					return(BlitTransLucent50AlphaZReadPtr);
				}

				return(BlitTransLucent50ZReadPtr);
			}

			if (flags & SHAPE_ALPHA) {
				return(BlitTransLucent50AlphaPtr);
			}

			if (flags & SHAPE_ZERO_ALPHA) {
				return(BlitTranslucent50ZeroAlphaPtr);
			}

			if (flags & SHAPE_NONZERO_ALPHA) {
				return(BlitTranslucent50NonzeroAlphaPtr);
			}

			return(Translucent2Blitter);

		case SHAPE_TRANSLUCENT75:

			if (flags & SHAPE_ZWRITE) {

				if (flags & SHAPE_ALPHA) {
					return(BlitTransLucent75AlphaZReadWritePtr);
				}

				return(BlitTransLucent75ZReadWritePtr);
			}

			if (flags & z_read_flags) {

				if (flags & SHAPE_PREDATOR) {

					if (flags & SHAPE_ALPHA) {
						return(BlitTransLucent75AlphaZReadWarpPtr);
					}

					return(BlitTransLucent75ZReadWarpPtr);
				}

				if (flags & SHAPE_ALPHA) {
					return(BlitTransLucent75AlphaZReadPtr);
				}

				return(BlitTransLucent75ZReadPtr);
			}

			if (flags & SHAPE_ALPHA) {
				return(BlitTransLucent75AlphaPtr);
			}

			if (flags & SHAPE_ZERO_ALPHA) {
				return(BlitTranslucent75ZeroAlphaPtr);
			}

			if (flags & SHAPE_NONZERO_ALPHA) {
				return(BlitTranslucent75NonzeroAlphaPtr);
			}

			return(Translucent1Blitter);
	}

	if (flags & SHAPE_DARKEN) {

		if (flags & SHAPE_ZWRITE) {
			return(BlitTransDarkenZReadWritePtr);
		}

		if (flags & z_read_flags) {
			return(BlitTransDarkenZReadPtr);
		}

		return(ShadowBlitter);
	}

	if (flags & SHAPE_NOTRANS) {

		if (flags & SHAPE_ZWRITE) {

			if (flags & SHAPE_ALPHA) {
				return(BlitTransXlatAlphaZReadWritePtr);
			}

			return(BlitTransXlatZReadWritePtr);
		}

		if (flags & z_read_flags) {

			if (flags & SHAPE_ALPHA) {
				return(BlitTransXlatAlphaZReadPtr);
			}

			return(BlitTransXlatZReadPtr);
		}

		if (flags & SHAPE_ALPHA) {
			return(BlitPlainXlatAlphaPtr);
		}

		return(PlainBlitter);
	}

	if (flags & SHAPE_ZWRITE) {

		if (flags & SHAPE_ALPHA) {
			return(BlitTransXlatAlphaZReadWritePtr);
		}

		return(BlitTransXlatZReadWritePtr);
	}

	if (flags & z_read_flags) {

		if (flags & SHAPE_ALPHA) {
			return(BlitTransXlatAlphaZReadPtr);
		}

		return(BlitTransXlatZReadPtr);
	}

	if (flags & SHAPE_ALPHA_WRITE) {
		return(BlitTransXlatWriteAlphaPtr);
	}

	if (flags & SHAPE_ALPHA_WRITE_MULT) {
		return(BlitTransXlatMultWriteAlphaPtr);
	}

	if (flags & SHAPE_ALPHA_BLEND) {
		return(BlitTranslucentWriteAlphaPtr);
	}

	if (flags & SHAPE_ALPHA) {
		return(BlitTransXlatAlphaPtr);
	}

	return(TransBlitter);
}


/// <summary>
/// Fetches the RLE blitter that satisfies the drawing flags.
/// This routine is used by the shape drawing routines to pick the blitter that performs
/// the requested combination of remapping, translucency, alpha and depth buffer work on
/// a compressed shape. If this drawer has no blitters yet, they are created first.
/// </summary>
/// <returns>Returns with a pointer to the RLE blitter to draw with.</returns>
RLEBlitter const * ConvertClass::RLEBlitter_From_Flags(ShapeFlags_Type flags) const
{
	static ShapeFlags_Type z_read_flags = ShapeFlags_Type(SHAPE_ZREAD|SHAPE_ZGRAD);

	if (PlainBlitter == NULL) {
		((ConvertClass *)this)->Create_Blitters();
	}

	if (flags & SHAPE_REMAP) {

		if (flags & SHAPE_ZWRITE) {

			if (flags & SHAPE_ALPHA) {
				return(RLEBlitTransZRemapXlatAlphaZReadWritePtr);
			}

			return(RLEBlitTransZRemapXlatZReadWritePtr);
		}

		if (flags & z_read_flags) {

			if (flags & SHAPE_ALPHA) {
				return(RLEBlitTransZRemapXlatAlphaZReadPtr);
			}

			return(RLEBlitTransZRemapXlatZReadPtr);
		}

		if (flags & SHAPE_ALPHA) {
			return(RLEBlitTransZRemapXlatAlphaPtr);
		}

		return(RLERemapBlitter);
	}

	/*
	**	Quick check to see if this is a translucent operation. If so, then no
	**	further examination of the flags is necessary.
	*/
	switch (flags & (SHAPE_TRANSLUCENT25 | SHAPE_TRANSLUCENT50 | SHAPE_TRANSLUCENT75)) {
		case SHAPE_TRANSLUCENT25:

			if (flags & SHAPE_ZWRITE) {

				if (flags & SHAPE_ALPHA) {
					return(RLEBlitTransLucent25AlphaZReadWritePtr);
				}

				return(RLEBlitTransLucent25ZReadWritePtr);
			}

			if (flags & z_read_flags) {
				if (flags & SHAPE_PREDATOR) {

					if (flags & SHAPE_ALPHA) {
						return(RLEBlitTransLucent25AlphaZReadWarpPtr);
					}

					return(RLEBlitTransLucent25ZReadWarpPtr);
				}

				if (flags & SHAPE_ALPHA) {
					return(RLEBlitTransLucent25AlphaZReadPtr);
				}

				return(RLEBlitTransLucent25ZReadPtr);
			}

			if (flags & SHAPE_ALPHA) {
				return(RLEBlitTransLucent25AlphaPtr);
			}

			return(RLETranslucent3Blitter);

		case SHAPE_TRANSLUCENT50:

			if (flags & SHAPE_ZWRITE) {

				if (flags & SHAPE_ALPHA) {
					return(RLEBlitTransLucent50AlphaZReadWritePtr);
				}

				return(RLEBlitTransLucent50ZReadWritePtr);
			}

			if (flags & z_read_flags) {

				if (flags & SHAPE_PREDATOR) {

					if (flags & SHAPE_ALPHA) {
						return(RLEBlitTransLucent50AlphaZReadWarpPtr);
					}

					return(RLEBlitTransLucent50ZReadWarpPtr);
				}

				if (flags & SHAPE_ALPHA) {
					return(RLEBlitTransLucent50AlphaZReadPtr);
				}

				return(RLEBlitTransLucent50ZReadPtr);
			}

			if (flags & SHAPE_ALPHA) {
				return(RLEBlitTransLucent50AlphaPtr);
			}

			return(RLETranslucent2Blitter);

		case SHAPE_TRANSLUCENT75:

			if (flags & SHAPE_ZWRITE) {

				if (flags & SHAPE_ALPHA) {
					return(RLEBlitTransLucent75AlphaZReadWritePtr);
				}

				return(RLEBlitTransLucent75ZReadWritePtr);
			}

			if (flags & z_read_flags) {

				if (flags & SHAPE_PREDATOR) {

					if (flags & SHAPE_ALPHA) {
						return(RLEBlitTransLucent75AlphaZReadWarpPtr);
					}

					return(RLEBlitTransLucent75ZReadWarpPtr);
				}

				if (flags & SHAPE_ALPHA) {
					return(RLEBlitTransLucent75AlphaZReadPtr);
				}

				return(RLEBlitTransLucent75ZReadPtr);
			}

			if (flags & SHAPE_ALPHA) {
				return(RLEBlitTransLucent75AlphaPtr);
			}

			return(RLETranslucent1Blitter);
	}

	if (flags & SHAPE_DARKEN) {

		if (flags & SHAPE_ZWRITE) {
			return(RLEBlitTransDarkenZReadWritePtr);
		}

		if (flags & z_read_flags) {
			return(RLEBlitTransDarkenZReadPtr);
		}

		return(RLEShadowBlitter);
	}

	// This should be fixed to return the RLEPlainBlitter when one is available
	// but if you need to use this in the mean time just don't RLE compress the
	// shape (since it only compresses transparent pixels and the reason we compress
	// them is so we can skip them easily.)
	if (flags & SHAPE_NOTRANS) {

		if (flags & SHAPE_ZWRITE) {

			if (flags & SHAPE_ALPHA) {
				return(RLEBlitTransXlatAlphaZReadWritePtr);
			}

			return(RLEBlitTransXlatZReadWritePtr);
		}

		if (flags & z_read_flags) {

			if (flags & SHAPE_ALPHA) {
				return(RLEBlitTransXlatAlphaZReadPtr);
			}

			return(RLEBlitTransXlatZReadPtr);
		}

		if (flags & SHAPE_ALPHA) {
			return(RLEBlitTransXlatAlphaPtr);
		}

		return(RLETransBlitter);

	}

	if (flags & SHAPE_ZWRITE) {

		if (flags & SHAPE_ALPHA) {
			return(RLEBlitTransXlatAlphaZReadWritePtr);
		}

		return(RLEBlitTransXlatZReadWritePtr);
	}

	if (flags & z_read_flags) {

		if (flags & SHAPE_ALPHA) {
			return(RLEBlitTransXlatAlphaZReadPtr);
		}

		return(RLEBlitTransXlatZReadPtr);
	}

	if (flags & SHAPE_ALPHA) {
		return(RLEBlitTransXlatAlphaPtr);
	}

	return(RLETransBlitter);
}


/// <summary>
/// Rebuilds the hicolor translation tables of every drawer.
/// This routine is used when the display has changed to a different pixel format. Each
/// hicolor drawer has its translation table unpacked using the shifts of the format the
/// table was built for and repacked into the format the display now uses. The blitters
/// are recreated afterwards, since they capture the brightness masks of the format.
/// </summary>
/// <param name="redleft">Left shift of the red component in the old pixel format.</param>
/// <param name="redright">Right shift of the red component in the old pixel format.</param>
/// <param name="greenleft">Left shift of the green component in the old pixel format.</param>
/// <param name="greenright">Right shift of the green component in the old pixel format.</param>
/// <param name="blueleft">Left shift of the blue component in the old pixel format.</param>
/// <param name="blueright">Right shift of the blue component in the old pixel format.</param>
void ConvertClass::Reinitialize_Hicolor_Tables(int redleft, int redright, int greenleft, int greenright, int blueleft, int blueright)
{
	for (int i = 0; i < Drawers.Count(); i++) {
		ConvertClass * converter = Drawers[i];
		if (converter->Bytes_Per_Pixel() == 2) {
			unsigned short * table = (unsigned short *)converter->IntensityTranslator;
			for (int index = 0; index < 256; index++) {

				unsigned short color = table[index];

				RGBClass rgb;
				rgb.Set_Blue((color >> redright) << redleft);
				rgb.Set_Green((color >> greenright) << greenleft);
				rgb.Set_Red((color >> blueright) << blueleft);

				table[index] = DSurface::Build_Hicolor_Pixel(rgb.Get_Blue(),rgb.Get_Green(), rgb.Get_Red());
			}

			/*
			**	Fetch the pixel mask values to be used for the various algorithmic
			**	pixel processing performed for hicolor displays.
			*/
			converter->HalfbrightMask = DSurface::Get_Halfbright_Mask();
			converter->QuarterbrightMask = DSurface::Get_Quarterbright_Mask();

			converter->Destroy_Blitters();
			converter->Create_Blitters();
		}
	}
}
