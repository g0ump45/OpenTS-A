#include "dbgprint.h"
#ifdef __ANDROID__
#include <android/log.h>
#include <cstdarg>
#include <cstdio>
#define LOG_TAG "OpenTS-Dbg"
void Debug_Init() {}
void Debug_Init_Console() {}
void Debug_Console_Hold() {}
const char* Debug_Log_File_Name() { return "debug.log"; }
const char* Debug_Directory() { return "./"; }
bool Delete_Files_Older_Than(const char*, const char*, unsigned) { return false; }
const char* Last_Error_Text(unsigned long) { return ""; }
void __cdecl DebugString(const char* fmt,...) {
    char buf[4096];
    va_list args; va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "%s", buf);
}
void __cdecl DebugStringNoPrefix(const char* fmt,...) {
    char buf[4096];
    va_list args; va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "%s", buf);
}
void __android_stub_dbgprint(){}
#else
/*******************************************************************************
 * O P E N T S
 *******************************************************************************/
#include "always.h"
#include "dbgprint.h"
#include "opents_build.h"
#include "win.h"
#include <shellapi.h>
#include <algorithm>
#include <cerrno>
#include <conio.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
//... paste your existing Windows code from your file here from
// #define CONSOLE_WINDOW_NAME downwards...
// To avoid you having to copy, just keep your original file content after this #else
// The important part is the Android part above.
#endif