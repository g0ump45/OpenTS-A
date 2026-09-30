/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

// Pins the two spellings of a spawn house, with no engine and no game data: which names
// and numbers name a start position, which are refused, and what is written back.

#include <cstdio>
#include <cstring>

#include "spawnhouse.h"

namespace {

int Failures = 0;


void Check(bool condition, char const * what)
{
	std::printf("%-64s %s\n", what, condition ? "ok" : "FAILED");

	if (!condition) {
		Failures++;
	}
}


constexpr char const * const SpawnSpelling[SPAWN_HOUSE_COUNT] = {
	"Spawn1", "Spawn2", "Spawn3", "Spawn4", "Spawn5", "Spawn6", "Spawn7", "Spawn8"
};

constexpr char const * const PlayerAtSpelling[SPAWN_HOUSE_COUNT] = {
	"<Player @ A>", "<Player @ B>", "<Player @ C>", "<Player @ D>",
	"<Player @ E>", "<Player @ F>", "<Player @ G>", "<Player @ H>"
};

}


int main(void)
{
	/*
	 * Both spellings, in either case, name the same eight positions.
	 */
	{
		bool names = true;
		bool numbers = true;
		for (int spawn_waypoint = 0; spawn_waypoint < SPAWN_HOUSE_COUNT; spawn_waypoint++) {
			names = names && Spawn_House_Waypoint(SpawnSpelling[spawn_waypoint]) == spawn_waypoint;
			names = names && Spawn_House_Waypoint(PlayerAtSpelling[spawn_waypoint]) == spawn_waypoint;
			numbers = numbers && Spawn_House_Waypoint(static_cast<HousesType>(50 + spawn_waypoint)) == spawn_waypoint;
			numbers = numbers && Spawn_House_Waypoint(static_cast<HousesType>(4475 + spawn_waypoint)) == spawn_waypoint;
		}
		Check(names, "Spawn1..Spawn8 and <Player @ A>..<Player @ H> name positions 0..7");
		Check(numbers, "50..57 and 4475..4482 number positions 0..7");
		Check(Spawn_House_Waypoint("SPAWN3") == 2 && Spawn_House_Waypoint("<player @ c>") == 2,
			"either spelling is matched without regard to case");
		Check(Spawn_House_Waypoint(HOUSE_SPAWN_FIRST) == 0 &&
			Spawn_House_Waypoint(HOUSE_SPAWN_LAST) == SPAWN_HOUSE_COUNT - 1 &&
			Spawn_House_Waypoint(HOUSE_PLAYER_AT_FIRST) == 0 &&
			Spawn_House_Waypoint(HOUSE_PLAYER_AT_LAST) == SPAWN_HOUSE_COUNT - 1,
			"the ends of both numeric ranges are spawn houses");
	}

	/*
	 * Anything else is refused, the numbers just past each range included.
	 */
	{
		bool refused = true;
		char const * const rejected[] = {
			"Spawn0", "Spawn9", "Spawn10", "Spawn 1", "Spawn1x", "Spawn", "<Player @ I>",
			"<Player @ A", "Player @ A", "<Player @A>", "GDI", "Neutral", ""
		};
		for (char const * name : rejected) {
			refused = refused && Spawn_House_Waypoint(name) == -1;
		}
		Check(refused && Spawn_House_Waypoint(nullptr) == -1,
			"a name that is not one of the sixteen spellings names nothing");

		bool outside = true;
		int const numbers[] = { -1, 0, 1, 3, 49, 58, 59, 60, 4474, 4483 };
		for (int number : numbers) {
			outside = outside && Spawn_House_Waypoint(static_cast<HousesType>(number)) == -1;
		}
		Check(outside, "49, 58..60, 4474 and 4483 name nothing, as does a country");
	}

	/*
	 * A position is written back in the Tiberian Sun spelling and reads back as itself.
	 */
	{
		bool round = true;
		for (int spawn_waypoint = 0; spawn_waypoint < SPAWN_HOUSE_COUNT; spawn_waypoint++) {
			round = round && Spawn_House_Type(spawn_waypoint) == static_cast<HousesType>(50 + spawn_waypoint);
			round = round && Spawn_House_Waypoint(Spawn_House_Type(spawn_waypoint)) == spawn_waypoint;
			round = round && Spawn_House_Waypoint(Spawn_House_Name(spawn_waypoint)) == spawn_waypoint;
		}
		Check(round, "a position round trips through 50 + spawn_waypoint and its Spawn name");
		Check(std::strcmp(Spawn_House_Name(0), "Spawn1") == 0 && std::strcmp(Spawn_House_Name(7), "Spawn8") == 0,
			"the written name is Spawn<spawn_waypoint + 1>");
		Check(Spawn_House_Type(-1) == HOUSE_NONE && Spawn_House_Type(SPAWN_HOUSE_COUNT) == HOUSE_NONE &&
			Spawn_House_Name(-1) == nullptr && Spawn_House_Name(SPAWN_HOUSE_COUNT) == nullptr,
			"a start waypoint outside 0..7 has no number and no name");
	}

	return Failures == 0 ? 0 : 1;
}
