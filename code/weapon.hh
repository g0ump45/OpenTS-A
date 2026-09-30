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

#pragma once

/**********************************************************************
**	This enumerates the various weapon types. The weapon is characterized
**	by the projectile it launches, the damage it does, and the rate of
**	fire.
*/
enum WeaponType {
	WEAPON_NONE=-1,

	WEAPON_VULCAN2,
	WEAPON_MULTILAUNCHER,
	WEAPON_CHEMLAUNCHER,
	WEAPON_VULCANTOWER,
	WEAPON_EMPULSEWEAPON,
	WEAPON_LASERFIRE,
	WEAPON_LASERFIRE2,
	WEAPON_REDEYE2,
	WEAPON_RPGTOWER,
	WEAPON_90MM,
	WEAPON_120MMX,
	WEAPON_155MM,
	WEAPON_BOMB,
	WEAPON_PROTON,
	WEAPON_HARPYCLAW,
	WEAPON_HELLFIRE,
	WEAPON_MAMMOTHTUSK,
	WEAPON_120MM,
	WEAPON_BIKEMISSILE,
	WEAPON_HOVERMISSILE,
	WEAPON_SONICZAP,
	WEAPON_DRAGON,
	WEAPON_MECHRAILGUN,
	WEAPON_ASSAULTCANNON,
	WEAPON_REPAIRBULLET,
	WEAPON_FIREBALLLAUNCHER,
	WEAPON_RAIDERCANNON,
	WEAPON_SLIMEATTACK,
	WEAPON_SUICIDEBOMB,
	WEAPON_MINIGUN,
	WEAPON_M1CARBINE,
	WEAPON_GRENADE,
	WEAPON_BAZOOKA,
	WEAPON_HEAL,
	WEAPON_MULTICLUSTER,
	WEAPON_VULCAN,
	WEAPON_JUMPCANNON,
	WEAPON_FIENDSHARD,
	WEAPON_CYCANNON,
	WEAPON_SNIPER,
	WEAPON_LTRAIL,
	WEAPON_VULCAN3,
	WEAPON_PISTOLA,

	/*
	 * Firestorm additions start here
	 */
	WEAPON_DROPGUN,
	WEAPON_JUGG90MM,
	WEAPON_LIMP,
	WEAPON_AALASERFIRE,
	WEAPON_CABLASER,
	WEAPON_QUADLAUNCHER,
	WEAPON_WEBLAUNCHER,
	WEAPON_TENTACLE,
	WEAPON_DEFOB,
	WEAPON_DUALROCKETS,
	WEAPON_MOBILEEMPULSEWEAPON,

	WEAPON_COUNT,
	WEAPON_FIRST=0
};
