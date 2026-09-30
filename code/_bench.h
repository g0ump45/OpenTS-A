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

class Benchmark;

extern Benchmark * Benches;

#ifdef _DEBUG
#define	BStart(a)	if (Benches != NULL) Benches[a].Begin()
#define	BEnd(a)		if (Benches != NULL) Benches[a].End()
#else
#define	BStart(a)
#define	BEnd(a)
#endif
