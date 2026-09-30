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
**	This is the various threat scan methods that can be used when looking
**	for targets.
*/
enum ThreatType {
	THREAT_NORMAL=0x0000,       // Any distance threat scan?
	THREAT_RANGE=0x0001,        // Limit scan to weapon range?
	THREAT_AREA=0x0002,         // Limit scan to general area (twice weapon range)?
	THREAT_AIR=0x0004,          // Scan for air units?
	THREAT_INFANTRY=0x0008,     // Scan for infantry units?
	THREAT_VEHICLES=0x0010,     // Scan for vehicles?
	THREAT_BUILDINGS=0x0020,    // Scan for buildings?
	THREAT_TIBERIUM=0x0040,     // Limit scan to Tiberium processing objects?
	THREAT_BOATS=0x0080,        // Scan for gunboats?
	THREAT_CIVILIANS=0x0100,    // Consider civilians to be primary target?
	THREAT_CAPTURE=0x0200,      // Consider capturable buildings only?
	THREAT_FAKES=0x0400,        // Consider fake buildings a greater target?
	THREAT_POWER=0x0800,        // Consider power generating facilities a greater target?
	THREAT_FACTORIES=0x1000,    // Consider factories a greater target?
	THREAT_BASE_DEFENSE=0x2000, // Consider base defense buildings a greater target?
	THREAT_ALLIES=0x4000,       /// Scan for allies?
};

#define THREAT_GROUND	(THREAT_VEHICLES|THREAT_BUILDINGS|THREAT_INFANTRY)
