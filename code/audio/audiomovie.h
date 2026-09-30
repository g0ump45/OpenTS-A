/*******************************************************************************
 *                                O P E N  T S
 * audiomovie.h - Android fix with guard
 ******************************************************************************/

#pragma once

#include "vqaplay.h"

#ifndef AHANDLEINITPARAMS_DEFINED
#define AHANDLEINITPARAMS_DEFINED
struct AhandleInitParams
{
        unsigned short SampleRate;
        unsigned char Channels;
        unsigned char BitsPerSample;
        unsigned long Flags;
        void * Callback1;
        void * Callback2;
};
#endif

typedef long (__cdecl * AHANDLE_CALLBACK_1)(VQAHandle * vqa);
typedef long (__cdecl * AHANDLE_CALLBACK_2)(VQAHandle * vqa, void * buffer);

unsigned long __cdecl Simple_Timer_Callback_Audio_Handler(VQAHandle * vqa);
unsigned long __cdecl Timer_Callback_Audio_Handler(VQAHandle * vqa);

long __cdecl Lock_Audio_Handler(void);
long __cdecl Unlock_Audio_Handler(void);
intptr_t __cdecl Stream_Audio_Handler(VQAHandle * vqa, long action, void * buffer, long nbytes);
