/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "theater.h"

#include "_theater.h"
#include "ccini.h"
#include "findmake.h"

#include <cctype>


/*
 * Tiberian Sun hard-coded these two theaters, so they are what a rules file declaring no
 * theater list gets, and what a list naming either of them starts from.
 */
struct TheaterSeedType
{
	char const * Name;
	char const * Root;
	char const * IsoRoot;
	char const * Suffix;
	char const * MMSuffix;
	char ImageLetter;
	bool IsArctic;
	bool IsIceGrowth;
	float LowRadarBrightness;
	float HighRadarBrightness;
};

static TheaterSeedType const _Seeds[] = {
	{"TEMPERATE", "TEMPERAT", "ISOTEMP", "TEM", "MMT", 'T', false, false, 1.0f, 1.6f},
	{"SNOW",      "SNOW",     "ISOSNOW", "SNO", "MMS", 'A', true,  true,  0.8f, 1.1f},
};


/// <summary>
/// Creates a theater and adds it to the global theater list.
/// One carrying a name Tiberian Sun hard-coded starts from that theater's settings, so a
/// rules file may name it without restating them.
/// </summary>
/// <param name="listed">Only the placeholder As_Reference hands back for an unusable index
/// passes false and stays out of the list.</param>
TheaterClass::TheaterClass(char const * name, bool listed) :
	IniName(name),
	Root(name),
	IsoRoot(name),
	Suffix(),
	MMSuffix(),
	ImageLetter('\0'),
	IsArctic(false),
	IsIceGrowth(false),
	LowRadarBrightness(1.0f),
	HighRadarBrightness(1.6f)
{
	for (TheaterSeedType const & seed : _Seeds) {
		if (stricmp(seed.Name, IniName) == 0) {
			Root = seed.Root;
			IsoRoot = seed.IsoRoot;
			Suffix = seed.Suffix;
			MMSuffix = seed.MMSuffix;
			ImageLetter = seed.ImageLetter;
			IsArctic = seed.IsArctic;
			IsIceGrowth = seed.IsIceGrowth;
			LowRadarBrightness = seed.LowRadarBrightness;
			HighRadarBrightness = seed.HighRadarBrightness;
			break;
		}
	}

	if (listed) {
		Theaters.Add(this);
	}
}


TheaterClass::~TheaterClass(void)
{
	Theaters.Delete(this);
}


/// <summary>
/// Converts a theater name into a theater index.
/// The comparison ignores case, so that a map's Theater= matches however it was written.
/// </summary>
/// <returns>Returns with the identifier of the matching theater, or THEATER_NONE if no
/// theater was declared under that name.</returns>
TheaterType TheaterClass::From_Name(char const * name)
{
	if (name != NULL) {
		for (int classid = 0; classid < Theaters.Count(); classid++) {
			if (stricmp(Theaters[classid]->Name(), name) == 0) {
				return((TheaterType)classid);
			}
		}
	}

	return(THEATER_NONE);
}


/// <summary>
/// Fetches the theater declared under the name given, creating it if there is none.
/// </summary>
/// <returns>Returns with the theater, or NULL if the name was the "none" placeholder.</returns>
TheaterClass * TheaterClass::Find_Or_Make(char const * name)
{
	return(TFind_Or_Make(name, Theaters));
}


/// <summary>
/// Fetches the theater the index names.
/// An index outside the declared list yields a theater naming no archive and no suffix, so
/// a caller composing an artwork name gets a plain one rather than reading past the list.
/// </summary>
TheaterClass const & TheaterClass::As_Reference(TheaterType theater)
{
	static TheaterClass const _unknown(NULL, false);

	if ((unsigned)theater >= (unsigned)Theaters.Count()) {
		return(_unknown);
	}

	return(*Theaters[theater]);
}


/// <summary>
/// Declares the two theaters Tiberian Sun hard-coded, in their original order.
/// This is what a game whose rules declare no theater list plays with.
/// </summary>
void TheaterClass::One_Time(void)
{
	for (TheaterSeedType const & seed : _Seeds) {
		if (From_Name(seed.Name) == THEATER_NONE) {
			new TheaterClass(seed.Name);
		}
	}
}


void TheaterClass::Clear(void)
{
	while (Theaters.Count() > 0) {
		delete Theaters[0];
	}
}


/// <summary>
/// Reads this theater's settings from the section carrying its own name.
/// </summary>
/// <returns>bool; Was a section for this theater present?</returns>
bool TheaterClass::Read_INI(CCINIClass const & ini)
{
	if (!ini.Is_Present(Name())) {
		return(false);
	}

	ini.Get_String(Name(), "Root", Root);
	ini.Get_String(Name(), "IsoRoot", IsoRoot);
	ini.Get_String(Name(), "Suffix", Suffix);
	ini.Get_String(Name(), "MMSuffix", MMSuffix);

	TStringID<2> letter;
	if (ini.Get_String(Name(), "ImageLetter", "", letter) > 0) {
		ImageLetter = (char)std::toupper((unsigned char)letter[0]);
	}

	IsArctic = ini.Get_Bool(Name(), "IsArctic", IsArctic);
	IsIceGrowth = ini.Get_Bool(Name(), "IsIceGrowthEnabled", IsIceGrowth);
	LowRadarBrightness = (float)ini.Get_Float(Name(), "LowRadarBrightness", LowRadarBrightness);
	HighRadarBrightness = (float)ini.Get_Float(Name(), "HighRadarBrightness", HighRadarBrightness);
	return(true);
}
