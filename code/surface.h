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
 *                     $Archive:: /Commando/Code/wwlib/surface.h                              $*
 *                                                                                             *
 *                      $Author:: Byon_g                                                      $*
 *                                                                                             *
 *                     $Modtime:: 11/28/00 2:40p                                              $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "buff.h"
#include "rect.h"
#include "rgb.h"

/*
**	This is an abstract interface class for a graphic surface. Graphic operations will use this
**	interface to perform their function. The philosphy behind this interface is that it represents
**	a small but useful set of functions. Emphasis is placed on supporting those functions which are
**	likely to have hardware assist.
*/
class Surface
{
	public:
		/// Surface(void) : Width(0), Height(0) {}
		Surface(int width, int height) : Width(width), Height(height) {}
		virtual ~Surface(void) {};

		/*
		**	Copies regions from one surface to another.
		*/
		virtual bool Blit_From(Rect const & dcliprect, Rect const & destrect, Surface const & source, Rect const & scliprect, Rect const & sourcerect, bool trans=false, bool unknown=true) = 0;
		virtual bool Blit_From(Rect const & destrect, Surface const & source, Rect const & sourcerect, bool trans=false, bool unknown=true) = 0;
		virtual bool Blit_From(Surface const & source, bool trans=false, bool unknown=true) = 0;

		/*
		**	Fills a region with a constant color.
		*/
		virtual bool Fill_Rect(Rect const & rect, int color) = 0;
		virtual bool Fill_Rect(Rect const & cliprect, Rect const & fillrect, int color) = 0;
		virtual bool Fill(int color) = 0;
		virtual bool Fill_Rect_Trans(Rect const & rect, RGBClass const & color, unsigned int opacity) = 0;

		virtual bool Draw_Ellipse(Point2D point, int radius_x, int radius_y, Rect clip, int color) = 0;

		/*
		**	Fetches and stores a pixel to the display (pixel is in surface format).
		*/
		virtual bool Put_Pixel(Point2D const & point, int color) = 0;
		virtual int Get_Pixel(Point2D const & point) const = 0;

		/*
		**	Draws lines onto the surface.
		*/
		virtual bool Draw_Line(Point2D const & startpoint, Point2D const & endpoint, int color) = 0;
		virtual bool Draw_Line(Rect const & cliprect, Point2D const & startpoint, Point2D const & endpoint, int color) = 0;
		virtual bool Draw_Depth_Shaded_Line(Rect const & cliprect, Point2D const & startpoint, Point2D const & endpoint, unsigned color, int start_depth, int end_depth, bool write_depth = false) = 0;
		virtual bool Draw_Depth_Glow_Line(Rect const & cliprect, Point2D const & startpoint, Point2D const & endpoint, int glow_strength, int start_depth, int end_depth, bool write_depth = false) = 0;
		virtual bool Draw_Depth_Antialiased_Line(Rect const & cliprect, Point2D const & startpoint, Point2D const & endpoint, RGBClass & color, int start_depth, int end_depth, bool write_depth, bool blend_red, bool blend_green, bool blend_blue, float intensity) = 0;

		virtual bool Plot_Line(Rect const &area, Point2D &start, Point2D &end, void(*drawer_callback)(Point2D const &)) = 0;

		virtual int Draw_Dashed_Line(Point2D const &start, Point2D const &end, unsigned color, bool pattern[], int offset) = 0;
		virtual int Draw_Masked_Dashed_Line(Point2D const & startpoint, Point2D const & endpoint, unsigned color, bool pattern[], int offset, bool draw_on_zero_alpha) = 0;
		virtual bool Draw_Masked_Line(Point2D const & startpoint, Point2D const & endpoint, unsigned color, bool draw_on_zero_alpha) = 0;

		/*
		**	Draws rectangle onto the surface.
		*/
		virtual bool Draw_Rect(Rect const & rect, int color) = 0;
		virtual bool Draw_Rect(Rect const & cliprect, Rect const & rect, int color) = 0;

		/*
		**	Gets and frees a direct pointer to the video memory.
		*/
		virtual void * Lock(Point2D point = Point2D(0, 0)) const = 0;
		virtual bool Unlock(void) const = 0;
		virtual bool Can_Lock(int x = 0, int y = 0) const {return(true);}
		/// Is the surface ready to draw to? The mouse code consults this before rendering.
		virtual bool entry_64(Point2D pt = Point2D(0, 0)) const {return(true);}
		virtual bool Is_Locked(void) const = 0;

		/*
		**	Queries information about the surface.
		*/
		virtual int Bytes_Per_Pixel(void) const = 0;
		virtual int Stride(void) const = 0;
		virtual Rect Get_Rect(void) const {return(Rect(0, 0, Width, Height));}
		virtual int Get_Width(void) const {return(Width);}
		virtual int Get_Height(void) const {return(Height);}

		/*
		**	Hack function to serve the purpose that RTTI was invented for, but since
		**	the Watcom compiler doesn't support RTTI, we must resort to using this
		**	alternative.
		*/
		virtual bool Is_GDI_Backed(void) const {return(false);}

	protected:

		/*
		**	Records logical pixel dimensions of the surface.
		*/
		int Width;
		int Height;
};
