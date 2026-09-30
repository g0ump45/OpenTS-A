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

/* $Header: /CounterStrike/WRITEPCX.CPP 1     3/03/97 10:26a Joe_bostic $ */
/***************************************************************************
 **   C O N F I D E N T I A L --- W E S T W O O D   A S S O C I A T E S   **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : iff                                      *
 *                                                                         *
 *                    File Name : WRITEPCX.CPP                             *
 *                                                                         *
 *                   Programmer : Julio R. Jerez                           *
 *                                                                         *
 *                   Start Date : May 2, 1995                              *
 *                                                                         *
 *                  Last Update : May 2, 1995   [JRJ]                      *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * int Save_PCX_File (char* name, GraphicViewPortClass& pic, char* palette)*
 *= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =*/

#include "always.h"

#include "dsurface.h"
#include "pcx.h"


static void Write_Pcx_ScanLine(FileClass & file, int scansize, char * ptr);
static int Write_Pcx_ScanLine_Buf(int scansize, char * ptr, char * file_ptr);


/***************************************************************************
 * WRITE_PCX_FILE -- Write the data in ViewPort to a pcx file              *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * INPUT:  name is a NULL terminated string of the format [xxxx.pcx]       *
 *           pic    is a pointer to a GraphicViewPortClass or to a         *
 *                GraphicBufferClass holding the picture.                  *
 *        palette is a pointer the the memory block holding the color      *
 *              palette of the picture.                                    *
 *                                                                         *
 * OUTPUT: FALSE  if the function fails zero otherwise                     *
 *                                                                         *
 * WARNINGS:                                                               *
 *                                                                         *
 * HISTORY:                                                                *
 *   05/04/1995 JRJ : Created.                                             *
 *   08/01/1995 SKB : Copy the palette so it is not modified.              *
 *   06/03/1996 JLB : Converted to C++ and file class I/O.                 *
 *=========================================================================*/

static const unsigned char rle_code = 0xC0;                         // Run code.
static const unsigned char rle_max_run = 0x2F;                      // Maximum run allowed.
static const unsigned char rle_full_run = (rle_max_run|rle_code);   // Full character run.


/***********************************************************************************************
 * Write_PCX_File -- Write a PCX file from specified buffer.                                   *
 *                                                                                             *
 *    This routine will take the specified buffer and write out the data as a PCX file to the  *
 *    the file object specified.                                                               *
 *                                                                                             *
 * INPUT:   file     -- Reference to the file object to write the buffer as a PCX file.        *
 *                                                                                             *
 *          pic      -- Reference to a graphic buffer that contains the data to be written.    *
 *                                                                                             *
 *          palette  -- Reference to the palette to be attached to the PCX file as well.       *
 *                                                                                             *
 * OUTPUT:  bool; Was there an error?                                                          *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool Write_PCX_File(FileClass & file, Surface & pic, PaletteClass * palette)
{
	unsigned char palcopy[256 * sizeof(RGB)];
	char	* ptr;
	//RGB	* pal;
	PCX_HEADER header = {
		10,
		5,
		1,
		8,
		0,
		0,
		(unsigned short)(pic.Get_Width()-1),
		(unsigned short)(pic.Get_Height()-1),
		(short)(pic.Get_Width()),
		(short)(pic.Get_Height()),
		{{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},
		0,
		(unsigned char)(pic.Bytes_Per_Pixel() == 2 ? 3 : 1),
		(unsigned short)pic.Get_Width(),
		1,
		(short)(pic.Get_Width()),
		(short)(pic.Get_Height()),
		{0}
	};

	/*
	**	Open the output file and write out the header information. If the file
	**	is already open, then just presume that it is positioned correctly and is
	**	open for write.
	*/
	bool open = false;
	if (!file.Is_Open()) {
		file.Open(FileClass::WRITE);
		open = true;
	}
	file.Write(&header, sizeof(header));

	if (pic.Bytes_Per_Pixel() == 2) {

		unsigned char *line1 = new unsigned char[pic.Get_Width()];
		unsigned char *line2 = new unsigned char[pic.Get_Width()];
		unsigned char *line3 = new unsigned char[pic.Get_Width()];
		unsigned char *file_ptr = new unsigned char[pic.Get_Width() * ((4 + 1) * 2)];

		for (int line = 0; line < header.height + 1; line++) {
			unsigned short * buffer = (unsigned short *)pic.Lock(Point2D(0, line));
			if (buffer == NULL) {
				return(1);
			}
			for (int j = 0; j < pic.Get_Width(); j++) {
				RGBClass color = DSurface::Deconstruct_Hicolor_Pixel(*buffer++);
				line1[j] = color.Get_Red();
				line2[j] = color.Get_Green();
				line3[j] = color.Get_Blue();
			}
			pic.Unlock();
			int size = 0;
			size += Write_Pcx_ScanLine_Buf(pic.Get_Width(),(char *)line1, (char *)file_ptr + size);
			size += Write_Pcx_ScanLine_Buf(pic.Get_Width(),(char *)line2, (char *)file_ptr + size);
			size += Write_Pcx_ScanLine_Buf(pic.Get_Width(),(char *)line3, (char *)file_ptr + size);

			file.Write(file_ptr, size);
		}

		delete [] line1;
		delete [] line2;
		delete [] line3;
		delete [] file_ptr;

	} else {

		/*
		**	Write out the picture, line by line.
		*/
		for (int line = 0; line < header.height + 1; line++) {
			ptr = (char *)pic.Lock(Point2D(0, line));
			Write_Pcx_ScanLine(file, header.byte_per_line, ptr);
			pic.Unlock();
		}
	}

	/*
	**	Special marker for end of RLE data.
	*/
	unsigned char ender = 0x0C;
	file.Write(&ender, sizeof(ender));

	if (pic.Bytes_Per_Pixel() == 1) {
		/*
		**	Convert the palette from 6 bit to 8 bit format.
		*/
		memmove(palcopy, palette, sizeof(PaletteClass));
		#if 0
		pal = (RGB *)palcopy ;
		for (int palindex = 0; palindex < 256; palindex++) {
			pal->red = (unsigned char)((pal->red<<2)); // | (pal->red>>6));
			pal->green = (unsigned char)((pal->green<<2)); // | (pal->green>>6));
			pal->blue = (unsigned char)((pal->blue<<2)); // | (pal->blue>>6));
			pal++;
		}
		#endif

		/*
		**	Write the palette out.
		*/
		file.Write(palcopy, sizeof(palcopy));
	}

	/*
	**	Close the file (if necessary) and exit with no error flag.
	*/
	if (open) {
		file.Close();
	}
	return(false);
}


