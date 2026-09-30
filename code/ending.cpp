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

/* $Header: /CounterStrike/ENDING.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : ENDING.H                                                     *
 *                                                                                             *
 *                   Programmer : Barry W. Green                                               *
 *                                                                                             *
 *                   Start Date : July 10, 1995                                                *
 *                                                                                             *
 *                  Last Update : July 10, 1995 [BWG]                                          *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "ending.h"


/// <summary>
/// Plays the ending movies for GDI players.
/// This routine is called when the GDI campaign has been won. It runs the victory
/// movies, presents the score screen, and closes with the teaser for what comes next.
/// </summary>
void GDI_Ending(void)
{
#ifdef NEVER
	if (TempleIoned) {
		Play_Movie("GDIFINB");
	} else {
		Play_Movie("GDIFINA");
	}

	Score.Presentation();

	if (TempleIoned) {
		Play_Movie("GDIEND2");
	} else {
		Play_Movie("GDIEND1");
	}
	Play_Movie("CC2TEASE");
#endif
}


/***********************************************************************************************
 * Nod_Ending -- play ending movies for Nod players                                            *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   7/10/1995 BWG : Created.                                                                  *
 *=============================================================================================*/
void Nod_Ending(void)
{
#ifdef NEVER
	static char const _tanpal[]={0x0,0x0,0xED,0x0,0x2C,0x0,0xFB,0x0,0xFD,0x0,0x0,0x0,0x0,0x0,0x52,0x0};

	char fname[12];
	char * satpic = new char[64000];
	int oldfontxspacing = FontXSpacing;
	void const * oldfont;

	Score.Presentation();

	oldfont = Set_Font(ScoreFontPtr);

	void * localpal = Load_Alloc_Data(CCFileClass("SATSEL.PAL"));
	Load_Uncompress(CCFileClass("SATSEL.CPS"), HidPage, HidPage);
	memcpy(satpic, HidPage.Get_Buffer(), 64000);

	void * kanefinl = Load_Sample("KANEFINL.AUD");
	void * loopie6m = Load_Sample("LOOPIE6M.AUD");

	Play_Movie("NODFINAL", THEME_NONE, false);

	Hide_Mouse();
	Wait_Vert_Blank(VertBlank);
	Set_Palette(localpal);
	memcpy(SeenBuff.Get_Buffer(), satpic, 64000);
	Show_Mouse();

	Keyboard->Clear();
	Play_Sample(kanefinl, 255, 128);
	Play_Sample(loopie6m, 255, 128);

	bool mouseshown = false;
	bool done = false;
	int selection = 1;
	bool printedtext = false;
	while (!done) {
		if (!printedtext && !Is_Sample_Playing(kanefinl)) {
			printedtext++;
			Alloc_Object(new ScorePrintClass(Text_String(TXT_SEL_TARGET), 0, 180, _tanpal));
			mouseshown = true;
			Show_Mouse();
		}
		Call_Back_Delay(1);
		if (!Keyboard->Check()) {
			if (!Is_Sample_Playing(loopie6m))	Play_Sample(loopie6m, 255, 128);
		} else {
			if (Is_Sample_Playing(kanefinl)) {
				Clear_KeyBuffer();
			} else {
				int key = Keyboard->Get();
				if ((key & 0xFF) == KN_LMOUSE && !(key & KN_RLSE_BIT)) {
					int mousex = MouseQX;
					int mousey = MouseQY;
					if (mousey >= 22 && mousey <= 177) {
						done++;
						if (mousex <  160 && mousey <  100) selection = 2;
						if (mousex <  160 && mousey >= 100) selection = 3;
						if (mousex >= 160 && mousey >= 100) selection = 4;
					}
				}
			}
		}
	}
	if (mouseshown) Hide_Mouse();
	delete satpic;

/* get rid of all the animating objects */
	for (int i = 0; i < MAXSCOREOBJS; i++) if (ScoreObjs[i]) {
		delete ScoreObjs[i];
		ScoreObjs[i] = 0;
	}
	// erase the "choose a target" text
	SeenBuff.Fill_Rect(0, 180, 319, 199, 0);

	Hide_Mouse();
	Keyboard->Clear();

	Set_Font(oldfont);
	FontXSpacing = oldfontxspacing;
	Free_Sample(kanefinl);
	Free_Sample(loopie6m);

	sprintf(fname, "NODEND%d", selection);
	PreserveVQAScreen = 1;
	Play_Movie(fname);

	Play_Movie("CC2TEASE");
#endif
}
