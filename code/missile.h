/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

class Coord;
template <typename T>
class TVelocity3D;
class DirType;

int Projectile_Motion(Coord & coord, TVelocity3D<double> & velocity, Coord const & target_coord, DirType const & dir, bool aircraft, bool airburst, bool veryhigh);
