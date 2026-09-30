/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "ccfile.h"
#include "ini.h"
#include "wdtnet.h"

using namespace WorldDominationTour;


/// <summary>
/// Fetches the cycle ID recorded for a campaign.
/// Use this routine to peek at the tour history file without having to build a Campaign
/// object first.
/// </summary>
/// <param name="section">The name of the campaign to look up.</param>
/// <returns>Returns with the recorded campaign ID, or -1 if the history file holds no
/// entry for that campaign.</returns>
int WDT_Get_Campaign_ID(const char * section)
{
	CDFileClass file("WDTHist.INI");
	if (file.Is_Available()) {
		INIClass ini;
		ini.Load(file);
		file.Close();
		return(ini.Get_Int(section, "CampaignID", -1));
	}
	return(-1);
}


/// <summary>
/// Constructor for a World Domination Tour campaign.
/// This routine gathers a conflict for every territory currently in dispute, then picks up
/// where the player left off by reading the cycle, tick and chosen side out of the tour
/// history file. A campaign whose recorded cycle no longer matches the tour's is treated
/// as a fresh start rather than a continuation.
/// </summary>
/// <param name="name">The name of the campaign. This doubles as its history file section.</param>
/// <param name="props">The properties and current world state of the tour.</param>
Campaign::Campaign(char const *name, CampaignProperties const &props) :
	Properties(props),
	IsContinued(true),
	CycleHistory(props.TourState),
	Conflicts(4),
	PreviousTick(0),
	PlayerFaction(0)
{
	strncpy(Name, name, sizeof(Name));

	if (props.TourState != NULL) {
		State state = CycleHistory.Get_State(props.Get_Current_Tick());
		unsigned int terrnum = props.TourState->NumTerritories;
		while (terrnum--) {
			if (state.Get_Territory_State(terrnum) == State::DISPUTED) {
				DynamicVectorClass<WDTTerritory *> & territories = props.TourState->Territories;
				if (terrnum < (unsigned)territories.Count()) {
					WDTTerritory * territory = territories[terrnum];
					if (territory != NULL) {
						Conflict conflict(territory);
						Conflicts.Add(conflict);
					}
				}
			}
		}
	}

	CDFileClass file("WDTHist.INI");
	if (file.Is_Available()) {
		INIClass ini;
		ini.Load(file);
		file.Close();
		int cycle_id = ini.Get_Int(Name, "CampaignID", -1);
		CycleID = cycle_id < 0 ? 0 : cycle_id;
		if (CycleID == props.Get_Cycle_ID()) {
			int previous_tick = ini.Get_Int(Name, "Previous", 0);
			PreviousTick = previous_tick < 0 ? 0 : previous_tick;
			PlayerFaction = ini.Get_Int(Name, "PlayerFaction", PlayerFaction);
		} else {
			PreviousTick = 0;
			IsContinued = false;
		}
	}
}


/// <summary>
/// Destructor for a World Domination Tour campaign.
/// </summary>
Campaign::~Campaign(void)
{

}


/// <summary>
/// Has the tour started a new cycle?
/// The recorded cycle is the one this campaign last saw; the properties carry the cycle
/// the tour is running now.
/// </summary>
/// <returns>bool; Has the tour moved on to a cycle this campaign has not seen?</returns>
bool Campaign::Is_Different_Cycle(void)
{
	return(CycleID != Properties.Get_Cycle_ID());
}


/// <summary>
/// Has the tour advanced since this campaign was last recorded?
/// The tour screen uses this routine to decide whether the world map needs bringing up to
/// date before the player is shown it.
/// </summary>
/// <returns>bool; Is either the cycle or the tick out of date?</returns>
bool Campaign::Is_Different(void)
{
	return(Is_Different_Cycle() || PreviousTick != Properties.Get_Current_Tick());
}


/// <summary>
/// Records the campaign's progress in the tour history file.
/// This routine is called once the player has caught up with the tour, so that the next
/// session knows which cycle and which tick were last seen.
/// </summary>
void Campaign::Write_INI(void)
{
	CycleID = Properties.Get_Cycle_ID();
	PreviousTick = Properties.Get_Current_Tick();
	INIClass ini;
	Load_INI(ini);
	ini.Put_Int(Name, "CampaignID", CycleID, 0);
	ini.Put_Int(Name, "Previous", PreviousTick, 0);
	CDFileClass file;
	file.Open("WDTHist.ini", 2);
	ini.Save(file);
}


/// <summary>
/// Clears the campaign's recorded progress.
/// Use this routine to start the campaign over. The history entry is zeroed and the
/// campaign stops counting as a continuation of an earlier session.
/// </summary>
void Campaign::Reset_INI(void)
{
	INIClass ini;
	Load_INI(ini);
	ini.Put_Int(Name, "CampaignID", 0, 0);
	ini.Put_Int(Name, "Previous", 0, 0);
	CDFileClass file;
	file.Open("WDTHist.ini", 2);
	ini.Save(file);
	IsContinued = false;
}


/// <summary>
/// Fetches the conflict fought over a territory.
/// The tour screen uses this routine when the player picks a territory, to reach the
/// conflict that will be fought over it.
/// </summary>
/// <param name="index">The territory to find the conflict for.</param>
/// <returns>Returns with a pointer to the conflict. Otherwise, NULL is returned if that
/// territory is not in dispute.</returns>
Conflict * Campaign::FindConflict(int index)
{
	for (Conflict & conflict : Conflicts) {
		if (conflict.Get_Territory_Index() == index) {
			return(&conflict);
		}
	}
	return(NULL);
}


/// <summary>
/// Sets the side the player is fighting for.
/// The choice is written straight out to the tour history file so that it survives into
/// the next session. Choosing the side the player is already on does nothing at all.
/// </summary>
/// <param name="faction">The side the player has chosen to fight for.</param>
void Campaign::Set_Faction(int faction)
{
	if (PlayerFaction != faction) {
		PlayerFaction = faction;
		INIClass ini;
		Load_INI(ini);
		ini.Put_Int(Name, "PlayerFaction", PlayerFaction);
		CDFileClass file;
		file.Open("WDTHist.ini", 2);
		ini.Save(file);
	}
}


/// <summary>
/// Loads the tour history file into an INI database.
/// This routine is used by the routines that record campaign progress. The history file is
/// created empty when it is missing, so the caller always ends up with a usable database.
/// </summary>
/// <param name="ini">The INI database to load the history into.</param>
void Campaign::Load_INI(INIClass & ini)
{
	CDFileClass file;
	file.Open("WDTHist.ini");
	if (!file.Is_Available()) {
		file.Create();
		file.Close();
		file.Open("WDTHist.ini");
	}
	ini.Load(file);
	file.Close();
}
