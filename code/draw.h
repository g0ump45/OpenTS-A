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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /Commando/Library/Draw.h                                    $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "surface.h"

#include "draw.hh"
#include "zgrad.hh"

class ConvertClass;
class ShapeSet;
class Blitter;

void Draw_Shape(Surface & surface, ConvertClass & convert, ShapeSet const * shapefile, int shapenum, Point2D const & point, Rect const & window, ShapeFlags_Type flags = SHAPE_NORMAL, unsigned char const * remap = NULL, int height_offset = 0, ZGradientType zgrad = ZGRAD_GROUND, int intensity = 1000, ShapeSet const * z_shapefile = NULL, int z_shapenum = 0, Point2D z_off = Point2D(0,0));
void Blit_Block(Surface & surface, ConvertClass & convert, Surface const & source, Rect const & sourcerect, Point2D const & point, Rect const & clipwindow, unsigned char const * remap = NULL, Blitter const * blitter = NULL, int = 0, ZGradientType zgrad = ZGRAD_GROUND, int = 1000, int = 0);
