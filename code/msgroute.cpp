/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "msgroute.h"

#include "vidscale.h"
#include "win.h"

#include <windowsx.h>


// Set while a re-targeted message is being delivered, so the receiving procedure's own
// call passes it straight through instead of routing it a second time.
static bool _RoutingMouseMessage = false;


/// <summary>
/// Does this message carry a mouse position in its lParam?
/// </summary>
static bool Is_Mouse_Coordinate_Message(UINT message)
{
	switch (message) {
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:
		case WM_MOUSEWHEEL:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_XBUTTONDBLCLK:
			return(true);

		default:
			return(false);
	}
}


/// <summary>
/// Is this message's position measured from the corner of the screen rather than from
/// the window it is delivered to?
/// </summary>
static bool Uses_Screen_Coordinates(UINT message)
{
	return(message == WM_MOUSEWHEEL);
}


/// <summary>
/// Finds the deepest descendant that owns a position, examining children topmost-first
/// the way native hit-testing does. A window answering WM_NCHITTEST with HTTRANSPARENT
/// passes the position to the sibling beneath it, which is what lets a click reach a
/// control that a group box frames.
/// </summary>
/// <param name="parent">The window whose children to search.</param>
/// <param name="parent_point">The position, in the parent's client space.</param>
/// <param name="screen_point">The same position in screen coordinates, for the
/// WM_NCHITTEST probe.</param>
/// <returns>The descendant that owns the position, or NULL when no child does.</returns>
static HWND Child_From_Logical_Point(HWND parent, POINT parent_point, POINT screen_point)
{
	for (HWND child = GetTopWindow(parent); child != NULL; child = GetWindow(child, GW_HWNDNEXT)) {
		if (!IsWindowVisible(child) || !IsWindowEnabled(child)) {
			continue;
		}

		RECT rect;
		GetWindowRect(child, &rect);
		MapWindowPoints(HWND_DESKTOP, parent, (POINT *)&rect, 2);
		if (!PtInRect(&rect, parent_point)) {
			continue;
		}

		if (SendMessage(child, WM_NCHITTEST, 0, MAKELPARAM((short)screen_point.x, (short)screen_point.y)) == HTTRANSPARENT) {
			continue;
		}

		POINT child_point = parent_point;
		MapWindowPoints(parent, child, &child_point, 1);

		HWND descendant = Child_From_Logical_Point(child, child_point, screen_point);
		return(descendant != NULL ? descendant : child);
	}

	return(NULL);
}


/// <summary>
/// Finds the window that owns a position in the frame, walking the tree the way Windows
/// would if the controls stood where the player sees them.
/// A window holding the mouse capture keeps the message whatever the position, which is
/// what lets the controls track a drag.
/// </summary>
/// <param name="logical_point">The position, in the frame.</param>
/// <returns>The window that owns it, or the main window when no control does.</returns>
static HWND Window_From_Logical_Point(POINT logical_point)
{
	HWND capture = GetCapture();
	if (capture != NULL && (capture == MainWindow || IsChild(MainWindow, capture))) {
		return(capture);
	}

	POINT screen_point = logical_point;
	ClientToScreen(MainWindow, &screen_point);

	HWND child = Child_From_Logical_Point(MainWindow, logical_point, screen_point);
	return(child != NULL ? child : MainWindow);
}


/// <summary>
/// Packs a frame position into an lParam in the space the receiving window expects.
/// </summary>
static LPARAM Logical_LParam_For_Target(HWND target, UINT message, POINT logical_point)
{
	POINT target_point = logical_point;

	if (Uses_Screen_Coordinates(message)) {
		Game_Point_To_Screen(target_point);
	} else if (target != MainWindow) {
		MapWindowPoints(MainWindow, target, &target_point, 1);
	}

	return(MAKELPARAM((short)target_point.x, (short)target_point.y));
}


/// <summary>
/// Converts a mouse message into frame coordinates and sends it to the window the player
/// sees under the cursor.
/// </summary>
/// <param name="window">The window whose procedure received the message.</param>
/// <param name="message">The message.</param>
/// <param name="wparam">Passed along unchanged.</param>
/// <param name="lparam">The position as Windows delivered it.</param>
/// <param name="translated_lparam">Receives the position to carry on with when this
/// returns false.</param>
/// <returns>bool; Was the message delivered elsewhere? The caller returns without
/// handling it when so.</returns>
bool Route_Mouse_Message(HWND window, UINT message, WPARAM wparam, LPARAM lparam, LPARAM * translated_lparam)
{
	if (translated_lparam != NULL) {
		*translated_lparam = lparam;
	}

	if (!Is_Mouse_Coordinate_Message(message) || MainWindow == NULL || _RoutingMouseMessage) {
		return(false);
	}

	if (!Video_Scaling_Active()) {
		return(false);
	}

	POINT point;
	point.x = GET_X_LPARAM(lparam);
	point.y = GET_Y_LPARAM(lparam);

	if (Uses_Screen_Coordinates(message)) {
		ScreenToClient(MainWindow, &point);
	} else if (window != MainWindow) {
		MapWindowPoints(window, MainWindow, &point, 1);
	}

	Window_Point_To_Game(point);

	HWND target = Window_From_Logical_Point(point);
	LPARAM target_lparam = Logical_LParam_For_Target(target, message, point);

	if (target == window) {
		if (translated_lparam != NULL) {
			*translated_lparam = target_lparam;
		}
		return(false);
	}

	if (IsWindow(target)) {
		_RoutingMouseMessage = true;
		SendMessage(target, message, wparam, target_lparam);
		_RoutingMouseMessage = false;
	}

	return(true);
}
