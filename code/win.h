#pragma once
#ifdef __ANDROID__
#include "android_compat.h"
#endif

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
#include <cstdint>
#include <cstring>
#include <strings.h>
#include <unistd.h>

#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#ifndef _MAX_PATH
#define _MAX_PATH MAX_PATH
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef DEG_TO_RAD
#define DEG_TO_RAD(x) ((x) * 0.01745329251994329576923690768489f)
#endif

#ifdef __ANDROID__
// On Android, most base types come from android_compat.h
#ifndef _EXTRA_TYPES_DEFINED
#define _EXTRA_TYPES_DEFINED
typedef void* HACCEL;
typedef void* HRSRC; typedef void* HGLOBAL;
typedef const char* LPCTSTR;
typedef DWORD* PUINT;
typedef void* HFONT; typedef void* HBRUSH; typedef void* HBITMAP; typedef void* HGDIOBJ;
#define SW_HIDE 0
#define SW_SHOW 5
#define SW_SHOWNORMAL 1
#define IDCANCEL 2
#define IDOK 1
#define WM_COMMAND 0x0111
#define WM_INITDIALOG 0x0110
#define WM_CLOSE 0x0010
#define WM_DESTROY 0x0002
#define LOWORD(l) ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l) ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#ifndef _CONTROL
#define _CONTROL(c) ((c) & 0x1F)
#endif
#ifndef strupr
#define strupr _strupr
#endif


#endif
#else
// Non-Android, non-Win32: full definitions
typedef void* HWND; typedef void* HINSTANCE; typedef void* HANDLE; typedef void* HDC;
typedef void* HMODULE; typedef uint32_t DWORD; typedef uint32_t ULONG;
typedef int BOOL; typedef unsigned int UINT; typedef long LONG;
typedef char* LPSTR; typedef const char* LPCSTR; typedef const wchar_t* LPCWSTR;
typedef long HRESULT; typedef uintptr_t WPARAM; typedef intptr_t LPARAM;
typedef intptr_t INT_PTR; typedef uintptr_t UINT_PTR; typedef intptr_t LRESULT;
typedef intptr_t LONG_PTR; typedef uintptr_t ULONG_PTR; typedef uintptr_t DWORD_PTR;
typedef void* LPVOID; typedef const void* LPCVOID; typedef unsigned char BYTE;
typedef unsigned short WORD; typedef int INT;
typedef short SHORT; typedef unsigned short USHORT;
typedef void* HBITMAP; typedef void* HGDIOBJ; typedef void* HPALETTE;
typedef void* HBRUSH; typedef void* HFONT; typedef void* HRGN;
typedef DWORD COLORREF;
typedef void* HACCEL;
typedef void* HRSRC; typedef void* HGLOBAL;
typedef const char* LPCTSTR;
typedef DWORD* PUINT;
typedef struct _FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; } FILETIME;
typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime; FILETIME ftLastAccessTime; FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh; DWORD nFileSizeLow; DWORD dwReserved0; DWORD dwReserved1;
    char cFileName[MAX_PATH]; char cAlternateFileName[14];
} WIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
typedef WIN32_FIND_DATAA WIN32_FIND_DATA;
typedef struct tagRECT { LONG left; LONG top; LONG right; LONG bottom; } RECT, *LPRECT;
typedef struct tagPOINT { LONG x; LONG y; } POINT, *LPPOINT;
typedef struct tagMSG { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; } MSG, *LPMSG;
typedef struct tagDRAWITEMSTRUCT { UINT CtlType; UINT CtlID; UINT itemID; UINT itemAction; UINT itemState; HWND hwndItem; HDC hDC; RECT rcItem; ULONG_PTR itemData; } DRAWITEMSTRUCT, *LPDRAWITEMSTRUCT, *PDRAWITEMSTRUCT;
typedef LRESULT (CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
inline HANDLE FindFirstFileA(const char*, LPWIN32_FIND_DATAA) { return INVALID_HANDLE_VALUE; }
inline BOOL FindNextFileA(HANDLE, LPWIN32_FIND_DATAA) { return FALSE; }
inline BOOL FindClose(HANDLE) { return TRUE; }
#define FindFirstFile FindFirstFileA
#define FindNextFile FindNextFileA
#endif

// Common stubs for all non-Win32 (including Android) - but avoid duplicates when __ANDROID__
#ifndef __ANDROID__
// Only define these when not on Android, because android_compat.h already defines them
#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE ((HANDLE)(intptr_t)-1)
#endif
#ifndef MAXLONG
#define MAXLONG 0x7fffffff
#endif
#ifndef _ReturnAddress
#define _ReturnAddress() __builtin_return_address(0)
#endif
#define WINAPI
#define CALLBACK
#ifndef __forceinline
#define __forceinline inline
#endif
#ifndef MAKELONG
#define MAKELONG(a,b) ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#endif
#ifndef MAKELRESULT
#define MAKELRESULT(a,b) ((LRESULT)MAKELONG(a,b))
#endif
#ifndef LOWORD
#define LOWORD(l) ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#endif
#ifndef HIWORD
#define HIWORD(l) ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#endif
#ifndef DWLP_USER
#define DWLP_USER 8
#endif
#ifndef DWL_USER
#define DWL_USER DWLP_USER
#endif
#ifndef GWL_USERDATA
#define GWL_USERDATA (-21)
#endif
#ifndef GWLP_USERDATA
#define GWLP_USERDATA (-21)
#endif
#ifndef DWLP_MSGRESULT
#define DWLP_MSGRESULT 0
#endif
#ifndef RGB
#define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif
#define GetRValue(rgb) ((BYTE)(rgb))
#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb) ((BYTE)((rgb)>>16))
#ifndef FILE_ATTRIBUTE_READONLY
#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#define FILE_ATTRIBUTE_TEMPORARY 0x00000100
#endif
#define WM_COMMAND 0x0111
#define WM_INITDIALOG 0x0110
#define WM_CLOSE 0x0010
#define WM_DESTROY 0x0002
#define WM_PAINT 0x000F
#define WM_NOTIFY 0x004E
#define WM_HSCROLL 0x0114
#define WM_VSCROLL 0x0115
#define WM_USER 0x0400
#define SW_HIDE 0
#define SW_SHOW 5
#define SW_SHOWNORMAL 1
#define IDCANCEL 2
#define IDOK 1
#define IDYES 6
#define IDNO 7
#ifndef TEXT
#define TEXT(x) x
#endif
#define CP_UTF8 65001
#define MAX_COMPUTERNAME_LENGTH 15
#define MB_OK 0x00000000
#define MB_OKCANCEL 0x00000001
#define MB_YESNO 0x00000004
#define MB_ICONERROR 0x10
#define MB_ICONSTOP MB_ICONERROR
#define MB_ICONINFORMATION 0x40
#define MB_ICONQUESTION 0x20
#define MB_SETFOREGROUND 0x00010000
#define MB_TOPMOST 0x00040000
#define LANG_NEUTRAL 0x00
#define SUBLANG_DEFAULT 0x01
#define SUBLANG_NEUTRAL 0x00
#define ULONGLONG uint64_t
#define LONGLONG int64_t
#endif // __ANDROID__

#endif
extern int ShowCommand;
extern HINSTANCE ProgramInstance;
extern HWND MainWindow;
extern HWND UnusedWindow;
extern bool GameInFocus;
