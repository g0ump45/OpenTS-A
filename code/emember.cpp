/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "emember.h"

#include "airctype.h"
#include "crc.h"
#include "globals.h"
#include "infatype.h"
#include "techtype.h"
#include "unittype.h"

#include <cstdio>


/// <summary>
/// Creates a task force member from its rules entry.
/// This routine is used when a task force is being read in. The entry names how many
/// of the object are wanted and what the object is; infantry, vehicle and aircraft
/// types are all searched for a match. A name that belongs to none of them leaves the
/// member without an object, and the task force will discard it.
/// </summary>
/// <param name="entry">The rules text describing the member, as quantity and type name.</param>
EnlistedMemberClass::EnlistedMemberClass(char const * entry)
{
	char name[64];
	int quantity;

	Quantity = 0;
	Class = NULL;

	sscanf(entry, "%d,%s", &quantity, name);

	Quantity = quantity;

	int type = InfantryTypeClass::From_Name(name);
	if (type != INFANTRY_NONE) {
		Class = InfantryTypes[type];
		return;
	}

	type = UnitTypeClass::From_Name(name);
	if (type != UNIT_NONE) {
		Class = UnitTypes[type];
		return;
	}

	type = AircraftTypeClass::From_Name(name);
	if (type != AIRCRAFT_NONE) {
		Class = AircraftTypes[type];
	}
}


/// <summary>
/// Builds the rules entry that describes this member.
/// This routine composes the quantity and object type back into the single string a
/// task force writes out for each of its members. It is the inverse of the
/// constructor that parses such an entry.
/// </summary>
/// <returns>Returns with a pointer to the entry text.</returns>
/// <remarks>The text is held in a shared buffer, so use it before building another entry.</remarks>
char const * EnlistedMemberClass::Build_INI_Entry(void) const
{
	static char _buf[32];

	sprintf(_buf, "%d,%s", Quantity, (char const *)Class->IniName);
	return(_buf);
}


/// <summary>
/// Adds this member to a running checksum.
/// This routine is called by the task force it belongs to so that the multiplayer
/// synchronization check covers the composition of every team.
/// </summary>
void EnlistedMemberClass::Compute_CRC(CRCEngine & crc) const
{
	crc(Quantity);
	if (Class != NULL) {
		crc((RTTIType)Class->RTTI);
		crc(Class->Fetch_ID());
	}
}
