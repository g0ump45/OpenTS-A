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

#include "always.h"

#include "_warhead.h"

#include "vector.h"
#include "warhead.h"

/***************************************************************************
**	This is the warhead data object array.
*/
DynamicVectorClass<WarheadTypeClass *> Warheads;


/// <summary>
/// Converts a warhead name into a warhead type.
/// This routine is used when the rules are read in and a warhead is referred to by name.
/// A name that has not been encountered before will have a warhead type object created
/// for it, so an unknown name is not treated as an error.
/// </summary>
/// <returns>Returns with the warhead type that matches the name. Otherwise, WARHEAD_NONE
/// is returned.</returns>
WarheadType Warhead_From_Name(char const * name)
{
	if (name != NULL && stricmp(name, "<none>") != 0 && stricmp(name, "none") != 0) {
		for (int index = WARHEAD_FIRST; index < Warheads.Count(); index++) {
			if (stricmp(name, Warheads[index]->Name()) == 0) {
				return(WarheadType(index));
			}
		}
		WarheadTypeClass *ptr = new WarheadTypeClass(name);
		return(WarheadType(Warheads.ID(ptr)));

	}
	return(WARHEAD_NONE);
}


/// <summary>
/// Fetches the name of the specified warhead.
/// This routine is used when a warhead must be written back out to an INI file or
/// displayed, since the rules refer to warheads by name rather than by index.
/// </summary>
/// <returns>Returns with a pointer to the warhead's name. Otherwise, NULL is returned.</returns>
char const * Warhead_Name(WarheadType warhead)
{
	if (warhead == WARHEAD_NONE || (unsigned)warhead >= (unsigned)Warheads.Count()) return(NULL);

	return(Warheads[warhead]->Name());
}
