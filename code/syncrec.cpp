/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "syncrec.h"


static SyncCallerContextType CallerContext = { 0, nullptr };


void Sync_Set_Caller_Context(SyncCallerContextType const & context)
{
	CallerContext = context;
}


static unsigned Min_Count(unsigned a, unsigned b)
{
	return(a < b ? a : b);
}


void Sync_Format_Caller(char * buffer, size_t size, uint32_t rva)
{
	// An address outside the image keeps only its low bits, and belongs to a module the other
	// machine may have loaded elsewhere, so it identifies a call site no further than this.
	if ((rva & SYNC_CALLER_EXTERN) != 0) {
		std::snprintf(buffer, size, "extern:%08x", rva & ~SYNC_CALLER_EXTERN);
		return;
	}

	char const * description = (CallerContext.Describe != nullptr)
		? CallerContext.Describe(rva) : nullptr;
	if (description != nullptr && description[0] == '\0') {
		description = nullptr;
	}

	char const * const gap = (description != nullptr) ? " " : "";
	char const * const named = (description != nullptr) ? description : "";

	// Without the base the map file was written against, the offset is printed on its own rather
	// than turned into an address that would not be in any map file.
	if (CallerContext.MapImageBase != 0) {
		std::snprintf(buffer, size, "+%08x (map %08x)%s%s",
			rva, rva + CallerContext.MapImageBase, gap, named);
	} else {
		std::snprintf(buffer, size, "+%08x%s%s", rva, gap, named);
	}
}


void SyncRecorderClass::Reset(void)
{
	Randoms.Reset();
	Facings.Reset();
	Targets.Reset();
	Missions.Reset();
	Anims.Reset();
	Executed.Reset();
	Queued.Reset();
	InRangedDraw = false;
}


static char const * Rtti_Name(SyncNamesType const & names, int rtti)
{
	return(names.Rtti != nullptr ? names.Rtti(rtti) : "?");
}


void SyncRecorderClass::Print_Randoms(FILE * fp, SyncNamesType const &, unsigned max) const
{
	std::fprintf(fp, "\n----- Random draws (newest first) -----\n");

	char caller[256];
	unsigned const count = Min_Count(Randoms.Count(), max);
	for (unsigned n = 0; n < count; n++) {
		SyncRandomEntryType const & e = Randoms.Nth_Newest(n);
		Sync_Format_Caller(caller, sizeof(caller), e.Caller);

		char const kind = (e.Kind == SYNC_RANDOM_CRITICAL) ? 'C' : 'N';
		char const shape = (e.Shape == SYNC_DRAW_RANGED) ? 'R' : (e.Shape == SYNC_DRAW_INNER) ? 'I' : 'P';

		char range[24];
		if (e.Shape == SYNC_DRAW_RANGED) {
			std::snprintf(range, sizeof(range), "[%d..%d]", e.Min, e.Max);
		} else {
			range[0] = '\0';
		}

		std::fprintf(fp, "F%-8d  %c%c  i1=%3d i2=%3d  val=%08x  %-16s  %s\n",
			e.Frame, kind, shape, e.Index1, e.Index2, (unsigned)e.Value, range, caller);
	}
}


void SyncRecorderClass::Print_Facings(FILE * fp, unsigned max) const
{
	std::fprintf(fp, "\n----- Facing assignments (newest first) -----\n");

	char caller[256];
	unsigned const count = Min_Count(Facings.Count(), max);
	for (unsigned n = 0; n < count; n++) {
		SyncFacingEntryType const & e = Facings.Nth_Newest(n);
		Sync_Format_Caller(caller, sizeof(caller), e.Caller);
		// The facing value itself is advisory: it has been seen to differ between machines that
		// are still in sync, so the caller and frame are the comparable keys.
		std::fprintf(fp, "F%-8d  facing=%-4d  %s\n", e.Frame, e.Facing, caller);
	}
}


