/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

// Delivery of mouse messages to the right dialog control once the frame is scaled.
//
// The dialogs are ordinary child windows sitting at positions in the frame, but the
// window shows that frame scaled, so Windows hands each click to whichever control
// physically covers the cursor rather than the one the player sees under it. Every
// window procedure that handles the mouse calls this first: it redoes the hit test in
// frame coordinates and sends the message on to the window that really owns the spot.

#pragma once

#include "win.h"


bool Route_Mouse_Message(HWND window, UINT message, WPARAM wparam, LPARAM lparam, LPARAM * translated_lparam);
