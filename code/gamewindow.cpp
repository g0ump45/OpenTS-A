/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "gamewindow.h"

#include "_map.h"
#include "_surface.h"
#include "_xmouse.h"
#include "globals.h"
#include "gscreen.h"
#include "init.h"
#include "movies.h"
#include "video.h"


static bool _HandlingMouseWheel = false;


/// <summary>
/// Updates and presents the frame when the application window needs repainting.
/// </summary>
void Game_Window_On_Paint(bool update_surface)
{
	if (update_surface) {
		if (MouseCursor != NULL && VisibleSurface != NULL && HiddenSurface != NULL && CompositeSurface != NULL) {
			if (ScenarioActive == true) {
				Map.Blit_Sidebar(true);
				Update_Visible_Surface(CompositeSurface);
			} else if (Movie_Is_Playing() == true) {
				Movie_Update_Visible_Surface();
			} else {
				Update_Visible_Surface(HiddenSurface);
			}
		}
	}
	Video_Present_If_Dirty();
}


/// <summary>
/// Stops tactical scrolling from coasting after the right mouse button is released.
/// </summary>
void Game_Window_On_Right_Mouse_Up(void)
{
	Map.Set_Scroll_Coasting_Allowed(false);
}


/// <summary>
/// Applies a mouse wheel step to the sidebar.
/// </summary>
void Game_Window_On_Mouse_Wheel(int delta)
{
	if (_HandlingMouseWheel) {
		return;
	}

	_HandlingMouseWheel = true;
	Execute_Command(delta < 0 ? "SidebarDown" : "SidebarUp");
	_HandlingMouseWheel = false;
}
