/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

enum VQOptionType {
	OPTION_PLAY_FROM_MIXFILE,		// use mixfile instead of ccfile
	OPTION_1,						// cache related?
	OPTION_USE_LOOPS,				// loop related?
	OPTION_NO_AUDIO,				// OPTION_AUDIO_DISABLED in TSYR project.
	OPTION_SIMPLE_TIMER_CALLBACK,	// different audio timer?
	OPTION_5,						// prints frame in nox?
	OPTION_6,
	OPTION_7,
	OPTION_8,
	OPTION_9,
	OPTION_10,
	OPTION_ALTERNATE_UNVQ,			// alt unvq?
	OPTION_12,
	OPTION_13,
	OPTION_14,
	OPTION_NO_BUFFER,
	OPTION_16,
	OPTION_17,

	VQ_OPTION_COUNT,

	OPTION_SLOTS = 8,
	OPTION_SHIFT = 3,
};


void Initialize_Options(void);
void Set_Option(int flag);
void Clear_Option(int flag);
bool Get_Option(int flag);
int Toggle_Option(int flag);
