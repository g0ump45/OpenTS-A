/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

// The renderer's private interface. Only bgfxbackend.cpp includes bgfx, so no bgfx type
// appears here and no other translation unit needs the library's headers or its build
// settings. video.cpp is the only caller.

#pragma once

#include "nativewindow.hh"


enum BackendRenderer {
	BACKEND_RENDERER_AUTO,
	BACKEND_RENDERER_D3D11,
	BACKEND_RENDERER_D3D12,
	BACKEND_RENDERER_VULKAN,
	BACKEND_RENDERER_OPENGL,
};


enum BackendScaleMode {
	BACKEND_SCALE_NEAREST,
	BACKEND_SCALE_LINEAR,
	BACKEND_SCALE_PIXELART,
};


// Drawable sizes are physical pixel dimensions supplied by the application shell.
bool Backend_Init(NativeWindow const & window, int drawablewidth, int drawableheight, BackendRenderer renderer, bool vsync);
void Backend_Shutdown(void);

bool Backend_Set_Frame_Size(int width, int height);
void Backend_On_Resize(int drawablewidth, int drawableheight);

// Uploads the frame and presents it. The pixels are 16 bit 565 and stay owned by the
// caller; they are consumed before this returns.
void Backend_Present(void const * pixels, int pitch, int destx, int desty, int destwidth, int destheight, BackendScaleMode mode);

char const * Backend_Renderer_Name(void);
