/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "syncrec.h"

#include <cstdio>
#include <cstring>

// The core is engine-free, so its global instance is defined here for the harness rather than
// pulled in from _syncrec.cpp (which the engine build owns).
SyncRecorderClass SyncRecorder;

namespace {

int Failures = 0;

void Check(bool condition, char const * what)
{
	std::printf("%-52s %s\n", what, condition ? "ok" : "FAILED");
	if (!condition) {
		Failures++;
	}
}


void Test_Ring_Wraparound(void)
{
	SyncHistoryClass<int, 8> ring;
	for (int i = 1; i <= 11; i++) {
		ring.Add(i);
	}
	Check(ring.Count() == 8, "ring keeps at most its size after overflow");
	Check(ring.Nth_Newest(0) == 11, "newest entry is the last one added");
	Check(ring.Nth_Newest(7) == 4, "oldest kept entry is size-1 back");

	ring.Reset();
	Check(ring.Count() == 0, "reset empties the ring");
}


void Test_Bounded_Print(void)
{
	SyncRecorderClass rec;
	SyncRandomEntryType e {};
	for (int i = 0; i < 5000; i++) {
		e.Frame = i;
		rec.Add_Random(e);
	}

	std::FILE * fp = std::tmpfile();
	SyncNamesType const names = {};
	rec.Print_Randoms(fp, names, 4096);

	std::rewind(fp);
	int data_lines = 0;
	char line[256];
	while (std::fgets(line, sizeof(line), fp) != nullptr) {
		if (line[0] == 'F') {
			data_lines++;
		}
	}
	std::fclose(fp);

	Check(data_lines == 4096, "print honors the ring size cap");
}


char const * Stub_Describe(uint32_t rva)
{
	return((rva == 0x0012ab34) ? "FacingClass::Set()+0x2f [facing.cpp:131]" : nullptr);
}


void Test_Caller_Format(void)
{
	char buffer[256];

	SyncCallerContextType context;
	context.MapImageBase = 0x00400000u;
	context.Describe = nullptr;
	Sync_Set_Caller_Context(context);

	Sync_Format_Caller(buffer, sizeof(buffer), 0x0012ab34);
	Check(std::strcmp(buffer, "+0012ab34 (map 0052ab34)") == 0, "in-image caller shows offset and map address");

	Sync_Format_Caller(buffer, sizeof(buffer), SYNC_CALLER_EXTERN | 0x1234);
	Check(std::strstr(buffer, "extern") != nullptr, "out-of-image caller is flagged extern");

	context.MapImageBase = 0x10000000u;
	Sync_Set_Caller_Context(context);

	Sync_Format_Caller(buffer, sizeof(buffer), 0x0012ab34);
	Check(std::strcmp(buffer, "+0012ab34 (map 1012ab34)") == 0, "the map address follows the image base given");

	context.MapImageBase = 0x00400000u;
	context.Describe = Stub_Describe;
	Sync_Set_Caller_Context(context);

	Sync_Format_Caller(buffer, sizeof(buffer), 0x0012ab34);
	Check(std::strcmp(buffer, "+0012ab34 (map 0052ab34) FacingClass::Set()+0x2f [facing.cpp:131]") == 0,
		"a named caller keeps its offset and gains the name");

	Sync_Format_Caller(buffer, sizeof(buffer), 0x00005678);
	Check(std::strcmp(buffer, "+00005678 (map 00405678)") == 0, "an unnamed caller falls back to the offset");

	context.MapImageBase = 0;
	Sync_Set_Caller_Context(context);

	Sync_Format_Caller(buffer, sizeof(buffer), 0x0012ab34);
	Check(std::strcmp(buffer, "+0012ab34 FacingClass::Set()+0x2f [facing.cpp:131]") == 0,
		"an unknown image base drops the map address rather than inventing one");

	context.Describe = nullptr;
	Sync_Set_Caller_Context(context);
}


void Test_Ranged_Shape(void)
{
	SyncRecorderClass rec;
	Check(!rec.In_Ranged_Draw(), "ranged flag starts clear");
	rec.Begin_Ranged_Draw();
	Check(rec.In_Ranged_Draw(), "begin sets the ranged flag");
	rec.End_Ranged_Draw();
	Check(!rec.In_Ranged_Draw(), "end clears the ranged flag");
}


void Test_Recording_Flag(void)
{
	SyncRecorderClass rec;
	Check(!rec.Is_Recording(), "recording starts off");
	rec.Set_Recording(true);
	Check(rec.Is_Recording(), "set recording on");
	rec.Reset();
	Check(rec.Is_Recording(), "reset does not change the recording flag");
	rec.Set_Recording(false);
	Check(!rec.Is_Recording(), "set recording off");
}

} // namespace


int main(void)
{
	Test_Ring_Wraparound();
	Test_Bounded_Print();
	Test_Caller_Format();
	Test_Ranged_Shape();
	Test_Recording_Flag();

	std::printf("\n%s (%d failures)\n", Failures == 0 ? "PASSED" : "FAILED", Failures);
	return(Failures == 0 ? 0 : 1);
}
