/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "animfile.h"

#include "bsurface.h"
#include "palette.h"
#include "wwfile.h"

#include <cassert>

/// Size of a large page header: the page descriptor, a reserved word, and one size entry
/// per record.

#define LP_HEADER_SIZE(nRecords) ( (sizeof(LPDescriptor) + sizeof(unsigned short)) + (nRecords) * sizeof(unsigned short) )


/// <summary>
/// Constructs an empty animation.
/// No file is attached until Load is called.
/// </summary>
AnimFile::AnimFile(void) :
Animate(),
File(NULL),
Processed(false),
FileOpen(false),
Palette(),
SurfacePtr(NULL),
BufferPtr(NULL),
LastFrame(-1),
LastLargePage(-1)
{

}


/// <summary>
/// Destroys the animation and releases the file it was playing.
/// </summary>
AnimFile::~AnimFile(void)
{
	Reset();
}


/// <summary>
/// Determines how much of the file the header occupies.
/// This covers the header proper, the color cycling table, the palette and the large
/// page table -- everything, in other words, that precedes the first large page.
/// </summary>
/// <returns>Returns with the size of the file header in bytes.</returns>
int AnimFile::Get_Header_Size(void) const
{
	return(sizeof(Header) + sizeof(Cycles) + sizeof(FilePalette) + sizeof(LPFTable));
}


/// <summary>
/// Attaches an animation file and prepares it for playback.
/// The file is opened if the caller has not opened it already, and its header is
/// processed. A file that turns out not to be a playable animation is released again.
/// </summary>
/// <returns>bool; Was the animation loaded and found to be valid?</returns>
/// <remarks>The file object is borrowed rather than copied. It must survive for as long
/// as frames are being fetched from it.</remarks>
bool AnimFile::Load(FileClass *file)
{
	assert(file != NULL);

	File = file;
	if (File != NULL) {
		if (!File->Is_Open()) {
			File->Open();
			FileOpen = true;
		}
		return(Process());
	}

	return(false);
}


/// <summary>
/// Releases the animation and everything it allocated.
/// The file is closed if this object was the one that opened it, and the frame surface
/// and page buffer are freed. The object is left ready to load another animation.
/// </summary>
void AnimFile::Reset(void)
{
	if (FileOpen) {
		File->Close();
		FileOpen = false;
	}
	File = NULL;
	if (SurfacePtr != NULL) {
		delete SurfacePtr;
		SurfacePtr = NULL;
	}

	if (BufferPtr != NULL) {
		delete [] (unsigned char *)BufferPtr;
		BufferPtr = NULL;
	}

	Processed = false;
}


/// <summary>
/// Reads the animation header and prepares for playback.
/// This routine will pull in the header, the color cycling table, the palette and the
/// large page table, then allocate the frame surface and the working page buffer. A
/// file that fails validation is released again rather than played.
/// </summary>
/// <returns>bool; Is the animation ready to have frames fetched from it?</returns>
bool AnimFile::Process(void)
{
	if (!Processed && File != NULL) {
		Processed = true;

		memset(&Header, 0, sizeof(Header));
		File->Read(&Header, sizeof(Header));

		memset(Cycles, 0, sizeof(Cycles));
		File->Read(Cycles, sizeof(Cycles));

		File->Seek(0, SEEK_CUR);
		File->Read(FilePalette, sizeof(FilePalette));
		for (int i = 0; i < PaletteClass::COLOR_COUNT; i++) {
			Palette[i] = RGBClass(FilePalette[i][2], FilePalette[i][1], FilePalette[i][0]);
		}

		memset(&LPFTable, 0, sizeof(LPFTable));
		File->Read(&LPFTable, sizeof(LPFTable));

		if (!Is_Valid()) {
			Reset();
			return(false);
		}

		SurfacePtr = new BSurface(Header.width, Header.height, 1);
		assert(SurfacePtr != NULL);

		BufferPtr = new unsigned char[MAX_LARGE_PAGE_SIZE];
		assert(BufferPtr != NULL);

		memset(BufferPtr, 0, MAX_LARGE_PAGE_SIZE);
	}

	return(Processed);
}


