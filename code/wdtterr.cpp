/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "ini.h"
#include "wdtnet.h"

#include <cstdio>

using namespace WorldDominationTour;


/// <summary>
/// Constructs a territory from its entry in the campaign map control file.
/// This routine fetches the territory's name, the description written for the player's
/// side, and the point its target marker is pinned to. It then creates the ownership and
/// highlight overlays and hands them to the presentation engine, which owns them from
/// then on. Both overlays start out inactive.
/// </summary>
/// <param name="fname">Name of the shape file the overlay animations are drawn from.</param>
/// <param name="name">Name of the control file section describing this territory.</param>
/// <param name="side">The side whose description text should be fetched.</param>
/// <param name="pos">Screen position of the map, which the territory origin is relative to.</param>
Territory::Territory(int id, const char * fname, INIClass const & ini, const char * name, int side, MSEngine & engine, ConvertClass * drawer, MS_ANIM_LIST * anims, Point2D const & pos) :
	ID(id),
	OwnerAnim(NULL),
	HighlightAnim(NULL),
	TargetAnim(NULL)
{
	ini.Get_String(name, "Name", 0, Name, sizeof(Name));

	char desc[64];
	sprintf(desc, "%sDescription", side == 3 ? "NOD" : "GDI");
	ini.Get_String(name, desc, 0, Description, sizeof(Description));

	Target = ini.Get_Point(name, "Target", Target);

	Point2D origin;
	origin = ini.Get_Point(name, "Origin", origin);
	origin += pos;

	OwnerAnim = new MSOverlayAnim(fname, origin.X, origin.Y, drawer, 3, anims, true, -1);
	OwnerAnim->Set_Active(false);
	engine.Add_Animation(OwnerAnim);

	HighlightAnim = new MSOverlayAnim(fname, origin.X, origin.Y, drawer, 2, anims, true, 0);
	HighlightAnim->Set_Active(false);
	engine.Add_Animation(HighlightAnim);
}


/// <summary>
/// Destroys the territory.
/// The overlay animations belong to the presentation engine rather than to the
/// territory, so there is nothing here to give back.
/// </summary>
Territory::~Territory(void)
{
	//nothing
}


/// <summary>
/// Sets the ownership overlay shown over this territory.
/// This routine is used as the campaign advances and territories change hands. The
/// overlay is switched to the artwork for the new owner and the affected part of the
/// map is restored, so the change is on screen by the time the routine returns.
/// </summary>
/// <param name="state">The ownership to display -- disputed, GDI held, or Nod held. Any
/// other value hides the overlay entirely.</param>
void Territory::Set_Owner_State(int state, MSEngine & engine, bool wait)
{
	if (OwnerAnim != NULL) {
		int frame = -1;
		switch (state) {
			case 1:
				frame = 3;
				break;
			case 2:
				frame = 2;
				break;
			case 3:
				frame = 1;
				break;
		}
		Rect oldanimrect = OwnerAnim->Get_Rect();
		if (frame >= 0) {
			OwnerAnim->Set_Frame(frame);
			OwnerAnim->Set_Active(true);
			OwnerAnim->Restart();
		} else {
			OwnerAnim->Set_Active(false);
		}

		Rect newanimrect = OwnerAnim->Get_Rect();
		Rect rect = Union(newanimrect, oldanimrect);
		engine.Restore_Anims(rect);
		engine.Restore_And_Advance();
		if (wait) {
			engine.Wait_Delay(1);
		} else {
			engine.Wait_Delay(1);
		}

	}
}


/// <summary>
/// Sets the mouse highlight for this territory.
/// This routine is used as the player moves the mouse across the campaign map and the
/// selected territory changes hands.
/// </summary>
/// <param name="active">Should the territory be shown as highlighted?</param>
/// <remarks>This routine will not return until the highlight animation has played out.</remarks>
void Territory::Set_Highlight(bool active, MSEngine & engine)
{
	if (HighlightAnim != NULL) {
		HighlightAnim->Set_Active(active);
		HighlightAnim->Restart();

		engine.Restore_Anims(HighlightAnim->Get_Rect());
		engine.Restore_And_Advance();
		engine.Wait_For_Anim(HighlightAnim);
	}
}


/// <summary>
/// Attaches the target marker animation to this territory.
/// This routine is used when the campaign map flags a territory as disputed, so that the
/// marker can be found again when the selection changes or the cycle ends.
/// </summary>
void Territory::Set_Target_Anim(MSAnim * anim)
{
	TargetAnim = anim;
}


/// <summary>
/// Detaches the target marker animation from this territory.
/// This routine is used when the campaign map tears down the markers left over from the
/// previous cycle, since it must know which animation to pull out of the presentation
/// engine.
/// </summary>
/// <returns>Returns with the animation detached, or NULL if this territory had none.</returns>
/// <remarks>The territory forgets the animation, so the caller must dispose of it.</remarks>
MSAnim * Territory::Remove_Target_Anim(void)
{
	MSAnim * old = TargetAnim;
	TargetAnim = NULL;
	return(old);
}


/// <summary>
/// Finds the territory that carries the specified identifier.
/// This routine is used by the world domination map handler to turn a territory number
/// -- picked off the click map or remembered from the hover state -- back into the
/// territory it belongs to.
/// </summary>
/// <returns>Returns with a pointer to the territory found. Otherwise, NULL is returned.</returns>
Territory * WorldDominationTour::Find_Territory_By_ID(TERR_LIST & terr, int id)
{
	for (Territory * territory : terr) {
		if (territory->ID == id) {
			return(territory);
		}
	}

	return(NULL);
}
