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

#include "effects.h"

#include "palette.h"
#include "win.h"


void * Build_Fading_Table(PaletteClass const & palette, void * dest, int color, int frac);

/***************************************************************************
 * Conquer_Build_Fading_Table -- Builds custom shadow/light fading table.  *
 *                                                                         *
 *    This routine is used to build a special fading table for C&C.  There *
 *    are certain colors that get faded to and cannot be faded again.      *
 *    With this rule, it is possible to draw a shadow multiple times and   *
 *    not have it get any lighter or darker.                               *
 *                                                                         *
 * INPUT:   palette  -- Pointer to the 768 byte IBM palette to build from. *
 *                                                                         *
 *          dest     -- Pointer to the 256 byte remap table.               *
 *                                                                         *
 *          color    -- Color index of the color to "fade to".             *
 *                                                                         *
 *          frac     -- The fraction to fade to the specified color        *
 *                                                                         *
 * OUTPUT:  Returns with pointer to the remap table.                       *
 *                                                                         *
 * WARNINGS:   none                                                        *
 *                                                                         *
 * HISTORY:                                                                *
 *   10/07/1992 JLB : Created.                                             *
 *=========================================================================*/
void * Conquer_Build_Fading_Table(PaletteClass const & palette, void * dest, int color, int frac)
{
	if (dest) {
		unsigned char * ptr = (unsigned char *)dest;
//		HSVClass desthsv = palette[color];

		/*
		**	Find an appropriate remap color index for every color in the palette.
		**	There are certain exceptions to this, but they are trapped within the
		**	loop.
		*/
		for (int index = 0; index < PaletteClass::COLOR_COUNT; index++) {

			/*
			**	If this color should not be remapped, then it will be stored as a remap
			**	to itself. This is effectively no remap.
			*/
			if (index > PaletteClass::COLOR_COUNT-16 || index == 0) {
				*ptr++ = index;
			} else {

				/*
				**	Find the color that, ideally, the working color should be remapped
				**	to in the special remap range.
				*/
				RGBClass trycolor = palette[index];
				trycolor.Adjust(frac, palette[color]);			// Try to match this color.

				/*
				**	Search through the remap range to find the color that should be remapped
				**	to. This special range is used for shadows or other effects that are
				**	not compounded if additively applied.
				*/
				int best = -1;
				int bvalue = 0;
				for (int id = PaletteClass::COLOR_COUNT-16; id < PaletteClass::COLOR_COUNT-1; id++) {
					int diff = palette[id].Difference(trycolor);
					if (best == -1 || diff < bvalue) {
						best = id;
						bvalue = diff;
					}
				}
				*ptr++ = best;
			}
		}
	}
	return(dest);
}


/***********************************************************************************************
 * Translucent_Table_Size -- Determines the size of a translucent table.                       *
 *                                                                                             *
 *    Use this routine to determine how big the translucent table needs                        *
 *    to be given the specified number of colors. This value is typically                      *
 *    used when allocating the buffer for the translucent table.                               *
 *                                                                                             *
 * INPUT:   count -- The number of colors that are translucent.                                *
 *                                                                                             *
 * OUTPUT:  Returns the size of the translucent table.                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/02/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
int Translucent_Table_Size(int count)
{
	return(256L + (256L * count));
}


/***********************************************************************************************
 * Build_Translucent_Table -- Creates a translucent control table.                             *
 *                                                                                             *
 *    The table created by this routine is used by Draw_Shape (GHOST) to                       *
 *    achieve a translucent affect. The original color of the shape will                       *
 *    show through. This differs from the fading effect, since that                            *
 *    affect only alters the background color toward a single destination                      *
 *    color.                                                                                   *
 *                                                                                             *
 * INPUT:   palette  -- Pointer to the control palette.                                        *
 *                                                                                             *
 *          control  -- Pointer to array of structures that control how                        *
 *                      the translucent table will be built.                                   *
 *                                                                                             *
 *          count    -- The number of entries in the control array.                            *
 *                                                                                             *
 *          buffer   -- Pointer to buffer to place the translucent table.                      *
 *                      If NULL is passed in, then the buffer will be                          *
 *                      allocated.                                                             *
 *                                                                                             *
 * OUTPUT:  Returns with pointer to the translucent table.                                     *
 *                                                                                             *
 * WARNINGS:   This routine is exceedingly slow. Use sparingly.                                *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/02/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
void * Build_Translucent_Table(PaletteClass const & palette, TLucentType const * control, int count, void * buffer)
{
	unsigned char	const *table;   // Remap table pointer.
	int			index;              // Working color index.

	if (count && control) {
		if (!buffer) {
			buffer = new char [Translucent_Table_Size(count)];
		}

		if (buffer) {
			memset(buffer, -1, 256);
			table = (unsigned char*)buffer + 256;

			/*
			**	Build the individual remap tables for each translucent color.
			*/
			for (index = 0; index < count; index++) {
				((unsigned char*)buffer)[control[index].SourceColor] = index;
				Build_Fading_Table(palette, (void*)table, control[index].DestColor, control[index].Fading);
				table = (unsigned char*)table + 256;
			}
		}
	}
	return(buffer);
}


