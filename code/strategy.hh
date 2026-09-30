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
**	These are the various actions a house may perform. These actions refer
**	to global events that encompass selling and production. Low level house
**	specific actions of choosing targets is handled elsewhere.
*/
enum StrategyType {
	STRATEGY_FIRE_SALE,				// Situation hopeless, sell and attack.
	STRATEGY_RAISE_MONEY,			// Money is low, emergency raise cash.

	STRATEGY_COUNT,
	STRATEGY_FIRST=STRATEGY_FIRE_SALE
};
