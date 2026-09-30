
/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 ******************************************************************************/

#include "always.h"
#include "mouse.h"
#include "_mixfile.h"
#include "animtype.h"
#include "builtype.h"
#include "cell.h"
#include "data.h"
#include "isotype.h"
#include "mixfile.h"
#include "overtype.h"
#include "rawfile.h"
#include "saveload.h"
#include "savestream.h"
#include "scenario.h"
#include "shapeset.h"
#include "smudtype.h"
#include "terrtype.h"
#include "xmouse.h"
#include <memory>

#define MOUSE_HOTSPOT_MIN 0
#define MOUSE_HOTSPOT_CENTER 12345
#define MOUSE_HOTSPOT_MAX 54321
#define HSMIN MOUSE_HOTSPOT_MIN
#define HSMAX MOUSE_HOTSPOT_MAX
#define HSCNR MOUSE_HOTSPOT_CENTER

ShapeSet const * MouseClass::MouseShapes;
CDTimerClass<SystemTimerClass> MouseClass::Timer = 0;

MouseClass::MouseClass(void) :
    IsSmall(false),
    CurrentMouseShape(MOUSE_NORMAL),
    NormalMouseShape(MOUSE_NORMAL),
    Frame(0)
{
}

void MouseClass::Set_Default_Mouse(MouseType mouse, bool size)
{
#ifdef __ANDROID__
    if ((unsigned)mouse >= MOUSE_COUNT) return;
    NormalMouseShape = mouse;
    CurrentMouseShape = mouse;
    IsSmall = size;
    return;
#else
    assert((unsigned)mouse < MOUSE_COUNT);
    NormalMouseShape = mouse;
    Override_Mouse_Shape(mouse, size);
#endif
}

void MouseClass::Revert_Mouse_Shape(void)
{
#ifdef __ANDROID__
    return;
#else
    Override_Mouse_Shape(NormalMouseShape, false);
#endif
}

void MouseClass::Mouse_Small(bool wsmall)
{
#ifdef __ANDROID__
    if (!MouseCursor) return;
    IsSmall = wsmall;
    return;
#else
    MouseStruct const * control = &MouseControl[CurrentMouseShape];
    if (IsSmall == wsmall) return;
    IsSmall = wsmall;
    int frame = Get_Mouse_Current_Frame(CurrentMouseShape, wsmall);
    Point2D hotspot = Get_Mouse_Hotspot(CurrentMouseShape);
    if (MouseCursor) MouseCursor->Set_Cursor(hotspot, MouseShapes, frame);
#endif
}

int MouseClass::Get_Mouse_Current_Frame(MouseType mouse, bool wsmall) const
{
    MouseStruct const * control = &MouseControl[mouse];
    if (wsmall) {
        if (control->SmallFrame != -1) {
            return(control->SmallFrame + Frame);
        }
    }
    return(control->StartFrame + Frame);
}

Point2D MouseClass::Get_Mouse_Hotspot(MouseType mouse) const
{
    Point2D hotspot(0,0);
#ifdef __ANDROID__
    if (MouseShapes == NULL) return(hotspot);
#else
    if (MouseShapes == NULL) return(hotspot);
#endif
    MouseStruct const * control = &MouseControl[mouse];
    if (control->X == MOUSE_HOTSPOT_CENTER) {
        hotspot.X = MouseShapes->Get_Width() / 2;
    }
    if (control->X == MOUSE_HOTSPOT_MAX) {
        hotspot.X = MouseShapes->Get_Width();
    }
    if (control->Y == MOUSE_HOTSPOT_CENTER) {
        hotspot.Y = MouseShapes->Get_Height() / 2;
    }
    if (control->Y == MOUSE_HOTSPOT_MAX) {
        hotspot.Y = MouseShapes->Get_Height();
    }
    return(hotspot);
}

int MouseClass::Get_Mouse_Start_Frame(MouseType mouse) const
{
    return(MouseControl[mouse].StartFrame);
}

