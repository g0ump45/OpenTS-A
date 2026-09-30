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

/* $Header: /CounterStrike/CARRY.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : CARRY.H                                                      *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 02/26/96                                                     *
 *                                                                                             *
 *                  Last Update : February 26, 1996 [JLB]                                      *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "coord.h"
#include "link.h"

#include "house.hh"
#include "infantry.hh"
#include "rtti.hh"
#include "struct.hh"
#include "unit.hh"


class TechnoClass;


class CarryoverClass : public LinkClass {
		typedef LinkClass BASECLASS;

	public:
		CarryoverClass(TechnoClass * techno = 0);

		bool Create(void) const;

	protected:
		/*
		**	What type of object this is.
		*/
		RTTIType RTTI;

		/*
		**	This is the object type that is to be carried over. The exact nature of
		**	this type depends on the RTTI value. Only certain object types are
		**	recorded.
		*/
		union {
			StructType Building;
			UnitType Unit;
			InfantryType Infantry;
		} Type;

		/*
		**	The location of the object.
		*/
		Cell CellID;

		/*
		**	The strength of the object at the time is was recorded.
		*/
		int Strength;

		/*
		**	This is the owner of the object.
		*/
		HousesType House;
};
