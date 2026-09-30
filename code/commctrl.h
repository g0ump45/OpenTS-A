#pragma once
#ifdef __ANDROID__
#include "win.h"
typedef struct { DWORD dwSize; DWORD dwICC; } INITCOMMONCONTROLSEX;
#define ICC_BAR_CLASSES 0x00000004
inline void InitCommonControls() {}
inline BOOL InitCommonControlsEx(void*) { return TRUE; }
#ifndef TBM_SETRANGE
#define TBM_SETRANGE (0x0400+6)
#define TBM_SETPOS (0x0400+5)
#define TBM_GETPOS (0x0400)
#define TBM_SETRANGEMIN (0x0400+7)
#define TBM_SETRANGEMAX (0x0400+8)
#define TBS_HORZ 0
#endif
#ifndef PBM_SETRANGE
#define PBM_SETRANGE (0x0400+1)
#define PBM_SETPOS (0x0400+2)
#endif
#else
#include <commctrl.h>
#endif
