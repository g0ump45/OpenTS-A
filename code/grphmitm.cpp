/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "grphmitm.h"

#include "ini.h"
#include "mschoice.h"

GraphicMenuItem * GM_Read_Image_Item(const char * name, INIClass const & ini, MSEngine & engine, Point2D & image_size);
GraphicMenuItem * GM_Read_Shortcut_Item(const char * name, INIClass const & ini);
GraphicMenuItem * GM_Read_Version_Item(const char * name, INIClass const & ini, MSEngine & engine);


/// <summary>
/// Creates a graphic menu item from its INI description.
/// This routine looks at the type recorded in the section specified and hands the work
/// to the reader for that kind of item. Whatever item comes back is given the select
/// sound the section names, if it names one.
/// </summary>
/// <param name="name">The INI section that describes the item to create.</param>
/// <param name="ini">The INI database to read the description from.</param>
/// <param name="engine">The menu engine that the new item will belong to.</param>
/// <param name="image_size">The screen offset of the menu backdrop. Item positions are
/// relative to it.</param>
/// <returns>Returns with a pointer to the item created. Otherwise, NULL is returned.</returns>
GraphicMenuItem *GM_Create_Item_From_INI(const char * name, INIClass const & ini, MSEngine & engine, Point2D & image_size)
{
	char type[256];
	ini.Get_String(name, "Type", "", type, sizeof(type));
	GraphicMenuItem * item = NULL;

	if (strcmpi(type, "Image") == 0) {
		item = GM_Read_Image_Item(name, ini, engine, image_size);
	} else if (strcmpi(type, "Shortcut") == 0) {
		item = GM_Read_Shortcut_Item(name, ini);
	} else if (strcmpi(type, "Version") == 0) {
		item = GM_Read_Version_Item(name, ini, engine);
	}

	if (item != NULL) {
		char sound[64];
		if (ini.Get_String(name, "SelectSound", "", sound, sizeof(sound)) > 0) {
			item->Set_Select_Sound(new MSSfxEntry("SelectSound", sound));
		}
	}
	return(item);
}


/// <summary>
/// Constructor for a graphic menu item.
/// The item starts out enabled, unhighlighted, and with no select sound of its own.
/// </summary>
/// <param name="id">The identifier the menu uses to tell this item from its fellows.</param>
GraphicMenuItem::GraphicMenuItem(int id) :
	ID(id),
	Selected(false),
	Enabled(true),
	SelectSound(NULL)
{
}


/// <summary>
/// Destructor for a graphic menu item.
/// This routine disposes of the select sound that was handed to the item, since the
/// item takes ownership of it.
/// </summary>
GraphicMenuItem::~GraphicMenuItem(void)
{
	if (SelectSound != NULL) {
		delete SelectSound;
	}
}


/// <summary>
/// Sets whether this menu item is the highlighted one.
/// The item is told of the change through On_Selected_Change, and only when the state
/// really differs, so derived items never see a redundant notification.
/// </summary>
/// <param name="selected">Should the item become the highlighted one?</param>
void GraphicMenuItem::Set_Selected(bool selected)
{
	if (selected != Selected) {
		Selected = selected;
		On_Selected_Change(selected);
	}
}


/// <summary>
/// Sets whether this menu item may be chosen.
/// The item is told of the change through On_Enabled_Change, and only when the state
/// really differs, so derived items never see a redundant notification.
/// </summary>
/// <param name="enabled">Should the item be available for use?</param>
void GraphicMenuItem::Set_Enabled(bool enabled)
{
	if (enabled != Enabled) {
		Enabled = enabled;
		On_Enabled_Change(enabled);
	}
}


/// <summary>
/// Handles a change to this item's selected state.
/// The base item has nothing to do. Derived items override this routine when they must
/// adjust their appearance as the menu highlight moves on or off them.
/// </summary>
void GraphicMenuItem::On_Selected_Change(bool)
{
	//nothing
}


/// <summary>
/// Handles a change to this item's enabled state.
/// The base item has nothing to do. Derived items override this routine when they must
/// swap artwork or drop a highlight as they are turned on and off.
/// </summary>
void GraphicMenuItem::On_Enabled_Change(bool)
{
	//nothing
}


/// <summary>
/// Is the mouse hovering over this menu item?
/// The base item cannot be pointed at and always answers false. Items that occupy a
/// region of the screen override this routine to test against their own bounds.
/// </summary>
/// <param name="mouse">The current mouse position.</param>
bool GraphicMenuItem::Is_Mouse_Over(Point2D const & mouse)
{
	return(false);
}


/// <summary>
/// Does this menu item answer to the key specified?
/// The base item claims no keys at all. Items that carry a keyboard shortcut override
/// this routine so the menu knows where to send the key press.
/// </summary>
/// <param name="key">The key that was pressed.</param>
bool GraphicMenuItem::Is_Input_Key(KeyNumType key)
{
	return(false);
}


/// <summary>
/// Performs whatever this menu item was put on the menu to do.
/// The base item merely plays its select sound. Derived items override this routine
/// and chain back to it so that the sound is still heard.
/// </summary>
/// <param name="engine">The menu engine that is running this item's menu.</param>
void GraphicMenuItem::Action(MSEngine * engine)
{
	if (SelectSound != NULL) {
		SelectSound->Play();
	}
}
