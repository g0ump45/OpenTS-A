/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "grphmsct.h"

#include "grphmenu.h"
#include "grphmitm.h"
#include "grphmsct.h"
#include "ini.h"
#include "keyboard.h"


unsigned int GM_Build_Key(const char *list);

/// <summary>
/// Creates a shortcut menu item from the INI database.
/// This routine is used while a graphic menu is being built up from its INI
/// description. The section must name the menu item it stands for; the key list is
/// optional and an item with no keys simply never answers to the keyboard.
/// </summary>
/// <param name="name">The INI section to read the item from.</param>
/// <returns>Returns with a pointer to the item created. If the section does not identify a
/// menu item, NULL is returned.</returns>
GraphicMenuItem * GM_Read_Shortcut_Item(const char * name, INIClass const & ini)
{
	int id = ini.Get_Int(name, "ID", -1);
	if (id == -1) {
		return(NULL);
	}
	char buffer[256];
	ini.Get_String(name, "Keys", "", buffer, sizeof(buffer));

	return(new GraphicMenuShortcutItem(id, buffer));
}


/// <summary>
/// Creates a shortcut item for a graphic menu.
/// The key list is split apart and each description is converted into a key code
/// that the item will answer to. Descriptions that cannot be recognized are quietly
/// discarded.
/// </summary>
/// <param name="keys">The shortcut key descriptions, separated by commas.</param>
GraphicMenuShortcutItem::GraphicMenuShortcutItem(int id, const char * keys) :
	GraphicMenuItem(id)
{
	char buffer[256];
	strncpy(buffer, keys, sizeof(buffer));
	char *tok = strtok(buffer, ",");
	while (tok != NULL) {
		unsigned int key = GM_Build_Key(tok);
		if (key != 0) {
			Shortcuts.Add(key);
		}
		tok = strtok(NULL, ",;");
	}
}


/// <summary>
/// Converts a shortcut key description into a key code.
/// This routine is used to translate the human readable key names stored in the INI
/// database into the key codes the keyboard system deals in. A leading "ctrl-",
/// "alt-", or "shift-" prefix contributes the matching modifier bit, and the
/// remainder may be either a single character or one of the recognized key names.
/// </summary>
/// <param name="list">The shortcut description to convert, modifier prefixes included.</param>
/// <returns>Returns with the key code and modifier bits. If the description could not be
/// recognized, VK_NONE is returned.</returns>
unsigned int GM_Build_Key(const char *list)
{
	static struct {
		char const * Name;
		unsigned int Key;
	} _name2key[] =	{
		{ "BACKSPACE", KN_BACKSPACE },
		{ "ESC", KN_ESC }
	};

	int modifiers = 0;
	const char *lst = list;

	if (strnicmp(lst, "ctrl-", 5) == 0) {
		modifiers |= KN_CTRL_BIT;
		lst += 5;
	}
	if (strnicmp(lst, "alt-", 4) == 0) {
		modifiers |= KN_ALT_BIT;
		lst += 4;
	}
	if (strnicmp(lst, "shift-", 6) == 0) {
		modifiers |= KN_SHIFT_BIT;
		lst += 6;
	}

	unsigned int key;
	switch (strlen(lst)) {
		case 0:
			key = 0;
			break;

		case 1:
			if (*lst >= 'a' && *lst <= 'z') {
				key = (unsigned char)(*lst - ('a' - 'A'));
			} else {
				key = (unsigned char)*lst;
			}
			break;

		default: {
			int k = -1;
			for (int i = ARRAY_SIZE(_name2key) - 1; i >= 0; i--) {
				if (stricmp(lst, _name2key[i].Name) == 0) {
					k = i;
					break;
				}
			}

			if (k >= 0) {
				key = _name2key[k].Key;
			} else {
				key = 0;
			}
			break;
		}
	}

	if (key != VK_NONE)	{
		modifiers |= key;
	} else {
		modifiers = VK_NONE;
	}
	return(modifiers);
}


/// <summary>
/// Destroys the graphic menu shortcut item.
/// The shortcut list cleans up after itself, so there is nothing left for this
/// routine to do.
/// </summary>
GraphicMenuShortcutItem::~GraphicMenuShortcutItem(void)
{
	//nothing
}


/// <summary>
/// Determines if a key press triggers this menu item.
/// This routine is called by the graphic menu when it is looking for the item that
/// should respond to a key press. A disabled item never claims a key.
/// </summary>
/// <returns>bool; Is this key one of the item's shortcuts?</returns>
bool GraphicMenuShortcutItem::Is_Input_Key(KeyNumType key)
{
	if (!Enabled) {
		return(false);
	}

	for (unsigned int shortcut : Shortcuts) {
		if (shortcut == (unsigned int)key) {
			return(true);
		}
	}

	return(false);
}
