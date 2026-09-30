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
**	If an object can cloak, then it will be in one of these states.
**	For objects that cannot cloak, they will always be in the
**	UNCLOAKED state. This state controls how the object transitions between
**	cloaked and uncloaked conditions.
*/
enum CloakType {
	UNCLOAKED,  // Completely visible (normal state).
	CLOAKING,   // In process of cloaking.
	CLOAKED,    // Completely cloaked (invisible).
	UNCLOAKING  // In process of uncloaking.
};
