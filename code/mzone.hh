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
**	The map is prescanned to mark of movement zones according to certain
**	movement characteristics. This enum specifies those characteristics
**	and movement zones kept track of.
*/
enum MZoneType {
	MZONE_NONE=-1,

	MZONE_NORMAL,				// Normal terrestrial objects (can't crush walls).
	MZONE_CRUSHER,				// Can crush crushable wall types.
	MZONE_DESTROYER,			// Can destroy walls.
	MZONE_AMPHIBIOUS_DESTROYER,
	MZONE_AMPHIBIOUS_CRUSHER,
	MZONE_AMPHIBIOUS,			// Water based objects.
	MZONE_SUBTERANNEAN,
	MZONE_INFANTRY,
	MZONE_INFANTRY_DESTROYER,
	MZONE_FLYER,

	MZONE_COUNT,
	MZONE_FIRST=0,
};

#define	MZONEF_NORMAL					(1<<MZONE_NORMAL)
#define	MZONEF_CRUSHER					(1<<MZONE_CRUSHER)
#define	MZONEF_DESTROYER				(1<<MZONE_DESTROYER)
#define	MZONEF_AMPHIBIOUS_DESTROYER		(1<<MZONE_AMPHIBIOUS_DESTROYER)
#define	MZONEF_AMPHIBIOUS_CRUSHER		(1<<MZONE_AMPHIBIOUS_CRUSHER)
#define	MZONEF_AMPHIBIOUS				(1<<MZONE_AMPHIBIOUS)
#define	MZONEF_SUBTERANNEAN				(1<<MZONE_SUBTERANNEAN)
#define	MZONEF_INFANTRY					(1<<MZONE_INFANTRY)
#define	MZONEF_INFANTRY_DESTROYER		(1<<MZONE_INFANTRY_DESTROYER)
#define	MZONEF_FLYER					(1<<MZONE_FLYER)
#define	MZONEF_ALL						(MZONEF_NORMAL|MZONEF_CRUSHER|MZONEF_DESTROYER|MZONEF_AMPHIBIOUS_DESTROYER| \
										MZONEF_AMPHIBIOUS_CRUSHER|MZONE_AMPHIBIOUS|MZONEF_SUBTERANNEAN|MZONEF_INFANTRY| \
										MZONEF_INFANTRY_DESTROYER|MZONEF_FLYER)
