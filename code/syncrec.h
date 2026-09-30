/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "syncrec.hh"

#include <cstdint>
#include <cstdio>

// Bounded in-memory histories of the state changes leading up to a desync; the core holds no
// engine types, so recording is a cheap masked store and the module tests on its own.

struct SyncRandomEntryType {
	int32_t Frame;
	uint32_t Caller;
	int32_t Index1;
	int32_t Index2;
	int32_t Value;
	int32_t Min;
	int32_t Max;
	uint8_t Kind;
	uint8_t Shape;
};

struct SyncFacingEntryType {
	int32_t Frame;
	uint32_t Caller;
	int16_t Facing;
	uint8_t Kind;
};

struct SyncTargetEntryType {
	int32_t Frame;
	uint32_t Caller;
	int32_t SubjectID;
	int32_t TargetID;
	int8_t SubjectRTTI;
	int8_t TargetRTTI;
};

struct SyncMissionEntryType {
	int32_t Frame;
	uint32_t Caller;
	int32_t SubjectID;
	int8_t SubjectRTTI;
	int8_t Before;
	int8_t After;
	uint8_t Kind;
};

struct SyncAnimEntryType {
	int32_t Frame;
	uint32_t Caller;
	int32_t AnimID;
	int32_t X;
	int32_t Y;
	int32_t Z;
	int16_t TypeHeapID;
};

struct SyncEventEntryType {
	int32_t Frame;
	int32_t SeenAt;
	int32_t House;
	uint8_t Type;
	uint8_t Source;
	uint8_t Length;
	uint8_t Bytes[40];
};

// Set on a caller offset the recorder could not resolve to the running image. A resolved offset
// is bounded by the image size, which a 32 bit image keeps far below this bit.
constexpr uint32_t SYNC_CALLER_EXTERN = 0x80000000u;

// What the printer needs to name a call site, supplied by the engine because neither the image
// layout nor the symbol handler belongs in the core.
struct SyncCallerContextType {
	// The base the build's map file is written against, taken from the image's own header rather
	// than assumed, and added to a recorded offset to give the address the map file lists.
	uint32_t MapImageBase;

	// Names the call site at an offset, or answers null when no symbols are loaded.
	char const * (*Describe)(uint32_t rva);
};

void Sync_Set_Caller_Context(SyncCallerContextType const & context);

// Names the printer needs for engine enumerations, supplied by the engine so the core stays free
// of engine headers. A null pointer prints the raw number instead.
struct SyncNamesType {
	char const * (*Rtti)(int rtti);
	char const * (*Mission)(int mission);
	char const * (*Event)(int type);
	char const * (*Anim)(int heap_id);
};

template<typename T, unsigned SIZE>
class SyncHistoryClass {
	public:
		static_assert((SIZE & (SIZE - 1)) == 0, "SyncHistoryClass size must be a power of two.");

		void Add(T const & entry) { Entries[Total & (SIZE - 1)] = entry; Total++; }
		void Reset(void) { Total = 0; }

		unsigned Count(void) const { return(Total < SIZE ? Total : SIZE); }

		// The entry n steps back from the most recent one; n must be below Count().
		T const & Nth_Newest(unsigned n) const { return(Entries[(Total - 1 - n) & (SIZE - 1)]); }

	private:
		unsigned Total = 0;
		T Entries[SIZE] = {};
};

class SyncRecorderClass {
	public:
		void Set_Recording(bool on) { IsRecording = on; }
		bool Is_Recording(void) const { return(IsRecording); }
		void Reset(void);

		void Begin_Ranged_Draw(void) { InRangedDraw = true; }
		void End_Ranged_Draw(void) { InRangedDraw = false; }
		bool In_Ranged_Draw(void) const { return(InRangedDraw); }

		void Add_Random(SyncRandomEntryType const & entry) { Randoms.Add(entry); }
		void Add_Facing(SyncFacingEntryType const & entry) { Facings.Add(entry); }
		void Add_Target(SyncTargetEntryType const & entry) { Targets.Add(entry); }
		void Add_Mission(SyncMissionEntryType const & entry) { Missions.Add(entry); }
		void Add_Anim(SyncAnimEntryType const & entry) { Anims.Add(entry); }
		void Add_Executed_Event(SyncEventEntryType const & entry) { Executed.Add(entry); }
		void Add_Queued_Event(SyncEventEntryType const & entry) { Queued.Add(entry); }

		void Print_All(FILE * fp, SyncNamesType const & names) const;

		void Print_Randoms(FILE * fp, SyncNamesType const & names, unsigned max) const;
		void Print_Facings(FILE * fp, unsigned max) const;
		void Print_Targets(FILE * fp, SyncNamesType const & names, unsigned max) const;
		void Print_Missions(FILE * fp, SyncNamesType const & names, unsigned max) const;
		void Print_Anims(FILE * fp, SyncNamesType const & names, unsigned max) const;
		void Print_Events(FILE * fp, SyncNamesType const & names, unsigned max) const;

	private:
		bool IsRecording = false;
		bool InRangedDraw = false;

		SyncHistoryClass<SyncRandomEntryType, 4096> Randoms;
		SyncHistoryClass<SyncFacingEntryType, 1024> Facings;
		SyncHistoryClass<SyncTargetEntryType, 1024> Targets;
		SyncHistoryClass<SyncMissionEntryType, 1024> Missions;
		SyncHistoryClass<SyncAnimEntryType, 512> Anims;
		SyncHistoryClass<SyncEventEntryType, 2048> Executed;
		SyncHistoryClass<SyncEventEntryType, 256> Queued;
};

// Formats a module-relative caller offset into the buffer, so a report line can be matched
// against the map file of the same build regardless of where the image was loaded.
void Sync_Format_Caller(char * buffer, size_t size, uint32_t rva);

extern SyncRecorderClass SyncRecorder;
