/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "lightcon.h"

#include "dsurface.h"
#include "globals.h"
#include "ion.h"
#include "scenario.h"
#include "sun.h"

#include <algorithm>

extern "C" {
	void __cdecl Adjust_Color_555(void * palette, void * translator, int red_tint, int green_tint, int blue_tint, int intensity, bool * tint_mask);
	void __cdecl Adjust_Color_556(void * palette, void * translator, int red_tint, int green_tint, int blue_tint, int intensity, bool * tint_mask);
	void __cdecl Adjust_Color_565(void * palette, void * translator, int red_tint, int green_tint, int blue_tint, int intensity, bool * tint_mask);
	void __cdecl Adjust_Color_655(void * palette, void * translator, int red_tint, int green_tint, int blue_tint, int intensity, bool * tint_mask);
}

bool _default_mask[256] = {
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
	true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,
};

DSurfaceColorMode PrimaryColorMode = COLORMODE_INVALID;


/// <summary>
/// Creates a color conversion object that applies a lighting tint.
/// This routine builds the intensity tables that art is drawn through, tinted as the
/// caller asked. If an ion storm is raging at the time, the storm's tint is used
/// instead and the requested tint is remembered for when the storm passes.
/// </summary>
/// <param name="blitters_created">Have the blitters already been created?</param>
/// <param name="tint_mask">Table flagging which palette entries the tint applies to. NULL
/// requests the default mask, which tints every color.</param>
LightConvertClass::LightConvertClass(PaletteClass const & artpalette, PaletteClass const & screenpalette, Surface const & typicalsurface, int red_tint, int green_tint, int blue_tint, bool blitters_created, bool * tint_mask, int intensity_levels) :
	BASECLASS(artpalette, screenpalette, typicalsurface, intensity_levels, true),
	ArtPalette(artpalette),
	ScreenPalette(screenpalette),
	TintMask(tint_mask),
	ReferenceCount(0),
	NormalRedTint(red_tint),
	NormalGreenTint(green_tint),
	NormalBlueTint(blue_tint),
	IonRedTint(red_tint),
	IonGreenTint(green_tint),
	IonBlueTint(blue_tint),
	UseIonLighting(false)
{
	if (IntensityLevels >= 1) {
		if (tint_mask == NULL) {
			TintMask = _default_mask;
		}

		if (PrimaryColorMode == COLORMODE_INVALID) {
			PrimaryColorMode = (DSurfaceColorMode)DSurface::Get_Primary_Color_Mode();
		}

		if (IonStormClass::Is_Ion_Storm_Active()) {
			if (red_tint == -1) {
				NormalRedTint = NORMAL_LIGHT;
				NormalGreenTint = NORMAL_LIGHT;
				NormalBlueTint = NORMAL_LIGHT;
			} else {
				NormalRedTint = red_tint;
				NormalGreenTint = green_tint;
				NormalBlueTint = blue_tint;
			}
			Apply_Tint(NORMAL_LIGHT * Scen->IonRedTint / 100, NORMAL_LIGHT * Scen->IonGreenTint / 100, NORMAL_LIGHT * Scen->IonBlueTint / 100, true);
		} else {
			Apply_Tint(red_tint, green_tint, blue_tint, false);
		}

		if (!blitters_created) {
			Create_Blitters();
		}
	}
}


