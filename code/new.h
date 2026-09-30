#pragma once
#ifdef __ANDROID__
#include <new>
#else
#include_next <new.h>
#endif
