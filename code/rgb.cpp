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
 *                     $Archive:: /Commando/Library/RGB.CPP                                   $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   RGBClass::Adjust -- Adjust one RGB value toward another.                                  *
 *   RGBClass::Difference -- Determines the "distance" between two colors.                     *
 *   RGBClass::operator HSVClass -- Conversion operator for RGB to HSV object.                 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "rgb.h"

#include "hsv.h"

#include <algorithm>

RGBClass const BlackColor(0, 0, 0);


/// <summary>
/// Sets this color to a blend of two other colors.
/// This routine will interpolate each color component between the two colors specified,
/// clamping the result to the legal color range.
/// </summary>
/// <param name="t">The blend fraction, where zero yields the first color and one yields
/// the second.</param>
/// <returns>Returns with a reference to this color object.</returns>
RGBClass & RGBClass::Lerp(RGBClass const & a, RGBClass const & b, float t)
{
	Red = (unsigned char)std::max(0.0f, std::min(255.0f, a.Red * (1.0f - t) + b.Red * t));
	Green = (unsigned char)std::max(0.0f, std::min(255.0f, a.Green * (1.0f - t) + b.Green * t));
	Blue = (unsigned char)std::max(0.0f, std::min(255.0f, a.Blue * (1.0f - t) + b.Blue * t));

	return(*this);
}


/// <summary>
/// Sets this color to a scaled version of another color.
/// This routine will multiply each color component of the source color by the value
/// specified, clamping the result to the legal color range.
/// </summary>
/// <param name="value">The scale to apply to each color component.</param>
/// <returns>Returns with a reference to this color object.</returns>
RGBClass & RGBClass::Set(RGBClass const & rgb, float value)
{
	Red = (unsigned char)std::max(0.0f, std::min(255.0f, rgb.Red * value));
	Green = (unsigned char)std::max(0.0f, std::min(255.0f, rgb.Green * value));
	Blue = (unsigned char)std::max(0.0f, std::min(255.0f, rgb.Blue * value));

	return(*this);
}

/***********************************************************************************************
 * RGBClass::Adjust -- Adjust one RGB value toward another.                                    *
 *                                                                                             *
 *    This routine is used to modify an RGB value to proportionately match another RGB value   *
 *    according to the ratio parameter specified. Typical use of this routine is in palette    *
 *    fading from one palette to another or to black.                                          *
 *                                                                                             *
 * INPUT:   ratio    -- The ration of transformation. This value is in the form of 0 to 255,   *
 *                      with 0 being no change, and 255 being 100% transformed into the        *
 *                      destination color.                                                     *
 *                                                                                             *
 *          rgb      -- Reference to the destination RGB color to transform this color into.   *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/02/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
void RGBClass::Adjust(int ratio, RGBClass const & rgb)
{
	/*
	**	Ratio conversion is limited to 0 through 100%. This is
	**	the range of 0 to 255.
	*/
	ratio &= 0x00FF;

	/*
	**	Adjust the color guns by the ratio specified toward the
	**	destination color.
	*/
	int value = (int)rgb.Red - (int)Red;
	Red = (unsigned char)((int)Red + (value * ratio) / 256);

	value = (int)rgb.Green - (int)Green;
	Green = (unsigned char)((int)Green + (value * ratio) / 256);

	value = (int)rgb.Blue - (int)Blue;
	Blue = (unsigned char)((int)Blue + (value * ratio) / 256);
}


/***********************************************************************************************
 * RGBClass::Difference -- Determines the "distance" between two colors.                       *
 *                                                                                             *
 *    This routine is used to calculate a relative distance between two colors. The value is   *
 *    relative only to itself and thus is useful only for determining the magnitude of         *
 *    color difference rather than the nature of the color difference. Palette remapping       *
 *    code uses this routine to find closest matches for colors.                               *
 *                                                                                             *
 * INPUT:   rgb   -- Reference to the color to be compared to this color.                      *
 *                                                                                             *
 * OUTPUT:  Returns the difference between the two colors. The value returned is zero if the   *
 *          colors exactly match. The greater the positive value the greater the difference    *
 *          between the colors.                                                                *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   12/02/1995 JLB : Created.                                                                 *
 *=============================================================================================*/
int RGBClass::Difference(RGBClass const & rgb) const
{
	int r = (int)Red - (int)rgb.Red;
	if (r < 0) r = -r;

	int g = (int)Green - (int)rgb.Green;
	if (g < 0) g = -g;

	int b = (int)Blue - (int)rgb.Blue;
	if (b < 0) b = -b;

	/*
	**	At first crack, the difference algorithm might be coded as the sum of the color differences
	**	(or sum of the square of the color distances). However, this would not take advantage of the
	**	fact that the human eye is most sensative to green, followed by the color blue. With this
	**	thought in mind, the following difference algorithm is used.
	*/
	return(4*g + 3*b + 2*r);
	//return(r*r + g*g + b*b);
}


/***********************************************************************************************
 * RGBClass::operator HSVClass -- Conversion operator for RGB to HSV object.                   *
 *                                                                                             *
 *    This conversion operator will convert an RGBClass object into an HSVClass object.        *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with a reference (implicit) to the HSVClass object that most closely       *
 *          represents the RGBClass object.                                                    *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/20/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
RGBClass::operator HSVClass (void) const
{
	int hue;
	int saturation;
	int value;

	/*
	**	Fetch working component values for the color guns.
	*/
	int red = Get_Red();
	int green = Get_Green();
	int blue = Get_Blue();

	/*
	**	The hue defaults to none. Only if there is a saturation value will the
	**	hue be calculated.
	*/
	hue = 0;

	/*
	**	Set the value (brightness) to match the brightest color gun.
	*/
	value = (red > green) ? red : green;
	if (blue > value) value = blue;

	/*
	**	Determine the amount of true white present in the color. This is the
	**	minimum color gun value. The white component is used to determine
	**	color saturation.
	*/
	int white = (red < green) ? red : green;
	if (blue < white) white = blue;

	/*
	**	Determine the saturation (intensity) of the color by comparing the
	**	ratio of true white as a component of the overall color. The more
	**	white component, the less saturation.
	*/
	saturation = 0;
	if (value) {
		saturation = ((value - white) * 255) / value;
	}

	/*
	**	If there is any saturation at all, then the hue must be calculated. The
	**	hue is based on a six sided color wheel.
	*/
	if (saturation != 0) {
		unsigned int tmp = value - white;
	 	unsigned int r1 = ((value - red) * 255) / tmp;
	 	unsigned int g1 = ((value - green) * 255) / tmp;
	 	unsigned int b1 = ((value - blue) * 255) / tmp;

		// Find effect of second most predominant color.
		// In which section of the hexagon of colors does the color lie?
		if (value == red) {
		 	if (white == green) {
				tmp = 5 * 256 + b1;
			} else {
				tmp = 1 * 256 - g1;
			}
		} else {
			if (value == green) {
			 	if (white == blue) {
					tmp = 1 * 256 + r1;
				} else {
					tmp = 3 * 256 - b1;
				}
			} else {
			 	if (white == red) {
					tmp = 3 * 256 + g1;
				} else {
					tmp = 5 * 256 - r1;
				}
			}
		}

		// Divide by six and round.
		hue = tmp / 6;
	}

	HSVClass hsv((unsigned char)hue, (unsigned char)saturation, (unsigned char)value);
	return(hsv);
}
