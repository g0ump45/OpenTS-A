/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/


#pragma once

#include "coord.h"

class AbstractClass;
class Surface;
struct UILineStyleType;


// Where an order line pointing at the target ends: its center, lifted onto a bridge deck
// when the cell lies under one.
Coord Action_Line_Coord(AbstractClass const * target);

// Draws one order line between two map coordinates, clipped to the tactical view, with a
// square of point_size pixels on each end. Dashes are dash_length pixels long and march by
// the wall clock at dash_rate milliseconds a step, or by game frame when dash_rate is zero.
void Draw_Action_Line_Segment(Surface & surface, Coord const & start, Coord const & end, UILineStyleType const & style, int point_size, int dash_length, int dash_rate);
