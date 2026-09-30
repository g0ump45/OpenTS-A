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

enum AttachType {
	ATTACH_NONE=0x00,				// Trigger doesn't attach to anything (orphan trigger types).
	ATTACH_CELL=0x01,				// Trigger can only attach to a cell.
	ATTACH_OBJECT=0x02,				// Trigger can attach only to object (usually building or vehicle).
	ATTACH_MAP=0x04,				// Trigger applies to the general map (usually zone or parallel triggers).
	ATTACH_HOUSE=0x08,				// Trigger applies only to a house.
	ATTACH_GENERAL=0x10,			// General purpose trigger attached to game state.
	ATTACH_TEAM=0x20				// Trigger applies to team object.
};
