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
**	When a unit gets damaged, the result of the damage is returned as
**	this type. It can range from no damage taken to complete destruction.
*/
enum ResultType {
	RESULT_NONE,				// No damage was taken by the target.
	RESULT_LIGHT,				// Some damage was taken, but no state change occurred.
	RESULT_HALF,				// Damaged to below half strength (only returned on transition).
	RESULT_MAJOR,				// Damaged down to 1 hit point.
	RESULT_DESTROYED,			// Damaged to complete destruction.
	RESULT_ALREADY_DESTROYED	/// Some damage was taken, but did not kill the target.
								/// However, something else has finished the target off and handled its destruction.
};
