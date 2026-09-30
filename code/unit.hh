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

#pragma once

/**********************************************************************
**	The game units are enumerated here. These include not only traditional
**	vehicles, but also hovercraft and gunboats.
*/
enum UnitType {
	UNIT_NONE=-1,

	UNIT_MCV,
	UNIT_HARV,
	UNIT_APC,
	UNIT_4TNK,
	UNIT_MMCH,
	UNIT_BIKE,
	UNIT_SAPC,
	UNIT_SONIC,
	UNIT_CAR,
	UNIT_BUS,
	UNIT_STNK,
	UNIT_WINI,
	UNIT_PICK,
	UNIT_ART2,
	UNIT_TTNK,
	UNIT_HMEC,
	UNIT_SMECH,
	UNIT_HVR,
	UNIT_LPST,
	UNIT_REPAIR,
	UNIT_HORV,
	UNIT_LOCOMOTIVE,
	UNIT_TRAINCAR,
	UNIT_SUBTANK,
	UNIT_BGGY,
	UNIT_JEEP,
	UNIT_TRUCKA,
	UNIT_TRUCKB,
	UNIT_VISC_SML,
	UNIT_VISC_LRG,
	UNIT_ICBM,
	UNIT_CARGOCAR,
	UNIT_WEED,
	UNIT_GHUNTER,
	UNIT_NHUNTER,

	/*
	 * Firestorm additions start here
	 */
	UNIT_REAPER,
	UNIT_JFISH,
	UNIT_JUGG,
	UNIT_LIMPET,
	UNIT_MOBILEMP,
	UNIT_SGEN,
	UNIT_MOBWARG,
	UNIT_MOBWARN,
	UNIT_FLMTNK,
	UNIT_DEFENDER,
	UNIT_CMOBILEMP,

	UNIT_COUNT,
	UNIT_FIRST=0
};
