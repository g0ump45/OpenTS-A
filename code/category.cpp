/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "category.h"

#include "incdec.h"

#include <cstring>


static struct {
	char const * Description;
	char const * Name;
} _categories[CATEGORY_COUNT] = {
	{ "Soldier", "Soldier" },
	{ "Civilian", "Civilian" },
	{ "VIP/Agent", "VIP" },
	{ "Recon Vehicle", "Recon" },
	{ "Armored Fighting Vehicle", "AFV" },
	{ "Infantry Fighting Vehicle", "IFV" },
	{ "Indirect Fire Support", "LRFS" },
	{ "Misc. Support Vehicle", "Support" },
	{ "Transport Vehicle", "Transport" },
	{ "Air Combat Support", "AirPower" },
	{ "Air Transport", "AirLift" }
};


/// <summary>
/// Fetches the descriptive text for a unit category.
/// This routine yields the long form of the category, suitable for showing to the
/// player rather than for storing in the rules.
/// </summary>
/// <returns>Returns with the description text. An out of range category yields a
/// placeholder string.</returns>
char const * Description_From_Category(CategoryType category)
{
	if ((unsigned)category < (unsigned)CATEGORY_COUNT) {
		return(_categories[category].Description);
	}
	return("<none>");
}


/// <summary>
/// Fetches the abbreviated name of a unit category.
/// This routine yields the short form of the category, which is the spelling written
/// out to and read back from the rules.
/// </summary>
/// <returns>Returns with the abbreviated name. An out of range category yields a
/// placeholder string.</returns>
char const * Name_From_Category(CategoryType category)
{
	if ((unsigned)category < (unsigned)CATEGORY_COUNT) {
		return(_categories[category].Name);
	}
	return("<none>");
}


/// <summary>
/// Converts a category name back into its category identifier.
/// This routine is the counterpart of the two lookups above and is used when reading
/// the category assigned to an object type from the rules. Either the abbreviated name
/// or the full description is accepted, and the comparison ignores case.
/// </summary>
/// <returns>Returns with the category identified, or CATEGORY_NONE if the name is
/// unknown.</returns>
CategoryType Category_From_Name(char const * name)
{
	if (name != NULL) {
		for (CategoryType index = CATEGORY_FIRST; index < CATEGORY_COUNT; index++) {
			if (strcmpi(_categories[index].Name, name) == 0 || strcmpi(_categories[index].Description, name) == 0) {
				return(index);
			}
		}
	}
	return(CATEGORY_NONE);
}
