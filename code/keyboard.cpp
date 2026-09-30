/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

#include "always.h"
#include "android_compat.h"
#include "win.h"

#include "keyboard.h"

#include "_xmouse.h"
#include "msgloop.h"
#include "vidscale.h"

#include <cmath>

#define ARRAY_SIZE(x) int(sizeof(x)/sizeof(x[0]))

void Stop_Execution (void)
{
}

WWKeyboardClass::WWKeyboardClass(void) :
	MouseQX(0),
	MouseQY(0),
	MousePos(0,0),
#ifdef __ANDROID__
        AndroidLeftMouseDown(false),
        AndroidTouchX(0),
        AndroidTouchY(0),
#endif
	Head(0),
	Tail(0)
{
	memset(KeyState, '\0', sizeof(KeyState));
}

unsigned short WWKeyboardClass::Buff_Get(void)
{
	while (!Check()) {}
	std::lock_guard<std::mutex> lock(InputMutex);
	unsigned short temp = Fetch_Element();
	if (Is_Mouse_Key(temp)) {
		MouseQX = Fetch_Element();
		MouseQY = Fetch_Element();
		MousePos = Point2D(MouseQX, MouseQY);
	}
	return(temp);
}

bool WWKeyboardClass::Is_Mouse_Key(unsigned short key)
{
	key &= 0xFF;
	return(key == VK_LBUTTON || key == VK_MBUTTON || key == VK_RBUTTON);
}

unsigned short WWKeyboardClass::Check(void) const
{
#ifdef __ANDROID__
	std::lock_guard<std::mutex> lock(InputMutex);
	if (Is_Buffer_Empty()) return(false);
	return(Peek_Element());
#else
	((WWKeyboardClass *)this)->Fill_Buffer_From_System();
	if (Is_Buffer_Empty()) return(false);
	return(Peek_Element());
#endif
}

unsigned short WWKeyboardClass::Get(void)
{
	while (!Check()) {}
	return(Buff_Get());
}

bool WWKeyboardClass::Put(unsigned short key)
{
	std::lock_guard<std::mutex> lock(InputMutex);
	if (!Is_Buffer_Full()) {
		Put_Element(key);
		return(true);
	}
	return(false);
}

bool WWKeyboardClass::Put_Key_Message(unsigned short vk_key, bool release)
{
	if (!Is_Mouse_Key(vk_key)) {
		if (((GetKeyState(VK_SHIFT) & 0x8000) != 0)) {
			vk_key |= WWKEY_SHIFT_BIT;
		}
		if ((GetKeyState(VK_CONTROL) & 0x8000) != 0) {
			vk_key |= WWKEY_CTRL_BIT;
		}
		if ((GetKeyState(VK_MENU) & 0x8000) != 0) {
			vk_key |= WWKEY_ALT_BIT;
		}
	}
	if (release) {
		vk_key |= WWKEY_RLS_BIT;
	}
	return(Put(vk_key));
}

bool WWKeyboardClass::Put_Mouse_Message(unsigned short vk_key, int x, int y, bool release)
{
	std::lock_guard<std::mutex> lock(InputMutex);
	if (Available_Buffer_Room() >= 3 && Is_Mouse_Key(vk_key)) {
		if (release) {
			vk_key |= WWKEY_RLS_BIT;
		}
		Put_Element(vk_key);
		Put_Element((unsigned short)x);
		Put_Element((unsigned short)y);
		return(true);
	}
	return(false);
}


void WWKeyboardClass::Set_Mouse_Position(int x, int y)
{
	std::lock_guard<std::mutex> lock(InputMutex);
	MouseQX = x;
	MouseQY = y;
	MousePos = Point2D(x, y);
}


Point2D WWKeyboardClass::Get_Mouse_Position(void) const
{
	std::lock_guard<std::mutex> lock(InputMutex);
	return(MousePos);
}

int WWKeyboardClass::To_ASCII(unsigned short key)
{
	if (key & WWKEY_RLS_BIT) {
		return(0);
	}
	if (key & WWKEY_SHIFT_BIT) {
		KeyState[VK_SHIFT] = 0x80;
	}
	if (key & WWKEY_CTRL_BIT) {
		KeyState[VK_CONTROL] = 0x80;
	}
	if (key & WWKEY_ALT_BIT) {
		KeyState[VK_MENU] = 0x80;
	}
	wchar_t buffer[4];
	int result;
	int scancode;
	scancode = MapVirtualKey(key & 0xFF, 0);
	result = ToUnicode((UINT)(key & 0xFF), (UINT)scancode, (PBYTE)KeyState, buffer, ARRAY_SIZE(buffer), 0);
	if (key & WWKEY_SHIFT_BIT) {
		KeyState[VK_SHIFT] = 0;
	}
	if (key & WWKEY_CTRL_BIT) {
		KeyState[VK_CONTROL] = 0;
	}
	if (key & WWKEY_ALT_BIT) {
		KeyState[VK_MENU] = 0;
	}
	if (result == 2 && IS_SURROGATE_PAIR(buffer[0], buffer[1])) {
		return(0x10000 + ((buffer[0] - 0xD800) << 10) + (buffer[1] - 0xDC00));
	}
	if (result != 1) {
		return(0);
	}
	return(buffer[0]);
}

