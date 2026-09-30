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
 *                     $Archive:: /G/wwlib/bsurface.h                                         $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 11:59a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "buff.h"
#include "xsurface.h"

/*
**	This class handles a simple surface that exists in system RAM.
*/
class BSurface : public XSurface
{
		typedef XSurface BASECLASS;

	friend class DisplayClass;
	public:
		BSurface(int width, int height, int bbp, void * buffer=NULL) :
			BASECLASS(width, height),
			BBP(bbp),
			Buff(buffer, width * height * bbp)
		{
		}

		/*
		**	Gets and frees a direct pointer to the buffer.
		*/
		virtual void * Lock(Point2D point = Point2D(0, 0)) const override
		{
			BASECLASS::Lock();
			return(((char*)Buff.Get_Buffer()) + point.Y * Stride() + point.X * Bytes_Per_Pixel());
		}

		/*
		**	Queries information about the surface.
		*/
		virtual int Bytes_Per_Pixel(void) const override {return(BBP);}
		virtual int Stride(void) const override {return(Get_Width() * BBP);}

	protected:

		/*
		**	Recorded bytes per pixel (used when determining pixel positions).
		*/
		int BBP;

		/*
		**	Tracks the buffer that this surface represents.
		*/
		Buffer Buff;
};