int MouseClass::Get_Mouse_Frame_Count(MouseType mouse) const
{
    return(MouseControl[mouse].FrameCount);
}

bool MouseClass::Override_Mouse_Shape(MouseType mouse, bool wsmall)
{
#ifdef __ANDROID__
    if ((unsigned)mouse >= MOUSE_COUNT) return false;
    CurrentMouseShape = mouse;
    IsSmall = wsmall;
    if (!MouseCursor || !MouseShapes) {
        return true;
    }
    int frame = Get_Mouse_Current_Frame(mouse, wsmall);
    Point2D hotspot = Get_Mouse_Hotspot(mouse);
    MouseCursor->Set_Cursor(hotspot, MouseShapes, frame);
    return true;
#else
    if ((unsigned)mouse >= MOUSE_COUNT) return false;
    if (MouseShapes == NULL) return false;
    if (MouseCursor == NULL) return false;
    int frame = Get_Mouse_Current_Frame(mouse, wsmall);
    Point2D hotspot = Get_Mouse_Hotspot(mouse);
    MouseCursor->Set_Cursor(hotspot, MouseShapes, frame);
    CurrentMouseShape = mouse;
    IsSmall = wsmall;
    return true;
#endif
}

void MouseClass::One_Time(void)
{
    BASECLASS::One_Time();
#ifdef __ANDROID__
    return;
#else
    // Original One_Time loads mouse.shp - skip on Android
    MouseShapes = (ShapeSet const *)MFCD::Retrieve("MOUSE.SHP");
#endif
}

void MouseClass::Init_Clear(void)
{
    IsSmall = false;
    CurrentMouseShape = MOUSE_NORMAL;
    NormalMouseShape = MOUSE_NORMAL;
    Frame = 0;
}

void MouseClass::AI(KeyNumType &input, Point2D const & xy)
{
#ifdef __ANDROID__
    BASECLASS::AI(input, xy);
    return;
#else
    // Original AI animates mouse - skip if needed
    if (MouseShapes == NULL) return;
    // ... minimal
#endif
}

