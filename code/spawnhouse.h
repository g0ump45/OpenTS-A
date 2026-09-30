/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/


#pragma once

#include "house.hh"


/*
 * A spawn house names whoever starts at one of the eight numbered start positions.
 * No house exists for it: a scenario spells it "Spawn1".."Spawn8" or "<Player @ A>".."<Player @ H>",
 * a numeric parameter 50..57 or 4475..4482, and it resolves to a live house only while
 * somebody holds that position.
 */
constexpr int SPAWN_HOUSE_COUNT = 8;

// Either spelling, exact and case-insensitive, to its start waypoint 0..7; -1 for anything else.
int Spawn_House_Waypoint(char const * name);

// Either numeric family to its start waypoint 0..7; -1 for anything else, 58..60 included.
int Spawn_House_Waypoint(HousesType house);

// The spellings written back: 50 + spawn_waypoint and "Spawn<spawn_waypoint + 1>".
HousesType Spawn_House_Type(int spawn_waypoint);
char const * Spawn_House_Name(int spawn_waypoint);
