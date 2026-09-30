/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

/// Names derived from LightBehaviorNames
enum LightBehaviorType {
	LIGHT_BEHAVIOR_NONE,
	LIGHT_BEHAVIOR_SWEEP,
	LIGHT_BEHAVIOR_CIRCLE,
	LIGHT_BEHAVIOR_FOLLOW,

	LIGHT_BEHAVIOR_COUNT,
	LIGHT_BEHAVIOR_FIRST=0
};
