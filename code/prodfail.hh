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
**	These are the various return conditions that production may
**	produce.
*/
enum ProdFailType {
	PROD_OK,        // Production request successful.
	PROD_LIMIT,     // Failed with production capacity limit reached.
	PROD_ILLEGAL,   // Failed because of illegal request.
	PROD_CANT       // Failed because unable to comply (busy or occupied).
};
