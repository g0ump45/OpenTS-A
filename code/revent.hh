/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

/// Names derived from RadarEventNames
enum RadarEventType {
	RADAREVENT_NONE=-1,

	RADAREVENT_COMBAT,
	RADAREVENT_NONCOMBAT,
	RADAREVENT_DROPZONE,
	RADAREVENT_BASE_ATTACKED,
	RADAREVENT_HARVESTER_ATTACKED,
	RADAREVENT_ENEMY_SENSED,

	RADAREVENT_COUNT,
	RADAREVENT_FIRST=0
};
