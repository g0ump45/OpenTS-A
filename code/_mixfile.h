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

template<class T> class DynamicVectorClass;
class MixFileClass;


/*
**	Convenient alias for MixFileClass<CDFileClass> object. This allows
**	easier entry into the code and less clutter.
*/
typedef MixFileClass	MFCD;


/***************************************************************************
**	This holds the theater specific mixfiles.
*/
extern DynamicVectorClass<MFCD *> ExpandMix;
extern DynamicVectorClass<MFCD *> ExpandSpeechMix;
extern MFCD * MultiMix;
extern MFCD * MarbleMix;
extern DynamicVectorClass<MFCD *> ExpandSideMix;
extern MFCD * GameMix;
extern MFCD * TheaterData;
extern MFCD * TheaterDat;
extern MFCD * IsometricTheaterData;
extern MFCD * MoviesMix;

extern MFCD * ScoresMix;
extern MFCD * MainMix;
extern MFCD * ConquerMix;
extern MFCD * CacheMix;
extern MFCD * LocalMix;
extern MFCD * MapsMix;

extern MFCD * SpeechMix;
extern MFCD * SoundsMix;
extern MFCD * Sounds01Mix;
extern MFCD * Scores01Mix;
extern MFCD * SideCMix;
extern MFCD * SideNCMix;
extern MFCD * SideCDMix;

/*
 * Every MAPS*.MIX and MOVIES*.MIX beyond the first one found.
 */
extern DynamicVectorClass<MFCD *> MapsMixLocal;
extern DynamicVectorClass<MFCD *> MoviesMixLocal;
