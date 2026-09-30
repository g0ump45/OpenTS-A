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

/*************************************************************************************
 **   C O N F I D E N T I A L --- W E S T W O O D    S T U D I O S                  **
 *************************************************************************************
 *                                                                                   *
 *                 Project Name : Command & Conquer - Red Alert                      *
 *                                                                                   *
 *                    File Name : EGOS.H                                             *
 *                                                                                   *
 *                   Programmer : Steve Tall                                         *
 *                                                                                   *
 *                   Start Date : September 4th, 1996                                *
 *                                                                                   *
 *                  Last Update : September 4th, 1996 [ST]                           *
 *                                                                                   *
 *-----------------------------------------------------------------------------------*
 * Overview:                                                                         *
 *                                                                                   *
 *   Scrolling movie style credits.                                                  *
 *                                                                                   *
 *-----------------------------------------------------------------------------------*
 * Functions:                                                                        *
 *                                                                                   *
 *                                                                                   *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "dialog.hh"

class Surface;

class EgoClass {

	public:

		EgoClass (int x, int y, char *text, TextPrintType flags);
		~EgoClass (void);

		bool Scroll (int distance);
		void Render (bool fresh);
		void Wipe (Surface *background);


		char				*Text;
		int				XPos;
		int				YPos;
		TextPrintType 	Flags;
};

void Show_Who_Was_Responsible(void);
