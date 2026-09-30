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

class Vector4
{
	public:
		//Vector4(void) {};
		//Vector4(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }

		Vector4 & operator = (const Vector4 & v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return(*this); }

		void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }

		//float & operator [](int i) { return (&X)[i]; }
		//const float operator [](int i) const { return (&X)[i]; }

		float X;
		float Y;
		float Z;
		float W;
};
