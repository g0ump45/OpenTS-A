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
**	The various aircraft types are enumerated here. These include helicopters
**	as well as traditional aircraft.
*/
enum AircraftType {
	AIRCRAFT_NONE=-1,

	AIRCRAFT_ORCAB,
	AIRCRAFT_DSHP,
	AIRCRAFT_DPOD,
	AIRCRAFT_SCRIN,
	AIRCRAFT_APACHE,
	AIRCRAFT_ORCATRAN,
	AIRCRAFT_TRNSPORT,
	AIRCRAFT_ORCA,

	AIRCRAFT_COUNT,
	AIRCRAFT_FIRST=0
};
