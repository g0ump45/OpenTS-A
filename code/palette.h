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
 *                     $Archive:: /G/wwlib/PALETTE.H                                          $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 12:00p                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "rgb.h"

/*
**	The palette class is used to manipulate a palette as a whole. All 256 colors are
**	represented by the palette class object.
*/
class PaletteClass
{
	public:
		enum {
			COLOR_COUNT=256			// Number of color indices on the palette.
		};

		PaletteClass(void) {};
		PaletteClass(RGBClass const & rgb);
		PaletteClass(unsigned char * binary_palette);

		RGBClass & operator[] (int index) {return(Palette[index % COLOR_COUNT]);};
		RGBClass const & operator[] (int index) const {return(Palette[index % COLOR_COUNT]);};
		RGBClass & Get_Color(int index) {return(Palette[index % COLOR_COUNT]);};
		RGBClass const & Get_Color(int index) const {return(Palette[index % COLOR_COUNT]);};
		bool operator == (PaletteClass const & palette) const;
		bool operator != (PaletteClass const & palette) const {return(!(operator ==(palette)));};
		PaletteClass & operator = (PaletteClass const & palette);
		operator const unsigned char * (void) const {return((const unsigned char *)&Palette[0]);};
		operator unsigned char * (void) {return((unsigned char *)&Palette[0]);};

		void Adjust(int ratio);
		void Adjust(int ratio, PaletteClass const & palette);
		void Partial_Adjust(int ratio, char *lut);
		void Partial_Adjust(int ratio, PaletteClass const & palette, char * lut);
		int Closest_Color(RGBClass const & rgb) const;

	protected:
		RGBClass Palette[COLOR_COUNT];
};