bool MouseClass::Load(SaveStreamClass & stream)
{
	int i;

	bool result = BASECLASS::Load(stream);
	if (result) {
		int theater;
		stream.Serialize(theater);
		if (stream.Was_Error()) {
			return(false);
		}

		LastTheater = THEATER_NONE;

		/*
		**	Free the cell array, because we're about to overwrite its pointers
		*/
		Free_Cells();

		delete [] CellSubzones;
		CellSubzones = NULL;
		delete [] CellZones;
		CellZones = NULL;
		ZoneAdjacency.clear();

		for (i = 0; i < SUBZONE_COUNT; i++) {
			SubzoneTracking[i].Clear();
			SubzoneTrackingEntryCount[i] = 0;
		}

		for (i = 0; i < MZONE_COUNT; i++) {
			delete [] Zones[i];
			Zones[i] = NULL;
		}

		for (i = 0; i < SUBZONE_COUNT; i++) {
			SubzoneConnectionStaging[i].clear();
		}

		Array.Clear();

		stream.Set_Context("MouseClass");
		Serialize(stream);
		if (stream.Was_Error()) {
			return(false);
		}

		/*
		**	Reallocate the cell array
		*/
		Alloc_Cells();

		/*
		**	Init all cells to empty
		*/
		Init_Cells();

		Set_Map_Dimensions(PlayRect, 1, 0, false);

		CellSubzones = new CellSubzoneStruct[CellZoneCount];
		CellZones = new CellZoneStruct[CellZoneCount];

		for (i = 0; i < SUBZONE_COUNT; i++) {
			int v = (1 << (i + 1));
			SubzoneTracking[i].Clear();
			SubzoneTrackingEntryCount[i] = 0;
			SubzoneTracking[i].Set_Growth_Step((4 * PlayRect.Width * PlayRect.Height) / (v * v));
		}

		/*
		 * These blocks are read raw, so a file whose records are a different size would drag
		 * the rest of the stream out of step.
		 */
		stream.Serialize_Bytes(CellZones, (int)(sizeof(*CellZones) * CellZoneCount));
		if (stream.Was_Error()) {
			return(false);
		}

		for (i = 0; i < MZONE_COUNT; i++) {
			Zones[i] = new int[ZoneCount];
			stream.Serialize_Bytes(Zones[i], (int)(sizeof(*Zones[i]) * ZoneCount));
			if (stream.Was_Error()) {
				return(false);
			}
		}

		stream.Serialize(ZoneConnections);
		if (stream.Was_Error()) {
			return(false);
		}

		for (i = 0; i < Array.Length(); i++) {
			delete Array[i];
			Array[i] = NULL;
		}
		int count;
		stream.Serialize(count);
		if (stream.Was_Error()) {
			return(false);
		}
		for (i = 0; i < count; i++) {
			std::unique_ptr<CellClass> cell = Load_Object_As<CellClass>(stream);
			if (cell == nullptr) {
				return(false);
			}
			// The cell put itself into the map's array as it finished loading, and the map
			// is what deletes it from here on.
			cell.release();
		}

		TerrainTypeClass::Init(Scen->Theater);
		if (Scen->Theater != LastTheater) {
			IsometricTileTypeClass::Read_Control_File(Scen->Theater, true);
		} else {
			IsometricTileTypeClass::Clear_Use_Counts();
		}
		IsometricTileTypeClass::Load_Tiles(false, false);
		OverlayTypeClass::Init(Scen->Theater);
		BuildingTypeClass::Init(Scen->Theater);
		AnimTypeClass::Init(Scen->Theater);
		SmudgeTypeClass::Init(Scen->Theater);
		DraggedWaypoint = NULL;
		LastTheater = Scen->Theater;

		result = true;
	}
	return(result);
}
bool MouseClass::Save(SaveStreamClass & stream)
{
	int i;
	int count;

	bool result = BASECLASS::Save(stream);
	if (result) {
		int theater = Scen->Theater;
		stream.Serialize(theater);
		if (stream.Was_Error()) {
			return(false);
		}

		Serialize(stream);
		if (stream.Was_Error()) {
			return(false);
		}

		stream.Serialize_Bytes(CellZones, (int)(sizeof(*CellZones) * CellZoneCount));
		if (stream.Was_Error()) {
			return(false);
		}

		for (i = 0; i < MZONE_COUNT; i++) {
			stream.Serialize_Bytes(Zones[i], (int)(sizeof(*Zones[i]) * ZoneCount));
			if (stream.Was_Error()) {
				return(false);
			}
		}

		stream.Serialize(ZoneConnections);
		if (stream.Was_Error()) {
			return(false);
		}

		count = 0;
		Reset_Iterator();
		CellClass *cptr = Iterate();
		while (cptr != NULL) {
			Cell cell = cptr->CellID;
			if (Is_Valid(cell)) {
				count++;
			}
			cptr = Iterate();
		}
		stream.Serialize(count);
		if (stream.Was_Error()) {
			return(false);
		}
		Reset_Iterator();
		cptr = Iterate();
		while (cptr != NULL) {
			Cell cell = cptr->CellID;
			if (Is_Valid(cell)) {
				Save_Object(stream, cptr);
				count--;
			}
			cptr = Iterate();
		}
		// The count was written before the cells, so a second pass that disagrees with it
		// has already written a map no load can read back.
		if (count != 0) {
			stream.Fail();
			return(false);
		}

		result = true;
	}
	return(result);
}
void MouseClass::Serialize(SaveStreamClass & stream)
{
	BASECLASS::Serialize(stream);
	// MouseShapes -- the cursor artwork and the table that drives it, both established by
	// One_Time.
	// MouseControl
	// IsSmall -- the cursor the player is looking at, which the input pass chooses again from
	// whatever lies beneath it.
	// CurrentMouseShape
	// NormalMouseShape
	// Timer
	// Frame
}

