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

#include "vector.h"

class TheaterClass;

/*
 * Every theater the rules declared, in the order they declared them. A theater's position
 * here is its TheaterType, so the list is fixed once the rules have been read.
 */
extern DynamicVectorClass<TheaterClass *> Theaters;
