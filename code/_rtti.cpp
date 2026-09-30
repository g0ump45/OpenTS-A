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

#include "_rtti.h"

#include "object.h"


struct {
	char const *Name;
	RTTIType RTTI;
} RTTIs[RTTI_COUNT] = {
	{ "<none>",				RTTI_NONE },
	{ "Unit",				RTTI_UNIT },
	{ "Aircraft",			RTTI_AIRCRAFT },
	{ "AircraftType",		RTTI_AIRCRAFTTYPE },
	{ "Anim",				RTTI_ANIM },
	{ "AnimType",			RTTI_ANIMTYPE },
	{ "Building",			RTTI_BUILDING },
	{ "BuildingType",		RTTI_BUILDINGTYPE },
	{ "Bullet",				RTTI_BULLET },
	{ "BulletType",			RTTI_BULLETTYPE },
	{ "Campaign",			RTTI_CAMPAIGN },
	{ "Cell",				RTTI_CELL },
	{ "Factory",			RTTI_FACTORY },
	{ "House",				RTTI_HOUSE },
	{ "HouseType",			RTTI_HOUSETYPE },
	{ "Infantry",			RTTI_INFANTRY },
	{ "InfantryType",		RTTI_INFANTRYTYPE },
	{ "Isotile",			RTTI_ISOTILE },
	{ "IsotileType",		RTTI_ISOTILETYPE },
	{ "Light",				RTTI_LIGHT },
	{ "Overlay",			RTTI_OVERLAY },
	{ "OverlayType",		RTTI_OVERLAYTYPE },
	{ "Particle",			RTTI_PARTICLE },
	{ "ParticleType",		RTTI_PARTICLETYPE },
	{ "ParticleSystem",		RTTI_PARTICLESYSTEM },
	{ "ParticleSystemType",	RTTI_PARTICLESYSTEMTYPE },
	{ "Script",				RTTI_SCRIPT },
	{ "ScriptType",			RTTI_SCRIPTTYPE },
	{ "Side",				RTTI_SIDE },
	{ "Smudge",				RTTI_SMUDGE },
	{ "SmudgeType",			RTTI_SMUDGETYPE },
	{ "Special",			RTTI_SPECIAL },
	{ "SuperWeaponType",	RTTI_SUPERWEAPONTYPE },
	{ "TaskForce",			RTTI_TASKFORCE },
	{ "Team",				RTTI_TEAM },
	{ "TeamType",			RTTI_TEAMTYPE },
	{ "Terrain",			RTTI_TERRAIN },
	{ "TerrainType",		RTTI_TERRAINTYPE },
	{ "Trigger",			RTTI_TRIGGER },
	{ "TriggerType",		RTTI_TRIGGERTYPE },
	{ "UnitType",			RTTI_UNITTYPE },
	{ "VoxelAnim",			RTTI_VOXELANIM },
	{ "VoxelAnimType",		RTTI_VOXELANIMTYPE },
	{ "Wave",				RTTI_WAVE },
	{ "Tag",				RTTI_TAG },
	{ "TagType",			RTTI_TAGTYPE },
	{ "Tiberium",			RTTI_TIBERIUM },
	{ "Action",				RTTI_ACTION },
	{ "Event",				RTTI_EVENT },
	{ "WeaponType",			RTTI_WEAPONTYPE },
	{ "WarheadType",		RTTI_WARHEADTYPE },
	{ "Waypoint",			RTTI_WAYPOINT },
	{ "Abstract",			RTTI_ABSTRACT },
	{ "Tube",				RTTI_TUBE },
	{ "LightSource",		RTTI_LIGHTSOURCE },
	{ "EMPulse",			RTTI_EMPULSE },
	{ "TacticalMap",		RTTI_TACTICALMAP },
	{ "SuperWeapon",		RTTI_SUPERWEAPON },
	{ "AITrigger",			RTTI_AITRIGGER },
	{ "AITriggerType",		RTTI_AITRIGGERTYPE },
	{ "Neuron",				RTTI_NEURON },
	{ "FoggedObject",		RTTI_FOGGEDOBJECT },
	{ "AlphaShape",			RTTI_ALPHASHAPE },
	{ "VeinholeMonster",	RTTI_VEINHOLEMONSTER },
};

static char UNKNOWN_RTTI_NAME[] = { "Unknown" };


/// <summary>
/// Fetches the readable name for an RTTI type.
/// Use this routine whenever an object type must be recorded in human readable form --
/// when storing it in an INI database, or when logging object state for the sync debugger.
/// </summary>
/// <returns>Returns with the name of the RTTI type specified. If the type has no name
/// assigned, then "Unknown" is returned.</returns>
char const *Name_From_RTTI(RTTIType rtti)
{
	for (int i = 0; i < RTTI_COUNT; i++) {
		if (RTTIs[i].RTTI == rtti) {
			return(RTTIs[i].Name);
		}
	}
	return(UNKNOWN_RTTI_NAME);
}


/// <summary>
/// Converts an RTTI name back into its RTTI type.
/// This routine is the counterpart to Name_From_RTTI and is used when an object type is
/// read back out of an INI database. The name comparison ignores case.
/// </summary>
/// <returns>Returns with the RTTI type that the name refers to, or RTTI_NONE if the name
/// is not recognized.</returns>
RTTIType RTTI_From_Name(char const *name)
{
	for (int i = 0; i < RTTI_COUNT; i++) {
		if (!strcasecmp(RTTIs[i].Name, name)) {
			return(RTTIs[i].RTTI);
		}
	}
	return(RTTI_NONE);
}


/***********************************************************************************************
 * As_Techno -- Converts a target value into a TechnoClass pointer.                            *
 *                                                                                             *
 *    This routine will take the target value specified and convert it into a TechnoClass      *
 *    pointer if the target represents an object that has a TechnoClass.                       *
 *                                                                                             *
 * INPUT:   target   -- The target value to convert into a TechnoClass pointer.                *
 *                                                                                             *
 * OUTPUT:  Returns with a pointer to the associated object's TechnoClass. If the target       *
 *          cannot be converted into a TechnoClass pointer, then NULL is returned.             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/02/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
template <>
TechnoClass const * Dynamic_Cast<TechnoClass const *>(AbstractClass const * target)
{
	if (target != NULL) {
		RTTIType rtti = target->RTTI;
		switch (rtti) {
			case RTTI_INFANTRY:
				return((TechnoClass *)target);
			case RTTI_UNIT:
				return((TechnoClass *)target);
			case RTTI_BUILDING:
				return((TechnoClass *)target);
			case RTTI_AIRCRAFT:
				return((TechnoClass *)target);
		}
	}
	return(NULL);
}


/// <summary>
/// Converts an abstract object pointer into a TechnoClass pointer.
/// This routine will take the object specified and convert it into a TechnoClass pointer
/// if that object is one of the techno derived types. It is the non-const counterpart to
/// the specialization above.
/// </summary>
/// <returns>Returns with a pointer to the associated object's TechnoClass. If the object
/// cannot be converted into a TechnoClass pointer, then NULL is returned.</returns>
template <>
TechnoClass * Dynamic_Cast<TechnoClass *>(AbstractClass * target)
{
	if (target != NULL) {
		RTTIType rtti = target->RTTI;
		switch (rtti) {
			case RTTI_INFANTRY:
				return((TechnoClass *)target);
			case RTTI_UNIT:
				return((TechnoClass *)target);
			case RTTI_BUILDING:
				return((TechnoClass *)target);
			case RTTI_AIRCRAFT:
				return((TechnoClass *)target);
		}
	}
	return(NULL);
}
