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


class GraphicMenuVersionText : public GraphicMenuItem
{
	public:
		GraphicMenuVersionText(int id, MSEngine & engine);
		virtual ~GraphicMenuVersionText(void) override;
};


class MSVersionTextAnim : public MSAnim
{
	public:
		MSVersionTextAnim(bool transient);
		virtual ~MSVersionTextAnim(void) override;
		virtual bool Advance(Surface * surface, Rect & rect) override;
		virtual void Redraw(Surface * surface, Rect const * rect) override;
		virtual Rect Get_Rect(void) const override;
		virtual bool Has_Finished(void) const override;
		virtual void Restore(Rect const & rect) override;

	private:
		/*
		 * If the anim is to be retired by its owner rather than by itself, then this flag
		 * will be true. Otherwise it asks to be deleted once the version stamp is down.
		 */
		bool Transient;

		/*
		 * If the version stamp has been put down, then this flag will be true. One pass is
		 * all it takes, so nothing more is drawn from then on.
		 */
		bool Done;
};
