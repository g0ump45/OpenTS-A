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

/* $Header: /CounterStrike/COORD.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : COORD.CPP                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : September 10, 1993                                           *
 *                                                                                             *
 *                  Last Update : July 22, 1996 [JLB]                                          *
 *                                                                                             *
 * Support code to handle the coordinate system is located in this module.                     *
 * Routines here will be called QUITE frequently during play and must be                       *
 * as efficient as possible.                                                                   *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Cardinal_To_Fixed -- Converts cardinal numbers into a fixed point number.                 *
 *   Coord_Cell -- Convert a coordinate into a cell number.                                    *
 *   Coord_Move -- Moves a coordinate an arbitrary direction for an arbitrary distance         *
 *   Coord_Scatter -- Determines a random coordinate from an anchor point.                     *
 *   Coord_Spillage_List -- Calculate a spillage list for the dirty rectangle specified.       *
 *   Coord_Spillage_List -- Determines the offset list for cell spillage/occupation.           *
 *   Distance -- Determines the cell distance between two cells.                               *
 *   Distance -- Determines the lepton distance between two coordinates.                       *
 *   Distance -- Fetch distance between two target values.                                     *
 *   Fixed_To_Cardinal -- Converts a fixed point number into a cardinal number.                *
 *   Normal_Move_Point -- Moves point with tilt compensation.                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "coord.h"

#include "_map.h"
#include "inline.h"
#include "mouse.h"


/***************************************************************************
**	This array is used to index a facing in order to retrieve a cell
**	offset that, when added to another cell, will achieve the adjacent cell
**	in the indexed direction.
*/
Cell const AdjacentCell[FACING_COUNT] = {
	Cell(0,  -1),		// North
	Cell(1,  -1),		// North East
	Cell(1,   0),		// East
	Cell(1,   1),		// South East
	Cell(0,   1),		// South
	Cell(-1,  1),		// South West
	Cell(-1,  0),		// West
	Cell(-1, -1),		// North West
};


Point2D const AdjacentPoint[FACING_COUNT] = {
	Point2D(0,              -CELL_LEPTON_H),
	Point2D(CELL_LEPTON_W,  -CELL_LEPTON_H),
	Point2D(CELL_LEPTON_W,  0             ),
	Point2D(CELL_LEPTON_W,  CELL_LEPTON_H ),
	Point2D(0,              CELL_LEPTON_H ),
	Point2D(-CELL_LEPTON_W, CELL_LEPTON_H ),
	Point2D(-CELL_LEPTON_W, 0             ),
	Point2D(-CELL_LEPTON_W, -CELL_LEPTON_H),
};


/***********************************************************************************************
 * Coord_Scatter -- Determines a random coordinate from an anchor point.                       *
 *                                                                                             *
 *    This routine will perform a scatter algorithm on the specified                           *
 *    anchor point in order to return with another coordinate that is                          *
 *    randomly nearby the original. Typical use of this would be for                           *
 *    missile targeting.                                                                       *
 *                                                                                             *
 * INPUT:   coord    -- This is the anchor coordinate.                                         *
 *                                                                                             *
 *          distance -- This is the distance in pixels that the scatter                        *
 *                      should fall within.                                                    *
 *                                                                                             *
 *          lock     -- bool; Convert the new coordinate into a center                         *
 *                      cell based coordinate?                                                 *
 *                                                                                             *
 * OUTPUT:  Returns with a new coordinate that is nearby the original.                         *
 *                                                                                             *
 * WARNINGS:   Maximum pixel scatter distance is 255.                                          *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/01/1992 JLB : Created.                                                                 *
 *   05/13/1992 JLB : Only uses Random().                                                      *
 *=============================================================================================*/
Coord Coord_Scatter(Coord const & coord, int distance, bool lock)
{
	Coord newcoord;

	newcoord = Move_Coord(coord, Random_Dir(DIR_N, DIR_MAX), distance);

	unsigned int cell_x = newcoord.X / CELL_LEPTON_W;
	unsigned int cell_y = newcoord.Y / CELL_LEPTON_H;
	if (cell_x >= MAP_CELL_W || cell_y >= MAP_CELL_H) newcoord = coord;

	if (lock) {
		newcoord = Coord_Snap(newcoord);
	}

	return(newcoord);
}


/// <summary>
/// Fetches the adjacent coordinate, following the lay of the land.
/// This routine steps one cell in the direction specified and then shifts the result
/// vertically by the difference in ground height, so it stays the same distance above
/// the terrain as the coordinate it came from. Use this routine when walking across
/// sloped ground, where a plain adjacent coordinate would end up buried in a hill or
/// hanging over a cliff.
/// </summary>
/// <returns>Returns with the adjacent coordinate, adjusted to match the ground.</returns>
Coord Adjacent_Coord_With_Height(Coord const & coord, FacingType dir)
{
	Coord newcoord = (coord + AdjacentPoint[(int)dir]);
	newcoord.Z += Map.Get_Height_GL(newcoord) - Map.Get_Height_GL(coord);
	return(newcoord);
}
