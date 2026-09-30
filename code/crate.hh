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
**	These enumerate the various crate powerups that are available.
*/
enum CrateType {
	CRATE_MONEY,
	CRATE_UNIT,
	CRATE_HEAL_BASE,
	CRATE_CLOAK,
	CRATE_EXPLOSION,
	CRATE_NAPALM,
	CRATE_SQUAD,
	CRATE_DARKNESS,
	CRATE_REVEAL,
	CRATE_ARMOR,
	CRATE_SPEED,
	CRATE_FIREPOWER,
	CRATE_ICBM,
	CRATE_INVULN,
	CRATE_VETERAN,
	CRATE_ION_STORM,
	CRATE_GAS,
	CRATE_TIBERIUM,
	CRATE_POD,

	CRATE_COUNT,
	CRATE_FIRST=0
};
