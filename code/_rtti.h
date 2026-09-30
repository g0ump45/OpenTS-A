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

#include "rtti.hh"

class TechnoClass;
class AbstractClass;

char const * Name_From_RTTI(RTTIType rtti);
RTTIType RTTI_From_Name(char const * name);

/*
 * Primary template - DECLARED ONLY
 */
template <typename T>
T Dynamic_Cast(AbstractClass const * target);
template <typename T>
T Dynamic_Cast(AbstractClass * target);

/*
 * Specializations
 */
template <>
TechnoClass const * Dynamic_Cast<TechnoClass const *>(AbstractClass const * target);
template <>
TechnoClass * Dynamic_Cast<TechnoClass *>(AbstractClass * target);
