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
 *                     $Archive:: /G/wwlib/Convert.h                                          $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 11:59a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "draw.hh"

class Blitter;
class RLEBlitter;
class PaletteClass;
class Surface;
template<class T> class DynamicVectorClass;

#define NUM_INTENSITY_LEVELS 63

/*
**	This class is the data that represents the marriage between a source art
**	palette and a destination palette/pixel-format. Facilities provied by this
**	class allow conversion from the source 8 bit pixel format to the correct
**	screen pixel format.
**
**	Although this class can convert one pixel at a time through the conversion
**	function, the preferred way to convert pixels is through the translation
**	table provided. This table consists of 256 entries. Each entry is either
**	an 8 bit or 16 bit pixel in the correct screen-space format. Use the
**	Bytes_Per_Pixel() function to determine how to index into this translation
**	table.
**
**	Expected use of this class would be to create separate objects of this class for
**	every source art palette. For an 8 bit display, an additional object will be
**	required for every additional palette set to the video DAC registers. It is
**	presumed that one general best-case palette will be used.
*/
class ConvertClass
{
		friend class IsometricTileTypeClass;
	public:
		ConvertClass(PaletteClass const & artpalette, PaletteClass const & screenpalette, Surface const & typicalsurface, int intensity_levels = 1, bool quick_init = false);
		virtual ~ConvertClass(void);

		/*
		**	Convert from source pixel to dest screen pixel.
		*/
		int Convert_Pixel(int pixel) const {
			if (BBP == 1) return(((unsigned char const *)Translator)[pixel]);
			return(((unsigned short const *)Translator)[pixel]);
		}

		/*
		**	Fetch a blitter object to use according to the draw flags
		**	specified.
		*/
		Blitter const * Blitter_From_Flags(ShapeFlags_Type flags) const;
		RLEBlitter const * RLEBlitter_From_Flags(ShapeFlags_Type flags) const;

		/*
		**	This returns the bytes per pixel. Use this to determine how to index
		**	through the translation table.
		*/
		int Bytes_Per_Pixel(void) const {return(BBP);}

		/*
		**	Fetches the translation table. Sometimes the provided blitter objects
		**	won't suffice and manual access to the translation process is necessary.
		*/
		void const * Get_Translate_Table(void) const {return(Translator);}

		/*
		**	Sets the dynamic remap table so that the remapping blitters will use
		**	it without having to recreate the blitter objects.
		*/
		void Set_Remap(unsigned char const * remap) {RemapTable = remap;}

		void Create_Blitters(void);
		void Destroy_Blitters(void);

		static void Reinitialize_Hicolor_Tables(int redleft, int redright, int greenleft, int greenright, int blueleft, int blueright);

	protected:
		/*
		**	Bytes per pixel in screen format.
		*/
		int BBP;

		/*
		**	These are the blitter objects used to handle all the draw styles that this
		**	drawing dispatcher implements.
		*/
		Blitter * PlainBlitter;         // No transparency (rarely used).
		Blitter * TransBlitter;         // Skips transparent pixels.
		Blitter * ShadowBlitter;        // Shadowizes the destination pixels.
		Blitter * RemapBlitter;         // Remaps source pixels then draws with transparency.
		Blitter * Translucent1Blitter;  // 25% translucent.
		Blitter * Translucent2Blitter;  // 50% translucent.
		Blitter * Translucent3Blitter;  // 75% translucent.

		/*
		 * These are the blitters that test the depth buffer but leave it alone, so a sprite is
		 * hidden by whatever was drawn in front of it. The Warp variants blend with a
		 * destination pixel offset from the one they cover, distorting the scene behind them.
		 */
		Blitter * BlitPlainXlatZReadPtr;
		Blitter * BlitTransXlatZReadPtr;
		Blitter * BlitTransDarkenZReadPtr;
		Blitter * BlitTransZRemapXlatZReadPtr;
		Blitter * BlitTransLucent75ZReadPtr;
		Blitter * BlitTransLucent50ZReadPtr;
		Blitter * BlitTransLucent25ZReadPtr;
		Blitter * BlitTransLucent75ZReadWarpPtr;
		Blitter * BlitTransLucent50ZReadWarpPtr;
		Blitter * BlitTransLucent25ZReadWarpPtr;

