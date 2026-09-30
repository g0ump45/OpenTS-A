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
**	Urgency rating used to determine what action to perform. The greater
**	the urgency the more likely the corresponding action will be chosen.
**	These values are assigned to each potential desired action the house
**	is to perform.
*/
enum UrgencyType {
	URGENCY_NONE,				// No action on this matter is needed or desired.

	URGENCY_LOW,        // Minimal attention requested.
	URGENCY_MEDIUM,     // Normal attention requested.
	URGENCY_HIGH,       // High attention requested.
	URGENCY_CRITICAL,   // This matter must be addressed immediately.

	URGENCY_COUNT,
	URGENCY_FIRST=URGENCY_CRITICAL
};
