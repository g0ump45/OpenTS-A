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

class PKey;

extern PKey FastKey;
#ifdef _DEBUG
extern PKey SlowKey;
#endif

/// This declaration is load-bearing, not just documentation: without it the
/// const array in _pk.cpp gets internal linkage and the compiler discards it.
extern char const Keys[];
