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
 *                     $Archive:: /Commando/Code/wwlib/base64.cpp                             $*
 *                                                                                             *
 *                      $Author:: Jani_p                                                      $*
 *                                                                                             *
 *                     $Modtime:: 5/04/01 8:08p                                               $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Base64_Decode -- Decodes Base 64 data into its original data form.                        *
 *   Base64_Encode -- Encode data into Base 64 format.                                         *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "base64.h"

#include <cstddef>

/*
**	This is the magic padding character used to fill out the encoded data to a multiple of
**	4 characters even though the source data is less than necessary to accomplish this.
**	The pad character lets the decoder know of this condition and it will compensate
**	accordingly.
*/
static char const * const _pad = "=";

/*
**	This encoder translation table will convert a 6 bit number into an ASCII character.
*/
static char const * const _encoder = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*
**	The decoder translation table takes an ASCII character and converts it into a
**	6 bit number.
*/
#define	BAD	0xFE			// Ignore this character in source data.
#define	END	0xFF			// Signifies premature end of input data.
static unsigned char const _decoder[256] = {
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,62,BAD,BAD,BAD,63,
	52,53,54,55,56,57,58,59,60,61,BAD,BAD,BAD,END,BAD,BAD,
	BAD,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
	15,16,17,18,19,20,21,22,23,24,25,BAD,BAD,BAD,BAD,BAD,
	BAD,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50,51,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
	BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD
};

int const PacketChars = 4;




/***********************************************************************************************
 * Base64_Encode -- Encode data into Base 64 format.                                           *
 *                                                                                             *
 *    This will take an arbitrary length of source data and transform it into base 64 format   *
 *    data. Base 64 format has the property of being very portable across text editors and     *
 *    country character encoding schemes. As such it is ideal for e-mail. Note that the output *
 *    data will be about 33% larger than the source.                                           *
 *                                                                                             *
 * INPUT:   source   -- Pointer to the source data to convert.                                 *
 *                                                                                             *
 *          slen     -- The number of bytes to encode.                                         *
 *                                                                                             *
 *          dest     -- Pointer to the destination buffer that will hold the encoded data.     *
 *                                                                                             *
 *          dlen     -- The size of the destination buffer.                                    *
 *                                                                                             *
 * OUTPUT:  Returns with the number of bytes stored into the destination buffer.               *
 *                                                                                             *
 * WARNINGS:   Be sure that the destination buffer is big enough to hold the encoded output.   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int Base64_Encode(void const * source, int slen, void * dest, int dlen)
{
	/*
	**	Check the parameters for legality.
	*/
	if (source == NULL || slen == 0 || dest == NULL || dlen == 0) {
		return(0);
	}

	/*
	**	Process the source data in blocks of three bytes. Fewer than three bytes
	**	results in special padding output characters (automatically discarded
	**	during the decode process).
	*/
	int total = 0;
	unsigned char const * sptr = (unsigned char const *)source;
	unsigned char * dptr = (unsigned char *)dest;
	while (slen > 0 && dlen >= PacketChars) {

		/*
		**	Fetch 24 bits of source data.
		*/
		unsigned int packet = 0;

		int pad = 0;
		packet = 0;
		packet = (unsigned int)*sptr++ << 16;
		slen--;
		if (slen) {
			packet |= (unsigned int)*sptr++ << 8;
			slen--;
		} else {
			pad++;
		}
		if (slen) {
			packet |= *sptr++;
			slen--;
		} else {
			pad++;
		}

		/*
		**	Translate and write 4 characters of Base64 data. Pad with pad
		**	characters if there is insufficient source data for a full packet.
		*/
		*dptr++ = _encoder[((packet >> 18) & 0x3f)];
		*dptr++ = _encoder[((packet >> 12) & 0x3f)];
		if (pad < 2) {
			*dptr++ = _encoder[((packet >> 6) & 0x3f)];
		} else {
			*dptr++ = _pad[0];
		}
		if (pad < 1) {
			*dptr++ = _encoder[((packet >> 0) & 0x3f)];
		} else {
			*dptr++ = _pad[0];
		}

		dlen -= PacketChars;
		total += PacketChars;
	}

	/*
	**	Add a trailing null as a courtesy measure.
	*/
	if (dlen > 0) {
		*dptr = '\0';
	}

	/*
	**	Return with the total number of characters in the output buffer.
	*/
	return(total);
}


