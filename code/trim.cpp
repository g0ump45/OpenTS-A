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
 *                     $Archive:: /Commando/Code/wwlib/trim.cpp                               $*
 *                                                                                             *
 *                      $Author:: Denzil_l                                                    $*
 *                                                                                             *
 *                     $Modtime:: 11/08/01 11:35a                                             $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include <cstring>

/***********************************************************************************************
 * strtrim -- Trim leading and trailing white space off of string.                             *
 *                                                                                             *
 *    This routine will remove the leading and trailing whitespace from the string specifed.   *
 *    The string is modified in place.                                                         *
 *                                                                                             *
 * INPUT:   buffer   -- Pointer to the string to be trimmed.                                   *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   02/06/1997 JLB : Created.                                                                 *
 *=============================================================================================*/
char * strtrim(char * buffer)
{
	if (buffer) {

		/*
		**	Strip leading white space from the string.
		*/
		char * source = buffer;
		//while (isspace(*source)) {
		while ((*source != 0) && ((unsigned char)*source <= 32)) {
			source++;
		}

		if (source != buffer) {
			memmove(buffer, source, strlen(source) + 1);
		}

		/*
		**	Clip trailing white space from the string.
		*/
		for (int index = strlen(buffer)-1; index >= 0; index--) {
			//if (isspace(buffer[index])) {
			if ((*source != 0) && ((unsigned char)buffer[index] <= 32)) {
				buffer[index] = '\0';
			} else {
				break;
			}
		}
	}
	return(buffer);
}
