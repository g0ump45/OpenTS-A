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
 *                     $Archive:: /Commando/Code/Tools/pluglib/jshell.cpp                     $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 11/07/00 2:32p                                              $*
 *                                                                                             *
 *                    $Revision:: 28                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Fatal -- General purpose fatal error handler.                                             *
 *   Set_Bit -- Set bit in a bit array.                                                        *
 *   Get_Bit -- Fetch the bit value from a bit array.                                          *
 *   First_True_Bit -- Return with the first true bit index.                                   *
 *   First_False_Bit -- Find the first false bit in the bit array.                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "except.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

/// <summary>
/// Reports an unrecoverable engine error and ends the process.
/// </summary>
/// <param name="message">A printf style description of what went wrong.</param>
/// <remarks>
/// The message is raised as an exception rather than printed, so that the crash handler
/// reports it with the machine state that produced it. A platform without the handler prints
/// it instead. This never returns.
/// </remarks>
void Fatal(char const * message, ...)
{
	// Static because the report reads it from the raised exception, after this frame is gone.
	static char _text[1024];

	va_list va;
	va_start(va, message);
	vsnprintf(_text, sizeof(_text), message, va);
	va_end(va);

#if defined(_WIN32)
	ULONG_PTR const argument = (ULONG_PTR)_text;
	RaiseException(EXCEPTION_OPENTS_FATAL, EXCEPTION_NONCONTINUABLE, 1, &argument);

	TerminateProcess(GetCurrentProcess(), EXIT_FAILURE);
#else
	fputs(_text, stderr);
	fputc('\n', stderr);
	abort();
#endif
}
