#ifndef _CONTROL
#define _CONTROL(c) ((c) & 0x1F)
#endif
#pragma once
#ifdef __ANDROID__
#include "android_compat.h"
#include "win.h"
#else
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include_next <windows.h>
#else
#include "win.h"
#endif
#endif