/// <summary>
/// Is this a well formed animation file?
/// The header is checked against the format's limits and against the one bitmap layout
/// this player understands. Process uses this to reject a file before it commits to
/// allocating buffers for it.
/// </summary>
/// <returns>bool; Does the header describe an animation this class can play?</returns>
bool AnimFile::Is_Valid(void) const
{
	if (Header.id != LARGE_PAGE_FILE_ID || Header.contentType != ANIM_CONTENTS_ID) {
		return(false);
	}

	if (Header.maxLps != MAX_LARGE_PAGE || Header.nRecords > MAX_RECORDS) {
		return(false);
	}

	if (Header.maxRecsPerLp > MAX_RECORDS_PER_LP) {
		return(false);
	}

	if (Header.lpfTableOffset != LPF_TABLE_OFFSET	||
		Header.width != 320 || Header.height != 200	||
		Header.highestBBComp > BBC_RUN_SKIP_DUMP 	||
		Header.bitmaptype != 1 || Header.otherRecsPerFrm != 0 || Header.pixelType != 0
		) {
		return(false);
	}

	for (int i = 0; i < Header.nLps; i++) {

		if (LPFTable[i].nRecords > MAX_RECORDS_PER_LP) {
			return(false);
		}
	}

	return(true);
}


/// <summary>
/// Fetches the number of frames in the animation.
/// A file may carry an extra last-to-first delta record so that it can loop seamlessly.
/// That record is not a frame and is not counted here.
/// </summary>
int AnimFile::Get_Frame_Count(void) const
{
	int num = Header.FrameCount;

	if (Header.hasLastDelta) {
		num--;
	}

	return(num);
}


/// <summary>
/// Fetches the width of the animation in pixels.
/// </summary>
int AnimFile::Get_Width(void) const
{
	return(Header.width);
}


/// <summary>
/// Fetches the height of the animation in pixels.
/// </summary>
int AnimFile::Get_Height(void) const
{
	return(Header.height);
}


/// <summary>
/// Fetches the surface holding a particular animation frame.
/// The frames are stored as deltas against the frame before them, so this routine
/// composes every record lying between the frame last drawn and the one asked for,
/// starting over from a cleared surface when it cannot get there by going forward.
/// </summary>
/// <returns>Returns with a pointer to the frame surface, which the animation owns and
/// reuses. Otherwise, NULL is returned.</returns>
Surface *AnimFile::Load_Frame(int frame)
{
	assert(frame <= int(Header.FrameCount));

	void *dest;
	int dlength;
	void *source;

	if (!Processed) {
		return(NULL);
	}

	if (LastFrame > frame) {
		if (Header.hasLastDelta && Header.lastDeltaValid) {

			if (LastFrame != (int)Header.nRecords || frame != 0) {
				SurfacePtr->Fill(0);
				LastFrame = -1;
			}

		} else {
			SurfacePtr->Fill(0);
			LastFrame = -1;
		}
	}

	if (LastFrame != frame) {

		dest = SurfacePtr->Lock();

		dlength = SurfacePtr->Get_Width() * SurfacePtr->Get_Height() * SurfacePtr->Bytes_Per_Pixel();

		while (LastFrame != frame) {

			LastFrame++;

			source = Get_Large_Page_Pointer_For_Record(LastFrame);

			if (source != NULL) {
				Decode_Frame(source, Get_Large_Page_Size_For_Record(LastFrame), dest, dlength);
			}

			if (LastFrame > int(Header.FrameCount)) {
				LastFrame = 0;
			}
		}

		SurfacePtr->Unlock();
	}

	return(SurfacePtr);
}


/// <summary>
/// Determines how many bytes a large page occupies in the file.
/// The page's own header and record size table are counted along with its contents, so
/// the answer is how much must be read to bring the whole page in.
/// </summary>
/// <returns>Returns with the size of the large page in bytes.</returns>
int AnimFile::Large_Page_Size_In_File(int nLp) const
{
	return(LP_HEADER_SIZE(LPFTable[nLp].nRecords) + LPFTable[nLp].nBytes);
}


