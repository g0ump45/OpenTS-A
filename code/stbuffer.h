/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "rect.h"

class Surface;

struct SurfaceRegion {
	/*
	 * This is the offset from the object's draw position at which the drawn image belongs.
	 * An object that came out off the center of the drawing buffer still lands in the right
	 * place on screen because of it.
	 */
	Point2D Point;

	/*
	 * This is the rectangle within the drawing buffer that the image actually occupies. Only
	 * this much of the buffer is captured and cleared afterwards, so nothing is paid for the
	 * part of it the object never touched.
	 */
	Rect Bounds;
};

class StaticBufferClass
{
	public:
		StaticBufferClass(int size);
		~StaticBufferClass(void);

		struct Entry {
			/*
			 * These are the screen offsets remembered with the cached image, taken from the
			 * region it was captured out of. They are added to the object's draw position
			 * when the image is blitted back, so it lands where it was rendered.
			 */
			short X;
			short Y;

			/*
			 * These are the dimensions of the cached image, expressed in pixels. The
			 * compressed data holds exactly this many rows, each of which decompresses to
			 * this many pixels.
			 */
			unsigned short Width;
			unsigned short Height;

			/*
			 * Pointer to the run length compressed rows of the image, which sit in the
			 * buffer immediately behind this header.
			 */
			unsigned char * Data;
		};

		StaticBufferClass::Entry * Add(Surface & surface, SurfaceRegion const & region);
		StaticBufferClass::Entry * Add(Surface & surface, Rect const & cliprect, short x, short y);

		unsigned char * Reserve(int size)
		{
			unsigned char * new_cursor = Cursor + size;
			if (new_cursor <= Buffer + Size) {
				unsigned char * old_cursor = Cursor;
				Cursor = new_cursor;
				return(old_cursor);
			}
			return(NULL);
		}

		void Reset(void) { Cursor = Buffer; }

	private:
		/*
		 * This is the capacity of the buffer, expressed in bytes and fixed when it was
		 * created. A reservation that would run past it is refused rather than granted by
		 * growing the block.
		 */
		unsigned int Size;

		/*
		 * Pointer to the one block of memory that every cached entry is carved out of. It is
		 * allocated whole when the buffer is created, so no entry outlives it.
		 */
		unsigned char * Buffer;

		/*
		 * This is the point in the block that the next reservation will be carved from.
		 * Space is only ever handed out ahead of it and individual entries are never given
		 * back, so winding it to the start is what reclaims the buffer for reuse.
		 */
		unsigned char * Cursor;
};