MouseClass::MouseStruct MouseClass::MouseControl[MOUSE_COUNT] = {
    {0,1,0,1,HSMIN,HSMIN},
    {2,1,0,-1,HSCNR,HSMIN},
    {3,1,0,-1,HSMAX,HSMIN},
    {4,1,0,-1,HSMAX,HSCNR},
    {5,1,0,-1,HSMAX,HSMAX},
    {6,1,0,-1,HSCNR,HSMAX},
    {7,1,0,-1,HSMIN,HSMAX},
    {8,1,0,-1,HSMIN,HSCNR},
    {9,1,0,-1,HSMIN,HSMIN},
    {10,1,0,-1,HSCNR,HSMIN},
    {11,1,0,-1,HSMAX,HSMIN},
    {12,1,0,-1,HSMAX,HSCNR},
    {13,1,0,-1,HSMAX,HSMAX},
    {14,1,0,-1,HSCNR,HSMAX},
    {15,1,0,-1,HSMIN,HSMAX},
    {16,1,0,-1,HSMIN,HSCNR},
    {17,1,0,-1,HSMIN,HSMIN},
    {18,13,4,-1,HSCNR,HSCNR},
    {31,10,4,42,HSCNR,HSCNR},
    {41,1,0,52,HSCNR,HSCNR},
    {53,5,4,63,HSCNR,HSCNR},
    {58,5,4,63,HSCNR,HSCNR},
    {68,5,4,73,HSCNR,HSCNR},
    {78,10,4,-1,HSCNR,HSCNR},
    {88,1,0,-1,HSCNR,HSCNR},
    {89,10,4,100,HSCNR,HSCNR},
    {99,1,0,63,HSCNR,HSCNR},
    {110,9,4,-1,HSCNR,HSCNR},
    {119,1,0,-1,HSCNR,HSCNR},
    {120,9,4,-1,HSCNR,HSCNR},
    {129,10,4,-1,HSCNR,HSCNR},
    {139,10,4,-1,HSCNR,HSCNR},
    {149,1,0,-1,HSCNR,HSCNR},
    {150,20,4,-1,HSCNR,HSCNR},
    {170,20,4,-1,HSCNR,HSCNR},
    {190,1,0,-1,HSCNR,HSCNR},
    {191,10,4,-1,HSCNR,HSCNR},
    {201,10,4,-1,HSCNR,HSCNR},
    {211,1,0,-1,HSCNR,HSCNR},
    {212,7,4,-1,HSCNR,HSCNR},
    {219,10,4,-1,HSCNR,HSCNR},
    {229,10,4,-1,HSCNR,HSCNR},
    {239,10,4,-1,HSCNR,HSCNR},
    {249,10,4,-1,HSCNR,HSCNR},
    {259,10,4,-1,HSCNR,HSCNR},
    {269,10,4,-1,HSCNR,HSCNR},
    {356,1,0,-1,HSCNR,HSCNR},
    {279,20,4,-1,HSCNR,HSCNR},
    {299,10,4,-1,HSCNR,HSCNR},
    {309,10,4,-1,HSCNR,HSCNR},
    {319,10,4,-1,HSCNR,HSCNR},
    {329,16,2,-1,HSCNR,HSCNR},
    {345,1,0,-1,HSCNR,HSCNR},
    {346,10,4,42,HSCNR,HSCNR},
    {357,20,3,-1,HSCNR,HSCNR},
    {377,1,0,-1,HSCNR,HSCNR},
    {378,1,0,-1,HSCNR,HSCNR},
    {379,1,0,-1,HSCNR,HSCNR},
    {380,1,0,-1,HSCNR,HSCNR},
    {381,1,0,-1,HSCNR,HSCNR},
    {382,1,0,-1,HSCNR,HSCNR},
    {383,1,0,-1,HSCNR,HSCNR},
    {384,1,0,-1,HSCNR,HSCNR},
    {385,1,0,-1,HSCNR,HSCNR},
    {386,1,0,-1,HSCNR,HSCNR},
    {387,10,4,-1,HSCNR,HSCNR},
};
