#pragma once
#include <ctime>
#ifndef _TIMEB_DEFINED
#define _TIMEB_DEFINED
struct _timeb { long time; short millitm; short timezone; short dstflag; };
struct __timeb32 { long time; short millitm; short timezone; short dstflag; };
struct __timeb64 { long long time; short millitm; short timezone; short dstflag; };
inline void _ftime(struct _timeb* t){ if(t){ t->time=0; t->millitm=0; t->timezone=0; t->dstflag=0; } }
inline void _ftime32(struct __timeb32* t){ if(t){ t->time=0; t->millitm=0; t->timezone=0; t->dstflag=0; } }
inline void _ftime64(struct __timeb64* t){ if(t){ t->time=0; t->millitm=0; t->timezone=0; t->dstflag=0; } }
#endif
#ifndef _INC_TIMEB
#define _INC_TIMEB
#endif
