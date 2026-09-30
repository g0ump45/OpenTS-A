/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "grphmitm.h"


class GraphicMenuShortcutItem : public GraphicMenuItem
{
	typedef DynamicVectorClass<unsigned int> SHORTCUT_LIST;

	public:
		GraphicMenuShortcutItem(int id, const char * keys);
		virtual ~GraphicMenuShortcutItem(void) override;
		virtual bool Is_Input_Key(KeyNumType key) override;

	private:
		/*
		 * These are the key codes, modifier bits included, that this menu item answers to.
		 * They are built from the item's key list when the menu is read in, and an item
		 * that gathered none simply never claims a key press.
		 */
		SHORTCUT_LIST Shortcuts;
};