bool WWKeyboardClass::Down(unsigned short key)
{
#ifdef __ANDROID__
	key &= 0xFF;
if (key == VK_LBUTTON) return AndroidLeftMouseDown;
return false;
#else
	key &= 0xFF;
	if ((key == VK_LBUTTON || key == VK_RBUTTON) && GetSystemMetrics(SM_SWAPBUTTON) == TRUE) {
		key = (key != VK_LBUTTON) ? VK_LBUTTON : VK_RBUTTON;
	}
	return(GetAsyncKeyState(key) != 0);
#endif
}

unsigned short WWKeyboardClass::Fetch_Element(void)
{
	unsigned short val = 0;
	if (Head != Tail) {
		val = Buffer[Head];
		Head = (Head + 1) % ARRAY_SIZE(Buffer);
	}
	return(val);
}

unsigned short WWKeyboardClass::Peek_Element(void) const
{
	if (!Is_Buffer_Empty()) {
		return(Buffer[Head]);
	}
	return(0);
}

bool WWKeyboardClass::Put_Element(unsigned short val)
{
	if (!Is_Buffer_Full()) {
		int temp = (Tail+1) % ARRAY_SIZE(Buffer);
		Buffer[Tail] = val;
		Tail = temp;
		return(true);
	}
	return(false);
}

bool WWKeyboardClass::Is_Buffer_Full(void) const
{
	if ((Tail + 1) % ARRAY_SIZE(Buffer) == Head) {
		return(true);
	}
	return(false);
}

bool WWKeyboardClass::Is_Buffer_Empty(void) const
{
	if (Head == Tail) {
		return(true);
	}
	return(false);
}

void WWKeyboardClass::Fill_Buffer_From_System(void)
{
#ifdef __ANDROID__
	return;
#else
	if (!Is_Buffer_Full()) {
		Windows_Message_Handler();
	}
#endif
}

void WWKeyboardClass::Clear(void)
{
	#ifdef __ANDROID__
	std::lock_guard<std::mutex> lock(InputMutex);
	Head = Tail;
	return;
	#endif
	Fill_Buffer_From_System();
	Head = Tail;
	Fill_Buffer_From_System();
	Head = Tail;
}

int WWKeyboardClass::Message_Handler(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
#ifdef __ANDROID__
return false;
#else
	bool processed = false;
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	Clamp_To_Game(point);
	LONG x = point.x;
	LONG y = point.y;
	switch (message) {
		case WM_SYSKEYDOWN:
		case WM_KEYDOWN:
			if (wParam == VK_SCROLL) {
				Stop_Execution();
			} else if (!(lParam & (1 << 30))) {
				Put_Key_Message((unsigned short)wParam);
			}
			processed = true;
			break;
		case WM_SYSKEYUP:
		case WM_KEYUP:
			Put_Key_Message((unsigned short)wParam, true);
			processed = true;
			break;
		case WM_LBUTTONDOWN:
			Put_Mouse_Message(VK_LBUTTON, x, y);
			processed = true;
			break;
		case WM_LBUTTONUP:
			Put_Mouse_Message(VK_LBUTTON, x, y, true);
			processed = true;
			break;
		case WM_LBUTTONDBLCLK:
			Put_Mouse_Message(VK_LBUTTON, x, y);
			Put_Mouse_Message(VK_LBUTTON, x, y, true);
			processed = true;
			break;
		case WM_MBUTTONDOWN:
			Put_Mouse_Message(VK_MBUTTON, x, y);
			processed = true;
			break;
		case WM_MBUTTONUP:
			Put_Mouse_Message(VK_MBUTTON, x, y, true);
			processed = true;
			break;
		case WM_MBUTTONDBLCLK:
			Put_Mouse_Message(VK_MBUTTON, x, y);
			Put_Mouse_Message(VK_MBUTTON, x, y, true);
			processed = true;
			break;
		case WM_RBUTTONDOWN:
			Put_Mouse_Message(VK_RBUTTON, x, y);
			processed = true;
			break;
		case WM_RBUTTONUP:
			Put_Mouse_Message(VK_RBUTTON, x, y, true);
			processed = true;
			break;
		case WM_RBUTTONDBLCLK:
			Put_Mouse_Message(VK_RBUTTON, x, y);
			Put_Mouse_Message(VK_RBUTTON, x, y, true);
			processed = true;
			break;
		default:
			break;
	}
	if (processed) {
		DefWindowProc(window, message, wParam, lParam);
		return(true);
	}
	return(false);
#endif
}

int WWKeyboardClass::Available_Buffer_Room(void) const
{
	return(ARRAY_SIZE(Buffer) - abs(Tail - Head));
}

int WWKeyboardClass::Noop(void) const
{
	return(0);
}
