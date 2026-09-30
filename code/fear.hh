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
**	This enumerates the various known fear states for infantry units.
**	At these stages, certain events or recovery actions are performed.
*/
enum FearType {
	FEAR_NONE=0,        // No fear at all (default state).
	FEAR_ANXIOUS=10,    // Something makes them scared.
	FEAR_SCARED=100,    // Scared enough to take cover.
	FEAR_PANIC=200,     // Run away! Run away!
	FEAR_MAXIMUM=255    // Scared to death.
};
