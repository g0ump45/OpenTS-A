#pragma once
#ifdef __ANDROID__
#include "android_compat.h"
// Minimal windowsx.h shim for Android
#ifndef _WINDOWSX_H
#define _WINDOWSX_H
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#define GET_X_PARAM(lParam) GET_X_LPARAM(lParam)
#define GET_Y_PARAM(lParam) GET_Y_LPARAM(lParam)
#endif
#else
#include_next <windowsx.h>
#endif
