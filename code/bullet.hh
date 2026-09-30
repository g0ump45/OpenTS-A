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
**	This enumerates the various bullet types. These types specify bullet's
**	visual and explosive characteristics.
*/
enum BulletType {
	BULLET_NONE=-1,

	BULLET_INVISIBLE,
	BULLET_MULTI_MISSILE,
	BULLET_CHEM_MISSILE,
	BULLET_PULSPR,
	BULLET_LLINE,
	BULLET_LLINE2,
	BULLET_AA_HEAT_SEEKER,
	BULLET_LOBBED2,
	BULLET_CANNON,
	BULLET_BALLISTIC,
	BULLET_CANNON2,
	BULLET_PROTON_TORPEDO,
	BULLET_INVISIBLE2,
	BULLET_AA_HEAT_SEEKER2,
	BULLET_HEAT_SEEKER,
	BULLET_NULL,
	BULLET_LOBBED,
	BULLET_INVISIBLE3,
	BULLET_DOG_SHARD,
	BULLET_PROTON_BLAST,
	BULLET_NUKE_UP,
	BULLET_NUKE_DOWN,

	/*
	 * Firestorm additions start here
	 */
	BULLET_BALLISTIC2,
	BULLET_LIMPET,
	BULLET_AA_LLINE,
	BULLET_DUAL_CLUSTER,
	BULLET_WEB_CAPSULE,

	BULLET_COUNT,
	BULLET_FIRST=0
};