/// <summary>
/// Loads a large page into the working buffer.
/// A page that is already resident is left alone, so asking for record after record out
/// of the same page costs nothing beyond the first read.
/// </summary>
/// <returns>bool; Is the requested page resident in the buffer?</returns>
bool AnimFile::Load_Large_Page(int nLp)
{
	if (Processed) {
		if (LastLargePage != nLp) {
			LastLargePage = nLp;

			File->Seek(Get_Header_Size() + (MAX_LARGE_PAGE_SIZE * nLp), SEEK_SET);

			if (File->Read(BufferPtr, Large_Page_Size_In_File(nLp)) == Large_Page_Size_In_File(nLp)) {
				return(true);
			}

		} else {
			return(true);
		}
	}
	return(false);
}


/// <summary>
/// Finds which large page holds an animation record.
/// Records are grouped into large pages, and this routine consults the page table so
/// that a record can be located without seeking through the file to find it.
/// </summary>
/// <returns>Returns with the large page number, or -1 if no page claims the record.</returns>
int AnimFile::Find_Large_Page_For_Record(int nRecord) const
{
	if (nRecord < (int)Header.FrameCount) {

		for (int nLp = 0; nLp < Header.nLps; nLp++) {

			const LPDescriptor *desc = &LPFTable[nLp];

			if (desc->baseRecord <= nRecord &&
				desc->baseRecord + desc->nRecords > nRecord) {
				return(nLp);
			}
		}
	}

	return(-1);
}

/// <summary>
/// Fetches a pointer to an animation record's data.
/// The large page holding the record is brought into the working buffer if it is not
/// already resident, and the record is then located within it.
/// </summary>
/// <returns>Returns with a pointer to the record's data. Otherwise, NULL is
/// returned.</returns>
/// <remarks>The pointer aims into the shared page buffer, so it stays valid only until a
/// record from another large page is requested.</remarks>
void *AnimFile::Get_Large_Page_Pointer_For_Record(int nRecord)
{

	int nLp = Find_Large_Page_For_Record(nRecord);

	if (nLp != -1) {
		bool ok = Load_Large_Page(nLp);

#ifdef _DEBUG
		assert(ok);
#endif
		int offset = LP_HEADER_SIZE(LPFTable[nLp].nRecords);
		unsigned short *sizes = ((LPStruct *)BufferPtr)->RecordSizes;
		nRecord -= LPFTable[nLp].baseRecord;
		int length = 0;
		while (nRecord > 0) {
			length = sizes[0];
			sizes++;
			offset += length;
			nRecord--;
		}
		assert(offset < MAX_LARGE_PAGE_SIZE);

		unsigned char *ptr = (unsigned char *)BufferPtr + offset;

		assert(length == 0 || ptr[0] == 'B'); /// IDNum is always 66
		assert(length == 0 || ptr[1] == 0); /// Flags needs to be 0

		return((void *)(ptr + sizeof(ptr[0]) + sizeof(ptr[1])));
	}
	return(NULL);
}


/// <summary>
/// Fetches the data size of an animation record.
/// The large page holding the record is brought in if it is not already resident. The
/// size excludes the record's own header, so it pairs with the pointer that
/// Get_Large_Page_Pointer_For_Record hands back.
/// </summary>
/// <returns>Returns with the size of the record in bytes, or zero if there is no such
/// record.</returns>
int AnimFile::Get_Large_Page_Size_For_Record(int nRecord)
{
	int size = 0;
	int nLp = Find_Large_Page_For_Record(nRecord);

	if (nLp != -1) {

		bool ok = Load_Large_Page(nLp);

		assert(ok);

		unsigned short *sizes = ((LPStruct *)BufferPtr)->RecordSizes;
		nRecord -= LPFTable[nLp].baseRecord;
		while (nRecord >= 0) {
			size = sizes[0];
			sizes++;
			if (size >= sizeof(unsigned short)) {
				size -= sizeof(unsigned short);
			}
			nRecord--;
		}
	}

	return(size);
}


