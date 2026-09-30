/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "rect.h"
#include "vector.h"

class MapStage;
class MSAnimEntry;
class MSSfxEntry;
class CCINIClass;
class INIClass;
class MSShapeAnim;
class MSTextEntry;


class MapChoice
{
	public:
		MapChoice(void);
		~MapChoice(void);

		bool Initialize(char const * house_name);
		void Deinit(void);

		MapStage * Find_Stage_By_Name(char const * name);
		MapStage * Find_Stage_By_ID(unsigned short id);
		short Get_Stage_ID(MapStage * stage);

		MSSfxEntry * Find_Sound(char const * name);
		void Add_Sound(MSSfxEntry * sound) {if (sound != NULL) SoundEntries.Add(sound);}

		Rect * Get_Text_Rect(void) {return(&TextRect);}
		char const * Get_Anim_Palette_Name(void) {return(AnimPaletteName);}
		int Anim_Entry_Count(void) {return(AnimEntries.Count());}
		MSAnimEntry * Get_Anim_Entry(int index) {return(AnimEntries[index]);}
		int Sound_Entry_Count(void) {return(SoundEntries.Count());}
		MSSfxEntry * Get_Sound_Entry(int index) {return(SoundEntries[index]);}

	private:
		/*
		 * These are the stages of the house's campaign, in the order its control file section
		 * lists them. A stage's position here is the identifier the scenario record remembers.
		 */
		DynamicVectorClass<MapStage *> Stages;

		/*
		 * This is the area stage descriptions are printed within, expressed relative to the
		 * 640x400 presentation area and defaulting to all of it.
		 */
		Rect TextRect;

		/*
		 * This is the palette the background animations and target markers are drawn through.
		 * Without it no drawer can be built and the map selection screen refuses to run.
		 */
		char const * AnimPaletteName;

		/*
		 * These are the looping animations that decorate the map, positioned and paced by the
		 * control file. They belong to the campaign as a whole rather than to any one stage.
		 */
		DynamicVectorClass<MSAnimEntry *> AnimEntries;

		/*
		 * These are the sound effects the screen plays, asked for by name through Find_Sound.
		 * They are only loaded when the audio system is available.
		 */
		DynamicVectorClass<MSSfxEntry *> SoundEntries;
};


class MapSelection
{
	public:
		char * Get_Stage_Label(void) {return(StageLabel);}
		void Set_Stage_Label(char const * stage_label) {if (stage_label != NULL) StageLabel = strdup(stage_label);}

		char Get_Index(void) { return(Index); }
		void Set_Index(char index) { Index = index; }

		void Set_Target_Anim(MSShapeAnim * anim) {TargetAnim = anim;}
		MSShapeAnim * Get_Target_Anim(void) {return(TargetAnim);}

	private:
		/*
		 * This is the label of the stage that picking this region leads to.
		 */
		char * StageLabel;

		/*
		 * This is the click map color that marks out this region. The screen reads the pixel
		 * under the cursor and matches it against this value to know what is being pointed at.
		 */
		char Index;

		/*
		 * Pointer to the pulsing target marker drawn over this region. Its frame range is
		 * switched as the cursor enters and leaves, which is how the marker highlights.
		 */
		MSShapeAnim * TargetAnim;
};


class MapStage
{
	public:
		MapStage(INIClass const & ini, char const * label);
		~MapStage(void);

		char * Get_Stage_Label(void) const {return(StageLabel);}
		char * Get_Scenario_Name(void) const {return(ScenarioName);}
		char * Get_Map_VQ_Name(void) const {return(MapVQName);}
		char * Get_Voiceover(void) const {return(VoiceOver);}
		char * Get_Description(void) const {return(Description);}
		int Overlay_Count(void) const {return(OverlayCount);}
		char * Get_Overlay_Name(int index) const {return(OverlayNames[index]);}
		char * Get_Click_Map_Name(void) const {return(ClickMapName);}

		int Target_Count(void) const {return(Targets.Count());}
		Point2D Get_Target(int index) const {return(Targets[index]);}

		int Text_Entry_Count(void) const {return(TextEntries.Count());}
		MSTextEntry * Get_Text_Entry(int index) const {return(TextEntries[index]);}

		int Get_Selection_Count(void) const {return(Selections.Count());}
		MapSelection * Get_Selection(int index) const {return(Selections[index]);}
		MapSelection * Find_Selection_By_Name(char const * name) const;
		char * Find_Selection_By_Index(int index) const;

