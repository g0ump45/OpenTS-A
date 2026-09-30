/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

// Holds LCW_Comp to the destination size LCW_Comp_Bound promises, and holds LCWPipe and
// LCWStraw to their buffers on both sides of a block stream. Those classes carry the map
// overlay packs, so a block that expands beyond a block, or a header claiming one, must stop
// at the buffer rather than run past it. Needs no game data.

#include <cstdio>
#include <cstring>

#include "lcw.h"
#include "lcwpipe.h"
#include "lcwstraw.h"
#include "xpipe.h"
#include "xstraw.h"

namespace {

int const BLOCK = 1024 * 8;
int const SRCMAX = BLOCK * 4;
int const DSTMAX = SRCMAX * 2;

// What the classes allocated before they were sized from LCW_Comp_Bound. A stream is only a
// useful test of the new sizing when at least one block would not have fit these.
int const OLD_READ_BUFFER = BLOCK + BLOCK / 128 + 1;
int const OLD_WRITE_BUFFER = BLOCK + 128;

unsigned char Source[SRCMAX];
unsigned char Packed[DSTMAX];
unsigned char Unpacked[SRCMAX];

unsigned int Seed = 1;

int Failures = 0;


unsigned int Next_Random(void)
{
	Seed = Seed * 1103515245u + 12345u;
	return(Seed >> 8);
}


void Report(char const * what, bool ok)
{
	std::printf("%-64s %s\n", what, ok ? "ok" : "FAILED");
	if (!ok) Failures++;
}


void Fill_Random(unsigned char * data, int size)
{
	for (int i = 0; i < size; i++) {
		data[i] = (unsigned char)(Next_Random() & 0xFF);
	}
}


// The most expensive input the compressor can meet. After a random first half, every group
// of four bytes copies three from more than 4K back, which only the three byte medium form
// can express, and follows them with a fresh byte that has to reopen a literal command.
void Fill_Adversarial(unsigned char * data, int size)
{
	int const half = size / 2;

	Fill_Random(data, size);

	for (int i = half; i + 3 < size; i += 4) {
		int const reach = i - 0x0FFF;
		if (reach <= 0) continue;

		int const from = (int)(Next_Random() % (unsigned)reach);
		data[i] = data[from];
		data[i + 1] = data[from + 1];
		data[i + 2] = data[from + 2];
	}
}


void Fill_Runs(unsigned char * data, int size)
{
	for (int i = 0; i < size; i++) {
		data[i] = (unsigned char)(((i / 64) & 1) ? 0x7E : (Next_Random() & 0xFF));
	}
}


void Fill_Shape(int shape, unsigned char * data, int size)
{
	switch (shape) {
		case 0:
			Fill_Random(data, size);
			break;
		case 1:
			Fill_Adversarial(data, size);
			break;
		case 2:
			Fill_Runs(data, size);
			break;
		default:
			std::memset(data, 0x7E, size);
			break;
	}
}


// Every shape at every small size, then the block sizes the classes use, must compress into
// LCW_Comp_Bound bytes and expand back exactly.
void Test_Bound(void)
{
	int const sizes[] = {1000, 4095, 4096, 4097, BLOCK - 1, BLOCK, BLOCK + 1, BLOCK * 2};

	bool ok = true;
	int worst_block = 0;
	int worst_block_shape = -1;

	for (int shape = 0; shape < 4; shape++) {
		for (int size = 1; size <= 300; size++) {
			Fill_Shape(shape, Source, size);
			int const packed = LCW_Comp(Source, Packed, size);
			int const unpacked = (int)LCW_Uncomp(Packed, Unpacked, (unsigned long)size);

			if (packed > LCW_Comp_Bound(size) || unpacked != size || std::memcmp(Source, Unpacked, size) != 0) {
				std::printf("  shape %d size %d: %d bytes, bound %d, expanded to %d\n",
					shape, size, packed, LCW_Comp_Bound(size), unpacked);
				ok = false;
			}
		}

		for (int const size : sizes) {
			Fill_Shape(shape, Source, size);
			int const packed = LCW_Comp(Source, Packed, size);
			int const unpacked = (int)LCW_Uncomp(Packed, Unpacked, (unsigned long)size);

			if (packed > LCW_Comp_Bound(size) || unpacked != size || std::memcmp(Source, Unpacked, size) != 0) {
				std::printf("  shape %d size %d: %d bytes, bound %d, expanded to %d\n",
					shape, size, packed, LCW_Comp_Bound(size), unpacked);
				ok = false;
			}

			if (size == BLOCK && packed > worst_block) {
				worst_block = packed;
				worst_block_shape = shape;
			}
		}
	}

	Report("compressed output stays within LCW_Comp_Bound", ok);
	std::printf("  largest %d byte block: %d bytes from shape %d, bound %d, old buffers %d and %d\n",
		BLOCK, worst_block, worst_block_shape, LCW_Comp_Bound(BLOCK), OLD_READ_BUFFER, OLD_WRITE_BUFFER);
}


// Walks a block stream, counting its blocks, and returns the largest compressed block.
int Largest_Block(unsigned char const * stream, int length, int & blocks)
{
	int largest = 0;
	int pos = 0;

	blocks = 0;
	while (pos + 4 <= length) {
		int const compcount = stream[pos] | (stream[pos + 1] << 8);
		if (compcount > largest) largest = compcount;
		pos += 4 + compcount;
		blocks++;
	}

	return(largest);
}


// LCWPipe compresses and LCWStraw expands, the pairing the overlay packs use. The adversarial
// blocks compress to more than either class allocated before.
void Test_Pipe_To_Straw(void)
{
	int const size = BLOCK * 3 + 100;

	for (int block = 0; block < 3; block++) {
		Fill_Adversarial(&Source[block * BLOCK], BLOCK);
	}
	Fill_Random(&Source[BLOCK * 3], 100);

	BufferPipe sink(Packed, DSTMAX);
	LCWPipe comp(LCWPipe::COMPRESS);
	comp.Put_To(&sink);

	int packed = comp.Put(Source, size);
	packed += comp.Flush();

	int blocks = 0;
	int const largest = Largest_Block(Packed, packed, blocks);

	std::memset(Unpacked, 0, sizeof(Unpacked));

	BufferStraw feed(Packed, packed);
	LCWStraw decomp(LCWStraw::DECOMPRESS);
	decomp.Get_From(&feed);

	int const got = decomp.Get(Unpacked, size);
	unsigned char extra[16];
	int const beyond = decomp.Get(extra, sizeof(extra));

	Report("pipe to straw round trip of blocks larger than the old buffers",
		got == size && beyond == 0 && std::memcmp(Source, Unpacked, size) == 0 && largest > OLD_WRITE_BUFFER);
	std::printf("  %d bytes in %d blocks, largest block %d bytes\n", size, blocks, largest);
}


// The reverse pairing, fed to the pipe in odd sized pieces so headers straddle calls.
void Test_Straw_To_Pipe(void)
{
	int const size = BLOCK * 2 + 777;

	Fill_Adversarial(Source, BLOCK);
	Fill_Runs(&Source[BLOCK], BLOCK);
	Fill_Random(&Source[BLOCK * 2], 777);

	BufferStraw raw(Source, size);
	LCWStraw comp(LCWStraw::COMPRESS);
	comp.Get_From(&raw);

	int const packed = comp.Get(Packed, DSTMAX);

	std::memset(Unpacked, 0, sizeof(Unpacked));

	BufferPipe sink(Unpacked, SRCMAX);
	LCWPipe decomp(LCWPipe::DECOMPRESS);
	decomp.Put_To(&sink);

	int got = 0;
	for (int pos = 0; pos < packed; pos += 1003) {
		int const piece = (packed - pos < 1003) ? (packed - pos) : 1003;
		got += decomp.Put(&Packed[pos], piece);
	}
	got += decomp.Flush();

	int blocks = 0;
	int const largest = Largest_Block(Packed, packed, blocks);

	Report("straw to pipe round trip in odd sized pieces",
		got == size && std::memcmp(Source, Unpacked, size) == 0 && largest > OLD_WRITE_BUFFER);
}


// Builds a stream from the block the original compressor wrote for a single byte, which
// claims 65537 bytes of output behind a header that says one, followed by an ordinary block.
int Build_Legacy_Stream(unsigned char * stream, unsigned char const * message, int length)
{
	static unsigned char const legacy[] = {
		0x09, 0x00, 0x01, 0x00,
		0x81, 0x7E, 0xFE, 0xFF, 0xFF, 0x00, 0x81, 0x7E, 0x80
	};

	std::memcpy(stream, legacy, sizeof(legacy));
	int pos = sizeof(legacy);

	int const packed = LCW_Comp(message, &stream[pos + 4], length);
	stream[pos] = (unsigned char)(packed & 0xFF);
	stream[pos + 1] = (unsigned char)(packed >> 8);
	stream[pos + 2] = (unsigned char)(length & 0xFF);
	stream[pos + 3] = (unsigned char)(length >> 8);

	return(pos + 4 + packed);
}


// Both readers must take the header's word for the block's size, yield the one byte, and
// carry on with the block after it.
void Test_Legacy_Block(void)
{
	static unsigned char const message[] = "overlay pack written by the original compressor";
	int const length = sizeof(message);

	int const stream = Build_Legacy_Stream(Packed, message, length);

	std::memset(Unpacked, 0, sizeof(Unpacked));

	BufferStraw feed(Packed, stream);
	LCWStraw decomp(LCWStraw::DECOMPRESS);
	decomp.Get_From(&feed);

	int const got = decomp.Get(Unpacked, SRCMAX);

	Report("straw reads a legacy one byte block as one byte",
		got == 1 + length && Unpacked[0] == 0x7E && std::memcmp(&Unpacked[1], message, length) == 0);

	std::memset(Unpacked, 0, sizeof(Unpacked));

	BufferPipe sink(Unpacked, SRCMAX);
	LCWPipe pipe(LCWPipe::DECOMPRESS);
	pipe.Put_To(&sink);

	int put = pipe.Put(Packed, stream);
	put += pipe.Flush();

	Report("pipe reads a legacy one byte block as one byte",
		put == 1 + length && Unpacked[0] == 0x7E && std::memcmp(&Unpacked[1], message, length) == 0);
}


// Headers the compressor cannot produce: no compressed bytes, more than a block of output,
// and more compressed bytes than a block can expand to. The straw stops at each; the pipe
// passes the four header bytes through and picks up the block after them.
void Test_Bad_Headers(void)
{
	static unsigned char const message[] = "the block after a bad header";
	int const length = sizeof(message);

	static unsigned short const headers[][2] = {
		{0, 1},
		{9, 0},
		{9, 0xFFFF},
		{0xFFFF, 1},
		{(unsigned short)(LCW_Comp_Bound(BLOCK) + 1), 1},
	};

	bool straw_ok = true;
	bool pipe_ok = true;

	for (auto const & header : headers) {
		Packed[0] = (unsigned char)(header[0] & 0xFF);
		Packed[1] = (unsigned char)(header[0] >> 8);
		Packed[2] = (unsigned char)(header[1] & 0xFF);
		Packed[3] = (unsigned char)(header[1] >> 8);

		int const packed = LCW_Comp(message, &Packed[8], length);
		Packed[4] = (unsigned char)(packed & 0xFF);
		Packed[5] = (unsigned char)(packed >> 8);
		Packed[6] = (unsigned char)(length & 0xFF);
		Packed[7] = (unsigned char)(length >> 8);
		int const stream = 8 + packed;

		std::memset(Unpacked, 0, sizeof(Unpacked));

		BufferStraw feed(Packed, stream);
		LCWStraw decomp(LCWStraw::DECOMPRESS);
		decomp.Get_From(&feed);

		if (decomp.Get(Unpacked, SRCMAX) != 0) {
			std::printf("  straw yielded data behind header %u/%u\n", header[0], header[1]);
			straw_ok = false;
		}

		std::memset(Unpacked, 0, sizeof(Unpacked));

		BufferPipe sink(Unpacked, SRCMAX);
		LCWPipe pipe(LCWPipe::DECOMPRESS);
		pipe.Put_To(&sink);

		int put = pipe.Put(Packed, stream);
		put += pipe.Flush();

		if (put != 4 + length || std::memcmp(Unpacked, Packed, 4) != 0 || std::memcmp(&Unpacked[4], message, length) != 0) {
			std::printf("  pipe put %d bytes behind header %u/%u\n", put, header[0], header[1]);
			pipe_ok = false;
		}
	}

	Report("straw stops at a header the compressor cannot produce", straw_ok);
	Report("pipe passes such a header through and resumes", pipe_ok);
}

}	// namespace


int main(void)
{
	Test_Bound();
	Test_Pipe_To_Straw();
	Test_Straw_To_Pipe();
	Test_Legacy_Block();
	Test_Bad_Headers();

	std::printf("%d failures\n", Failures);

	return(Failures == 0 ? 0 : 1);
}
