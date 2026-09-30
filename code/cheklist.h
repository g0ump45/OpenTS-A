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

/* $Header: /CounterStrike/CHEKLIST.H 1     3/03/97 10:24a Joe_bostic $ */
/***************************************************************************
 **   C O N F I D E N T I A L --- W E S T W O O D    S T U D I O S        **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : Command & Conquer                        *
 *                                                                         *
 *                    File Name : CHEKLIST.H                               *
 *                                                                         *
 *                   Programmer : Bill Randolph                            *
 *                                                                         *
 *                   Start Date : February 16, 1995                        *
 *                                                                         *
 *                  Last Update : February 16, 1995   [BR]                 *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * This class behaves just like the standard list box, except that if the  *
 * first character of a list entry is a space, clicking on it toggles the  *
 * space with a check-mark ('\3').  This makes each entry in the list box  *
 * "toggle-able".                                                          *
 *-------------------------------------------------------------------------*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "list.h"

class ShapeSet;

class CheckObject
{
	public:
		CheckObject(char const * text = 0, bool checked=false) :
			Text(text),
			IsChecked(checked)
		{};

		char const * Text;
		bool IsChecked;
};


class CheckListClass : public ListClass
{
		typedef ListClass BASECLASS;

	public:
		/*
		**	Constructor/Destructor
		*/
		CheckListClass(int id, int x, int y, int w, int h, TextPrintType flags,
			ShapeSet const * up, ShapeSet const * down);
		~CheckListClass(void);

		virtual int Add_Item(int text) override {return(BASECLASS::Add_Item(text));}
		virtual int Add_Item(char const * text) override;
		virtual char const * Current_Item(void) const override;
		virtual char const * Get_Item(int index) const override;
		virtual void Remove_Item(char const * text) override;
		virtual void Remove_Item(int text) override {BASECLASS::Remove_Item(text);}
		virtual void Set_Selected_Index(char const * text) override;
		virtual void Set_Selected_Index(int index) override {BASECLASS::Set_Selected_Index(index);};

		/*
		**	Checkmark utility functions
		*/
		void Check_Item(int index, bool checked);   // sets checked state of item
		bool Is_Checked(int index) const;           // gets checked state of item

		void Set_Read_Only(bool rdonly) {IsReadOnly = rdonly;}

		/*
		**	This defines the ASCII value of the checkmark character & non-checkmark
		**	character.
		*/
		enum CheckListClassEnum {
			CHECK_CHAR = '\3',
			UNCHECK_CHAR = ' '
		};

	protected:
		virtual int Action(unsigned flags, KeyNumType &key) override;
		virtual void Draw_Entry(int index, int x, int y, int width, int selected) override;

	private:
		bool IsReadOnly;
};
