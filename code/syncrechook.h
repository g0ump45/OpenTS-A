/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "syncrec.h"

class Random2Class;
class AbstractClass;
class ObjectClass;
class AnimClass;
class Coord;
class DirType;
class EventClass;

// Each wrapper is a guard around an out-of-line body, so a non-recording game pays only a branch.
// The caller is the raw return address captured at the hooked call site.

void Sync_Record_Random_Impl(Random2Class const & gen, int value, int minval, int maxval, bool ranged, unsigned caller);
void Sync_Record_Facing_Impl(DirType const & facing, unsigned caller);
void Sync_Record_Target_Impl(AbstractClass const & subject, AbstractClass const * target, unsigned caller);
void Sync_Record_Mission_Impl(ObjectClass const & subject, int before, int after, int kind, unsigned caller);
void Sync_Record_Anim_Impl(AnimClass const & anim, Coord const & coord, unsigned caller);
void Sync_Record_Event_Impl(EventClass const & event, int source);

inline void Sync_Record_Random(Random2Class const & gen, int value, int minval, int maxval, bool ranged, unsigned caller)
{
	if (!SyncRecorder.Is_Recording()) return;
	Sync_Record_Random_Impl(gen, value, minval, maxval, ranged, caller);
}

inline void Sync_Record_Facing(DirType const & facing, unsigned caller)
{
	if (!SyncRecorder.Is_Recording()) return;
	Sync_Record_Facing_Impl(facing, caller);
}

inline void Sync_Record_Target(AbstractClass const & subject, AbstractClass const * target, unsigned caller)
{
	if (!SyncRecorder.Is_Recording()) return;
	Sync_Record_Target_Impl(subject, target, caller);
}

inline void Sync_Record_Mission(ObjectClass const & subject, int before, int after, int kind, unsigned caller)
{
	if (!SyncRecorder.Is_Recording()) return;
	Sync_Record_Mission_Impl(subject, before, after, kind, caller);
}

inline void Sync_Record_Anim(AnimClass const & anim, Coord const & coord, unsigned caller)
{
	if (!SyncRecorder.Is_Recording()) return;
	Sync_Record_Anim_Impl(anim, coord, caller);
}

inline void Sync_Record_Event(EventClass const & event, int source)
{
	if (!SyncRecorder.Is_Recording()) return;
	Sync_Record_Event_Impl(event, source);
}

// Turns recording on for a network game or an armed recording/playback and caches the image base
// for caller offsets; the disarm clears the histories back to empty.
void Sync_Recorder_Arm(void);
void Sync_Recorder_Disarm(void);

// Supplies the printer with the engine's enumeration names for the report.
SyncNamesType const & Sync_Engine_Names(void);
