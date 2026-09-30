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

/**********************************************************************
**	These are the special weapons that can be used in the game. The common thread
**	with these weapons is that they are controlled through the sidebar
**	mechanism.
*/
enum SuperWeaponType {
	SUPER_NONE=-1,

	SUPER_MULTI_MISSILE,
	SUPER_EM_PULSE,
	SUPER_FIRESTORM,
	SUPER_ION_CANNON,
	SUPER_HUNTER_SEEKER,
	SUPER_CHEM_MISSILE,
	SUPER_DROP_PODS,

	SUPER_COUNT,
	SUPER_FIRST=0,

	SUPER_ANY=1
};
