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

#include "coord.h"

#include "armor.hh"
#include "land.hh"
#include "mph.hh"

class WarheadTypeClass;
class AnimTypeClass;
class TechnoClass;
class Coord;
class DirType;

int Modify_Damage(int damage, WarheadTypeClass const * warhead, ArmorType armor, int distance);
void Chain_Reaction_Damage(Cell const & cell);
void Explosion_Damage(Coord const & coord, int strength, TechnoClass * source, WarheadTypeClass const * warhead, bool dochainreaction=true);
AnimTypeClass const * Combat_Anim(int damage, WarheadTypeClass const * warhead, LandType land, Coord const & coord);
void Combat_Lighting(Coord coord, int damage, WarheadTypeClass const * warhead, bool forced=false);
void Wide_Area_Damage(Coord const & coord, LEPTON radius, int rawdamage, TechnoClass * source, WarheadTypeClass const * warhead);

bool Calculate_Projectile_Pitch(bool high_arc, int speed, int distance, int height, double gravity, DirType & pitch);
bool Calculate_Projectile_Angle(bool high_arc, int speed, int distance, int height, double gravity, double & angle);
bool Is_Projectile_Trajectory_Valid(int speed, int distance, int height, double gravity);

MPHType Calculate_Projectile_Speed(int range, double gravity);
int Get_Explosion_Z(Coord coord);
double Get_Floater_Gravity(void);
