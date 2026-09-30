/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "ini.h"
#include "wdtnet.h"

#include <cstdio>

using namespace WorldDominationTour;


/// <summary>
/// Creates an empty world domination tour map.
/// The territories are supplied afterwards by Add_Territory.
/// </summary>
/// <param name="id">The identifier of the campaign region this map depicts.</param>
Map::Map(int id) :
	ID(id)
{
	//nothing
}


/// <summary>
/// Destroys the map and the territories it owns.
/// </summary>
Map::~Map(void)
{
	for (Territory * territory : Territories) {
		delete territory;
	}
}


/// <summary>
/// Adds the territories that a campaign region is made of.
/// This routine is used when the tour selection screen builds its map. Every territory
/// listed in the section becomes a Territory object with its shape and highlight
/// animations registered with the presentation engine.
/// </summary>
/// <param name="name">The prefix of the territory shape file names.</param>
/// <param name="section">The INI section that lists the territories.</param>
/// <param name="side">The side the player is fighting for.</param>
/// <param name="pos">The screen position that territory origins are relative to.</param>
void Map::Add_Territory(const char * name, INIClass const & ini, const char * section, int side, MSEngine & engine, ConvertClass * drawer, MS_ANIM_LIST * anims, Point2D const & pos)
{
	char entry[32];
	char buffer[64];
	char fname[64];

	for (int i = 0; i < MAX_WDT_TERRITORIES; i++) {
		sprintf(entry, "Territory%02d", i);
		sprintf(fname, "%s%02d.shp", name, i + 1);
		if (ini.Get_String(section, entry, 0, buffer, sizeof(buffer)) > 0) {
			Territories.Add(new Territory(i, fname, ini, buffer, side, engine, drawer, anims, pos));
		}
	}
}