		/*
		 * These are the blitters that both test the depth buffer and record the depth of every
		 * pixel they draw, so that whatever is drawn after them is occluded in turn.
		 */
		Blitter * BlitPlainXlatZReadWritePtr;
		Blitter * BlitTransXlatZReadWritePtr;
		Blitter * BlitTransDarkenZReadWritePtr;
		Blitter * BlitTransZRemapXlatZReadWritePtr;
		Blitter * BlitTransLucent75ZReadWritePtr;
		Blitter * BlitTransLucent50ZReadWritePtr;
		Blitter * BlitTransLucent25ZReadWritePtr;

		/*
		 * These are the alpha lit blitters that ignore the depth buffer entirely.
		 */
		Blitter * BlitPlainXlatAlphaPtr;
		Blitter * BlitTransXlatAlphaPtr;
		Blitter * BlitTransZRemapXlatAlphaPtr;
		Blitter * BlitTransLucent75AlphaPtr;
		Blitter * BlitTransLucent50AlphaPtr;
		Blitter * BlitTransLucent25AlphaPtr;

		/*
		 * These two write no color at all. Each non-transparent source pixel accumulates a
		 * value into the alpha buffer instead, the Mult variant scaling its contribution by
		 * the source pixel, so that a light can be laid down before the objects it lights.
		 */
		Blitter * BlitTransXlatWriteAlphaPtr;
		Blitter * BlitTransXlatMultWriteAlphaPtr;

		/*
		 * This is the blitter that composites with the per-pixel alpha in the alpha buffer,
		 * weighting the source and the destination by that value across all three color
		 * components rather than by one of the fixed translucency ratios.
		 */
		Blitter * BlitTranslucentWriteAlphaPtr;

		/*
		 * These are the blitters that gate a fixed 50% or 75% translucency on the alpha
		 * buffer -- the Nonzero variants blend only where the alpha value under the pixel is
		 * set, and the Zero variants only where it is clear.
		 */
		Blitter * BlitTranslucent50NonzeroAlphaPtr;
		Blitter * BlitTranslucent50ZeroAlphaPtr;
		Blitter * BlitTranslucent75NonzeroAlphaPtr;
		Blitter * BlitTranslucent75ZeroAlphaPtr;

		/*
		 * These are the alpha lit blitters that test the depth buffer but leave it alone. The
		 * Warp variants blend with a destination pixel offset from the one they cover, which
		 * is how a cloaked object appears to distort the scene behind it.
		 */
		Blitter * BlitPlainXlatAlphaZReadPtr;
		Blitter * BlitTransXlatAlphaZReadPtr;
		Blitter * BlitTransZRemapXlatAlphaZReadPtr;
		Blitter * BlitTransLucent75AlphaZReadPtr;
		Blitter * BlitTransLucent50AlphaZReadPtr;
		Blitter * BlitTransLucent25AlphaZReadPtr;
		Blitter * BlitTransLucent75AlphaZReadWarpPtr;
		Blitter * BlitTransLucent50AlphaZReadWarpPtr;
		Blitter * BlitTransLucent25AlphaZReadWarpPtr;

		/*
		 * These are the alpha lit blitters that both test the depth buffer and record the
		 * depth of every pixel they draw.
		 */
		Blitter * BlitPlainXlatAlphaZReadWritePtr;
		Blitter * BlitTransXlatAlphaZReadWritePtr;
		Blitter * BlitTransZRemapXlatAlphaZReadWritePtr;
		Blitter * BlitTransLucent75AlphaZReadWritePtr;
		Blitter * BlitTransLucent50AlphaZReadWritePtr;
		Blitter * BlitTransLucent25AlphaZReadWritePtr;

		/*
		**	These are the RLE aware blitters to handle all drawing styles that may
		**	be used by RLE compressed images.
		*/
		RLEBlitter * RLETransBlitter;           // Skips transparent pixels.
		RLEBlitter * RLEShadowBlitter;          // Shadowizes the destination pixels.
		RLEBlitter * RLERemapBlitter;           // Remaps source pixels then draws with transparency.
		RLEBlitter * RLETranslucent1Blitter;    // 25% translucent.
		RLEBlitter * RLETranslucent2Blitter;    // 50% translucent.
		RLEBlitter * RLETranslucent3Blitter;    // 75% translucent.

		/*
		 * These are the RLE blitters that test the depth buffer but leave it alone. The Warp
		 * variants distort what is already on the surface as they draw.
		 */
		RLEBlitter * RLEBlitTransXlatZReadPtr;
		RLEBlitter * RLEBlitTransZRemapXlatZReadPtr;
		RLEBlitter * RLEBlitTransDarkenZReadPtr;
		RLEBlitter * RLEBlitTransLucent75ZReadPtr;
		RLEBlitter * RLEBlitTransLucent50ZReadPtr;
		RLEBlitter * RLEBlitTransLucent25ZReadPtr;
		RLEBlitter * RLEBlitTransLucent75ZReadWarpPtr;
		RLEBlitter * RLEBlitTransLucent50ZReadWarpPtr;
		RLEBlitter * RLEBlitTransLucent25ZReadWarpPtr;