/***********************************************************************************************
 * Write_Pcx_ScanLine -- Writes a PCX scanline.                                                *
 *                                                                                             *
 *    Writes out a PCX scanline using RLE compression.                                         *
 *                                                                                             *
 * INPUT:   file     -- Reference to the file to write the scan line to.                       *
 *                                                                                             *
 *          scansize -- The number of bytes to compress (write).                               *
 *                                                                                             *
 *          ptr      -- Pointer to the data to compress (write).                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   05/04/1995 JRJ : Created.                                                                 *
 *   06/03/1996 JLB : Converted to C++ and file class I/O.                                     *
 *=============================================================================================*/
static void Write_Pcx_ScanLine(FileClass & file, int scansize, char * ptr)
{
	unsigned char last = *ptr;
	unsigned char rle=1;
	unsigned char c;
	for (int i = 1; i < scansize; i++) {
		unsigned char color = (unsigned char)(0xff & * ++ptr);
		if (color == last) {
			rle++;
			if (rle == rle_max_run) {
				file.Write(&rle_full_run, sizeof(rle_full_run));
				file.Write(&color, sizeof(color));
				rle = 0 ;
			}
		} else {
			if (rle) {
				if (rle == 1 && (rle_code != (rle_code & last))) {
					file.Write(&last, sizeof(last));
				} else {
					c = (unsigned char)(rle | rle_code);
					file.Write(&c, sizeof(c));
					file.Write(&last, sizeof(last));
				}
			}
			last = color ;
			rle = 1 ;
		}
	}
	if (rle) {
		if (rle == 1 && ( rle_code != (rle_code & last))) {
			file.Write(&last, sizeof(last));
		} else {
			c = (unsigned char)(rle | rle_code);
			file.Write(&c, sizeof(c));
			file.Write(&last, sizeof(last));
		}
	}
}


/// <summary>
/// Compresses a PCX scanline into a memory buffer.
/// This routine is the buffered counterpart to Write_Pcx_ScanLine. It is used when
/// writing a hicolor picture, where the three color planes of a line are packed into
/// one buffer and then written to the file as a single block.
/// </summary>
/// <param name="scansize">The number of bytes to compress.</param>
/// <param name="ptr">Pointer to the data to compress.</param>
/// <param name="file_ptr">Buffer to place the compressed scanline into.</param>
/// <returns>Returns with the number of bytes placed into the destination buffer.</returns>
/// <remarks>Be sure that the destination buffer is big enough to hold the worst case
/// expansion of the scanline.</remarks>
#define WRITE_CHAR(x) {	file_ptr [size++] = x ; }
static int Write_Pcx_ScanLine_Buf( int scansize, char * ptr, char * file_ptr )
{
	unsigned char last = *ptr;
	unsigned char rle=1;
	unsigned char c;
	int size = 0;

	for (int i = 1; i < scansize; i++) {
		unsigned char color = (unsigned char)(0xff & * ++ptr);
		if (color == last) {
			rle++;
			if (rle == rle_max_run) {
				WRITE_CHAR((*(unsigned char *)&rle_full_run));
				WRITE_CHAR(color);
				rle = 0 ;
			}
		} else {
			if (rle) {
				if (rle == 1 && (rle_code != (rle_code & last))) {
					WRITE_CHAR(last);
				} else {
					c = (unsigned char)(rle | rle_code);
					WRITE_CHAR(c);
					WRITE_CHAR(last);
				}
			}
			last = color ;
			rle = 1 ;
		}
	}
	if (rle) {
		if (rle == 1 && ( rle_code != (rle_code & last))) {
			WRITE_CHAR(last);
		} else {
			c = (unsigned char)(rle | rle_code);
			WRITE_CHAR(c);
			WRITE_CHAR(last);
		}
	}

	return(size);
}
