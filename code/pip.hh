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

/****************************************************************************
**	The pip shapes and text shapes are enumerated according to the following
**	type. These special shapes are drawn over special objects or in other places
**	where shape technology is needed.
*/
enum PipEnum {
	PIP_NONE = -1,

	PIP_EMPTY,			// Empty pip spot.
	PIP_GREEN,			/// Full pip with green coloring.
	PIP_YELLOW,			/// Full pip with yellow coloring.
	PIP_WHITE,			/// Full pip with white coloring.
	PIP_RED,			/// Full pip with red coloring.
	PIP_BLUE,			/// Full pip with blue coloring.
	PIP_MEDIC,			// Little medic red cross.
	PIP_VETERAN,		/// Veteran unit pip.
	PIP_ELITE,			/// Elite unit pip.
	PIP_HEALTH_GREEN,	/// Green health pip.
	PIP_HEALTH_YELLOW,	/// Yellow health pip.
	PIP_HEALTH_RED,		/// Red health pip.

	PIP_COUNT,
};


enum Pip2Enum  {
	PIP2_NONE = -1,

	PIP2_EMPTY,			// Empty pip spot.
	PIP2_GREEN,			/// Full pip with green coloring.
	PIP2_YELLOW,		/// Full pip with yellow coloring.
	PIP2_WHITE,			/// Full pip with white coloring.
	PIP2_RED,			/// Full pip with red coloring.
	PIP2_BLUE,			/// Full pip with blue coloring.
	PIP2_AMMO,			/// Ammo pip.

	PIP2_COUNT,
};


enum PipScaleType {
	PIPSCALE_NONE,

	PIPSCALE_AMMO,
	PIPSCALE_TIBERIUM,
	PIPSCALE_PASSENGERS,
	PIPSCALE_POWER,
	PIPSCALE_CHARGE,

	PIPSCALE_COUNT,
};