/***********************************************************************************************
 * Base64_Decode -- Decodes Base 64 data into its original data form.                          *
 *                                                                                             *
 *    Use this routine to decode base 64 data back into the original data. A property of this  *
 *    decode process is that unrecognized input characters are ignored. This allows mangled    *
 *    source (filled with line breaks or spaces) to be correctly decoded. The decode process   *
 *    terminates when the end of the source data has been reached or the special end of data   *
 *    marker is encountered.                                                                   *
 *                                                                                             *
 * INPUT:   source   -- Pointer to the source data to decode.                                  *
 *                                                                                             *
 *          slen     -- The number of bytes in the source data buffer.                         *
 *                                                                                             *
 *          dest     -- Pointer to the destination buffer to be filled with the decoded data.  *
 *                                                                                             *
 *          dlen     -- The maximum size of the destination buffer.                            *
 *                                                                                             *
 * OUTPUT:  Returns with the number of bytes stored into the destination buffer. This will     *
 *          always be less than the number of source bytes (usually by about 33%).             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/06/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int Base64_Decode(void const * source, int slen, void * dest, int dlen)
{
	/*
	**	Check the parameters for legality.
	*/
	if (source == NULL || slen == 0 || dest == NULL || dlen == 0) {
		return(0);
	}

	int total = 0;
	unsigned char const * sptr = (unsigned char const *)source;
	unsigned char * dptr = (unsigned char *)dest;
	while (slen > 0 && dlen > 0) {

		unsigned int packet = 0;
		packet = 0;

		/*
		**	Process input until a full packet has been accumulated or the
		**	source is exhausted.
		*/
		int pcount = 0;
		while (pcount < PacketChars && slen > 0) {
			unsigned char c = *sptr++;
			slen--;

			unsigned char code = _decoder[c];

			/*
			**	An unrecognized character is skipped.
			*/
			if (code == BAD) continue;

			/*
			**	The "=" character signifies the end of data regardless of what
			**	the source buffer length value may be.
			*/
			if (code == END) {
				slen = 0;
				break;
			}

			/*
			**	A valid Base64 character was found so add it to the packet
			**	data.
			*/
			packet |= (unsigned int)code << (18 - 6 * pcount);
			pcount++;
		}

		/*
		**	A packet block is ready for output into the destination buffer.
		*/
		*dptr++ = (unsigned char)(packet >> 16);
		dlen--;
		total++;
		if (dlen > 0 && pcount > 2) {
			*dptr++ = (unsigned char)(packet >> 8);
			dlen--;
			total++;
		}
		if (dlen > 0 && pcount > 3) {
			*dptr++ = (unsigned char)(packet >> 0);
			dlen--;
			total++;
		}
	}

	/*
	**	Return with the total number of characters decoded into the
	**	output buffer.
	*/
	return(total);
}


