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

/* $Header: /CounterStrike/EDIT.H 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : EDIT.H                                                       *
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

#include "control.h"

#include "dialog.hh"

class EditClass : public ControlClass
{
		typedef ControlClass BASECLASS;

	public:
		enum EditStyle {
			ALPHA			=0x0001,    // Edit accepts alphabetic characters.
			NUMERIC		=0x0002,        // Edit accepts numbers.
			MISC			=0x0004,    // Edit accepts misc graphic characters.
			UPPERCASE	=0x0008,        // Force to upper case.
			ALPHANUMERIC=(int)ALPHA|(int)NUMERIC|(int)MISC
		};

		EditClass (int id, char * text, int max_len, TextPrintType flags, int x, int y, int w=-1, int h=-1, EditStyle style=ALPHANUMERIC);
		virtual ~EditClass(void) override;

		virtual void Set_Focus(void) override;
		virtual int  Draw_Me(int forced) override;
		virtual void Set_Text(char * text, int max_len);
		virtual char * Get_Text(void) {return(String);};
		void Set_Color (int color) { Color = color; }

		void Set_Read_Only(int rdonly) {IsReadOnly = rdonly;}

	protected:

		/*
		**	These are the text size and style flags to be used when displaying the text
		**	of the edit gadget.
		*/
		TextPrintType TextFlags;

		/*
		**	Input flags that control what characters are allowed in the string.
		*/
		EditStyle EditFlags;

		/*
		**	Pointer to text staging buffer and the maximum length of the string it
		**	can contain.
		*/
		char *String;
		int MaxLength;

		/*
		**	This is the current length of the string. This length will never exceed the
		**	MaxLength allowed.
		*/
		int Length;

		/*
		**	This is the desired color of the edit control.
		*/
		int Color;

		virtual int Action (unsigned flags, KeyNumType &key) override;
		virtual void Draw_Background(void);
		virtual void Draw_Text(char const * text);
		virtual bool Handle_Key(KeyASCIIType ascii);

	private:
		int IsReadOnly;
};
