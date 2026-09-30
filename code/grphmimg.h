/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "grphmitm.h"


class GraphicMenuImageItem : public GraphicMenuItem
{
	friend GraphicMenuItem * GM_Read_Image_Item(const char * name, INIClass const & ini, MSEngine & engine, Point2D & image_size);

	public:
		GraphicMenuImageItem(int id, MSEngine & engine, Point2D const & origin, Rect const & rect, const char * image, const char * highlight_image, const char * disabled_image, char * highlight_sound, const char * select_vq);
		virtual ~GraphicMenuImageItem(void) override;

		virtual bool Is_Mouse_Over(Point2D const & mouse) override;
		virtual void Action(MSEngine * engine) override;
		virtual void On_Selected_Change(bool) override;
		virtual void On_Enabled_Change(bool) override;

	public:
		/*
		 * This points to the menu engine that owns this item. It holds the item's artwork
		 * and is the one asked to refresh the screen whenever the item changes state.
		 */
		MSEngine * Engine;

		/*
		 * This is the screen area the mouse must be within for this item to be selected. It
		 * is also the area redrawn whenever the item's artwork is swapped.
		 */
		Rect ActiveRect;

		/*
		 * These are the three pieces of artwork this item is drawn with, one for each of its
		 * states, of which only one is ever active at a time. Any of them may be absent, in
		 * which case that state of the item shows nothing at all.
		 */
		MSAnim * Image;				/// Available but not selected.
		MSAnim * HighlightImage;		/// Selected.
		MSAnim * DisabledImage;		/// Unavailable.

		/*
		 * This is the sound played as this item gains the selection. If NULL, then the item
		 * highlights silently.
		 */
		MSSfxEntry * HighlightSound;

		/*
		 * This is the name of the movie to play when this item is chosen. The movie runs
		 * after the item's action and the menu waits for it to finish.
		 */
		char SelectVQ[64];
};
