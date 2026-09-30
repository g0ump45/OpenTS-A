/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

class Surface;
class FileClass;
class PaletteClass;

class Animate
{
	public:
		Animate(void) {}
		virtual ~Animate(void) {};
		virtual bool Load(FileClass *file) = 0;
		virtual void Reset(void) = 0;
		virtual Surface *Load_Frame(int frame) = 0;
		virtual PaletteClass &Get_Palette(void) = 0;
		virtual int Get_Frame_Count(void) const = 0;
		virtual int Get_Width(void) const = 0;
		virtual int Get_Height(void) const = 0;
};