/// <summary>
/// Decodes one animation record into the destination bitmap.
/// This is the low level decompressor that Load_Frame uses to lay each record over the
/// working surface. Only uncompressed and Run-Skip-Dump bodies are understood; any
/// other compression is refused rather than guessed at.
/// </summary>
/// <param name="source">Pointer to the record data, which begins with its body type.</param>
/// <param name="nBytes">Length of the record data in bytes.</param>
/// <param name="dest">Pointer to the bitmap to decode into.</param>
/// <param name="dlength">Size of the destination bitmap in bytes.</param>
/// <returns>bool; Was the record decoded?</returns>
bool AnimFile::Decode_Frame(void *source, int nBytes, void *dest, int dlength)
{
	assert(source != NULL);
	assert(dest != NULL);
	assert(dlength > 0);

	int bodyType;
	unsigned char *dst;
	bool decoded;

	if (nBytes == 0) {
		return(true);
	}

	unsigned char *src;
	signed char cnt;
	int wordCnt;
	int pixel;

	bodyType = *(short *)source;
	nBytes -= sizeof(short);
	source = (unsigned char *)source + sizeof(short);
	dst = (unsigned char *)dest;

	if (nBytes == 0) {
		return(true); /// empty delta == no change
	}

	decoded = true;

	enum {
		BMBODY_UNCOMPRESSED	= 0,
		BMBODY_RUNSKIPDUMP = 1,
		BMBODY_STOP_CODE_LEN = 3,

		BBSTOP0	= 0x80,
		BBSTOP1 = 0,
		BBSTOP2	= 0,
	};

	switch (bodyType) {

		case BMBODY_UNCOMPRESSED: {
			if (nBytes != dlength) {
				/// dest buffer is too small
				decoded = false;
			} else {
				memcpy(dst, source, nBytes);
			}
			break;
		}

		case BMBODY_RUNSKIPDUMP: {

			src = (unsigned char *)source + nBytes - BMBODY_STOP_CODE_LEN;

			/// stop code should consist of a long operation with count 0
			if (nBytes < BMBODY_STOP_CODE_LEN || src[0] != BBSTOP0 || src[1] != BBSTOP1 || src[2] != BBSTOP2) {
				decoded = false;
				/// stop code is missing
				break;
			}

			src = (unsigned char *)source;

			{
			next_op:
				cnt = *src++;

				if (cnt > 0) {
					goto short_dump;
				}

				if (cnt == 0) {
					goto short_run;
				}

				cnt -= (signed char)0x80;

				if (cnt == 0) {
					goto long_op;
				}

			/// short_skip:
				dst += cnt;
				goto next_op;

			short_dump:
				memcpy(dst, src, cnt);
				dst += cnt;
				src += cnt;
				goto next_op;

			short_run:
				wordCnt = *(unsigned char *)src;
				src += sizeof(unsigned char);
				pixel = *src;
				src += sizeof(unsigned char);
				memset(dst, pixel, wordCnt);
				dst += wordCnt;
				goto next_op;

			long_op:

				wordCnt = *(unsigned short *)src;
				src += sizeof(unsigned short);

				if ((signed short)wordCnt <= 0) {
					goto not_long_skip;
				}

			/// long_skip:
				dst += wordCnt;
				goto next_op;

			not_long_skip:

				if (wordCnt == 0) {
					goto stop;
				}

				wordCnt -= 0x8000;

				if (wordCnt >= 0x4000) {
					goto long_run;
				}

			/// long_dump:
				memcpy(dst, src, wordCnt);
				dst += wordCnt;
				src += wordCnt;
				goto next_op;

			long_run:
				wordCnt -= 0x4000;
				pixel = *src;
				src += sizeof(unsigned char);
				memset(dst, pixel, wordCnt);
				dst += wordCnt;
				goto next_op;

			stop:
			;

			}
			break;
		}

		/// unsupported compression
		default:
			decoded = false;
			break;
	}

	return(decoded);
}
