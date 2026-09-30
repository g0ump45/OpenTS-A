/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#define PIXEL_RGB555(r,g,b) 		( (((r) & 0xF8) << 7) | (((g) & 0xF8) << 2) | (((b) & 0xF8) >> 3) )

/// <summary>
/// Clamps the color components of 24 bit pixel data.
/// This routine drops the low bits of every color component so that a later
/// conversion to 15 bit color costs the data nothing further.
/// </summary>
/// <param name="buf">The pixel data to clamp, modified in place.</param>
/// <param name="len">The number of pixels to clamp.</param>
void rgb24_clamp(unsigned char *buf, int len)
{
	for (unsigned i = 0; i < 3 * (unsigned)len; i++) {
		*buf &= 0xF8;
		buf++;
	}
}


/// <summary>
/// Clamps the color components of 32 bit pixel data.
/// This routine drops the low bits of every color component so that a later
/// conversion to 15 bit color costs the data nothing further. The fourth byte of each
/// pixel is stepped over rather than clamped.
/// </summary>
/// <param name="buf">The pixel data to clamp, modified in place.</param>
/// <param name="len">The number of pixels to clamp.</param>
void rgb32_to_rgb24_clamped(unsigned char *buf, int len)
{
	for (int i = 0; i < len; i++) {
		*buf &= 0xF8;
		buf++;

		*buf &= 0xF8;
		buf++;

		*buf &= 0xF8;
		buf++;

		/// Step over the fourth byte.
		buf++;
	}
}


/// <summary>
/// Converts 24 bit pixel data into 15 bit color.
/// The low bits of each color component are dropped so that the three components fit
/// into a single pixel. The buffer is converted in place, so it ends up holding two
/// bytes per pixel instead of three.
/// </summary>
/// <param name="buf">The pixel data to convert, packed down in place.</param>
/// <param name="count">The number of images the buffer holds.</param>
void rgb24_to_rgb555(unsigned char *buf, int rows, int columns, int count)
{
	unsigned len = rows * columns * count;

	unsigned char *src = buf;
	for (unsigned i = 0; i < len; i++) {
		*(unsigned short *)buf = PIXEL_RGB555(src[0], src[1], src[2]);
		buf += 2;
		src += 3;
	}
}


/// <summary>
/// Converts 24 bit pixel data into 15 bit color with an alpha bit.
/// Each source pixel is preceded by a marker byte that decides whether the alpha bit
/// should be raised on the converted pixel. The buffer is converted in place, so it
/// ends up holding two bytes per pixel instead of four.
/// </summary>
/// <param name="buf">The pixel data to convert, packed down in place.</param>
/// <param name="count">The number of images the buffer holds.</param>
/// <param name="max_opacity">The opacity level. Anything other than zero keeps the alpha
/// bit from ever being raised.</param>
void rgb24_to_rgb1555(unsigned char *buf, int rows, int columns, int count, int max_opacity)
{
	unsigned len = rows * columns * count;

	unsigned char *src = buf;
	unsigned short *dst = (unsigned short *)src;
	for (unsigned i = 0; i < len; i++) {

		unsigned short accum = 0;
		if (*src == 0 && max_opacity == 0) {
			accum = 0x8000; /// sets alpha to 1
		}
		src++;

		*dst = PIXEL_RGB555(src[0],src[1],src[2]);
		*dst |= accum;
		src += 3;
		dst++;
	}
}


/// <summary>
/// Converts 32 bit pixel data into 24 bit pixel data.
/// The leading byte of each pixel is thrown away and the color components are packed
/// down in place, so the buffer shrinks to three quarters of its original length.
/// </summary>
/// <param name="buf">The pixel data to convert, packed down in place.</param>
/// <param name="count">The number of images the buffer holds.</param>
void rgb32_to_rgb24(unsigned char *buf, int rows, int columns, int count)
{
	unsigned len = rows * columns * count;

	unsigned char *src = buf;
	for (unsigned i = 0; i < len; i++) {
		src++;

		*buf= *src;
		src++;
		buf++;

		*buf= *src;
		src++;
		buf++;

		*buf= *src;
		src++;
		buf++;
	}
}
