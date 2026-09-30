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
**	Infantry can be performing various activities. These can range from simple
**	idle animations to physical hand to hand combat.
*/
enum DoType {
	DO_NOTHING=-1,				// Not performing any choreographed sequence.

	DO_STAND_READY=0,
	DO_STAND_GUARD,
	DO_PRONE,
	DO_WALK,
	DO_FIRE_WEAPON,
	DO_LIE_DOWN,
	DO_CRAWL,
	DO_GET_UP,
	DO_FIRE_PRONE,
	DO_IDLE1,
	DO_IDLE2,
	DO_GUN_DEATH,
	DO_EXPLOSION_DEATH,
	DO_EXPLOSION2_DEATH,
	DO_GRENADE_DEATH,
	DO_FIRE_DEATH,
	DO_HOVER,
	DO_FLY,
	DO_TUMBLE,
	DO_FIREFLY,
	DO_STRUGGLE,

	DO_COUNT,
	DO_FIRST=0
};
