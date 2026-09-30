/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "_mixfile.h"

template<class T> class DynamicVectorClass;

enum {
	NSEL_EXIT,
	NSEL_START_NEW_GAME,
	NSEL_LOAD_MISSION,
	NSEL_LAN,
	NSEL_INTERNET,
	NSEL_SERIAL_MODEM,	// retired; slot kept to keep the button indices aligned
	NSEL_SKIRMISH,
	NSEL_WDT,
	NSEL_OPTIONS,
	NSEL_9,
	NSEL_INTRO,
	NSEL_VERSION,
	NSEL_VIEW_CREDITS,
	NSEL_OLD_MENU,

	GMENU_TIBSUN = 100,
	GMENU_FIRESTORM = 101,
	GMENU_BACK = 102
#ifdef __ANDROID__
	, NSEL_ANDROID_IMPORT = 200
#endif
};

class NewMenuClass
{
	public:
		NewMenuClass(void);
		~NewMenuClass(void);
		int Process_Game_Select(void);

	private:
		static __forceinline int Game_Select_Loop(NewMenuClass * menu);
		int Display_Game_Select_Menu(char const * section);
		int Display_Menu(char const * section, DynamicVectorClass<int> & options);
		int Select_Game_Type(void);
		int Display_Tiberian_Sun_Menu(void);
		int Display_Firestorm_Menu(void);

	public:
		/*
		 * This points to the mixfile that holds the graphical menu artwork, attached for as
		 * long as this object lives. If it is NULL, then the artwork was never installed and
		 * the game falls back to the old menu system.
		 */
		MFCD * MixFile;

		/*
		 * This specifies which main menu the player is looking at -- 0 for Tiberian Sun and
		 * 1 for Firestorm. If -1, then neither has been chosen yet and the game select page
		 * is showing instead.
		 */
		int GameMode;

		/*
		 * This is the name of the title page picture that the menus draw themselves over.
		 * Each menu page adopts whichever one it was described with, so that the backdrop
		 * changes along with the page.
		 */
		char * Background;
};

NewMenuClass * Get_New_Menu(void);
void Draw_Menu_Background(void);

extern DynamicVectorClass<int> NewMenuOptions;
