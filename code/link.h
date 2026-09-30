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

/* $Header: /CounterStrike/LINK.H 1     3/03/97 10:25a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : LINK.H                                                       *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 01/15/95                                                     *
 *                                                                                             *
 *                  Last Update : January 15, 1995 [JLB]                                       *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once


/*
**	This implements a simple linked list. It is possible to add, remove, and traverse the
**	list. Since this is a doubly linked list, it is possible to remove an entry from the
**	middle of an existing list.
*/
class LinkClass
{
	public:
		LinkClass(void) : Next(0), Prev(0) {};
		virtual ~LinkClass(void);

		virtual LinkClass * Get_Next(void) const;
		virtual LinkClass * Get_Prev(void) const;
		virtual LinkClass & Add(LinkClass & object);
		virtual LinkClass & Add_Tail(LinkClass & object);
		virtual LinkClass & Add_Head(LinkClass & object);
		virtual LinkClass & Head_Of_List(void);
		virtual LinkClass & Tail_Of_List(void);
		virtual void Zap(void);
		virtual LinkClass * Remove(void);

		LinkClass & operator=(LinkClass const & link);  // Assignment operator.
		LinkClass(LinkClass const & link);              // Copy constructor.

	private:
		/*
		**	Pointers to previous and next link objects in chain.
		*/
		LinkClass * Next;
		LinkClass * Prev;
};
