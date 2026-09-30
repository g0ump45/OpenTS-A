#pragma once
#ifndef _CPUID_DEFINED
#define _CPUID_DEFINED
#include "win.h"
inline void __cpuid(int cpuInfo[4], int infoType){ cpuInfo[0]=cpuInfo[1]=cpuInfo[2]=cpuInfo[3]=0; }
inline void __cpuidex(int cpuInfo[4], int infoType, int ecx){ cpuInfo[0]=cpuInfo[1]=cpuInfo[2]=cpuInfo[3]=0; }
#endif