/***********************************************************************************************
 * Conquer_Build_Translucent_Table -- Builds fading table for shadow colors only.              *
 *                                                                                             *
 *    This routine will build a translucent (fading) table to remap colors into the shadow     *
 *    color region of the palette. Shadow colors are not affected by this translucent table.   *
 *    This means that a shape can be overlapped any number of times and the imagery will       *
 *    remain deterministic (and constant).                                                     *
 *                                                                                             *
 * INPUT:   palette  -- Pointer to the palette to base the translucent process on.             *
 *                                                                                             *
 *          control  -- Pointer to special control structure that specifies the                *
 *                      target color, and percentage of fade.                                  *
 *                                                                                             *
 *          count    -- The number of colors to be remapped (entries in the control array).    *
 *                                                                                             *
 *          buffer   -- Pointer to the staging buffer that will hold the translucent table     *
 *                      data. If this parameter is NULL, then an appropriate sized table       *
 *                      will be allocated.                                                     *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the translucent table data.                              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/27/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
void * Conquer_Build_Translucent_Table(PaletteClass const & palette, TLucentType const * control, int count, void * buffer)
{
	unsigned char	const *table;		// Remap table pointer.

	if (count && control) {
		if (!buffer) {
			buffer = new char [Translucent_Table_Size(count)];
		}

		if (buffer) {
			memset(buffer, -1, 256);
			table = (unsigned char*)buffer + 256;

			/*
			**	Build the individual remap tables for each translucent color.
			*/
			for (int index = 0; index < count; index++) {
				((unsigned char*)buffer)[control[index].SourceColor] = index;
				Conquer_Build_Fading_Table(palette, (void*)table, control[index].DestColor, control[index].Fading);
				table = (unsigned char*)table + 256;
			}
		}
	}
	return(buffer);
}


/// <summary>
/// Builds a plain color fading table.
/// This routine is the unrestricted counterpart to Conquer_Build_Fading_Table. Every
/// palette entry is faded toward the specified color and matched against the whole
/// palette, rather than being confined to the reserved shadow range, so a table built
/// here is not safe to apply more than once.
/// </summary>
/// <param name="dest">Pointer to the 256 byte remap table to fill in. May be NULL.</param>
/// <param name="color">Color index of the color to fade toward.</param>
/// <param name="frac">The fraction to fade toward the specified color.</param>
/// <returns>Returns with a pointer to the remap table.</returns>
void * Make_Fading_Table(PaletteClass const & palette, void * dest, int color, int frac)
{
	if (dest) {
		unsigned char * ptr = (unsigned char *)dest;

		/*
		**	Find an appropriate remap color index for every color in the palette.
		**	There are certain exceptions to this, but they are trapped within the
		**	loop.
		*/
		for (int index = 0; index < PaletteClass::COLOR_COUNT; index++) {

			/*
			**	Find the color that, ideally, the working color should be remapped
			**	to in the special remap range.
			*/
			RGBClass trycolor = palette[index];
			trycolor.Adjust(frac, palette[color]);			// Try to match this color.

			/*
			**	Search through the remap range to find the color that should be remapped
			**	to. This special range is used for shadows or other effects that are
			**	not compounded if additively applied.
			*/
			*ptr++ = palette.Closest_Color(trycolor);
		}
	}
	return(dest);
}


/***********************************************************
* BUILD_FADING_TABLE
*
* void *Build_Fading_Table(void *palette, void *dest, long int color, long int frac);
*
* This routine will create the fading effect table used to coerce colors
* from toward a common value.  This table is used when Fading_Effect is
* active.
*
* Bounds Checking: None
*
*/
void * Build_Fading_Table(PaletteClass const & palette, void * dest, int color, int frac)
{
	unsigned char * ptr = (unsigned char *)dest;

	RGBClass c = palette[color];
	ptr[0] = 0;
	for (int index = 1; index < PaletteClass::COLOR_COUNT; index++) {
		RGBClass rgb = palette[index];
		rgb.Adjust(frac, c);
		ptr[index] = palette.Closest_Color(rgb);
	}

	return(ptr);
}
