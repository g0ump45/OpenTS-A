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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /Commando/Library/HSV.H                                     $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

class RGBClass;
class HSVClass;

/*
**	Each color entry is represented by this class. It holds the values for the color
**	attributes. The values are recorded in a range from 0 to 255 with 255 being the
**	maximum.
*/
class HSVClass
{
	private:
		static HSVClass const BlackColor;

	public:
		HSVClass(void) : Hue(0), Saturation(0), Value(0) {};
		HSVClass(unsigned char hue, unsigned char saturation, unsigned char value) :
				Hue(hue),
				Saturation(saturation),
				Value(value)
			{};
		operator RGBClass (void) const;

		bool operator==(const HSVClass &that) const { return(Hue == that.Hue && Saturation == that.Saturation && Value == that.Value); }
		bool operator!=(const HSVClass &that) const { return(Hue != that.Hue || Saturation != that.Saturation || Value != that.Value); }

		enum {
			MAX_VALUE=255
		};

		void Adjust(int ratio, HSVClass const & hsv);
		int Difference(HSVClass const & hsv) const;
		int Get_Hue(void) const {return(Hue);};
		int Get_Saturation(void) const {return(Saturation);};
		int Get_Value(void) const {return(Value);};
		void Set_Hue(unsigned char value) {Hue = value;}
		void Set_Saturation(unsigned char value) {Saturation = value;}
		void Set_Value(unsigned char value) {Value = value;}

	private:
		unsigned char Hue;
		unsigned char Saturation;
		unsigned char Value;
};