/// <summary>
/// Applies a color tint to the lighting tables.
/// This routine rebuilds every intensity level of the translation table so that art
/// drawn through this converter picks up the new tint. Use this routine when the
/// lighting changes -- when an ion storm rolls in or clears, most notably -- rather
/// than building a fresh converter.
/// </summary>
/// <param name="ion_light">Is this the ion storm tint rather than the normal one?</param>
/// <remarks>A red tint of -1 keeps the tint already remembered for the lighting mode
/// selected, rather than replacing it.</remarks>
void LightConvertClass::Apply_Tint(int red_tint, int green_tint, int blue_tint, bool ion_light)
{
	if (IntensityLevels >= 1) {
		if (TintMask == NULL) {
			TintMask = _default_mask;
		}

		if (red_tint != -1) {
			red_tint = std::min(red_tint, 2000);
			red_tint = std::max(red_tint, 0);
			green_tint = std::min(green_tint, 2000);
			green_tint = std::max(green_tint, 0);
			blue_tint = std::min(blue_tint, 2000);
			blue_tint = std::max(blue_tint, 0);
		}

		if (ion_light) {
			if (red_tint == -1) {
				red_tint = IonRedTint;
				blue_tint = IonBlueTint;
				green_tint = IonGreenTint;
			} else {
				IonRedTint = red_tint;
				IonGreenTint = green_tint;
				IonBlueTint = blue_tint;
			}
			UseIonLighting = true;
		} else {
			if (red_tint == -1) {
				red_tint = NormalRedTint;
				green_tint = NormalGreenTint;
				blue_tint = NormalBlueTint;
			} else {
				NormalRedTint = red_tint;
				NormalGreenTint = green_tint;
				NormalBlueTint = blue_tint;
			}
			UseIonLighting = false;
		}

		int red_step = (int)((double)(NORMAL_LIGHT * red_tint) * (65536.0 / (double)(NORMAL_LIGHT * NORMAL_LIGHT)));
		int green_step = (int)((double)(NORMAL_LIGHT * green_tint) * (65536.0 / (double)(NORMAL_LIGHT * NORMAL_LIGHT)));
		int blue_step = (int)((double)(NORMAL_LIGHT * blue_tint) * (65536.0 / (double)(NORMAL_LIGHT * NORMAL_LIGHT)));

		unsigned short * translator = (unsigned short *)IntensityTranslator;

		int level_count = IntensityLevels - 1;

		int max_level = std::max(30 * IntensityLevels / 200 - 1, 0);
		max_level = std::min(max_level, level_count >> 1);

		int level = 0;

		if (level_count >= 0) {

			int intensity_accum = 0;
			int blue_accum = 0;
			int green_accum = 0;
			int red_accum = 0;

			for (; level <= IntensityLevels - 1; level++) {

				int interp_intensity;
				int interp_red;
				int interp_green;
				int interp_blue;

				if (IntensityLevels > 1) {
					interp_red = red_accum / level_count;
					interp_green = green_accum / level_count;
					interp_blue = blue_accum / level_count;
					if (level > max_level) {
						interp_intensity = 0x10000;
					} else {
						interp_intensity = intensity_accum / max_level;
					}
				} else {
					interp_red = red_step;
					interp_green = green_step;
					interp_blue = blue_step;
					interp_intensity = 0x10000;
				}

				switch (PrimaryColorMode) {
					case COLORMODE_555:
						Adjust_Color_555((void *)&ArtPalette, translator, interp_red, interp_green, interp_blue, interp_intensity, TintMask);
						translator += PaletteClass::COLOR_COUNT;
						break;

					case COLORMODE_556:
						Adjust_Color_556((void *)&ArtPalette, translator, interp_red, interp_green, interp_blue, interp_intensity, TintMask);
						translator += PaletteClass::COLOR_COUNT;
						break;

					case COLORMODE_565:
						Adjust_Color_565((void *)&ArtPalette, translator, interp_red, interp_green, interp_blue, interp_intensity, TintMask);
						translator += PaletteClass::COLOR_COUNT;
						break;

					case COLORMODE_655:
						Adjust_Color_655((void *)&ArtPalette, translator, interp_red, interp_green, interp_blue, interp_intensity, TintMask);
						translator += PaletteClass::COLOR_COUNT;
						break;

					default:
						*translator = 0;
						translator++;
						for (int i = 1; i < PaletteClass::COLOR_COUNT; i++) {
							if (TintMask[i]) {
								red_tint   = (interp_red   * (unsigned char)ArtPalette[i].Get_Red()) >> 16;
								green_tint = (interp_green * (unsigned char)ArtPalette[i].Get_Green()) >> 16;
								blue_tint  = (interp_blue   * (unsigned char)ArtPalette[i].Get_Blue()) >> 16;
							} else {
								red_tint   = (interp_intensity * (unsigned char)ArtPalette[i].Get_Red()) >> 16;
								green_tint = (interp_intensity * (unsigned char)ArtPalette[i].Get_Green()) >> 16;
								blue_tint  = (interp_intensity * (unsigned char)ArtPalette[i].Get_Blue()) >> 16;
							}
							red_tint = std::min(red_tint, 255);
							green_tint = std::min(green_tint, 255);
							blue_tint = std::min(blue_tint, 255);
							*translator = DSurface::Build_Hicolor_Pixel(red_tint, green_tint, blue_tint);
							translator++;
						}
						break;
				}
				red_accum += 2 * red_step;
				green_accum += 2 * green_step;
				blue_accum += 2 * blue_step;
				intensity_accum += 0x10000;
			}
		}
	}
}


/// <summary>
/// Destroys the lighting conversion object.
/// </summary>
LightConvertClass::~LightConvertClass(void)
{

}
