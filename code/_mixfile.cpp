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

#include "always.h"

#include "_mixfile.h"

#include "vector.h"

/***************************************************************************
**	This holds the theater specific mixfiles.
*/
DynamicVectorClass<MFCD *> ExpandMix;
DynamicVectorClass<MFCD *> ExpandSideMix;
DynamicVectorClass<MFCD *> ExpandSpeechMix;
MFCD * MultiMix = NULL;
MFCD * MarbleMix = NULL;
MFCD * GameMix = NULL;
MFCD * TheaterData = NULL;
MFCD * TheaterDat = NULL;
MFCD * IsometricTheaterData = NULL;
MFCD * MoviesMix = NULL;
MFCD * ScoresMix = NULL;
MFCD * MainMix = NULL;
MFCD * ConquerMix = NULL;
MFCD * CacheMix = NULL;
MFCD * LocalMix = NULL;
MFCD * MapsMix = NULL;
MFCD * SpeechMix = NULL;
MFCD * SoundsMix = NULL;
MFCD * Sounds01Mix = NULL;
MFCD * Scores01Mix = NULL;
MFCD * SideCMix = NULL;
MFCD * SideNCMix = NULL;
MFCD * SideCDMix = NULL;

DynamicVectorClass<MFCD *> MapsMixLocal;
DynamicVectorClass<MFCD *> MoviesMixLocal;
