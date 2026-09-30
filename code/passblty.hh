/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

enum PassabilityType {
	PASSABLE_LAND,
	PASSABLE_CRUSH,
	PASSABLE_BLOCKED,
	PASSABLE_WATER,
	PASSABLE_PARTIALLY_BLOCKED,
	PASSABLE_NO,
	PASSABLE_OUTSIDE,
	PASSABLE_COUNT
};


/*
 * This is what one style of movement makes of one kind of terrain, as looked up in
 * MZonePassability. Ground counts toward a movement zone only when it is TRAVERSAL_PASSABLE,
 * so the other two verdicts are alike as far as the zone layer is concerned; they are kept
 * apart only to distinguish ground this style cannot cross from ground that lies off the
 * playfield altogether.
 */
enum TraversalType {
	TRAVERSAL_PASSABLE = 1,
	TRAVERSAL_IMPASSABLE = 2,
	TRAVERSAL_ILLEGAL = 3
};
