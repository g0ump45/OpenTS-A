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

#include "point.h"
#include "sun.h"

class Coord;
class Cell;

Coord Coord_Scatter(Coord const & coord, int distance, bool lock=false);
Coord Adjacent_Coord_With_Height(Coord const & coord, FacingType dir);


/****************************************************************************
**	These are custom C&C specific types. The CELL is used for map coordinate
**	with cell resolution. The COORDINATE type is used for map coordinates that
**	have a lepton resolution. CELL is more efficient when indexing into the map
**	and when size is critical. COORDINATE is more efficient when dealing with
**	accuracy and object movement.
*/

typedef int LEPTON;

class Cell : public TPoint2D<short>
{
		typedef TPoint2D<short> BASECLASS;

	public:
		Cell(void) : BASECLASS() {}
		Cell(Coord const & cell);
		Cell(int x, int y) : BASECLASS(x, y) {}
		explicit Cell(TPoint2D<int> const & pt) : BASECLASS(pt.X, pt.Y) {}
		Cell(BASECLASS const & pt) : BASECLASS(pt) {};
		explicit Cell(int cellnum) : BASECLASS(cellnum % 128, cellnum / 128) {}

		Coord As_Coord(int z = 0) const;

		int As_Int(void) const { return((Y - (MAP_CELL_W * (X + Y)) - X) << 6); }
};


class Coord : public Point3D
{
		typedef TPoint3D<int> BASECLASS;

	public:
		Coord(void) : BASECLASS() {}
		Coord(Point2D const & pt, LEPTON z) {X=pt.X; Y=pt.Y; Z=z;}
		Coord(Cell const & cell, LEPTON z = 0);
		Coord(int x, int y, int z = 0) : BASECLASS(x, y, z) {}
		Coord(BASECLASS const & pt) : BASECLASS(pt) {};

		Cell As_Cell(void) const;

		int As_Int(void) { return((X / 10) + ((Y / 10) << 16)); }
};


inline Cell::Cell(Coord const & coord)
{
	*this = coord.As_Cell();
}


inline Coord Cell::As_Coord(int z) const
{
	Coord coord(X * CELL_LEPTON_W + CELL_LEPTON_W / 2, Y * CELL_LEPTON_H + CELL_LEPTON_H / 2, z);
	return(coord);
}


inline Coord::Coord(Cell const & cell, LEPTON z) :
	Point3D((cell.X * CELL_LEPTON_W) + (CELL_LEPTON_W / 2), (cell.Y * CELL_LEPTON_H) + (CELL_LEPTON_H / 2), z)
{

}


inline Cell Coord::As_Cell(void) const
{
	return(Cell(X / CELL_LEPTON_W, Y / CELL_LEPTON_H));
}


/*
 * These are types used by EventClass/TargetClass.
 */
struct xCell
{
	/*
	 * These are the column and row of the cell on the map. They mirror the like named
	 * members of Cell, which cannot serve here itself because a member of a union may not
	 * have a constructor.
	 */
	short X;
	short Y;

	xCell & operator = (Cell const & that)
	{
		X = that.X;
		Y = that.Y;
		return(*this);
	}
};


struct xCoord
{
	/*
	 * These are the horizontal and vertical position on the map, expressed in leptons. They
	 * mirror the like named members of Coord, but there is no Z here -- a position sent
	 * through an event keeps no height, and comes back out of one at ground level.
	 */
	LEPTON X;
	LEPTON Y;

	xCoord & operator = (Coord const & that)
	{
		X = that.X;
		Y = that.Y;
		return(*this);
	}
};
