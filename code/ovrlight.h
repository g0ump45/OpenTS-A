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

#include "coord.h"

template<class T> class DynamicVectorClass;

class SpotLightClass
{
	public:
		SpotLightClass(Coord pos, int size);
		~SpotLightClass(void);

		void Set_Radius(int radius) {Radius=radius;}
		void AI(void);
		void Draw_It(void);

		static void One_Time(void);
		static void Update_All(void);
		static void Clear_All(void);
		static void Draw_All(void);

		enum {
			SPOTLIGHT_RADIUS_STEP = 8,
			SPOTLIGHT_MAX_RADIUS = 80,
			SPOTLIGHT_SURFACE_COUNT = 64,
			SPOTLIGHT_EXTRA_SURFACE_COUNT = 10,
		};

	private:
		/*
		 * This is the map coordinate the glow is centered on, fixed when the light is created.
		 * Nothing is drawn if that coordinate lies off screen or under fog of war.
		 */
		Coord Position;

		/*
		 * This is how far the glow has spread, widened by SPOTLIGHT_RADIUS_STEP with
		 * every update until the light burns out at SPOTLIGHT_MAX_RADIUS. It doubles as
		 * the light's age, since it also picks which brightness ramp the glow is drawn from.
		 */
		int Radius;

		/*
		 * This is the scale of the light, specified when it is created. It scales the ramp
		 * picked by the radius, so that a large explosion throws a stronger glow than a
		 * small one of the same age.
		 */
		int Size;
};


extern DynamicVectorClass<SpotLightClass *> SpotLights;