/*
Base64 Content-Transfer-Encoding

The Base64 Content-Transfer-Encoding is designed to represent arbitrary
sequences of octets in a form that need not be humanly readable. The encoding
and decoding algorithms are simple, but the encoded data are consistently
only about 33 percent larger than the unencoded data. This encoding is
virtually identical to the one used in Privacy Enhanced Mail (PEM)
applications, as defined in RFC 1421. The base64 encoding is adapted from
RFC 1421, with one change: base64 eliminates the "*" mechanism for embedded
clear text.

A 65-character subset of US-ASCII is used, enabling 6 bits to be represented
per printable character. (The extra 65th character, "=", is used to signify a
special processing function.)

NOTE:
    This subset has the important property that it is represented identically
    in all versions of ISO 646, including US ASCII, and all characters in the
    subset are also represented identically in all versions of EBCDIC. Other
    popular encodings, such as the encoding used by the uuencode utility and
    the base85 encoding specified as part of Level 2 PostScript, do not share
    these properties, and thus do not fulfill the portability requirements a
    binary transport encoding for mail must meet.

The encoding process represents 24-bit groups of input bits as output strings
of 4 encoded characters. Proceeding from left to right, a 24-bit input group is
formed by concatenating 3 8-bit input groups. These 24 bits are then treated as
4 concatenated 6-bit groups, each of which is translated into a single digit in
the base64 alphabet. When encoding a bit stream via the base64 encoding, the
bit stream must be presumed to be ordered with the most-significant-bit first.
That is, the first bit in the stream will be the high-order bit in the first
byte, and the eighth bit will be the low-order bit in the first byte, and so on.

Each 6-bit group is used as an index into an array of 64 printable characters.
The character referenced by the index is placed in the output string. These
characters, identified in Table 1, below, are selected so as to be universally
representable, and the set excludes characters with particular significance to
SMTP (e.g., ".", CR, LF) and to the encapsulation boundaries defined in this
document (e.g., "-").

Table 1: The Base64 Alphabet

  Value Encoding  Value Encoding  Value Encoding  Value Encoding
       0 A            17 R            34 i            51 z
       1 B            18 S            35 j            52 0
       2 C            19 T            36 k            53 1
       3 D            20 U            37 l            54 2
       4 E            21 V            38 m            55 3
       5 F            22 W            39 n            56 4
       6 G            23 X            40 o            57 5
       7 H            24 Y            41 p            58 6
       8 I            25 Z            42 q            59 7
       9 J            26 a            43 r            60 8
      10 K            27 b            44 s            61 9
      11 L            28 c            45 t            62 +
      12 M            29 d            46 u            63 /
      13 N            30 e            47 v
      14 O            31 f            48 w         (pad) =
      15 P            32 g            49 x
      16 Q            33 h            50 y

The output stream (encoded bytes) must be represented in lines of no more than
76 characters each. All line breaks or other characters not found in Table 1
must be ignored by decoding software. In base64 data, characters other than
those in Table 1, line breaks, and other white space probably indicate a
transmission error, about which a warning message or even a message rejection
might be appropriate under some circumstances.

Special processing is performed if fewer than 24 bits are available at the end
of the data being encoded. A full encoding quantum is always completed at the
end of a body. When fewer than 24 input bits are available in an input group,
zero bits are added (on the right) to form an integral number of 6-bit groups.
Padding at the end of the data is performed using the '=' character. Since all
base64 input is an integral number of octets, only the following cases can
arise: (1) the final quantum of encoding input is an integral multiple of 24
bits; here, the final unit of encoded output will be an integral multiple of 4
characters with no "=" padding, (2) the final quantum of encoding input is
exactly 8 bits; here, the final unit of encoded output will be two characters
followed by two "=" padding characters, or (3) the final quantum of encoding
input is exactly 16 bits; here, the final unit of encoded output will be three
characters followed by one "=" padding character.

Because it is used only for padding at the end of the data, the occurrence of
any '=' characters may be taken as evidence that the end of the data has been
reached (without truncation in transit). No such assurance is possible,
however, when the number of octets transmitted was a multiple of three.

Any characters outside of the base64 alphabet are to be ignored in
base64-encoded data. The same applies to any illegal sequence of characters in
the base64 encoding, such as "====="

Care must be taken to use the proper octets for line breaks if base64 encoding
is applied directly to text material that has not been converted to canonical
form. In particular, text line breaks must be converted into CRLF sequences
prior to base64 encoding. The important thing to note is that this may be done
directly by the encoder rather than in a prior canonicalization step in some
implementations.

NOTE:
    There is no need to worry about quoting apparent encapsulation boundaries
    within base64-encoded parts of multipart entities because no hyphen
    characters are used in the base64 encoding.

*/
