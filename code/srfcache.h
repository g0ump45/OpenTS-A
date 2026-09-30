/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "dict.h"
#include "surface.h"
#include "wstring.h"

struct SurfaceCacheEntry
{
	/*
	 * Pointer to the cached picture. The cache owns it and deletes it when the entry is
	 * replaced or the cache is emptied.
	 */
	Surface * surf;

	/*
	 * This is the 256 color palette the picture was loaded with, three bytes per color. It
	 * is only filled in for an 8 bit surface, since a 16 bit one has its palette already
	 * worked into the pixels.
	 */
	char palette[768];

	SurfaceCacheEntry(void) {
		surf = NULL;
	}
};

class SurfaceCacheClass : public Dictionary<Wstring, SurfaceCacheEntry>
{
	public:
		SurfaceCacheClass(void);
		~SurfaceCacheClass(void);

		bool CacheBMP(char const *name, void *bitmap, int bytes, int bpp=2);

		bool CachePCX(char const *name, int bpp=2, int red_channel=false);
		bool CachePalettedPCX(char const *name);

		Surface * GetSurface(char const * name, void * palette = NULL);

		bool Draw(Rect const & rect, Surface & tosurface, Surface & fromsurface, int x = 0, int y = 0);
		bool DrawTrans(Rect const & rect, Surface & tosurface, Surface & fromsurface, short trans);
		bool DrawNullsub(Rect const & rect, Surface & tosurface, Surface & fromsurface);
		bool DrawMasked(Rect const & rect, Surface & tosurface, Surface & fromsurface, Surface & masksurface, void * palette, bool center, int x_offset, int y_offset);
};

int SurfaceCacheConvertPixel(int red, int green, int blue);
void SurfaceCacheConvertPalette(unsigned char *pal);

extern SurfaceCacheClass SurfaceCache;
