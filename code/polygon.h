/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "point.h"

/*
 * Contains a polygon defined as edges.
 */
struct PolygonShapeStruct
{
	/*
	 * This is the number of vertices in the outline. A shape with none rasterizes to nothing.
	 */
	int Count;

	/*
	 * This points to the vertices of the outline, in order around a closed loop -- the last
	 * one joins back to the first. The buffer belongs to whoever built the shape.
	 */
	Point2D * Vertices;

	PolygonShapeStruct(void) :
		Count(0),
		Vertices(NULL) {}

	enum {
		END_LEFT,
		END_MIDDLE,
		END_RIGHT,
		START_RIGHT,
		START_MIDDLE,
		START_LEFT
	};

};


/*
 * Contains a rasterized polygon as a set of points.
 */
struct PolygonRasterStruct
{
	/*
	 * This is the number of scanlines the polygon covers, and so the number of entries in
	 * the point list.
	 */
	int Count;

	/*
	 * This is the Y coordinate of the first scanline in the point list. Each entry that
	 * follows describes the scanline one row below the one before it.
	 */
	int BaseY;

	/*
	 * This points to the span list, one entry per scanline, holding the left edge of the
	 * polygon's interior in X and the right edge in Y. Rasterize_Polygon allocates the
	 * buffer if it finds none here, and it then belongs to whoever asked for the raster.
	 */
	Point2D * Points;

	PolygonRasterStruct(void) :
		Count(0),
		BaseY(0),
		Points(NULL) {}

};


void Rasterize_Polygon(const PolygonShapeStruct & shape, PolygonRasterStruct & raster);
void Rasterize_Line_Span(int x0, int y0, int x1, int y1, int axis, int skip, Point2D *&points);
