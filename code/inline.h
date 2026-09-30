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

/* $Header: /CounterStrike/INLINE.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : INLINE.H                                                     *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 08/21/96                                                     *
 *                                                                                             *
 *                  Last Update : September 30, 1996 [JLB]                                     *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Adjacent_Cell -- Calculate the adjacent cell in the direction specified.                  *
 *   Adjacent_Cell -- Calculate the adjacent cell in the direction specified.                  *
 *   Cell_Coord -- Convert a cell to a coordinate value.                                       *
 *   Cell_To_Lepton -- Convert a cell distance into a lepton distance.                         *
 *   Cell_X -- Fetch the X cell component from the cell value.                                 *
 *   Cell_Y -- Fetch the Y cell component from the cell value specified.                       *
 *   Coord_Add -- Adds coordinates together.                                                   *
 *   Coord_Fraction -- Discards all but the sub-cell components of the coordinate.             *
 *   Coord_Mid -- Finds the midpoint between two coordinates.                                  *
 *   Coord_Snap -- Coerce coordinate to refer to center of a cell.                             *
 *   Coord_Sub -- Subtracts one coordinate from another.                                       *
 *   Coord_Whole -- Discards the sub-cell components of the coordinate.                        *
 *   Coord_X -- Fetches the X lepton component from a coordinate value.                        *
 *   Coord_XCell -- Fetch the X cell component from a coordinate value.                        *
 *   Coord_XLepton -- Fetch the X sub-cell lepton component from the coordinate.               *
 *   Coord_Y -- Fetch the Y lepton component from the coordinate value.                        *
 *   Coord_YCell -- Fetch the Y cell component from a coordinate.                              *
 *   Coord_YLepton -- Fetches the Y lepton sub-cell component from the coordinate.             *
 *   Dir_Facing -- Convert a DirType into a FacingType value.                                  *
 *   Dir_To_16 -- Convert a facing to a 0..15 value.                                           *
 *   Dir_To_32 -- Convert a DirType into a 0..31 value.                                        *
 *   Dir_To_8 -- Convert a DirType into a value from 0 to 7.                                   *
 *   Direction -- Calculates the DirType from one cell to another.                             *
 *   Direction -- Determines the facing value from one coordinate to another.                  *
 *   Direction256 -- Calculate the facing value from one coordinate to another.                *
 *   Direction8 -- Fetches the direction from one coordinate to another.                       *
 *   Distance -- Finds the distance between two arbitrary points.                              *
 *   Facing_Dir -- Convert a FacingType into a DirType.                                        *
 *   Lepton_To_Cell -- Convert lepton distance to cell distance.                               *
 *   Lepton_To_Pixel -- Convert a lepton value into pixel value.                               *
 *   Percent_Chance -- Calculate a percentage chance event.                                    *
 *   Pixel_To_Lepton -- Convert pixel value into lepton equivalent.                            *
 *   Random_Pick -- Pick a random number in a specified range.                                 *
 *   Sim_Percent_Chance -- Calculates a percentage chance event for local events.              *
 *   Sim_Random_Pick -- Picks a random number that will not affect the game.                   *
 *   Text_String -- Convert a text number into a text pointer.                                 *
 *   XYP_COORD -- Convert pixel components into a coordinate value.                            *
 *   XYP_Coord -- Combine pixel values into a coordinate.                                      *
 *   XY_Cell -- Create a cell from X and Y cell components.                                    *
 *   XY_Coord -- Convert X Y lepton components into a COORD.                                   *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "ccrand.h"
#include "coord.h"
#include "facing.h"
#include "sun.h"

#include <cmath>


extern Cell const							AdjacentCell[FACING_COUNT];
extern Point2D const						AdjacentPoint[FACING_COUNT];


/***********************************************************************************************
 * Cell_To_Lepton -- Convert a cell distance into a lepton distance.                           *
 *                                                                                             *
 *    This routine will take the cell distance specified and convert it into a lepton distance.*
 *                                                                                             *
 * INPUT:   cell_distance  -- The distance in cells to convert.                                *
 *                                                                                             *
 * OUTPUT:  Returns with the lepton equivalent of the cell distance specified.                 *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/21/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline LEPTON Cell_To_Lepton(int cell_distance)
{
	LEPTON lepton;
	lepton = cell_distance * CELL_LEPTON_W;
	return(lepton);
}


/***********************************************************************************************
 * Lepton_To_Cell -- Convert lepton distance to cell distance.                                 *
 *                                                                                             *
 *    This routine will convert the specified lepton distance into the closest cell distance   *
 *    possible. This might require rounding up or down as necessary.                           *
 *                                                                                             *
 * INPUT:   lepton_distance   -- The lepton distance to convert.                               *
 *                                                                                             *
 * OUTPUT:  Returns with the cell distance that most closely corresponds to the lepton         *
 *          distance specified.                                                                *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/21/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline int Lepton_To_Cell(LEPTON lepton_distance)
{
	return(lepton_distance / CELL_LEPTON);
}


/***********************************************************************************************
 * Coord_Snap -- Coerce coordinate to refer to center of a cell.                               *
 *                                                                                             *
 *    This routine will take the specified coordinate and force it to refer to the center of   *
 *    the cell.                                                                                *
 *                                                                                             *
 * INPUT:   coord -- The coordinate to modify.                                                 *
 *                                                                                             *
 * OUTPUT:  Returns with the specified coordinate after it has been modified to refer to the   *
 *          center of the cell.                                                                *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/23/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Coord Coord_Snap(Coord const & coord)
{
	return(Coord(coord.X - (coord.X & (CELL_LEPTON_W-1)) + CELL_LEPTON_W/2, coord.Y - (coord.Y & (CELL_LEPTON_H-1)) + CELL_LEPTON_H/2, coord.Z));
}


/***********************************************************************************************
 * Coord_Fraction -- Discards all but the sub-cell components of the coordinate.               *
 *                                                                                             *
 *    Use this routine to discard the cell components of the coordinate, leaving only the      *
 *    sub-cell component.                                                                      *
 *                                                                                             *
 * INPUT:   coord -- The coordinate to modify.                                                 *
 *                                                                                             *
 * OUTPUT:  Returns with just the sub-cell components intact from the supplied coordinate.     *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/23/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Coord Coord_Fraction(Coord const & coord)
{
	Coord tmp;
	tmp.X = coord.X & (CELL_LEPTON_W-1);
	tmp.Y = coord.Y & (CELL_LEPTON_H-1);
	tmp.Z = coord.Z;
	return(tmp);
}


/***********************************************************************************************
 * Coord_Whole -- Discards the sub-cell components of the coordinate.                          *
 *                                                                                             *
 *    This routine will discard the sub-cell components, leaving only the whole cell portion.  *
 *                                                                                             *
 * INPUT:   coord -- The coordinate to modify.                                                 *
 *                                                                                             *
 * OUTPUT:  Returns with only the whole cell components of the coordinate intact. The          *
 *          resulting coordinate will refer to the upper left corner of the cell.              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/23/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Coord Coord_Whole(Coord const & coord)
{
	int x = coord.X / CELL_LEPTON_W;
	int y = coord.Y / CELL_LEPTON_H;

	return(Coord(x * CELL_LEPTON_W, y * CELL_LEPTON_H, coord.Z));
}


/***********************************************************************************************
 * Coord_Mid -- Finds the midpoint between two coordinates.                                    *
 *                                                                                             *
 *    This will find the coordinate that is exactly between the two coordinates specified.     *
 *                                                                                             *
 * INPUT:   coord1   -- The first coordinate.                                                  *
 *                                                                                             *
 *          coord2   -- The second coordinate.                                                 *
 *                                                                                             *
 * OUTPUT:  Returns with the midpoint between the two coordinates.                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/23/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Coord Coord_Mid(Coord const & coord1, Coord const & coord2)
{
	Coord coord = coord1 + coord2;
	coord.X = coord.X / 2;
	coord.Y = coord.Y / 2;
	coord.Z = coord.Z / 2;
	return(coord);
}


/***********************************************************************************************
 * Coord_Move -- Moves a coordinate an arbitrary direction for an arbitrary distance           *
 *                                                                                             *
 *    This function will move a coordinate in a using SIN and COS arithmetic.                  *
 *                                                                                             *
 * INPUT:   start    -- The starting coordinate.                                               *
 *                                                                                             *
 *          dir      -- The direction to move the coordinate.                                  *
 *                                                                                             *
 *          distance -- The distance to move the coordinate position (in leptons).             *
 *                                                                                             *
 * OUTPUT:  Returns the new coordinate position.                                               *
 *                                                                                             *
 * WARNINGS:   This routine uses multiplies -- use with caution.                               *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/27/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Coord Move_Coord(Coord const & start, DirType const & dir, int distance)
{
	double radians = dir.As_Radian();
	return(Coord((start.X + std::cos(radians) * distance), (start.Y - std::sin(radians) * distance), start.Z));
}


/***********************************************************************************************
 * Cell_Move -- Moves a cell an arbitrary direction for an arbitrary distance                  *
 *                                                                                             *
 *    This function will move a cell in a using SIN and COS arithmetic.                        *
 *                                                                                             *
 * INPUT:   start    -- The starting cell.                                                     *
 *                                                                                             *
 *          dir      -- The direction to move the cell.                                        *
 *                                                                                             *
 *          distance -- The distance to move the cell position.                                *
 *                                                                                             *
 * OUTPUT:  Returns the new cell position.                                                     *
 *                                                                                             *
 * WARNINGS:   This routine uses multiplies -- use with caution.                               *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/27/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Cell Move_Cell(Cell const & start, DirType const & dir, short distance)
{
	double radians = dir.As_Radian();
	return(Cell((start.X + std::cos(radians) * distance), (start.Y - std::sin(radians) * distance)));
}


/***********************************************************************************************
 * Dir_Facing -- Convert a DirType into a FacingType value.                                    *
 *                                                                                             *
 *    Use this routine to convert the specified DirType value into the closest FacingType      *
 *    value that matches it.                                                                   *
 *                                                                                             *
 * INPUT:   facing   -- The DirType to convert.                                                *
 *                                                                                             *
 * OUTPUT:  Returns with a FacingType value that most closely matches the DirType specified.   *
 *                                                                                             *
 * WARNINGS:   Precision of direction is lost by this transformation.                          *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline FacingType Dir_Facing(DirType facing)
{
	return(facing.As_Facing());
}


inline FacingType Dir_Facing(Dir256 facing)
{
	return(Dir_Facing(DirType(facing)));
}


/***********************************************************************************************
 * Facing_Dir -- Convert a FacingType into a DirType.                                          *
 *                                                                                             *
 *    This will conver the specified FacingType value into the DirType that exactly matches    *
 *    it.                                                                                      *
 *                                                                                             *
 * INPUT:   facing   -- The FacingType to convert.                                             *
 *                                                                                             *
 * OUTPUT:  Returns with the DirType that exactly matches the facing.                          *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Dir256 Facing_Dir(FacingType facing)
{
	return((Dir256)((int)facing << 5));
}


/***********************************************************************************************
 * Direction -- Determines the facing value from one coordinate to another.                    *
 *                                                                                             *
 *    This will determine the DirType from the first coordinate to the second.                 *
 *                                                                                             *
 * INPUT:   coord1   -- The first coordinate that facing will be calculated from.              *
 *                                                                                             *
 *          coord2   -- The second coordinate to calculate facing to.                          *
 *                                                                                             *
 * OUTPUT:  Returns with the DirType that represents the facing from coordinate 1 to coordinate*
 *          2.                                                                                 *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline DirType Direction(Coord const & coord1, Coord const & coord2)
{
	int x1 = coord1.X;
	int x2 = coord2.X;

	return(std::atan2((double)coord1.Y - (double)coord2.Y, (double)x2 - (double)x1));
}


/***********************************************************************************************
 * Direction -- Calculates the DirType from one cell to another.                               *
 *                                                                                             *
 *    This routine will calculate the facing to get from one cell to another. Since dealing    *
 *    with cells is much less precise than with coordinates, the return value is only          *
 *    accurate to 8 facings.                                                                   *
 *                                                                                             *
 * INPUT:   cell1 -- The cell to calculate the DirType from.                                   *
 *                                                                                             *
 *          cell2 -- The cell to calculate the DirType to.                                     *
 *                                                                                             *
 * OUTPUT:  Returns with the DirType to get from the first cell to the second.                 *
 *                                                                                             *
 * WARNINGS:   The return value is only accurate to the 8 primary compass rose directions.     *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline DirType Direction(Cell const & cell1, Cell const & cell2)
{
	return(std::atan2((double)(int)cell1.Y - (double)(int)cell2.Y, (double)(int)cell2.X - (double)(int)cell1.X));
}


inline DirType Direction(Point2D const & coord1, Point2D const & coord2)
{
	int x1 = coord1.X;
	int x2 = coord2.X;

	return(std::atan2((double)coord1.Y - (double)coord2.Y, (double)x2 - (double)x1));
}


/***********************************************************************************************
 * Adjacent_Cell -- Calculate the adjacent cell in the direction specified.                    *
 *                                                                                             *
 *    This will coerce the coordinate specified so that it will refer to the immediately       *
 *    adjacent cell in the direction specified.                                                *
 *                                                                                             *
 * INPUT:   coord -- The coordinate to calculate the adjacency from.                           *
 *                                                                                             *
 *          dir   -- The direction to travel to calculate the adjacent cell.                   *
 *                                                                                             *
 * OUTPUT:  Returns with the coordinate the refers to the adjacent cell in the direciton       *
 *          specified.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Coord Adjacent_Cell(Coord const & coord, FacingType dir)
{
	return(coord + AdjacentPoint[(int)dir & 0x07]);
}


/***********************************************************************************************
 * Adjacent_Cell -- Calculate the adjacent cell in the direction specified.                    *
 *                                                                                             *
 *    This will coerce the coordinate specified so that it will refer to the immediately       *
 *    adjacent cell in the direction specified.                                                *
 *                                                                                             *
 * INPUT:   coord -- The coordinate to calculate the adjacency from.                           *
 *                                                                                             *
 *          dir   -- The direction to travel to calculate the adjacent cell.                   *
 *                                                                                             *
 * OUTPUT:  Returns with the coordinate the refers to the adjacent cell in the direciton       *
 *          specified.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Coord Adjacent_Cell(Coord const & coord, Dir256 dir)
{
	return(Adjacent_Cell(coord, Dir_Facing(dir)));
}


/***********************************************************************************************
 * Adjacent_Cell -- Calculate the adjacent cell in the direction specified.                    *
 *                                                                                             *
 *    This routine will take the specified cell and coerce it to refer to the immediately      *
 *    adjacent cell in the direction specified.                                                *
 *                                                                                             *
 * INPUT:   cell  -- The cell to coerce into an adjacent cell.                                 *
 *                                                                                             *
 *          dir   -- The direction to determine the adjacent cell.                             *
 *                                                                                             *
 * OUTPUT:  Returns with the cell value that represents the adjacent cell in the direction     *
 *          specified.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Cell Adjacent_Cell(Cell const & cell, FacingType dir)
{
	return(cell + AdjacentCell[(int)dir & 0x07]);
}


/***********************************************************************************************
 * Adjacent_Cell -- Calculate the adjacent cell in the direction specified.                    *
 *                                                                                             *
 *    This routine will take the specified cell and coerce it to refer to the immediately      *
 *    adjacent cell in the direction specified.                                                *
 *                                                                                             *
 * INPUT:   cell  -- The cell to coerce into an adjacent cell.                                 *
 *                                                                                             *
 *          dir   -- The direction to determine the adjacent cell.                             *
 *                                                                                             *
 * OUTPUT:  Returns with the cell value that represents the adjacent cell in the direction     *
 *          specified.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline Cell Adjacent_Cell(Cell const & cell, Dir256 dir)
{
	return(cell + AdjacentCell[Dir_Facing(dir)]);
}


inline int Distance(Cell const & cell1, Cell const & cell2)
{
	return((cell1 - cell2).Length());
}


inline int Distance(Coord const & coord1, Coord const & coord2)
{
	return((coord1 - coord2).Length());
}


inline DirType Random_Dir(int min, int max)
{
	union Ugh {
		unsigned int UInt;
		struct {
			short LoWord : 16;
			short HiWord : 16;
		};
		struct {
			unsigned int LoByte : 8;
			unsigned int HiByte : 8;
		};
		unsigned short Dir;
	};

	Ugh dir;

	dir.LoWord = 0;
	dir.HiByte = Scen->RandomNumber();

	DirType d;
	d.Raw = dir.UInt;
	return(d);
}
