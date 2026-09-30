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

#include "vox.hh"

void Speak(VoxType voice, bool now=false);
void Speak_AI(void);
void Stop_Speaking(void);
bool Is_Speaking(void);

void Set_Speech_Volume(int volume);
void Set_Speech_State(bool state);
bool Get_Speech_State(void);

char const * Speech_Name(VoxType speech);

extern char const * Speech[VOX_COUNT];
