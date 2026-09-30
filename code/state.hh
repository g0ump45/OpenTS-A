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
**	This records the current state of the computer controlled base. The
**	AI will respond according to this state in order to control
**	production and unit orders.
*/
enum StateType {
	STATE_BUILDUP,      // Base is building up (defensive buildup stage).
	STATE_BROKE,        // Low on money, need cash or income source.
	STATE_THREATENED,   // Enemy units are designated to move close by.
	STATE_ATTACKED,     // Base is under direct attack.
	STATE_ENDGAME       // Resistance is futile.
};