void SyncRecorderClass::Print_Targets(FILE * fp, SyncNamesType const & names, unsigned max) const
{
	std::fprintf(fp, "\n----- Target assignments (newest first) -----\n");

	char caller[256];
	unsigned const count = Min_Count(Targets.Count(), max);
	for (unsigned n = 0; n < count; n++) {
		SyncTargetEntryType const & e = Targets.Nth_Newest(n);
		Sync_Format_Caller(caller, sizeof(caller), e.Caller);
		std::fprintf(fp, "F%-8d  %-10s ID:%-7d -> %-10s ID:%-7d  %s\n",
			e.Frame, Rtti_Name(names, e.SubjectRTTI), e.SubjectID,
			Rtti_Name(names, e.TargetRTTI), e.TargetID, caller);
	}
}


void SyncRecorderClass::Print_Missions(FILE * fp, SyncNamesType const & names, unsigned max) const
{
	std::fprintf(fp, "\n----- Mission orders (newest first) -----\n");

	char caller[256];
	unsigned const count = Min_Count(Missions.Count(), max);
	for (unsigned n = 0; n < count; n++) {
		SyncMissionEntryType const & e = Missions.Nth_Newest(n);
		Sync_Format_Caller(caller, sizeof(caller), e.Caller);

		char const * verb = (e.Kind == SYNC_MISSION_OVERRIDE) ? "override" : "assign";
		char const * before = (names.Mission != nullptr) ? names.Mission(e.Before) : "?";
		char const * after = (names.Mission != nullptr) ? names.Mission(e.After) : "?";
		std::fprintf(fp, "F%-8d  %-8s %-10s ID:%-7d  %-16s -> %-16s  %s\n",
			e.Frame, verb, Rtti_Name(names, e.SubjectRTTI), e.SubjectID, before, after, caller);
	}
}


void SyncRecorderClass::Print_Anims(FILE * fp, SyncNamesType const & names, unsigned max) const
{
	std::fprintf(fp, "\n----- Animation creations (newest first) -----\n");

	char caller[256];
	unsigned const count = Min_Count(Anims.Count(), max);
	for (unsigned n = 0; n < count; n++) {
		SyncAnimEntryType const & e = Anims.Nth_Newest(n);
		Sync_Format_Caller(caller, sizeof(caller), e.Caller);

		char const * type = (names.Anim != nullptr) ? names.Anim(e.TypeHeapID) : "?";
		char const * local = (e.AnimID == -2) ? " (local only)" : "";
		std::fprintf(fp, "F%-8d  ID:%-7d  type=%3d(%-12s)  coord=%7d,%7d,%6d  %s%s\n",
			e.Frame, e.AnimID, e.TypeHeapID, type, e.X, e.Y, e.Z, caller, local);
	}
}


static void Print_Event(FILE * fp, SyncNamesType const & names, SyncEventEntryType const & e)
{
	char const * name = (names.Event != nullptr) ? names.Event(e.Type) : "?";
	std::fprintf(fp, "seen=%-8d  frame=%-8d  house=%-2d  %-16s data:", e.SeenAt, e.Frame, e.House, name);
	for (unsigned i = 0; i < e.Length; i++) {
		std::fprintf(fp, " %02x", e.Bytes[i]);
	}
	std::fprintf(fp, "\n");
}


void SyncRecorderClass::Print_Events(FILE * fp, SyncNamesType const & names, unsigned max) const
{
	std::fprintf(fp, "\n----- Executed events (newest first) -----\n");
	unsigned count = Min_Count(Executed.Count(), max);
	for (unsigned n = 0; n < count; n++) {
		Print_Event(fp, names, Executed.Nth_Newest(n));
	}

	std::fprintf(fp, "\n----- Queued events (newest first) -----\n");
	count = Min_Count(Queued.Count(), max);
	for (unsigned n = 0; n < count; n++) {
		Print_Event(fp, names, Queued.Nth_Newest(n));
	}
}


void SyncRecorderClass::Print_All(FILE * fp, SyncNamesType const & names) const
{
	// The report reads the generator cursors without drawing, so no random-draw entry beyond the
	// mismatch frame appears here.
	Print_Randoms(fp, names, 4096);
	Print_Events(fp, names, 2048);
	Print_Targets(fp, names, 1024);
	Print_Missions(fp, names, 1024);
	Print_Facings(fp, 1024);
	Print_Anims(fp, names, 512);
}