		/*
		 * These are the RLE blitters that both test the depth buffer and record the depth of
		 * every pixel they draw.
		 */
		RLEBlitter * RLEBlitTransXlatZReadWritePtr;
		RLEBlitter * RLEBlitTransZRemapXlatZReadWritePtr;
		RLEBlitter * RLEBlitTransDarkenZReadWritePtr;
		RLEBlitter * RLEBlitTransLucent75ZReadWritePtr;
		RLEBlitter * RLEBlitTransLucent50ZReadWritePtr;
		RLEBlitter * RLEBlitTransLucent25ZReadWritePtr;

		/*
		 * These are the alpha lit RLE blitters that ignore the depth buffer entirely.
		 */
		RLEBlitter * RLEBlitTransXlatAlphaPtr;
		RLEBlitter * RLEBlitTransZRemapXlatAlphaPtr;
		RLEBlitter * RLEBlitTransLucent75AlphaPtr;
		RLEBlitter * RLEBlitTransLucent50AlphaPtr;
		RLEBlitter * RLEBlitTransLucent25AlphaPtr;

		/*
		 * These are the alpha lit RLE blitters that test the depth buffer but leave it alone.
		 * The Warp variants distort what is already on the surface as they draw.
		 */
		RLEBlitter * RLEBlitTransXlatAlphaZReadPtr;
		RLEBlitter * RLEBlitTransZRemapXlatAlphaZReadPtr;
		RLEBlitter * RLEBlitTransLucent75AlphaZReadPtr;
		RLEBlitter * RLEBlitTransLucent50AlphaZReadPtr;
		RLEBlitter * RLEBlitTransLucent25AlphaZReadPtr;
		RLEBlitter * RLEBlitTransLucent75AlphaZReadWarpPtr;
		RLEBlitter * RLEBlitTransLucent50AlphaZReadWarpPtr;
		RLEBlitter * RLEBlitTransLucent25AlphaZReadWarpPtr;

		/*
		 * These are the alpha lit RLE blitters that both test the depth buffer and record the
		 * depth of every pixel they draw.
		 */
		RLEBlitter * RLEBlitTransXlatAlphaZReadWritePtr;
		RLEBlitter * RLEBlitTransZRemapXlatAlphaZReadWritePtr;
		RLEBlitter * RLEBlitTransLucent75AlphaZReadWritePtr;
		RLEBlitter * RLEBlitTransLucent50AlphaZReadWritePtr;
		RLEBlitter * RLEBlitTransLucent25AlphaZReadWritePtr;

		/*
		 * This is the number of brightness steps the translation table was built with. A
		 * drawer that does no alpha lighting is built with a single level.
		 */
		int IntensityLevels;

		/*
		 * This points to the whole translation table -- IntensityLevels consecutive 256 entry
		 * tables running from black up to double brightness. The alpha lighting blitters index
		 * it by source pixel and light level together; Translator points at its middle level.
		 */
		void * IntensityTranslator;

		/*
		**	This is a translation table pointer. All source artwork is in 8 bit format.
		**	This table will translate this source pixel into a screen dependant pixel
		**	format datum.
		*/
		void * Translator;

		/*
		**	This will shade an 8 bit pixel to about 1/2 intensity.
		*/
		unsigned char * ShadowTable;

		/*
		**	Remap table pointer used for blits that require remapping. This value
		**	will change according to the draw parameter. The blitting routines keep track
		**	of this member object and use it to determine the remap table to use.
		*/
		mutable unsigned char const * RemapTable;

		/*
		 * These are the channel masks the shadow and translucency blitters use to halve or
		 * quarter a hicolor pixel without bleeding one color component into the next. They
		 * come from the display surface, so they are only meaningful to a hicolor drawer.
		 */
		int HalfbrightMask;
		int QuarterbrightMask;

	public:
		/*
		 * This is the list of every drawer object in existence. A drawer adds itself when it is
		 * constructed and takes itself off again when it is destroyed, so that the hicolor
		 * translation tables can all be rebuilt when the display changes pixel format.
		 */
		static DynamicVectorClass<ConvertClass *> Drawers;
};