	private:
		/*
		 * This is the name of the control file section this stage was read from. A selection
		 * names the stage it leads to by this label.
		 */
		char * StageLabel;

		/*
		 * This is the scenario that is started when the player picks this stage.
		 */
		char * ScenarioName;

		/*
		 * This is the movie that presents the map itself, played before any of the overlays
		 * or target markers arrive. Without it the screen has nothing to show and gives up.
		 */
		char * MapVQName;

		/*
		 * This is the voice over played while the cursor rests on this stage's region. It is
		 * queued after a short delay, so brushing past a region does not trigger it.
		 */
		char * VoiceOver;

		/*
		 * This is the text printed in the text rectangle while the cursor rests on this
		 * stage's region -- either a string table entry or a text block from the control file.
		 */
		char * Description;

		/*
		 * This is how many overlay names the control file supplied for this stage (0 - 2).
		 */
		int OverlayCount;

		/*
		 * These are the shapes revealed over the map one after another, each announced with
		 * a sound, before the target markers fly in.
		 */
		char * OverlayNames[2];

		/*
		 * This is the picture whose pixel colors mark out the selectable regions of this
		 * stage's map. The color under the cursor is matched against a selection's index.
		 */
		char * ClickMapName;

		/*
		 * These are the positions the target markers are placed at, expressed relative to
		 * the 640x400 presentation area. They pair up with the selections by position.
		 */
		DynamicVectorClass<Point2D> Targets;

		/*
		 * These are the captions that appear over the map while its movie plays, each with
		 * its own position and moment of arrival. At most seven may be listed.
		 */
		DynamicVectorClass<MSTextEntry *> TextEntries;

		/*
		 * These are the selectable regions of this stage's map, one for each click map color
		 * the control file names. Each one leads to another stage.
		 */
		DynamicVectorClass<MapSelection *> Selections;
};


class MSAnimEntry
{
		friend class MapStage;
		friend class MapChoice;

	public:
		MSAnimEntry(char * string);
		~MSAnimEntry(void) {if (Filename != NULL) free((void *)Filename);}

		const char * Get_Filename(void) const { return(Filename); }
		int Get_X_Pos(void) const { return(XPos); }
		int Get_Y_Pos(void) const { return(YPos); }
		int Get_Rate(void) const { return(Rate); }

	private:
		/*
		 * This is the shape file whose frames this animation plays.
		 */
		const char * Filename;

		/*
		 * These are the screen coordinates the animation is drawn at, expressed relative to
		 * the 640x400 presentation area rather than to the screen itself.
		 */
		int XPos;
		int YPos;

		/*
		 * This is the delay between one frame of the animation and the next, in game frames.
		 */
		int Rate;
};


class MSTextEntry
{
		friend class MapStage;
		friend class MapChoice;

	public:
		MSTextEntry(char * string);
		~MSTextEntry(void) {if (String != NULL) free((void *)String);}

		int Get_X_Pos(void) const { return(XPos); }
		int Get_Y_Pos(void) const { return(YPos); }
		int Get_Start_Time(void) const { return(StartTime); }
		char * Get_String(void) const { return(String); }

	private:
		/*
		 * These are the screen coordinates the caption is printed at, expressed relative to
		 * the 640x400 presentation area rather than to the screen itself.
		 */
		int XPos;
		int YPos;

		/*
		 * This is how long the caption waits before it starts printing, expressed in game
		 * frames from the moment its stage's movie begins.
		 */
		int StartTime;

		/*
		 * This is the caption text. The map selection screen word wraps it in place before
		 * handing it to the printing animation.
		 */
		char * String;
};


class MSSfxEntry
{
		friend class MapStage;
		friend class MapChoice;

	public:
		MSSfxEntry(char const * name, char * string);
		~MSSfxEntry(void);

		char const * Get_Name(void) { return(Name); }

		void Play(void);

	private:
		/*
		 * This is the name the map selection screen asks for this sound by, not the file
		 * name. It stays NULL when the sound could not be set up, which is how a caller
		 * can tell that this entry is unusable.
		 */
		char * Name;

		/*
		 * If the sample had to be read out of a loose file rather than found in the
		 * mixfiles, then this flag will be true. Only then does this entry own the sample.
		 */
		bool AllocLoaded;

		/*
		 * Pointer to the sample data this sound effect plays. It is borrowed from the
		 * mixfiles where they carry it, and read from a loose file otherwise.
		 */
		void * Sample;

		/*
		 * This is the volume the sample is played at (0 - 255), converted from the
		 * percentage the control file specifies. At zero the sample is never loaded at all.
		 */
		int Volume;
};
