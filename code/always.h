#pragma once
// OpenTS Android shim - ensure compat macros available everywhere
#ifndef _CONTROL
#define _CONTROL(c) ((c) & 0x1F)
#endif
#ifdef __ANDROID__
#include "android_compat.h"
#endif
// Minimal always.h to unblock Android builds - if original always.h exists, it should be included via chain
// The real OpenTS always.h includes many headers, but for Android we need at least this
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cassert>
