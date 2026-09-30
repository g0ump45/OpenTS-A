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
**	This is the complete list of VQs allowed to be played in the game.
*/
enum VQType {
	VQ_NONE=-1,

	VQ_CAP_TRAT,
	VQ_COUP,
	VQ_VEGAWIN,
	VQ_DISKDEST,
	VQ_INTRO,
	VQ_GDI_M02,
	VQ_GDI_M03,
	VQ_GDI_M04,
	VQ_GDI_M05,
	VQ_GDI_M06,
	VQ_GDI_M07,
	VQ_GDI_M08,
	VQ_GDI_M09A,
	VQ_GDI_M09B,
	VQ_GDI_M09C,
	VQ_GDI_M10A,
	VQ_GDIM09CW,
	VQ_GDI_M11,
	VQ_GDI_M12A,
	VQ_HIDESEEK,
	VQ_ICESKATE,
	VQ_MECHATAK,
	VQ_EVA,
	VQ_NOD_M02,
	VQ_NOD_M03,
	VQ_NOD_M04,
	VQ_NOD_M06,
	VQ_NOWCNOT,
	VQ_ORCASTRK,
	VQ_PODASSLT,
	VQ_RETRBTN,
	VQ_TENEVICT,
	VQ_TRAINROB,
	VQ_NOD06ABW,
	VQ_EMPULSE,
	VQ_NOD_M09,
	VQ_STARTUP,
	VQ_ICBMLNCH,
	VQ_BEACHEAD,
	VQ_GDI_FINL,
	VQ_NOD_M05,
	VQ_GENNODL1,
	VQ_GDIM09D1,
	VQ_GDI01_SB,
	VQ_GDI02_SB,
	VQ_GDI03_SB,
	VQ_NOD_M07,
	VQ_NOD_M08,
	VQ_NOD_M10,
	VQ_NOD_M11,
	VQ_NOD_M12,
	VQ_NOD_FINL,
	VQ_NOD01_SB,
	VQ_NOD02_SB,
	VQ_GENWIN01,
	VQ_UFOGUARD,
	VQ_WWLOGO,
	VQ_KILL_GDI,
	VQ_KILLMECH,
	VQ_UNSTPBLE,
	VQ_N_LOGO_W,
	VQ_N_LOGO_L,
	VQ_NOD_FLAG,
	VQ_GDI_LOGO,
	VQ_GDI_FLAG,
	VQ_DAMBREAK,

	/*
	**	Firestorm movies start here
	*/
	VQ_FSGDIM02,
	VQ_FSGDIM03,
	VQ_FSGDIM07,
	VQ_FSNODM02,
	VQ_FSNODM06,
	VQ_FS_TITLE,
	VQ_FSNODM01,
	VQ_FSNODM03,
	VQ_FSNODM04,
	VQ_FSNODM07,
	VQ_FSNODM09,
	VQ_FSNODM05,
	VQ_FSNODM08,
	VQ_MEKATAK2,
	VQ_FSGDIM04,
	VQ_FSGDIM05,
	VQ_FSGDIM06,
	VQ_FSGDIM08,
	VQ_FSGDIM09,
	VQ_FSGDIFNL,
	VQ_FSGDIINT,
	VQ_FS_SB01,
	VQ_TS_TITLE,
	VQ_FSNODFNL,

	VQ_COUNT,
	VQ_FIRST=0
};
