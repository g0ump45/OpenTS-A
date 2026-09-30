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

#include "quarry.h"

#include "win.h"


/***************************************************************************
**	Type of quarry to search out and attack. These values are used for team
**	attack missions.
*/
char const * const QuarryName[QUARRY_COUNT] = {
	"N/A",
	"Anything",
	"Buildings - any",
	"Harvesters",
	"Infantry",
	"Vehicles - any",
	"Factories",
	"Base Defenses",
	"Base Threats",
	"Power Facilities",
};



/// <summary>
/// Converts a quarry name into its matching quarry type.
/// This routine is used when reading team type data from the scenario file, where the
/// quarry that the team should seek out is recorded by name.
/// </summary>
/// <returns>Returns with the quarry type that matches the name. If the name is not
/// recognized, then QUARRY_NONE is returned.</returns>
QuarryType Quarry_From_Name(char const * name)
{
	//if (name) {
		for (int quarry = QUARRY_FIRST; quarry < QUARRY_COUNT; quarry++) {
			if (stricmp(name, QuarryName[quarry]) == 0) {
				return(QuarryType(quarry));
			}
		}
	//}
	return(QUARRY_NONE);
}


/// <summary>
/// Fetches the name of the quarry type specified.
/// This routine is the counterpart to Quarry_From_Name and is used when writing team
/// type data back out to the scenario file.
/// </summary>
/// <returns>Returns with a pointer to the name text of the quarry specified.</returns>
char const * Name_From_Quarry(QuarryType quarry)
{
	//if ((unsigned)quarry < QUARRY_COUNT) {
		return(QuarryName[quarry]);
	//}
	//return("None");
}
