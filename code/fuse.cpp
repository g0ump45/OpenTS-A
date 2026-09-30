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

/* $Header: /CounterStrike/FUSE.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : FUSE.CPP                                                     *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : April 24, 1994                                               *
 *                                                                                             *
 *                  Last Update : October 17, 1994   [JLB]                                     *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   FuseClass::Arm_Fuse -- Sets up fuse for detonation check.                                 *
 *   FuseClass::Fuse_Checkup -- Determines if the fuse triggers.                               *
 *   FuseClass::Fuse_Read -- Reads the fuse class data from the save game file.                *
 *   FuseClass::Fuse_Write -- Writes the fuse data to the save game file.                      *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "fuse.h"

#include <algorithm>


/***********************************************************************************************
 * FuseClass::FuseClass -- Constructor.                                                        *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   06/27/1995 BRR : Created.  Gosh, what a lotta work.                                       *
 *=============================================================================================*/
FuseClass::FuseClass(void) :
	Timer(0),
	Arming(0),
	HeadTo(0,0,0),
	Proximity(0)
{
}


/***********************************************************************************************
 * FuseClass::Arm_Fuse -- Sets up fuse for detonation check.                                   *
 *                                                                                             *
 *    This starts a fuse. Fuses are proximity detonation variety but                           *
 *    can be modified to have a minimum time to elapse before detonation                       *
 *    and a maximum time to exist before detonation. Typically, the                            *
 *    timing values are used for missiles that have a minimum arming                           *
 *    distance and a limited amount of fuel.                                                   *
 *                                                                                             *
 * INPUT:   location -- The coordinate where the projectile start. This                        *
 *                      is needed for proper proximity tracking.                               *
 *                                                                                             *
 *          target   -- The actual impact point. Fuses are based on real                       *
 *                      word coordinates.                                                      *
 *                                                                                             *
 *          time     -- The maximum time that the fuse may work before                         *
 *                      explosion is forced.                                                   *
 *                                                                                             *
 *          arming   -- The minimum time that must elapse before the                           *
 *                      fuse may explode.                                                      *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/24/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
void FuseClass::Arm_Fuse(Coord const & location, Coord const & target, int arming, int timeto)
{
	timeto = std::max(timeto, arming);
	Timer = timeto;
	Arming = arming;
	HeadTo = target;
	Proximity = location.Distance_To(target);
}


/***********************************************************************************************
 * FuseClass::Fuse_Checkup -- Determines if the fuse triggers.                                 *
 *                                                                                             *
 *    This will process the fuse and update the internal clocks as well                        *
 *    as check to see if the fuse should trigger (explode) or not.                             *
 *                                                                                             *
 * INPUT:   newlocation -- The new location of the fuse. This is needed                        *
 *                         to determine proximity explosions.                                  *
 *                                                                                             *
 * OUTPUT:  bool; Was the fuse triggered to explode now?                                       *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/24/1994 JLB : Created.                                                                 *
 *=============================================================================================*/
FuseResultType FuseClass::Fuse_Checkup(Coord const & newlocation)
{
	int	proximity;

	/*
	**	Always decrement the fuse timer.
	*/
	//if (Timer) Timer--;

	/*
	**	If the arming countdown has not expired, then do nothing.
	*/
	if (Arming) {
		return(FUSE_WAIT);
	} else {

		/*
		**	If the timer has run out, then the warhead explodes.
		*/
		//if (!Timer) return(true);

		proximity = newlocation.Distance_To(HeadTo) / 2;
		if (proximity < 0x0010*2) return(FUSE_EXPLODE_CLOSE);

		if (proximity < CELL_LEPTON_W && proximity > Proximity) {
			return(FUSE_EXPLODE_FAR);
		}
		Proximity = proximity;
	}
	return(FUSE_WAIT);
}
