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
 *                     $Archive:: /Commando/Library/B64PIPE.CPP                               $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Base64Pipe::Flush -- Flushes the final pending data through the pipe.                     *
 *   Base64Pipe::Put -- Processes a block of data through the pipe.                            *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "b64pipe.h"

#include "base64.h"

#include <cstring>


/***********************************************************************************************
 * Base64Pipe::Put -- Processes a block of data through the pipe.                              *
 *                                                                                             *
 *    This will take the data submitted and either Base64 encode or decode it (as specified    *
 *    in the pipe's constructor). The nature of Base64 encoding means that the data will       *
 *    grow 30% in size when encoding and decrease by a like amount when decoding.              *
 *                                                                                             *
 * INPUT:   source   -- Pointer to the data to be translated.                                  *
 *                                                                                             *
 *          length   -- The number of bytes to translate.                                      *
 *                                                                                             *
 * OUTPUT:  Returns with the actual number of bytes output at the far distant final end of     *
 *          the pipe chain.                                                                    *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int Base64Pipe::Put(void const * source, int slen)
{
	if (source == NULL || slen < 1) {
		return(BASECLASS::Put(source, slen));
	}

	int total = 0;

	char * from;
	int fromsize;
	char * to;
	int tosize;

	if (Control == ENCODE) {
		from = PBuffer;
		fromsize = sizeof(PBuffer);
		to = CBuffer;
		tosize = sizeof(CBuffer);
	} else {
		from = CBuffer;
		fromsize = sizeof(CBuffer);
		to = PBuffer;
		tosize = sizeof(PBuffer);
	}

	if (Counter > 0) {
		int len = (slen < (fromsize-Counter)) ? slen : (fromsize-Counter);
		memmove(&from[Counter], source, len);
		Counter += len;
		slen -= len;
		source = ((char *)source) + len;

		if (Counter == fromsize) {
			int outcount;
			if (Control == ENCODE) {
				outcount = Base64_Encode(from, fromsize, to, tosize);
			} else {
				outcount = Base64_Decode(from, fromsize, to, tosize);
			}
			total += BASECLASS::Put(to, outcount);
			Counter = 0;
		}
	}

	while (slen >= fromsize) {
		int outcount;
		if (Control == ENCODE) {
			outcount = Base64_Encode(source, fromsize, to, tosize);
		} else {
			outcount = Base64_Decode(source, fromsize, to, tosize);
		}
		source = ((char *)source) + fromsize;
		total += BASECLASS::Put(to, outcount);
		slen -= fromsize;
	}

	if (slen > 0) {
		memmove(from, source, slen);
		Counter = slen;
	}

	return(total);
}


/***********************************************************************************************
 * Base64Pipe::Flush -- Flushes the final pending data through the pipe.                       *
 *                                                                                             *
 *    If there is any non-processed data accumulated in the holding buffer (quite likely when  *
 *    encoding), then it will be processed and flushed out the end of the pipe.                *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the number of bytes output at the far distant final end of the pipe   *
 *          chain.                                                                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int Base64Pipe::Flush(void)
{
	int len = 0;

	if (Counter) {
		if (Control == ENCODE) {
			int chars = Base64_Encode(PBuffer, Counter, CBuffer, sizeof(CBuffer));
			len += BASECLASS::Put(CBuffer, chars);
		} else {
			int chars = Base64_Decode(CBuffer, Counter, PBuffer, sizeof(PBuffer));
			len += BASECLASS::Put(PBuffer, chars);
		}
		Counter = 0;
	}
	len += BASECLASS::Flush();
	return(len);
}
