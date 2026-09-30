/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once


enum SideType {
	SIDE_NONE=-1,

	SIDE_GDI,					/// Global Defense Initiative
	SIDE_NOD,					/// Brotherhood of Nod
	SIDE_CIVILIAN,				/// Civilians
	SIDE_MUTANT,				/// The Forgotten

	SIDE_COUNT,
	SIDE_FIRST=0
};
