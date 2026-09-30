/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

enum AddonType {
	ADDON_BASE_GAME,
	ADDON_FIRESTORM,
	ADDON_COUNT,

	ADDON_FIRST=0,
	ADDON_ANY=-1,
};


void Detect_Addons(void);
bool Addon_Installed(AddonType addon);
bool Addon_Enabled(AddonType addon);
void Enable_Addon(AddonType addon);
void Disable_Addon(AddonType addon);
bool Is_Required_Addon(AddonType addon);
AddonType Get_Required_Addon(void);
void Set_Required_Addon(AddonType addon);
const char *Get_Addon_Title(AddonType addon);
bool Select_Game_Type_Dialog(AddonType &type);

AddonType operator++(AddonType & val);
AddonType operator--(AddonType & val);
