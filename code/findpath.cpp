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

/* $Header: /CounterStrike/FINDPATH.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : FINDPATH.CPP                                                 *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : September 10, 1993                                           *
 *                                                                                             *
 *                  Last Update : May 25, 1995   [PWG]                                         *
 *                                                                                             *
 * The path algorithm works by following a LOS path to the target. If it                       *
 * collides with an impassable spot, it uses an Edge following routine to                      *
 * get around it. The edge follower moves along the edge in a clockwise or                     *
 * counter clockwise fashion until finding the destination spot. The                           *
 * destination is determined by Find_Path. It is the first passable that                       *
 * can be reached (so it will handle the doughnut case, where there is                         *
 * a passable in the center of an unreachable area).                                           *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Clear_Path_Overlap -- clears the path overlap list                                        *
 *   Find_Path -- Find a path from point a to point b.                                         *
 *   Find_Path_Cell -- Finds a given cell on a specified path                                  *
 *   Follow_Edge -- Follow an edge to get around an impassable spot.                           *
 *   FootClass::Unravel_Loop -- Unravels a loop in the movement path                           *
 *   Get_New_XY -- Get the new x,y based on current position and direction.                    *
 *   Optimize_Moves -- Optimize the move list.                                                 *
 *   Set_Path_Overlap -- Sets the overlap bit for given cell                                   *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "_astar.h"
#include "_bench.h"
#include "_map.h"
#include "astar.h"
#include "bench.h"
#include "foot.h"
#include "inline.h"

#include "bench.hh"


/*
**	Modify this macro so that given two cell values, it will return
**	a value between 0 and 7, with 0 being North and moving
**	clockwise (just like map degrees).
*/
#define	CELL_FACING(a, b)		Dir_Facing(::Direction((a), (b)))


/*-------------------------------------------------------------------------*/

/// <summary>
/// Fetches the facing directly opposite to the one specified.
/// This routine is used by the path finder when it must undo a move it has already
/// taken, or work back along a path it has built.
/// </summary>
/// <returns>Returns with the facing that points the other way, 180 degrees around.</returns>
inline FacingType Opposite(FacingType face)
{
	return( (FacingType) (face ^ 4));
}


/// <summary>
/// Fetches the facing that results from turning by the amount specified.
/// This routine is used by the path finder as it sweeps around an obstacle, rotating its
/// search direction a step at a time.
/// </summary>
/// <param name="dir">The amount to turn by, expressed as a facing offset.</param>
inline static FacingType Next_Direction(FacingType facing, FacingType dir)
{
	facing = FacingType(facing + dir);
	return(facing);
}


/***********************************************************************************************
 * Find_Path -- Find a path from point a to point b.                                           *
 *                                                                                             *
 * INPUT:      int source x,y, int destination x,y, char *final moves                          *
 *             array to store moves, int maximum moves we may attempt                          *
 *                                                                                             *
 * OUTPUT:     int number of moves it took (IMPOSSIBLE_MOVES if we could                       *
 *             not reach the destination                                                       *
 *                                                                                             *
 * WARNINGS:   This algorithm assumes that the target is NOT situated                          *
 *             inside an impassable. If this case may arise, the do-while                      *
 *             statement inside the inner while (true) must be changed                         *
 *             to include a check to se if the next_x,y is equal to the                        *
 *             dest_x,y. If it is, then return(IMPOSSIBLE_MOVES).                              *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/08/1991  CY : Created.                                                                 *
 *=============================================================================================*/
PathStruct * FootClass::Find_Path(Cell const & dest, FacingType * final_moves, int maxlen, MoveType threshhold, int path_offset, int avoidance)
{
	PathStruct *			path;								// Which path to actually use.
	Cell					source = Destination_Coord();		// Source expressed as cell

	/*
	**	If we have been provided an illegal place to store our final moves
	**	then forget it.
	*/
	if (!final_moves) return(NULL);

	BStart(BENCH_FINDPATH);

	source = Follow_Path(source, path_offset, Path);
	path = Search.Find_Path(source, dest, this, final_moves, -1, MZONE_NONE, (AStarClass::ObstacleAvoidanceType)avoidance);

	BEnd(BENCH_FINDPATH);

	return(path);
}


/// <summary>
/// Finds an approachable cell near the destination.
/// This routine is used to pick a staging spot alongside something the unit cannot
/// occupy itself, such as a building. It looks along the side of the destination that
/// faces the source and works outward until it finds ground this unit may enter.
/// </summary>
/// <param name="src">The cell the unit would be approaching from.</param>
/// <param name="dst">The cell to find a spot alongside.</param>
/// <param name="start">The closest distance, in cells, that may be considered.</param>
/// <param name="max">The distance at which the search gives up.</param>
/// <returns>Returns with the cell found. If nothing within range can be entered, then
/// CELL_NONE is returned.</returns>
Cell FootClass::Safety_Point(Cell const & src, Cell const & dst, int start, int max)
{
	FacingType dir;
	Cell		  next;
	int 		  lp;

	dir = Facing_Sub((CELL_FACING(src, dst) ^ 4), 1);

	/*
	**	Loop through the different acceptable distances.
	*/
	for (int dist = start; dist < max; dist ++) {

		/*
		**	Move to the starting location.
		*/
		next = dst;

		for (lp = 0; lp < dist; lp ++) {
			next = Adjacent_Cell(next, dir);
		}

		if (dir & 1) {
			/*
			**	If our direction is diagonal than we need to check
			**	only one side which is as long as both of the old sides
			**	together.
			*/
			for (lp = 0; lp < dist << 1; lp ++) {
				next = Adjacent_Cell(next, Facing_Add(dir, FACING_135));
				if (Can_Enter_Cell(&Map[next], Facing_Add(dir, FACING_135)) == MOVE_OK) {
					return(next);
				}
			}
		} else {
			/*
			**	If our direction is not diagonal than we need to check two
			**	sides so that we are checking a corner like location.
			*/
			for (lp = 0; lp < dist; lp ++) {
				next = Adjacent_Cell(next, Facing_Add(dir, FACING_90));
				if (Can_Enter_Cell(&Map[next], Facing_Add(dir, FACING_90)) == MOVE_OK) {
					return(next);
				}
			}

			for (lp = 0; lp < dist; lp ++) {
				next = Adjacent_Cell(next, Facing_Add(dir, FACING_180));
				if (Can_Enter_Cell(&Map[next], Facing_Add(dir, FACING_180)) == MOVE_OK) {
					return(next);
				}
			}
		}
	}
	return(CELL_NONE);
}
