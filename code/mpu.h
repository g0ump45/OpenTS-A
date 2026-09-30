#pragma once
#include <chrono>
inline unsigned int __cdecl Get_CPU_Clock(unsigned int & high) { high = 0; auto now = std::chrono::steady_clock::now().time_since_epoch(); return (unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(now).count(); }
inline unsigned int __cdecl Get_CPU_Rate(unsigned int & high) { high = 0; return 1000; }
inline void __cdecl RDTSC(void) {}
inline int __cdecl Get_RDTSC_CPU_Speed(void) { return 1000; }