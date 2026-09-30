/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "lightcalc.h"

#include "globals.h"
#include "goptions.h"
#include "sun.h"

#include <algorithm>


/// <summary>
/// Normalizes a tile lighting tint to its strongest channel.
/// This routine is used by the cell lighting recalculation so that the tint handed to a
/// tile drawer always peaks at full strength, with the brightness taken out of the tint
/// folded into the light level instead. The caller uses the reported intensity to bring
/// any other brightness values it is tracking for the cell into line.
/// </summary>
/// <param name="intensity">Filled in with the scale divided out of the tint, expressed in
/// 16.16 fixed point.</param>
/// <param name="light">The light level for the tile. It is scaled to suit the normalized
/// tint and limited to full brightness.</param>
/// <param name="red">The red tint level, where 1000 is full strength.</param>
/// <param name="green">The green tint level, where 1000 is full strength.</param>
/// <param name="blue">The blue tint level, where 1000 is full strength.</param>
void Adjust_Tile_RGB(int & intensity, int & light, int & red, int & green, int & blue)
{
	double temp;

	red = std::max(red, 0);
	green = std::max(green, 0);
	blue = std::max(blue, 0);

	intensity = 65536;

	if (red != NORMAL_LIGHT || green != red || blue != red) {
		if (green <= red && red >= blue) {
			temp = ((double)red * 65536) / NORMAL_LIGHT;
			intensity = temp;

			if (intensity < 66) {
				intensity = 65536;
				red = NORMAL_LIGHT;
				green = NORMAL_LIGHT;
				blue = NORMAL_LIGHT;
				light = 0;
			} else {
				red = NORMAL_LIGHT;

				green = (((double)green * 65536) / (double)temp);
				blue = (((double)blue * 65536) / (double)temp);

				light *= intensity;
				light >>= 16;
			}
		} else if (green >= red && green >= blue) {
			temp = ((double)green * 65536) / NORMAL_LIGHT;
			intensity = temp;

			if (intensity < 66) {
				intensity = 65536;
				red = NORMAL_LIGHT;
				green = NORMAL_LIGHT;
				blue = NORMAL_LIGHT;
				light = 0;
			} else {
				green = NORMAL_LIGHT;

				red = (((double)red * 65536) / (double)intensity);
				blue = (((double)blue * 65536) / (double)intensity);

				light *= intensity;
				light >>= 16;
			}
		} else {
			temp = ((double)blue * 65536) / NORMAL_LIGHT;
			intensity = temp;

			if (intensity < 66) {
				intensity = 65536;
				red = NORMAL_LIGHT;
				green = NORMAL_LIGHT;
				blue = NORMAL_LIGHT;
				light = 0;
			} else {
				blue = NORMAL_LIGHT;

				red = (((double)red * 65536) / (double)intensity);
				green = (((double)green * 65536) / (double)intensity);

				light *= intensity;
				light >>= 16;
			}
		}
	}

	light = light >= 2000 ? 2000 : light;
}


/// <summary>
/// Clamps and quantizes a tile lighting tint.
/// This routine is used before a tint is looked up in a tile's drawer cache. The lower the
/// detail level, the more coarsely the tint is rounded off, so that neighboring shades
/// share one drawer rather than each building a conversion table of its own.
/// </summary>
/// <param name="red">The red tint level, where 1000 is full strength.</param>
/// <param name="green">The green tint level, where 1000 is full strength.</param>
/// <param name="blue">The blue tint level, where 1000 is full strength.</param>
void Clamp_Tile_RGB(int & red, int & green, int & blue)
{
	red = std::min(red, NORMAL_LIGHT);
	green = std::min(green, NORMAL_LIGHT);
	blue = std::min(blue, NORMAL_LIGHT);

	red = std::max(red, 0);
	green = std::max(green, 0);
	blue = std::max(blue, 0);

	/// Apply quantization based on DetailLevel
	switch (Options.DetailLevel) {

		case 0:
			red &= ~((1 << 6) - 1);
			red += (red >> 4);

			green &= ~((1 << 6) - 1);
			green += (green >> 4);

			blue &= ~((1 << 6) - 1);
			blue += (blue >> 4);
			break;

		case 1:
			red &= ~((1 << 5) - 1);
			red += (red >> 5);

			green &= ~((1 << 5) - 1);
			green += (green >> 5);

			blue &= ~((1 << 5) - 1);
			blue += (blue >> 5);
			break;

		case 2:
			red &= ~((1 << 4) - 1);
			red += (red >> 6);

			green &= ~((1 << 4) - 1);
			green += (green >> 6);

			blue &= ~((1 << 4) - 1);
			blue += (blue >> 6);
			break;

		default:
			/*
			 * High detail (3 or more): no quantization applied
			 */
			break;
	}
}
