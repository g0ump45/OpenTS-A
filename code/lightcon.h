/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "convert.h"

#include <cstddef>


class Surface;
class PaletteClass;


class LightConvertClass : public ConvertClass
{
		typedef ConvertClass BASECLASS;

	public:
		LightConvertClass(PaletteClass const & artpalette, PaletteClass const & screenpalette, Surface const & typicalsurface, int red_tint = 1000, int green_tint = 1000, int blue_tint = 1000, bool blitters_created = false, bool * tint_mask = NULL, int intensity_levels = NUM_INTENSITY_LEVELS);
		virtual ~LightConvertClass(void) override;

		virtual void Apply_Tint(int red_tint, int green_tint, int blue_tint, bool ion_light);

		void Add_Reference(void) {ReferenceCount++;}
		void Remove_Reference(void) {ReferenceCount--;}

	private:
		/*
		 * This is the palette that the artwork being drawn was authored in. Every color of
		 * it is run through the tint and the lighting level to build the intensity
		 * translation tables that the art is finally drawn through.
		 */
		PaletteClass const & ArtPalette;

		/// Unused
		PaletteClass const & ScreenPalette;

		bool * TintMask; /// colors with "true" are tinted, colors with "false" are just shaded
	public:
		/// The routine that consumed this count, IsometricTileTypeClass::Free_Unused_Drawers,
		/// ships as a stub, so nothing ever reads it.

		/*
		 * This is the running count of the cells currently drawing through this converter.
		 * Cells claim a share as they adopt the lighting it represents and give it up again
		 * when their lighting changes.
		 */
		int ReferenceCount;

		/*
		 * These are the red, green and blue components of the tint that applies under
		 * ordinary lighting, expressed in thousandths -- 1000 leaves the color alone. They
		 * are kept while an ion storm overrides them, so that the normal lighting can be put
		 * back when the storm passes.
		 */
		int NormalRedTint;
		int NormalGreenTint;
		int NormalBlueTint;

		/*
		 * These are the red, green and blue components of the tint that applies while an ion
		 * storm is raging, in the same thousandths as the normal tint. They are remembered
		 * so that a later request can ask for the storm tint again without naming it.
		 */
		int IonRedTint;
		int IonGreenTint;
		int IonBlueTint;

		/*
		 * If the tables are currently built from the ion storm tint rather than the normal
		 * one, then this flag will be true.
		 */
		bool UseIonLighting;
};
