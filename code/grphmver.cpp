/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "grphmver.h"

#include "_surface.h"
#include "ini.h"
#include "init.h"
#include "msanim.h"

/// <summary>
/// Creates a version text item from a graphic menu INI section.
/// This routine is used by the graphic menu item factory when it comes across a section of
/// type "Version".
/// </summary>
/// <param name="name">The INI section to build the item from.</param>
/// <returns>Returns with a pointer to the item created. Otherwise, NULL is returned.</returns>
GraphicMenuItem * GM_Read_Version_Item(const char * name, INIClass const & ini, MSEngine & engine)
{
	int id = ini.Get_Int(name, "ID", -1);
	if (id == -1) {
		return(NULL);
	}
	return(new GraphicMenuVersionText(id, engine));
}


/// <summary>
/// Creates a version text item for a graphic menu.
/// This routine hands a version text animation to the menu engine, which is what actually
/// puts the game version onto the screen. The item itself has nothing further to draw.
/// </summary>
/// <param name="engine">The menu engine that will run the version text animation.</param>
GraphicMenuVersionText::GraphicMenuVersionText(int id, MSEngine & engine) :
	GraphicMenuItem(id)
{
	engine.Add_Animation(new MSVersionTextAnim(true));
}


/// <summary>
/// Destroys the version text menu item.
/// The animation this item handed to the menu engine belongs to the engine, so there is
/// nothing left here to clean up.
/// </summary>
GraphicMenuVersionText::~GraphicMenuVersionText(void)
{
	//nothing
}


/// <summary>
/// Creates the version text animation.
/// The animation comes up active, so the game version is stamped onto the menu the first
/// time the engine gets around to it.
/// </summary>
MSVersionTextAnim::MSVersionTextAnim(bool transient) :
	MSAnim(0,0,false),
	Transient(transient),
	Done(false)
{
	Active = true;
}


/// <summary>
/// Advances the version text animation.
/// This routine stamps the game version onto the surface while the animation is active.
/// There is nothing to animate -- once the stamp is down, the routine is done.
/// </summary>
/// <returns>bool; Should the menu engine dispose of this animation?</returns>
bool MSVersionTextAnim::Advance(Surface * surface, Rect & rect)
{
	if (!Done) {
		if (Active) {
			Draw_Version_Text(surface);
			Done = true;
		}
	}
	return(Done && !Transient);
}


/// <summary>
/// Destroys the version text animation.
/// The version stamp is drawn straight onto the menu surface, so this routine has nothing
/// of its own to release.
/// </summary>
MSVersionTextAnim::~MSVersionTextAnim(void)
{
	//nothing
}


/// <summary>
/// Draws the version text in its current state.
/// The menu engine calls this routine when the surface has been repainted underneath the
/// animation and the version stamp is owed to it again.
/// </summary>
void MSVersionTextAnim::Redraw(Surface * surface, Rect const * rect)
{
	if (!Done && Active) {
		Draw_Version_Text(surface);
	}
}


/// <summary>
/// Restores the version text onto the alternate surface.
/// The menu engine calls this routine when the artwork beneath the animation has been put
/// back, so that the version stamp is not lost along with it.
/// </summary>
void MSVersionTextAnim::Restore(Rect const & rect)
{
	if (Active) {
		Draw_Version_Text(AlternateSurface);
	}
}


/// <summary>
/// Fetches the bounding rectangle of the version text.
/// The version stamp places itself on the surface, so the menu engine is handed an empty
/// rectangle rather than a region to look after.
/// </summary>
/// <returns>Returns with an empty rectangle.</returns>
Rect MSVersionTextAnim::Get_Rect(void) const
{
	return(Rect(0,0,0,0));
}


/// <summary>
/// Has the version text finished drawing itself?
/// </summary>
/// <returns>bool; Has the version stamp been put down?</returns>
bool MSVersionTextAnim::Has_Finished(void) const
{
	return(Done);
}
