#pragma once
#ifndef ANDROID_COMPAT_H
#define ANDROID_COMPAT_H
#ifndef _CONTROL
#define _CONTROL(c) ((c) & 0x1F)
#endif
// Fix for Westwood size_of macro that breaks on Clang Android
#ifdef size_of
#undef size_of
#endif

// SAL annotations - Westwood uses IN, OUT etc
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef INOUT
#define INOUT
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif
#ifndef FAR
#define FAR
#endif
#ifndef NEAR
#define NEAR
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif
#define size_of(a,b) sizeof(((a*)nullptr)->b)
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#endif
#ifndef _countof
#define _countof(x) ARRAY_SIZE(x)
#endif

#ifdef __ANDROID__
#include <cstdint>
#include <cstring>
#include <strings.h>
#include <cmath>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <unistd.h>
#include <algorithm>
#include <utility>
#include <type_traits>
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#ifdef clamp
#undef clamp
#endif
// Permissive global min/max that handle mixed types - must be before any other code
template<class T, class U>
inline auto min(T a, U b) -> typename std::common_type<T,U>::type { using C = typename std::common_type<T,U>::type; return (C)a < (C)b ? (C)a : (C)b; }
template<class T, class U>
inline auto max(T a, U b) -> typename std::common_type<T,U>::type { using C = typename std::common_type<T,U>::type; return (C)a > (C)b ? (C)a : (C)b; }
template<class T, class U, class V>
inline auto min(T a, U b, V c) -> typename std::common_type<T,U, typename std::common_type<T,U>::type>::type { return min(min(a,b), c); }
template<class T, class U, class V>
inline auto max(T a, U b, V c) -> typename std::common_type<T,U, typename std::common_type<T,U>::type>::type { return max(max(a,b), c); }
// Also provide overloads that just use operator< without common_type for exotic types
template<class T, class U>
inline auto min_simple(T a, U b) { return a < b ? a : b; }

// Make std::min / std::max permissive for mixed int/size_t - MSVC allows this, Clang doesn't
// This is technically UB to add to std, but required for porting Westwood's std::min(int, size_t) usage
namespace std {
  template<class T, class U>
  inline auto min(T a, U b) -> typename std::enable_if<!std::is_same<T,U>::value, typename std::common_type<T,U>::type>::type {
    using C = typename std::common_type<T,U>::type;
    return (C)a < (C)b ? (C)a : (C)b;
  }
  template<class T, class U>
  inline auto max(T a, U b) -> typename std::enable_if<!std::is_same<T,U>::value, typename std::common_type<T,U>::type>::type {
    using C = typename std::common_type<T,U>::type;
    return (C)a > (C)b ? (C)a : (C)b;
  }
}



#ifndef stricmp
#define stricmp strcasecmp
#endif
#ifndef _stricmp
#define _stricmp strcasecmp
#endif
#ifndef _strnicmp
#define _strnicmp strncasecmp
#endif
#ifndef strnicmp
#define strnicmp strncasecmp
#endif
#ifndef strcmpi
#define strcmpi strcasecmp
#endif
#ifndef _strcmpi
#define _strcmpi strcasecmp
#endif
inline char* _strlwr(char* s){ for(char* p=s;*p;++p) *p=tolower(*p); return s; }
inline char* _strupr(char* s){ for(char* p=s;*p;++p) *p=toupper(*p); return s; }
#ifndef strlwr
#define strlwr _strlwr
#endif
#ifndef strupr
#define strupr _strupr
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif
#ifndef _MAX_PATH
#define _MAX_PATH MAX_PATH
#endif
#ifndef _MAX_FNAME
#define _MAX_FNAME 256
#endif
#ifndef _MAX_EXT
#define _MAX_EXT 256
#endif
#ifndef _MAX_DIR
#define _MAX_DIR 256
#endif
#ifndef _MAX_DRIVE
#define _MAX_DRIVE 3
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
#ifndef RAD_TO_DEG
#define RAD_TO_DEG(x) ((x) * 57.295779513082320876798154814105f)
#endif

#define WINAPI
#define CALLBACK
#ifndef __cdecl
#define __cdecl
#endif
#ifndef _cdecl
#define _cdecl
#endif

#include <cstddef>
typedef void* HWND; typedef void* HINSTANCE; typedef void* HANDLE; typedef void* HDC; typedef void* HACCEL;
typedef void* HMODULE; typedef uint32_t DWORD; typedef uint32_t ULONG;
typedef int BOOL; typedef unsigned int UINT; typedef long LONG;
typedef char* LPSTR; typedef const char* LPCSTR; typedef wchar_t* LPWSTR;
typedef const wchar_t* LPCWSTR; typedef long HRESULT;
typedef uintptr_t WPARAM; typedef intptr_t LPARAM; typedef intptr_t INT_PTR;
typedef uintptr_t UINT_PTR; typedef intptr_t LRESULT;
typedef intptr_t LONG_PTR; typedef uintptr_t DWORD_PTR; typedef uintptr_t ULONG_PTR;
typedef void* LPVOID; typedef const void* LPCVOID; typedef unsigned char BYTE;
typedef unsigned short WORD; typedef int INT;
typedef short SHORT; typedef unsigned short USHORT;
typedef struct _FILETIME { DWORD dwLowDateTime; DWORD dwHighDateTime; } FILETIME;
typedef FILETIME* LPFILETIME;
typedef FILETIME* PFILETIME;
typedef void* HBITMAP; typedef void* HGDIOBJ; typedef void* HPALETTE;
typedef void* HBRUSH;
typedef void* HRSRC; typedef void* HGLOBAL;
#ifndef _BITMAP_DEFINED
#define _BITMAP_DEFINED
typedef struct tagBITMAP { LONG bmType; LONG bmWidth; LONG bmHeight; LONG bmWidthBytes; WORD bmPlanes; WORD bmBitsPixel; LPVOID bmBits; } BITMAP, *PBITMAP;
#endif
typedef void* HFONT; typedef void* HRGN;
typedef DWORD COLORREF;
typedef DWORD* PUINT;
typedef uint64_t ULONGLONG;
typedef int64_t LONGLONG;
typedef BYTE* PBYTE; typedef WORD* PWORD; typedef DWORD* PDWORD;
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
#define MAKELANGID(p,s) ((((WORD)(s))<<10)|((WORD)(p)))
typedef struct tagMSGBOXPARAMSA { UINT cbSize; HWND hwndOwner; HINSTANCE hInstance; LPCSTR lpszText; LPCSTR lpszCaption; DWORD dwStyle; LPCSTR lpszIcon; DWORD dwContextHelpId; void* lpfnMsgBoxCallback; DWORD dwLanguageId; } MSGBOXPARAMSA, *LPMSGBOXPARAMSA;
typedef MSGBOXPARAMSA MSGBOXPARAMS;
#define _MSGBOXPARAMSA_DEFINED

typedef struct tagRECT { LONG left; LONG top; LONG right; LONG bottom; } RECT, *LPRECT;
typedef struct tagPOINT { LONG x; LONG y; } POINT, *LPPOINT;
typedef struct tagDRAWITEMSTRUCT { UINT CtlType; UINT CtlID; UINT itemID; UINT itemAction; UINT itemState; HWND hwndItem; HDC hDC; RECT rcItem; ULONG_PTR itemData; } DRAWITEMSTRUCT, *LPDRAWITEMSTRUCT, *PDRAWITEMSTRUCT;
typedef LRESULT (CALLBACK *DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef LRESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

inline LRESULT SendMessageA(HWND,UINT,WPARAM,LPARAM){ return 0; }
inline LRESULT SendMessageW(HWND,UINT,WPARAM,LPARAM){ return 0; }
inline LRESULT SendMessage(HWND,UINT,WPARAM,LPARAM){ return 0; }
inline BOOL UpdateWindow(HWND){ return TRUE; }
inline LONG_PTR SetWindowLongPtr(HWND,int,LONG_PTR){ return 0; }
inline LONG_PTR GetWindowLongPtr(HWND,int){ return 0; }
inline LONG SetWindowLong(HWND,int,LONG){ return 0; }
inline LONG GetWindowLong(HWND,int){ return 0; }
inline BOOL ShowWindow(HWND,int){ return TRUE; }
inline HWND GetDlgItem(HWND,int){ return nullptr; }
inline BOOL EndDialog(HWND,int){ return TRUE; }
inline int MessageBoxA(HWND,const char*,const char*,UINT){ return 0; }
inline int MessageBoxW(HWND,const wchar_t*,const wchar_t*,UINT){ return 0; }
#ifndef MessageBox
#define MessageBox MessageBoxA
#endif
#ifndef SNDMSG
#define SNDMSG ::SendMessage
#endif


// --- Basic Win32 constants missing previously ---
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
#define TEXT(x) x
#define CP_UTF8 65001
#define MAX_COMPUTERNAME_LENGTH 15
#ifndef LOWORD
#define LOWORD(l) ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#endif
#ifndef HIWORD
#define HIWORD(l) ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#endif
#ifndef MAKELONG
#define MAKELONG(a,b) ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#endif
#ifndef MAKELRESULT
#define MAKELRESULT(a,b) ((LRESULT)MAKELONG(a,b))
#endif
#ifndef MAKEWPARAM
#define MAKEWPARAM(l,h) ((WPARAM)MAKELONG(l,h))
#define MAKELPARAM(l,h) ((LPARAM)MAKELONG(l,h))
#endif
#ifndef DWLP_USER
#define DWLP_USER 8
#endif
#ifndef GWL_USERDATA
#define GWL_USERDATA (-21)
#ifndef GWLP_USERDATA
#define GWLP_USERDATA (-21)
#endif
#endif
#define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define GetRValue(rgb) ((BYTE)(rgb))
#define GetGValue(rgb) ((BYTE)(((WORD)(rgb)) >> 8))
#define GetBValue(rgb) ((BYTE)((rgb)>>16))

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE ((HANDLE)(intptr_t)-1)
#endif
#ifndef INVALID_FILE_SIZE
#define INVALID_FILE_SIZE ((DWORD)0xFFFFFFFF)
#endif
#ifndef FILE_BEGIN
#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2
#endif
#ifndef FILE_ATTRIBUTE_READONLY
#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
#define FILE_ATTRIBUTE_SYSTEM 0x00000004
#define FILE_ATTRIBUTE_DIRECTORY 0x00000010
#define FILE_ATTRIBUTE_ARCHIVE 0x00000020
#define FILE_ATTRIBUTE_TEMPORARY 0x00000100
#endif

#ifndef _WIN32_FIND_DATAA_DEFINED
#define _WIN32_FIND_DATAA_DEFINED
typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime; FILETIME ftLastAccessTime; FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh; DWORD nFileSizeLow; DWORD dwReserved0; DWORD dwReserved1;
    char cFileName[MAX_PATH]; char cAlternateFileName[14];
} WIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
typedef WIN32_FIND_DATAA WIN32_FIND_DATA;
#endif

typedef struct tagMSG { HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt; } MSG, *LPMSG;

inline unsigned long timeGetTime() { return (unsigned long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }

inline void _makepath(char* path, const char* drive, const char* dir, const char* fname, const char* ext) {
    path[0]=0; if(drive) strcat(path, drive); if(dir) strcat(path, dir); if(fname) strcat(path, fname);
    if (ext && ext[0]) {
        if (ext[0] != '.') strcat(path, ".");
        strcat(path, ext);
    }
}
inline void _splitpath(const char* path, char* drive, char* dir, char* fname, char* ext) {
    if(drive) drive[0]=0;
    if(dir){ dir[0]=0; const char* lastSlash = strrchr(path, '/'); if(!lastSlash) lastSlash=strrchr(path, '\\'); if(lastSlash){ size_t len=lastSlash-path+1; strncpy(dir, path, len); dir[len]=0; } }
    const char* base = strrchr(path, '/'); if(!base) base=strrchr(path, '\\'); if(base) base++; else base=path;
    const char* dot = strrchr(base, '.');
    if(fname){ if(dot){ size_t len=dot-base; strncpy(fname, base, len); fname[len]=0; } else strcpy(fname, base); }
    if(ext){ if(dot) strcpy(ext, dot); else ext[0]=0; }
}

#ifndef MAKELONG
#define MAKELONG(a,b) ((LONG)(((WORD)(((DWORD_PTR)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#endif
#ifndef DWLP_USER
#define DWLP_USER 8
#endif
#ifndef GWL_USERDATA
#define GWL_USERDATA (-21)
#ifndef GWLP_USERDATA
#define GWLP_USERDATA (-21)
#endif
#endif
#ifndef RGB
#define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif
#ifndef _ReturnAddress
#define _ReturnAddress() __builtin_return_address(0)
#endif
#ifndef OutputDebugString
#define OutputDebugStringA(x) ((void)0)
#define OutputDebugString OutputDebugStringA
#endif
#ifndef _aligned_malloc
#define _aligned_malloc(size,align) aligned_alloc(align, ((size + (align)-1) & ~((align)-1)))
#endif
#ifndef _aligned_free
#define _aligned_free(ptr) free(ptr)
#endif
inline void* _aligned_realloc(void* ptr, size_t size, size_t align){ (void)align; if(!ptr) return malloc(size); if(size==0){ free(ptr); return nullptr; } return realloc(ptr, size); }
inline HANDLE FindFirstFileA(const char*, LPWIN32_FIND_DATAA) { return INVALID_HANDLE_VALUE; }
inline BOOL FindNextFileA(HANDLE, LPWIN32_FIND_DATAA) { return FALSE; }
inline BOOL FindClose(HANDLE) { return TRUE; }
#define FindFirstFile FindFirstFileA
#define FindNextFile FindNextFileA

typedef struct _SYSTEMTIME { WORD wYear; WORD wMonth; WORD wDayOfWeek; WORD wDay; WORD wHour; WORD wMinute; WORD wSecond; WORD wMilliseconds; } SYSTEMTIME;
typedef union _ULARGE_INTEGER { struct { DWORD LowPart; DWORD HighPart; }; unsigned long long QuadPart; } ULARGE_INTEGER;
typedef struct _SRWLOCK { void* Ptr; } SRWLOCK;
#define SRWLOCK_INIT {0}
typedef void* HLOCAL;
inline HLOCAL LocalFree(HLOCAL) { return nullptr; }
inline const wchar_t* GetCommandLineW(){ return L""; }
#define _EXTRA_FUNCS_DEFINED
inline BOOL GetClientRect(HWND, LPRECT r){ if(r){ r->left=r->top=0; r->right=640; r->bottom=480; } return TRUE; }
inline BOOL GetWindowRect(HWND, LPRECT r){ if(r){ r->left=r->top=0; r->right=640; r->bottom=480; } return TRUE; }
inline BOOL InvalidateRect(HWND, const RECT*, BOOL){ return TRUE; }
inline HWND SetFocus(HWND h){ return h; }
inline void Sleep(DWORD ms){ usleep(ms*1000); }
inline DWORD GetLastError(){ return 0; }
inline BOOL GetDiskFreeSpaceExA(LPCSTR, void*, void*, void*){ return FALSE; }
inline BOOL GetDiskFreeSpaceExW(LPCWSTR, void*, void*, void*){ return FALSE; }
#define GetDiskFreeSpaceEx GetDiskFreeSpaceExA

inline void GetSystemTime(SYSTEMTIME*) {}
inline void GetLocalTime(SYSTEMTIME*) {}

inline LPWSTR* CommandLineToArgvW(const wchar_t*, int*){ return nullptr; }
inline BOOL SystemTimeToFileTime(const SYSTEMTIME*, FILETIME*){ return FALSE; }
inline BOOL DeleteFileA(const char*){ return TRUE; }
inline BOOL DeleteFileW(const wchar_t*){ return TRUE; }
#ifndef DeleteFile
#define DeleteFile DeleteFileA
#endif
inline BOOL AllocConsole(){ return TRUE; }
inline BOOL FreeConsole(){ return TRUE; }
inline HANDLE GetStdHandle(DWORD){ return nullptr; }
inline BOOL SetConsoleTextAttribute(HANDLE, WORD){ return TRUE; }
inline BOOL WriteConsoleA(HANDLE, const void*, DWORD, DWORD*, void*){ return TRUE; }
inline BOOL WriteConsoleW(HANDLE, const void*, DWORD, DWORD*, void*){ return TRUE; }

#ifndef _VERQUERYVALUE_DEFINED
#define _VERQUERYVALUE_DEFINED
template<typename T>
inline BOOL VerQueryValueA(LPCVOID,LPCSTR,LPVOID*,T*){ return FALSE; }
template<typename T>
inline BOOL VerQueryValueW(LPCVOID,LPCWSTR,LPVOID*,T*){ return FALSE; }
#endif

// --- Extended stubs ---
#ifndef _CONTROL
#define _CONTROL(c) ((c) & 0x1F)
#endif
// Fix for Westwood size_of macro that breaks on Clang Android
#ifdef size_of
#undef size_of
#endif

// SAL annotations - Westwood uses IN, OUT etc
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef INOUT
#define INOUT
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif
#ifndef FAR
#define FAR
#endif
#ifndef NEAR
#define NEAR
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif
#define size_of(a,b) sizeof(((a*)nullptr)->b)
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#endif
#ifndef _countof
#define _countof(x) ARRAY_SIZE(x)
#endif

#define WM_HELP 0x0053
#define WM_CONTEXTMENU 0x007B
#define BN_CLICKED 0
#define BN_DBLCLK 5
#define LBN_SELCHANGE 1
#define CBN_SELCHANGE 1
#define EN_CHANGE 0x0300
inline BOOL DestroyWindow(HWND){ return TRUE; }
#define ListBox_SetItemData(hwnd, idx, data) ((void)0)
#define ListBox_GetItemData(hwnd, idx) (0)

#define ComboBox_GetItemData(hwnd, idx) (0)
#define MAKEINTRESOURCEA(i) ((LPSTR)(uintptr_t)(i))
#define MAKEINTRESOURCEW(i) ((LPCWSTR)(uintptr_t)(i))
#define MAKEINTRESOURCE MAKEINTRESOURCEA
struct timeb { long time; unsigned short millitm; short timezone; short dstflag; };
inline int ftime(struct timeb* tp){ if(tp){ tp->time=0; tp->millitm=0; tp->timezone=0; tp->dstflag=0; } return 0; }
inline DWORD GetTickCount(){ return (DWORD)(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()); }
inline SHORT GetKeyState(int){ return 0; }
inline SHORT GetAsyncKeyState(int){ return 0; }
#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_CAPITAL 0x14
inline UINT MapVirtualKeyA(UINT, UINT){ return 0; }
inline UINT MapVirtualKeyW(UINT, UINT){ return 0; }
#define MapVirtualKey MapVirtualKeyA
#define MAPVK_VK_TO_VSC 0
#define MAPVK_VSC_TO_VK 1
#define IS_SURROGATE_PAIR(h,l) (0)
#define IS_HIGH_SURROGATE(w) (0)
#define IS_LOW_SURROGATE(w) (0)
#define SM_SWAPBUTTON 23
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define WM_SYSKEYDOWN 0x0104
#define WM_KEYDOWN 0x0100
#define WM_SYSKEYUP 0x0105
#define WM_KEYUP 0x0101
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_LBUTTONDBLCLK 0x0203
#define WM_MBUTTONDOWN 0x0207
#define WM_MBUTTONUP 0x0208
#define WM_MBUTTONDBLCLK 0x0209
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_RBUTTONDBLCLK 0x0206
#define WM_MOUSEMOVE 0x0200
#define WM_CHAR 0x0102
#define WM_MOUSEWHEEL 0x020A
inline INT_PTR DialogBoxParamA(HINSTANCE, LPCSTR, HWND, DLGPROC, LPARAM){ return 0; }
inline INT_PTR DialogBoxParamW(HINSTANCE, LPCWSTR, HWND, DLGPROC, LPARAM){ return 0; }
#define DialogBoxParam DialogBoxParamA
#define DialogBox DialogBoxParamA
inline int ToUnicode(UINT, UINT, const BYTE*, wchar_t*, int, UINT){ return 0; }
inline int GetSystemMetrics(int){ return 0; }
#ifndef _CPUID_DEFINED
#define _CPUID_DEFINED
inline void __cpuid(int cpuInfo[4], int infoType){ cpuInfo[0]=cpuInfo[1]=cpuInfo[2]=cpuInfo[3]=0; }
#endif
#define SB_THUMBTRACK 5
#define SB_THUMBPOSITION 4
#define SB_LINEUP 0
#define SB_LINEDOWN 1
#define SB_PAGEUP 2
#define SB_PAGEDOWN 3
#define SB_TOP 6
#define SB_BOTTOM 7
#define SB_ENDSCROLL 8
#define GW_CHILD 5
#define GW_HWNDNEXT 2
#define GW_HWNDPREV 3
#define RDW_INVALIDATE 0x0001
#define RDW_UPDATENOW 0x0100
#define RDW_ERASE 0x0004
#define RDW_ALLCHILDREN 0x0080
#define IDABORT 3
#define IDRETRY 4
#define IDIGNORE 5
inline BOOL RedrawWindow(HWND, const RECT*, HRGN, UINT){ return TRUE; }
inline HWND GetWindow(HWND, UINT){ return nullptr; }
#define Static_SetText(hwnd, txt) SetWindowText(hwnd, txt)
#define Button_SetText(hwnd, txt) SetWindowText(hwnd, txt)
#ifndef INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif
inline DWORD GetFileAttributesA(LPCSTR){ return 0; }
inline DWORD GetFileAttributesW(LPCWSTR){ return 0; }
#define GetFileAttributes GetFileAttributesA
inline BOOL CreateDirectoryA(LPCSTR, void*){ return TRUE; }
inline BOOL CreateDirectoryW(LPCWSTR, void*){ return TRUE; }
#define CreateDirectory CreateDirectoryA
#define Button_GetCheck(hwnd) (0)

#define BST_CHECKED 1
#define BST_UNCHECKED 0

// Additional stubs for conquer.cpp, data.cpp, desyncdlg.cpp
#define HWND_DESKTOP ((HWND)0)
#define HWND_TOP ((HWND)0)
#define HWND_BOTTOM ((HWND)1)
#define SWP_NOMOVE 0x0002
#define SWP_NOSIZE 0x0001
#define SWP_NOZORDER 0x0004
#define SWP_NOACTIVATE 0x0010
#define SWP_SHOWWINDOW 0x0040
#define SWP_HIDEWINDOW 0x0080
inline int LoadStringA(HINSTANCE, UINT, LPSTR, int){ return 0; }
inline int LoadStringW(HINSTANCE, UINT, LPWSTR, int){ return 0; }
#define LoadString LoadStringA
inline UINT GetACP(){ return 65001; }
inline HRSRC FindResourceA(HMODULE, LPCSTR, LPCSTR){ return nullptr; }
inline HRSRC FindResourceW(HMODULE, LPCWSTR, LPCWSTR){ return nullptr; }
#define FindResource FindResourceA
inline HGLOBAL LoadResource(HMODULE, HRSRC){ return nullptr; }
inline LPVOID LockResource(HGLOBAL){ return nullptr; }
inline HMODULE LoadLibraryA(LPCSTR){ return nullptr; }
inline HMODULE LoadLibraryW(LPCWSTR){ return nullptr; }
#define LoadLibrary LoadLibraryA
inline DWORD GetModuleFileNameA(HMODULE, LPSTR, DWORD){ return 0; }
inline DWORD GetModuleFileNameW(HMODULE, LPWSTR, DWORD){ return 0; }
#define GetModuleFileName GetModuleFileNameA
inline DWORD GetFileVersionInfoSizeA(LPCSTR, DWORD*){ return 0; }
inline DWORD GetFileVersionInfoSizeW(LPCWSTR, DWORD*){ return 0; }
#define GetFileVersionInfoSize GetFileVersionInfoSizeA
inline BOOL GetFileVersionInfoA(LPCSTR, DWORD, DWORD, LPVOID){ return FALSE; }
inline BOOL GetFileVersionInfoW(LPCWSTR, DWORD, DWORD, LPVOID){ return FALSE; }
#define GetFileVersionInfo GetFileVersionInfoA
inline BOOL SetWindowTextA(HWND, LPCSTR){ return TRUE; }
inline BOOL SetWindowTextW(HWND, LPCWSTR){ return TRUE; }
#define SetWindowText SetWindowTextA
inline BOOL SetForegroundWindow(HWND){ return TRUE; }
inline int MessageBoxIndirectA(const void*){ return 0; }
inline int MessageBoxIndirectW(const void*){ return 0; }
#define MessageBoxIndirect MessageBoxIndirectA

// More dialog/listbox stubs
#ifndef VerQueryValue
#define VerQueryValue VerQueryValueA
#endif
inline int MapWindowPoints(HWND, HWND, LPPOINT, UINT){ return 0; }
#define ListBox_ResetContent(hwnd) ((void)0)

#define ListBox_GetCount(hwnd) (0)
#define ListBox_DeleteString(hwnd, idx) (0)
#define ListBox_GetText(hwnd, idx, buf) (0)
#define ListBox_GetCurSel(hwnd) (0)
#define ListBox_SetCurSel(hwnd, idx) (0)
inline int GetWindowTextA(HWND, LPSTR, int){ return 0; }
inline int GetWindowTextW(HWND, LPWSTR, int){ return 0; }
#define GetWindowText GetWindowTextA
inline int GetWindowTextLengthA(HWND){ return 0; }
inline int GetWindowTextLengthW(HWND){ return 0; }
#define GetWindowTextLength GetWindowTextLengthA
inline BOOL SetDlgItemTextA(HWND, int, LPCSTR){ return TRUE; }
inline BOOL SetDlgItemTextW(HWND, int, LPCWSTR){ return TRUE; }
#define SetDlgItemText SetDlgItemTextA
#define WM_DRAWITEM 0x002B
#define WM_MOVING 0x0216
inline BOOL ValidateRect(HWND, const RECT*){ return TRUE; }
#define WM_CTLCOLORMSGBOX 0x0132
#define WM_CTLCOLOREDIT 0x0133
#define WM_CTLCOLORLISTBOX 0x0134
#define WM_CTLCOLORBTN 0x0135
#define WM_CTLCOLORDLG 0x0136
#define WM_CTLCOLORSCROLLBAR 0x0137
#define WM_CTLCOLORSTATIC 0x0138
#define WM_ERASEBKGND 0x0014
inline int wsprintfA(LPSTR, LPCSTR, ...){ return 0; }
inline int wsprintfW(LPWSTR, LPCWSTR, ...){ return 0; }
#define wsprintf wsprintfA
inline int wvsprintfA(LPSTR, LPCSTR, void*){ return 0; }
#define wvsprintf wvsprintfA


#define BLACK_BRUSH 4
#define WHITE_BRUSH 0
#define EN_SETFOCUS 0x0100
#define EN_KILLFOCUS 0x0200
#define BI_RGB 0
#define BI_BITFIELDS 3
#define DIB_RGB_COLORS 0
#define COLORONCOLOR 3
#define SRCCOPY 0x00CC0020
#define RGN_COPY 5
#define ListBox_SetTopIndex(hwnd, idx) ((void)0)
#define GetStockObject(x) nullptr
#pragma pack(push,1)
typedef struct tagBITMAPINFOHEADER { DWORD biSize; LONG biWidth; LONG biHeight; WORD biPlanes; WORD biBitCount; DWORD biCompression; DWORD biSizeImage; LONG biXPelsPerMeter; LONG biYPelsPerMeter; DWORD biClrUsed; DWORD biClrImportant; } BITMAPINFOHEADER, *PBITMAPINFOHEADER;
#pragma pack(pop)
typedef struct tagRGBQUAD { BYTE rgbBlue; BYTE rgbGreen; BYTE rgbRed; BYTE rgbReserved; } RGBQUAD;
typedef struct tagBITMAPINFO { BITMAPINFOHEADER bmiHeader; RGBQUAD bmiColors[1]; } BITMAPINFO, *PBITMAPINFO;
typedef struct tagDIBSECTION { BITMAP dsBm; BITMAPINFO dsBmih; DWORD dsOffset[3]; HANDLE dshSection; DWORD dsOffset2; } DIBSECTION, *PDIBSECTION;
inline HDC CreateCompatibleDC(HDC){ return nullptr; }
inline BOOL DeleteDC(HDC){ return TRUE; }
inline HGDIOBJ SelectObject(HDC, HGDIOBJ){ return nullptr; }
inline BOOL DeleteObject(HGDIOBJ){ return TRUE; }
inline BOOL GdiFlush(){ return TRUE; }
inline int SetStretchBltMode(HDC,int){ return 0; }
inline BOOL StretchBlt(HDC,int,int,int,int,HDC,int,int,int,int,DWORD){ return TRUE; }
inline BOOL BitBlt(HDC,int,int,int,int,HDC,int,int,DWORD){ return TRUE; }
inline HBITMAP CreateDIBSection(HDC, const void*, UINT, void**, HANDLE, DWORD){ return nullptr; }
inline int GetObjectA(HGDIOBJ,int,LPVOID){ return 0; }
inline int GetObjectW(HGDIOBJ,int,LPVOID){ return 0; }
#define GetObject GetObjectA
inline BOOL CloseWindow(HWND){ return TRUE; }
inline LRESULT DefWindowProcA(HWND,UINT,WPARAM,LPARAM){ return 0; }
inline LRESULT DefWindowProcW(HWND,UINT,WPARAM,LPARAM){ return 0; }
#define DefWindowProc DefWindowProcA
inline HDC GetDC(HWND){ return nullptr; }
inline int ReleaseDC(HWND,HDC){ return 1; }


#define LB_ERR (-1)
#define EM_SETLIMITTEXT 0x00C5
#ifndef Edit_SetSel
#define Edit_SetSel(hwnd, start, end) ((void)0)
#endif
#ifndef SendDlgItemMessageA
inline LRESULT SendDlgItemMessageA(HWND, int, UINT, WPARAM, LPARAM){ return 0; }
inline LRESULT SendDlgItemMessageW(HWND, int, UINT, WPARAM, LPARAM){ return 0; }
#endif
#ifndef SendDlgItemMessage
#define SendDlgItemMessage SendDlgItemMessageA
#endif
// SYSTEMTIME and filetime funcs already defined earlier at line 274/297, don't redefine
#ifndef _FILETIME_FUNCS_DEFINED_EXTRA
#define _FILETIME_FUNCS_DEFINED_EXTRA
#ifndef CompareFileTime
inline int CompareFileTime(const FILETIME*, const FILETIME*){ return 0; }
#endif
#ifndef FileTimeToLocalFileTime
inline BOOL FileTimeToLocalFileTime(const FILETIME*, FILETIME*){ return TRUE; }
#endif
#ifndef FileTimeToSystemTime
inline BOOL FileTimeToSystemTime(const FILETIME*, SYSTEMTIME*){ return TRUE; }
#endif
#endif

// --- Additional Win32 stubs for loaddlg, mainopt, milsectmr, mixfile ---
#ifndef LANG_USER_DEFAULT
#define LANG_USER_DEFAULT 0x0400
#endif
#ifndef TIME_NOMINUTESORSECONDS
#define TIME_NOMINUTESORSECONDS 0x00000001
#define TIME_NOSECONDS 0x00000002
#define TIME_NOTIMEMARKER 0x00000004
#define TIME_FORCE24HOURFORMAT 0x00000008
#endif
#ifndef LOCALE_USER_DEFAULT
#define LOCALE_USER_DEFAULT LANG_USER_DEFAULT
#endif
#ifndef GWL_STYLE
#define GWL_STYLE -16
#define GWL_EXSTYLE -20
#ifndef GWL_USERDATA
#define GWL_USERDATA -21
#endif
#ifndef GWLP_USERDATA
#define GWLP_USERDATA GWL_USERDATA
#endif
#endif
inline BOOL SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom){ if(lprc){ lprc->left=xLeft; lprc->top=yTop; lprc->right=xRight; lprc->bottom=yBottom; } return TRUE; }
inline BOOL SetRectEmpty(LPRECT lprc){ if(lprc){ lprc->left=lprc->top=lprc->right=lprc->bottom=0; } return TRUE; }
inline BOOL IsRectEmpty(const RECT* lprc){ return lprc==nullptr || (lprc->right<=lprc->left) || (lprc->bottom<=lprc->top); }
#ifndef MONITORINFO
typedef void* HMONITOR;
typedef struct tagMONITORINFO { DWORD cbSize; RECT rcMonitor; RECT rcWork; DWORD dwFlags; } MONITORINFO, *LPMONITORINFO;
#define MONITOR_DEFAULTTONULL 0
#define MONITOR_DEFAULTTOPRIMARY 1
#define MONITOR_DEFAULTTONEAREST 2
inline HMONITOR MonitorFromWindow(HWND, DWORD){ return nullptr; }
inline BOOL GetMonitorInfoA(HMONITOR, LPMONITORINFO){ return FALSE; }
#define GetMonitorInfo GetMonitorInfoA
#endif
inline BOOL PostMessageA(HWND, UINT, WPARAM, LPARAM){ return TRUE; }
inline BOOL PostMessageW(HWND, UINT, WPARAM, LPARAM){ return TRUE; }
#ifndef PostMessage
#define PostMessage PostMessageA
#endif
inline UINT timeBeginPeriod(UINT){ return 0; }
inline UINT timeEndPeriod(UINT){ return 0; }
// Ensure strupr available (already defined via _strupr but ensure macro after undef)
#ifndef strupr
#define strupr _strupr
#endif

// --- Extra stubs for mapgen, loaddlg, mainopt, mixfile ---
#ifndef GetDateFormat
inline int GetDateFormatA(DWORD, DWORD, const void*, const char*, char*, int){ return 0; }
inline int GetDateFormatW(DWORD, DWORD, const void*, const wchar_t*, wchar_t*, int){ return 0; }
#define GetDateFormat GetDateFormatA
inline int GetTimeFormatA(DWORD, DWORD, const void*, const char*, char*, int){ return 0; }
inline int GetTimeFormatW(DWORD, DWORD, const void*, const wchar_t*, wchar_t*, int){ return 0; }
#define GetTimeFormat GetTimeFormatA
#endif
#ifndef AdjustWindowRectEx
inline BOOL AdjustWindowRectEx(LPRECT, DWORD, BOOL, DWORD){ return TRUE; }
inline BOOL AdjustWindowRect(LPRECT, DWORD, BOOL){ return TRUE; }
#endif
#ifndef CopyFile
inline BOOL CopyFileA(LPCSTR, LPCSTR, BOOL){ return FALSE; }
inline BOOL CopyFileW(LPCWSTR, LPCWSTR, BOOL){ return FALSE; }
#define CopyFile CopyFileA
#endif
#ifndef SetWindowLongPtrA
inline LONG_PTR SetWindowLongPtrA(HWND, int, LONG_PTR){ return 0; }
inline LONG_PTR GetWindowLongPtrA(HWND, int){ return 0; }
inline LONG_PTR SetWindowLongPtrW(HWND, int, LONG_PTR){ return 0; }
inline LONG_PTR GetWindowLongPtrW(HWND, int){ return 0; }
#define SetWindowLongPtr SetWindowLongPtrA
#define GetWindowLongPtr GetWindowLongPtrA
#endif
// ComboBox messages
#ifndef CB_GETCOUNT
#define CB_GETCOUNT 0x0146
#define CB_ADDSTRING 0x0143
#define CB_DELETESTRING 0x0144
#define CB_GETCURSEL 0x0147
#define CB_SETCURSEL 0x014E
#define CB_SETITEMDATA 0x0151
#define CB_GETITEMDATA 0x0150
#define CB_FINDSTRING 0x014C
#define CB_FINDSTRINGEXACT 0x0158
#define CB_RESETCONTENT 0x014B
#define CB_GETLBTEXT 0x0148
#define CB_GETLBTEXTLEN 0x0149
#endif
// Ensure strupr still works after possible undef by other headers
#ifdef strupr
#undef strupr
#endif
#define strupr _strupr
#ifdef strlwr
#undef strlwr
#endif
#define strlwr _strlwr



// --- New batch for mpu, mpscore, mapgen dialog ---
#ifndef CheckDlgButton
inline BOOL CheckDlgButton(HWND, int, UINT){ return TRUE; }
inline UINT IsDlgButtonChecked(HWND, int){ return 0; }
inline BOOL CheckRadioButton(HWND,int,int,int){ return TRUE; }
#define BST_UNCHECKED 0
#define BST_CHECKED 1
#endif
#ifndef Button_Enable
#define Button_Enable(hwnd, b) ((void)0)
#ifndef Button_SetCheck
#define Button_SetCheck(hwnd, s) ((void)0)
#endif
#define Button_GetCheck(hwnd) (0)
#endif
// LARGE_INTEGER for mpu.cpp - only define if not already present
#ifndef _LARGE_INTEGER_DEFINED_EXTRA
#define _LARGE_INTEGER_DEFINED_EXTRA
#ifndef _LARGE_INTEGER_DEFINED
#define _LARGE_INTEGER_DEFINED
typedef union _LARGE_INTEGER {
  struct { DWORD LowPart; LONG HighPart; };
  struct { DWORD LowPart; LONG HighPart; } DUMMYSTRUCTNAME;
  struct { DWORD LowPart; LONG HighPart; } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
typedef LARGE_INTEGER _LARGE_INTEGER;
#endif
#ifndef _ULARGE_INTEGER_DEFINED_EXTRA
#define _ULARGE_INTEGER_DEFINED_EXTRA
// ULARGE_INTEGER already defined at line 313, only add PULARGE_INTEGER if missing
#ifndef PULARGE_INTEGER
typedef ULARGE_INTEGER* PULARGE_INTEGER;
#endif
#endif
inline BOOL QueryPerformanceFrequency(LARGE_INTEGER* f){ if(f) f->QuadPart=1000000; return TRUE; }
inline BOOL QueryPerformanceCounter(LARGE_INTEGER* c){ if(c){ c->QuadPart = (LONGLONG)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); } return TRUE; }
inline BOOL QueryPerformanceCounter(ULARGE_INTEGER* c){ if(c){ c->QuadPart = (ULONGLONG)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); } return TRUE; }
#endif
// __rdtsc for ARM - stub
#ifndef __rdtsc
inline uint64_t __rdtsc(){ return (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count(); }
#endif
// Fix strupr - force define after all
#ifdef strupr
#undef strupr
#endif
inline char* strupr(char* s){ for(char* p=s;*p;++p) *p=toupper(*p); return s; }
#ifdef _strupr
#undef _strupr
#endif
#define _strupr strupr



// --- Batch for msgbox, msgloop, netdlg2, msglist ---
#ifndef ScreenToClient
inline BOOL ScreenToClient(HWND, LPPOINT){ return TRUE; }
inline BOOL ScreenToClient(HWND, LPRECT){ return TRUE; }
inline BOOL ClientToScreen(HWND, LPPOINT){ return TRUE; }
inline BOOL ClientToScreen(HWND, LPRECT){ return TRUE; }
inline BOOL MoveWindow(HWND,int,int,int,int,BOOL){ return TRUE; }
#endif
#ifndef PM_NOREMOVE
#define PM_NOREMOVE 0x0000
#define PM_REMOVE 0x0001
#define PM_NOYIELD 0x0002
#endif
#ifndef GetMessage
inline BOOL GetMessageA(void*, HWND, UINT, UINT){ return FALSE; }
inline BOOL GetMessageW(void*, HWND, UINT, UINT){ return FALSE; }
#define GetMessage GetMessageA
inline BOOL PeekMessageA(void*, HWND, UINT, UINT, UINT){ return FALSE; }
inline BOOL PeekMessageW(void*, HWND, UINT, UINT, UINT){ return FALSE; }
#define PeekMessage PeekMessageA
inline BOOL TranslateMessage(const void*){ return FALSE; }
inline LRESULT DispatchMessageA(const void*){ return 0; }
inline LRESULT DispatchMessageW(const void*){ return 0; }
#define DispatchMessage DispatchMessageA
inline BOOL IsDialogMessageA(HWND, void*){ return FALSE; }
inline BOOL IsDialogMessageW(HWND, void*){ return FALSE; }
#define IsDialogMessage IsDialogMessageA
inline HACCEL TranslateAcceleratorA(HWND, HACCEL, void*){ return nullptr; }
inline HACCEL TranslateAcceleratorW(HWND, HACCEL, void*){ return nullptr; }
#define TranslateAccelerator TranslateAcceleratorA
#endif
// Listbox / Combobox extras missing
#ifndef CB_INSERTSTRING
#define CB_INSERTSTRING 0x014A
#define CB_ERR (-1)
#define CB_ERRSPACE (-2)
#define LB_GETTOPINDEX 0x018E
#define LB_SETTOPINDEX 0x019C
#define LB_RESETCONTENT 0x0184
#define LB_INSERTSTRING 0x0181
#define LB_ADDSTRING 0x0180
#define LB_DELETESTRING 0x0182
#define LB_GETCOUNT 0x018B
#define LB_GETCURSEL 0x0188
#define LB_SETCURSEL 0x0186
#define LB_GETTEXT 0x0189
#define LB_GETTEXTLEN 0x018A
#define LB_SETITEMDATA 0x019A
#define LB_GETITEMDATA 0x0199
#define LB_FINDSTRING 0x018F
#define LB_FINDSTRINGEXACT 0x01A2
#define LB_ERR (-1)
#define LB_ERRSPACE (-2)
#endif
// Fix bare _CONTROL usage: provide constant version
#ifndef _CONTROL_VALUE
#define _CONTROL_VALUE 32
#endif
// If code uses bare _CONTROL as constant, map it via macro trick
// We keep function macro _CONTROL(c) but also provide _CONTROL as 32 via enum hack for places that don't use parens
// Actually provide a fallback: if _CONTROL is used without parens, it will be undeclared, so we define a const int _CONTROL = 32 in C++
// But macro takes precedence, so we need to undefine and redefine as 32 for files that use bare version
// Workaround: define _CONTROL_BARE as 32 and patch msglist.cpp via script


// --- Batch for netshare.cpp ---
#ifndef SIZE_DEFINED
#define SIZE_DEFINED
typedef struct tagSIZE { LONG cx; LONG cy; } SIZE, *PSIZE, *LPSIZE;
#endif
#ifndef ListBox_InsertString
#define ListBox_InsertString(hwnd, idx, str) (0)
#ifndef ListBox_AddString
#define ListBox_AddString(hwnd, str) (0)
#endif
#define ListBox_GetCurSel(hwnd) (0)
#define ListBox_SetCurSel(hwnd, idx) (0)
#define ListBox_GetCount(hwnd) (0)
#endif
#ifndef WS_VISIBLE
#define WS_VISIBLE 0x10000000L
#define WS_CHILD 0x40000000L
#define WS_DISABLED 0x08000000L
#define WS_OVERLAPPED 0x00000000L
#define WS_CLIPSIBLINGS 0x04000000L
#define WS_CLIPCHILDREN 0x02000000L
#endif
#ifndef WM_SETTEXT
#define WM_SETTEXT 0x000C
#define WM_GETTEXT 0x000D
#define WM_GETTEXTLENGTH 0x000E
#define BM_SETCHECK 0x00F1
#define BM_GETCHECK 0x00F0
#define BST_PUSHED 0x0004
#endif
#ifndef SW_NORMAL
#define SW_NORMAL 1
#define SW_SHOWDEFAULT 10
#endif
#ifndef IsWindowEnabled
inline BOOL IsWindowEnabled(HWND){ return TRUE; }
#endif
#ifndef IsWindowVisible
inline BOOL IsWindowVisible(HWND){ return TRUE; }
#endif
#ifndef EnableWindow
inline BOOL EnableWindow(HWND, BOOL){ return TRUE; }
#endif
#ifndef LBS_MULTIPLESEL
#define LBS_MULTIPLESEL 0x0008
#define LBS_EXTENDEDSEL 0x0800
#define LBS_NOTIFY 0x0001
#define LBS_SORT 0x0002
#endif



// --- Batch for obscure, newmenu, options, ownrdraw ---
#ifndef strrev
inline char* strrev(char* s){ if(!s) return s; size_t len=strlen(s); for(size_t i=0;i<len/2;i++){ char t=s[i]; s[i]=s[len-1-i]; s[len-1-i]=t; } return s; }
#endif
#ifndef __forceinline
#define __forceinline inline
#endif
#ifndef HKM_GETHOTKEY
#define HKM_GETHOTKEY (WM_USER+1)
#define HKM_SETHOTKEY (WM_USER+2)
#define HKM_SETRULES (WM_USER+3)
#define HOTKEYF_SHIFT 0x01
#define HOTKEYF_CONTROL 0x02
#define HOTKEYF_ALT 0x04
#define HOTKEYF_EXT 0x08
#endif
#ifndef ComboBox_GetCurSel
#define ComboBox_GetCurSel(hwnd) (0)
#define ComboBox_SetCurSel(hwnd, idx) (0)
#define ComboBox_GetCount(hwnd) (0)
#define ComboBox_ResetContent(hwnd) (0)
#define ComboBox_AddString(hwnd, str) (0)
#define ComboBox_FindString(hwnd, idx, str) (-1)
#define ComboBox_FindStringExact(hwnd, idx, str) (-1)
#define ComboBox_GetText(hwnd, idx, buf) (0)
#define ComboBox_GetTextLength(hwnd, idx) (0)
#ifndef ComboBox_SetItemData
#define ComboBox_SetItemData(hwnd, idx, data) (0)
#endif
#define ComboBox_GetItemData(hwnd, idx) (0)
#define ComboBox_InsertString(hwnd, idx, str) (0)
#define ComboBox_DeleteString(hwnd, idx) (0)
#define ComboBox_Enable(hwnd, b) ((void)0)
#define ComboBox_ShowDropdown(hwnd, b) ((void)0)
#endif
// sys/timeb.h shim - Android doesn't have it, provide minimal struct
#ifndef _TIMEB_DEFINED
#define _TIMEB_DEFINED
struct _timeb { long time; short millitm; short timezone; short dstflag; };
inline void _ftime(struct _timeb* t){ if(t){ t->time=0; t->millitm=0; t->timezone=0; t->dstflag=0; } }
inline void _ftime_s(struct _timeb* t){ _ftime(t); }
#endif



// --- Batch for ownrdraw.cpp ---
#ifndef WNDCLASS
typedef struct tagWNDCLASSA { UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance; void* hIcon; void* hCursor; HBRUSH hbrBackground; LPCSTR lpszMenuName; LPCSTR lpszClassName; } WNDCLASSA, *PWNDCLASSA, *LPWNDCLASSA;
typedef WNDCLASSA WNDCLASS;
#define CS_HREDRAW 0x0002
#define CS_VREDRAW 0x0001
#define CS_DBLCLKS 0x0008
#endif
#ifndef CreateSolidBrush
inline HBRUSH CreateSolidBrush(COLORREF){ return nullptr; }
inline HBRUSH CreateHatchBrush(int, COLORREF){ return nullptr; }
#endif
#ifndef GetParent
inline HWND GetParent(HWND){ return nullptr; }
inline HWND GetAncestor(HWND, UINT){ return nullptr; }
#endif
#ifndef CB_GETITEMHEIGHT
#define CB_GETITEMHEIGHT 0x0154
#define CB_SETITEMHEIGHT 0x0153
#endif
#ifndef SCROLLINFO_DEFINED
#define SCROLLINFO_DEFINED
typedef struct tagSCROLLINFO { UINT cbSize; UINT fMask; int nMin; int nMax; UINT nPage; int nPos; int nTrackPos; } SCROLLINFO, *LPSCROLLINFO;
#define SIF_RANGE 0x0001
#define SIF_PAGE 0x0002
#define SIF_POS 0x0004
#define SIF_DISABLENOSCROLL 0x0008
#define SIF_TRACKPOS 0x0010
#define SIF_ALL (SIF_RANGE|SIF_PAGE|SIF_POS|SIF_TRACKPOS)
#define SBM_SETSCROLLINFO 0x00E9
#define SBM_GETSCROLLINFO 0x00EA
#define SB_HORZ 0
#define SB_VERT 1
#define SB_CTL 2
#endif
#ifndef BringWindowToTop
inline BOOL BringWindowToTop(HWND){ return TRUE; }
inline BOOL SetWindowPos(HWND, HWND, int, int, int, int, UINT){ return TRUE; }
#endif
#ifndef WM_CREATE
#define WM_CREATE 0x0001
#define WM_NCDESTROY 0x0082
#define WM_NCCREATE 0x0081
#define WM_SIZE 0x0005
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_MOUSEMOVE 0x0200
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#endif
#ifndef SetCapture
inline HWND SetCapture(HWND){ return nullptr; }
inline BOOL ReleaseCapture(){ return TRUE; }
inline HWND GetCapture(){ return nullptr; }
#endif
#ifndef GetScrollInfo
inline BOOL GetScrollInfo(HWND, int, LPSCROLLINFO){ return FALSE; }
inline int SetScrollInfo(HWND, int, LPSCROLLINFO, BOOL){ return 0; }
#endif



// --- Batch 6 for ownrdraw remaining ---
#ifndef RegisterClass
inline int RegisterClassA(const void*){ return 1; }
inline int RegisterClassW(const void*){ return 1; }
#define RegisterClass RegisterClassA
inline int UnregisterClassA(LPCSTR, HINSTANCE){ return 1; }
#define UnregisterClass UnregisterClassA
#endif
#ifndef SBM_GETPOS
#define SBM_GETPOS 0x00E0
#define SBM_GETRANGE 0x00E2
#define SBM_SETPOS 0x00E0
#define SBM_SETRANGE 0x00E6
#define CB_GETTOPINDEX 0x015C
#define CB_SETTOPINDEX 0x015D
#define CB_SHOWDROPDOWN 0x014F
#endif
#ifndef GWL_ID
#define GWL_ID -12
#define GWL_STYLE -16
#define GWL_EXSTYLE -20
#define GWLP_ID GWL_ID
#define GWLP_HINSTANCE -6
#endif
#ifndef CreateWindowEx
inline HWND CreateWindowExA(DWORD, LPCSTR, LPCSTR, DWORD, int,int,int,int, HWND, void*, HINSTANCE, LPVOID){ return (HWND)1; }
inline HWND CreateWindowExW(DWORD, LPCWSTR, LPCWSTR, DWORD, int,int,int,int, HWND, void*, HINSTANCE, LPVOID){ return (HWND)1; }
#define CreateWindowEx CreateWindowExA
inline HWND CreateWindowA(LPCSTR, LPCSTR, DWORD, int,int,int,int, HWND, void*, HINSTANCE, LPVOID){ return (HWND)1; }
#define CreateWindow CreateWindowA
#endif
#ifndef EnumChildWindows
typedef BOOL (CALLBACK *WNDENUMPROC)(HWND, LPARAM);
inline BOOL EnumChildWindows(HWND, WNDENUMPROC, LPARAM){ return TRUE; }
inline BOOL EnumWindows(WNDENUMPROC, LPARAM){ return TRUE; }
#endif
#ifndef GetClassName
inline int GetClassNameA(HWND, LPSTR, int){ return 0; }
inline int GetClassNameW(HWND, LPWSTR, int){ return 0; }
#define GetClassName GetClassNameA
#endif
#ifndef TRACKBAR_CLASS
#define TRACKBAR_CLASS "msctls_trackbar32"
#define PROGRESS_CLASS "msctls_progress32"
#define WC_TABCONTROL "SysTabControl32"
#define WC_LISTVIEW "SysListView32"
#define WC_TREEVIEW "SysTreeView32"
#define BS_GROUPBOX 0x00000007L
#define BS_AUTORADIOBUTTON 0x00000009L
#define BS_AUTOCHECKBOX 0x00000003L
#endif



// --- Batch for rawfile.cpp ---
#ifndef GENERIC_READ
#define GENERIC_READ 0x80000000L
#define GENERIC_WRITE 0x40000000L
#define GENERIC_EXECUTE 0x20000000L
#define GENERIC_ALL 0x10000000L
#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE 0x00000004
#define CREATE_NEW 1
#define CREATE_ALWAYS 2
#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4
#define TRUNCATE_EXISTING 5
#define FILE_ATTRIBUTE_NORMAL 0x80
#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_FLAG_SEQUENTIAL_SCAN 0x08000000
#define FILE_FLAG_RANDOM_ACCESS 0x10000000
#define INVALID_HANDLE_VALUE ((HANDLE)(intptr_t)-1)
#endif
#ifndef CloseHandle
// --- FIXED file handling for Android - use fopen/FILE* as HANDLE ---
inline BOOL CloseHandle(HANDLE h) {
    if (h == INVALID_HANDLE_VALUE || h == nullptr) return FALSE;
   if (h == (HANDLE)1) return TRUE;
    FILE* f = (FILE*)h;
    // Check if it's actually a FILE* by trying to see if it's a small integer (old stub)
    // If fclose fails, ignore
    fclose(f);
    return TRUE;
}
inline BOOL ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, DWORD* lpNumberOfBytesRead, LPVOID lpOverlapped) {
    if (hFile == INVALID_HANDLE_VALUE || hFile == nullptr) return FALSE;
    FILE* f = (FILE*)hFile;
    size_t read = fread(lpBuffer, 1, nNumberOfBytesToRead, f);
    if (lpNumberOfBytesRead) *lpNumberOfBytesRead = (DWORD)read;
    return TRUE; // Even if read < requested, return TRUE (EOF is not error)
}
inline BOOL WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, DWORD* lpNumberOfBytesWritten, LPVOID lpOverlapped) {
    if (hFile == INVALID_HANDLE_VALUE || hFile == nullptr) return FALSE;
    FILE* f = (FILE*)hFile;
    size_t written = fwrite(lpBuffer, 1, nNumberOfBytesToWrite, f);
    if (lpNumberOfBytesWritten) *lpNumberOfBytesWritten = (DWORD)written;
    return written == nNumberOfBytesToWrite;
}
inline DWORD SetFilePointer(HANDLE hFile, LONG lDistanceToMove, LONG* lpDistanceToMoveHigh, DWORD dwMoveMethod) {
    if (hFile == INVALID_HANDLE_VALUE || hFile == nullptr) return (DWORD)-1;
    FILE* f = (FILE*)hFile;
    int whence = SEEK_SET;
    if (dwMoveMethod == 1) whence = SEEK_CUR; // FILE_CURRENT
    else if (dwMoveMethod == 2) whence = SEEK_END; // FILE_END
    // Handle high part (ignore for now, files < 2GB)
    long offset = lDistanceToMove;
    if (lpDistanceToMoveHigh && *lpDistanceToMoveHigh != 0) {
        // 64-bit offset - combine
        int64_t full = ((int64_t)*lpDistanceToMoveHigh << 32) | (uint32_t)lDistanceToMove;
        // For simplicity, seek with fseeko if available, else limit
        fseek(f, (long)full, whence);
        long pos = ftell(f);
        return (DWORD)pos;
    }
    fseek(f, offset, whence);
    return (DWORD)ftell(f);
}
inline BOOL SetEndOfFile(HANDLE hFile) {
    if (hFile == INVALID_HANDLE_VALUE || hFile == nullptr) return FALSE;
    FILE* f = (FILE*)hFile;
    // Truncate at current position - use fflush and truncate via ftruncate if possible
    long pos = ftell(f);
    fflush(f);
    int fd = fileno(f);
    if (fd >= 0) {
        // ftruncate
        return ftruncate(fd, pos) == 0;
    }
    return TRUE;
}
inline DWORD GetFileSize(HANDLE hFile, DWORD* lpFileSizeHigh) {
    if (hFile == INVALID_HANDLE_VALUE || hFile == nullptr) return (DWORD)-1;
    FILE* f = (FILE*)hFile;
    long cur = ftell(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, cur, SEEK_SET);
    if (lpFileSizeHigh) *lpFileSizeHigh = 0;
    return (DWORD)size;
}
inline HANDLE CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, void* lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    if (!lpFileName) return INVALID_HANDLE_VALUE;
    // Choose mode based on access and disposition
    const char* mode = "rb";
    bool wantRead = (dwDesiredAccess & GENERIC_READ) != 0;
    bool wantWrite = (dwDesiredAccess & GENERIC_WRITE) != 0;
    if (wantWrite) {
        if (dwCreationDisposition == CREATE_ALWAYS) mode = "w+b";
        else if (dwCreationDisposition == CREATE_NEW) {
            FILE* test = fopen(lpFileName, "rb");
            if (test) { fclose(test); return INVALID_HANDLE_VALUE; }
            mode = "w+b";
        } else if (dwCreationDisposition == OPEN_ALWAYS) mode = "a+b";
        else if (dwCreationDisposition == TRUNCATE_EXISTING) mode = "w+b";
        else { // OPEN_EXISTING
            mode = wantRead ? "r+b" : "w+b";
        }
    } else {
        mode = "rb";
    }
    FILE* f = fopen(lpFileName, mode);
    if (!f) {
        // Try lower case fallback (Android ext4 is case sensitive)
        char lower[1024];
        strncpy(lower, lpFileName, sizeof(lower)-1);
        lower[sizeof(lower)-1]=0;
        for(char* p=lower; *p; ++p) *p=tolower(*p);
        f = fopen(lower, mode);
    }
    if (!f && wantRead) {
        // Last resort: try rb even if we wanted write
        f = fopen(lpFileName, "rb");
        if (!f) {
            char lower[1024];
            strncpy(lower, lpFileName, sizeof(lower)-1);
            lower[sizeof(lower)-1]=0;
            for(char* p=lower; *p; ++p) *p=tolower(*p);
            f = fopen(lower, "rb");
        }
    }
    if (!f) return INVALID_HANDLE_VALUE;
    return (HANDLE)f;
}
inline HANDLE CreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, void* lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    if (!lpFileName) return INVALID_HANDLE_VALUE;
    // Convert wide to narrow (simple)
    char narrow[1024];
    int i=0;
    for (; i<1023 && lpFileName[i]; ++i) narrow[i] = (char)lpFileName[i];
    narrow[i]=0;
    return CreateFileA(narrow, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}
#define CreateFile CreateFileA
#endif



// --- Batch for rawfile, savefile, saveload ---
#ifndef BY_HANDLE_FILE_INFORMATION_DEFINED
#define BY_HANDLE_FILE_INFORMATION_DEFINED
typedef struct _BY_HANDLE_FILE_INFORMATION {
  DWORD dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD dwVolumeSerialNumber;
  DWORD nFileSizeHigh;
  DWORD nFileSizeLow;
  DWORD nNumberOfLinks;
  DWORD nFileIndexHigh;
  DWORD nFileIndexLow;
} BY_HANDLE_FILE_INFORMATION, *PBY_HANDLE_FILE_INFORMATION, *LPBY_HANDLE_FILE_INFORMATION;
inline BOOL GetFileInformationByHandle(HANDLE hFile, LPBY_HANDLE_FILE_INFORMATION lpInfo) {
    if (hFile == INVALID_HANDLE_VALUE || hFile == nullptr || !lpInfo) return FALSE;
    FILE* f = (FILE*)hFile;
    long cur = ftell(f);
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, cur, SEEK_SET);
    memset(lpInfo, 0, sizeof(*lpInfo));
    lpInfo->nFileSizeLow = (DWORD)(size & 0xFFFFFFFF);
    lpInfo->nFileSizeHigh = (DWORD)((size >> 32) & 0xFFFFFFFF);
    lpInfo->dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
    return TRUE;
}
#endif
#ifndef DosDateTimeToFileTime_Defined
#define DosDateTimeToFileTime_Defined
inline BOOL DosDateTimeToFileTime(WORD, WORD, FILETIME*){ return FALSE; }
#endif
#ifndef FlushFileBuffers
inline BOOL FlushFileBuffers(HANDLE){ return TRUE; }
#define MOVEFILE_REPLACE_EXISTING 0x00000001
#define MOVEFILE_COPY_ALLOWED 0x00000002
inline BOOL MoveFileExA(LPCSTR, LPCSTR, DWORD){ return FALSE; }
inline BOOL MoveFileExW(LPCWSTR, LPCWSTR, DWORD){ return FALSE; }
#define MoveFileEx MoveFileExA
#endif
#ifndef GetSystemTimeAsFileTime
inline void GetSystemTimeAsFileTime(LPFILETIME){ }
inline BOOL FileTimeToDosDateTime(const FILETIME*, WORD*, WORD*){ return FALSE; }
inline BOOL SetFileTime(HANDLE, const FILETIME*, const FILETIME*, const FILETIME*){ return TRUE; }
inline BOOL GetFileTime(HANDLE, LPFILETIME, LPFILETIME, LPFILETIME){ return FALSE; }
#endif
#ifndef M_SQRT_2
#define M_SQRT_2 1.41421356237309504880
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef __int64
#define __int64 long long
#endif
#include <arpa/inet.h>
#ifndef ntohl
#define ntohl(x) __builtin_bswap32(x)
#define htonl(x) __builtin_bswap32(x)
#define ntohs(x) __builtin_bswap16(x)
#define htons(x) __builtin_bswap16(x)
#endif
#ifndef _int64
#define _int64 long long
#endif
// Fix static vs non-static for Add_Uncompressed_Events etc - just provide macros to remove static
// The real fix is in source, but we can avoid error by not defining static keyword?
// Better to patch queue.cpp / rules.cpp later, for now just ensure declarations match
// _FILETIME extra already defined above



// --- Batch for scroll.cpp ---
#ifndef WM_CAPTURECHANGED
#define WM_CAPTURECHANGED 0x0215
#define WM_MOUSEWHEEL 0x020A
#define WM_MOUSEHWHEEL 0x020E
#endif
#ifndef POINTS_DEFINED
#define POINTS_DEFINED
typedef struct tagPOINTS { SHORT x; SHORT y; } POINTS;
#define MAKEPOINTS(l) (*((POINTS*)&(l)))
#endif
#ifndef SM_CXDRAG
#define SM_CXDRAG 68
#define SM_CYDRAG 69
#define SM_CXDOUBLECLK 36
#define SM_CYDOUBLECLK 37
#endif
#ifndef GetDlgCtrlID
inline int GetDlgCtrlID(HWND){ return 0; }
#endif
#ifndef SetCursorPos
inline BOOL SetCursorPos(int, int){ return TRUE; }
inline BOOL GetCursorPos(LPPOINT p){ if(p){ p->x=0; p->y=0; } return TRUE; }
inline BOOL ClipCursor(const RECT*){ return TRUE; }
#endif



// --- Batch for srfcache, stats, startup ---
#ifndef BITMAPFILEHEADER_DEFINED
#define BITMAPFILEHEADER_DEFINED
#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER {
  WORD bfType;
  DWORD bfSize;
  WORD bfReserved1;
  WORD bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER, *LPBITMAPFILEHEADER;
#pragma pack(pop)
#endif
// BITMAPINFOHEADER, RGBQUAD, BITMAPINFO already defined above at line ~592
#ifndef RGBQUAD_DEFINED
#define RGBQUAD_DEFINED
// already defined
#endif

#ifndef MEMORYSTATUS_DEFINED
#define MEMORYSTATUS_DEFINED
typedef struct _MEMORYSTATUS {
  DWORD dwLength;
  DWORD dwMemoryLoad;
  DWORD dwTotalPhys;
  DWORD dwAvailPhys;
  DWORD dwTotalPageFile;
  DWORD dwAvailPageFile;
  DWORD dwTotalVirtual;
  DWORD dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;
inline void GlobalMemoryStatus(LPMEMORYSTATUS ms){ if(ms){ memset(ms,0,sizeof(*ms)); ms->dwLength=sizeof(*ms); ms->dwTotalPhys=1024*1024*1024; ms->dwAvailPhys=512*1024*1024; } }
#endif
#ifndef CP_ACP
#define CP_ACP 0
#define CP_UTF8 65001
#define CP_OEMCP 1
#endif
#ifndef CreateMutex
inline HANDLE CreateMutexA(void*, BOOL, LPCSTR){ return (HANDLE)1; }
inline HANDLE CreateMutexW(void*, BOOL, LPCWSTR){ return (HANDLE)1; }
#define CreateMutex CreateMutexA
inline HANDLE OpenMutexA(DWORD, BOOL, LPCSTR){ return (HANDLE)1; }
inline HANDLE OpenMutexW(DWORD, BOOL, LPCWSTR){ return (HANDLE)1; }
#define OpenMutex OpenMutexA
#define MUTEX_ALL_ACCESS 0x1F0001
#define ERROR_ALREADY_EXISTS 183L
#define WAIT_FAILED 0xFFFFFFFF
#define WAIT_OBJECT_0 0
#define WAIT_TIMEOUT 258
#define INFINITE 0xFFFFFFFF
inline DWORD WaitForSingleObject(HANDLE, DWORD){ return WAIT_OBJECT_0; }
inline DWORD WaitForSingleObjectEx(HANDLE, DWORD, BOOL){ return WAIT_OBJECT_0; }
inline HWND FindWindowA(LPCSTR, LPCSTR){ return nullptr; }
inline HWND FindWindowW(LPCWSTR, LPCWSTR){ return nullptr; }
#define FindWindow FindWindowA
#define SW_RESTORE 9
#endif
#ifndef GetStartupInfo
typedef struct _STARTUPINFOA { DWORD cb; LPSTR lpReserved; LPSTR lpDesktop; LPSTR lpTitle; DWORD dwX; DWORD dwY; DWORD dwXSize; DWORD dwYSize; DWORD dwXCountChars; DWORD dwYCountChars; DWORD dwFillAttribute; DWORD dwFlags; WORD wShowWindow; WORD cbReserved2; BYTE* lpReserved2; HANDLE hStdInput; HANDLE hStdOutput; HANDLE hStdError; } STARTUPINFOA, *LPSTARTUPINFOA;
#define GetStartupInfoA(x) ((void)0)
#define GetStartupInfo GetStartupInfoA
#endif



// --- Batch for startup.cpp, syncrechook.cpp ---
#ifndef WideCharToMultiByte
inline int WideCharToMultiByte(UINT, DWORD, LPCWSTR, int, LPSTR, int, LPCSTR, BOOL*){ return 0; }
inline int MultiByteToWideChar(UINT, DWORD, LPCSTR, int, LPWSTR, int){ return 0; }
#endif
#ifndef SetCurrentDirectory
inline BOOL SetCurrentDirectoryA(LPCSTR){ return TRUE; }
inline BOOL SetCurrentDirectoryW(LPCWSTR){ return TRUE; }
#define SetCurrentDirectory SetCurrentDirectoryA
inline DWORD GetCurrentDirectoryA(DWORD, LPSTR){ return 0; }
inline DWORD GetCurrentDirectoryW(DWORD, LPWSTR){ return 0; }
#define GetCurrentDirectory GetCurrentDirectoryA
#endif
#ifndef MB_ICONWARNING
#define MB_ICONWARNING 0x30
#define MB_ICONEXCLAMATION 0x30
#define MB_ICONASTERISK 0x40
#define MB_ICONHAND 0x10
#endif
#ifndef _controlfp
inline unsigned int _controlfp(unsigned int, unsigned int){ return 0; }
#define _MCW_EM 0x0008001F
#define _MCW_RC 0x00000300
#define _MCW_PC 0x00030000
#define _RC_NEAR 0x00000000
#define _PC_53 0x00010000
#endif

#ifndef FreeLibrary
typedef int (*FARPROC)();
inline BOOL FreeLibrary(HMODULE){ return TRUE; }
inline HMODULE GetModuleHandleA(LPCSTR){ return (HMODULE)1; }
inline HMODULE GetModuleHandleW(LPCWSTR){ return (HMODULE)1; }
#define GetModuleHandle GetModuleHandleA
inline FARPROC GetProcAddress(HMODULE, LPCSTR){ return (FARPROC)0; }
inline BOOL PostQuitMessage(int){ return TRUE; }
#endif
#ifndef IMAGE_DOS_HEADER_DEFINED
#define IMAGE_DOS_HEADER_DEFINED
#define IMAGE_DOS_SIGNATURE 0x5A4D
#define IMAGE_NT_SIGNATURE 0x00004550
#define IMAGE_NT_OPTIONAL_HDR32_MAGIC 0x10b
#define INVALID_SET_FILE_POINTER 0xFFFFFFFF
typedef struct _IMAGE_DOS_HEADER { WORD e_magic; WORD e_cblp; WORD e_cp; WORD e_crlc; WORD e_cparhdr; WORD e_minalloc; WORD e_maxalloc; WORD e_ss; WORD e_sp; WORD e_csum; WORD e_ip; WORD e_cs; WORD e_lfarlc; WORD e_ovno; WORD e_res[4]; WORD e_oemid; WORD e_oeminfo; WORD e_res2[10]; LONG e_lfanew; } IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;
typedef struct _IMAGE_FILE_HEADER { WORD Machine; WORD NumberOfSections; DWORD TimeDateStamp; DWORD PointerToSymbolTable; DWORD NumberOfSymbols; WORD SizeOfOptionalHeader; WORD Characteristics; } IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
typedef struct _IMAGE_DATA_DIRECTORY { DWORD VirtualAddress; DWORD Size; } IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;
#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES 16
typedef struct _IMAGE_OPTIONAL_HEADER32 { WORD Magic; BYTE MajorLinkerVersion; BYTE MinorLinkerVersion; DWORD SizeOfCode; DWORD SizeOfInitializedData; DWORD SizeOfUninitializedData; DWORD AddressOfEntryPoint; DWORD BaseOfCode; DWORD BaseOfData; DWORD ImageBase; DWORD SectionAlignment; DWORD FileAlignment; WORD MajorOperatingSystemVersion; WORD MinorOperatingSystemVersion; WORD MajorImageVersion; WORD MinorImageVersion; WORD MajorSubsystemVersion; WORD MinorSubsystemVersion; DWORD Win32VersionValue; DWORD SizeOfImage; DWORD SizeOfHeaders; DWORD CheckSum; WORD Subsystem; WORD DllCharacteristics; DWORD SizeOfStackReserve; DWORD SizeOfStackCommit; DWORD SizeOfHeapReserve; DWORD SizeOfHeapCommit; DWORD LoaderFlags; DWORD NumberOfRvaAndSizes; IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES]; } IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;
typedef struct _IMAGE_NT_HEADERS32 { DWORD Signature; IMAGE_FILE_HEADER FileHeader; IMAGE_OPTIONAL_HEADER32 OptionalHeader; } IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;
typedef IMAGE_NT_HEADERS32 IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS32 PIMAGE_NT_HEADERS;
#endif
// Ensure BITMAPFILEHEADER is packed to 14 bytes and MSBitmap size matches 58
#pragma pack(push,1)
#undef BITMAPFILEHEADER_DEFINED
#define BITMAPFILEHEADER_DEFINED_PACKED
struct tagBITMAPFILEHEADER_PACKED { WORD bfType; DWORD bfSize; WORD bfReserved1; WORD bfReserved2; DWORD bfOffBits; };
static_assert(sizeof(tagBITMAPFILEHEADER_PACKED)==14, "BITMAPFILEHEADER must be 14");
#pragma pack(pop)


// --- Batch for tactical.cpp GDI text/font ---
#ifndef FW_NORMAL
#define FW_DONTCARE 0
#define FW_THIN 100
#define FW_EXTRALIGHT 200
#define FW_LIGHT 300
#define FW_NORMAL 400
#define FW_MEDIUM 500
#define FW_SEMIBOLD 600
#define FW_BOLD 700
#define FW_EXTRABOLD 800
#define FW_HEAVY 900
#define ANSI_CHARSET 0
#define DEFAULT_CHARSET 1
#define OUT_DEFAULT_PRECIS 0
#define OUT_STRING_PRECIS 1
#define OUT_CHARACTER_PRECIS 2
#define OUT_STROKE_PRECIS 3
#define OUT_TT_PRECIS 4
#define OUT_DEVICE_PRECIS 5
#define OUT_RASTER_PRECIS 6
#define OUT_TT_ONLY_PRECIS 7
#define CLIP_DEFAULT_PRECIS 0
#define CLIP_CHARACTER_PRECIS 1
#define CLIP_STROKE_PRECIS 2
#define PROOF_QUALITY 2
#define DEFAULT_QUALITY 0
#define DRAFT_QUALITY 1
#define NONANTIALIASED_QUALITY 3
#define ANTIALIASED_QUALITY 4
#define FF_DONTCARE 0
#define FF_ROMAN 16
#define FF_SWISS 32
#define FF_MODERN 48
#define FF_SCRIPT 64
#define FF_DECORATIVE 80
#define DEFAULT_PITCH 0
#define FIXED_PITCH 1
#define VARIABLE_PITCH 2
#define TRANSPARENT 1
#define OPAQUE 2
#define TA_LEFT 0
#define TA_CENTER 6
#define TA_RIGHT 2
#define TA_TOP 0
#define TA_BOTTOM 8
#define TA_BASELINE 24
inline int SetBkMode(HDC, int){ return 0; }
inline int SetTextAlign(HDC, UINT){ return 0; }
inline COLORREF SetTextColor(HDC, COLORREF){ return 0; }
inline BOOL TextOutA(HDC, int, int, LPCSTR, int){ return TRUE; }
inline BOOL TextOutW(HDC, int, int, LPCWSTR, int){ return TRUE; }
#define TextOut TextOutA
inline BOOL ExtTextOutA(HDC,int,int,UINT,const RECT*,LPCSTR,UINT,const INT*){ return TRUE; }
#define ExtTextOut ExtTextOutA
#endif


// --- Batch for tooltip.cpp timers ---
#ifndef WM_TIMER
#define WM_TIMER 0x0113
#define WM_INITDIALOG 0x0110
#endif
#ifndef KillTimer
inline BOOL KillTimer(HWND, UINT_PTR){ return TRUE; }
inline UINT_PTR SetTimer(HWND, UINT_PTR, UINT, void*){ return 1; }
typedef void (CALLBACK *TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
#endif


// --- Batch for video.cpp DEVMODE ---
#ifndef POINTL_DEFINED
#define POINTL_DEFINED
typedef struct tagPOINTL { LONG x; LONG y; } POINTL, *PPOINTL, *LPPOINTL;
#endif
#ifndef DEVMODE_DEFINED
#define DEVMODE_DEFINED
#define CCHDEVICENAME 32
#define CCHFORMNAME 32
typedef struct _devicemodeA {
  BYTE dmDeviceName[CCHDEVICENAME];
  WORD dmSpecVersion;
  WORD dmDriverVersion;
  WORD dmSize;
  WORD dmDriverExtra;
  DWORD dmFields;
  short dmOrientation; short dmPaperSize; short dmPaperLength; short dmPaperWidth;
  short dmScale; short dmCopies; short dmDefaultSource; short dmPrintQuality;
  POINTL dmPosition;
  DWORD dmDisplayOrientation; DWORD dmDisplayFixedOutput;
  short dmColor; short dmDuplex; short dmYResolution; short dmTTOption; short dmCollate;
  BYTE dmFormName[CCHFORMNAME];
  WORD dmLogPixels; DWORD dmBitsPerPel; DWORD dmPelsWidth; DWORD dmPelsHeight;
  DWORD dmDisplayFlags;
  DWORD dmDisplayFrequency;
} DEVMODEA, *PDEVMODEA, *LPDEVMODEA;
typedef DEVMODEA DEVMODE;
typedef DEVMODEA* LPDEVMODE;
#define DM_PELSWIDTH 0x00080000
#define DM_PELSHEIGHT 0x00100000
#define DM_BITSPERPEL 0x00040000
#define DM_DISPLAYFREQUENCY 0x00400000
#define ENUM_CURRENT_SETTINGS ((DWORD)-1)
#define ENUM_REGISTRY_SETTINGS ((DWORD)-2)
inline BOOL EnumDisplaySettingsA(LPCSTR, DWORD, DEVMODEA*){ return FALSE; }
#define EnumDisplaySettings EnumDisplaySettingsA
inline LONG ChangeDisplaySettingsA(DEVMODEA*, DWORD){ return 0; }
#define ChangeDisplaySettings ChangeDisplaySettingsA
#define CDS_FULLSCREEN 0x00000004
#define DISP_CHANGE_SUCCESSFUL 0
#endif



// --- Batch for wincursor.cpp, windlg.cpp ---
#ifndef HCURSOR_DEFINED
#define HCURSOR_DEFINED
typedef void* HCURSOR;
typedef void* HICON;
typedef struct _ICONINFO { BOOL fIcon; DWORD xHotspot; DWORD yHotspot; HBITMAP hbmMask; HBITMAP hbmColor; } ICONINFO, *PICONINFO;
typedef struct tagLOGFONTA { LONG lfHeight; LONG lfWidth; LONG lfEscapement; LONG lfOrientation; LONG lfWeight; BYTE lfItalic; BYTE lfUnderline; BYTE lfStrikeOut; BYTE lfCharSet; BYTE lfOutPrecision; BYTE lfClipPrecision; BYTE lfQuality; BYTE lfPitchAndFamily; char lfFaceName[32]; } LOGFONTA, *PLOGFONTA, *LPLOGFONTA;
typedef LOGFONTA LOGFONT;
typedef LOGFONTA* LPLOGFONT;
typedef struct tagTEXTMETRICA { LONG tmHeight; LONG tmAscent; LONG tmDescent; LONG tmInternalLeading; LONG tmExternalLeading; LONG tmAveCharWidth; LONG tmMaxCharWidth; LONG tmWeight; LONG tmOverhang; LONG tmDigitizedAspectX; LONG tmDigitizedAspectY; BYTE tmFirstChar; BYTE tmLastChar; BYTE tmDefaultChar; BYTE tmBreakChar; BYTE tmItalic; BYTE tmUnderlined; BYTE tmStruckOut; BYTE tmPitchAndFamily; BYTE tmCharSet; } TEXTMETRICA, *PTEXTMETRICA, *LPTEXTMETRICA;
typedef TEXTMETRICA TEXTMETRIC;
typedef TEXTMETRICA* LPTEXTMETRIC;
typedef const void* LPCDLGTEMPLATEA;
typedef LPCDLGTEMPLATEA LPCDLGTEMPLATE;
#define GWLP_HWNDPARENT (-8)
#define GM_ADVANCED 2
inline HBITMAP CreateBitmap(int,int,UINT,UINT,const void*){ return nullptr; }
inline HCURSOR CreateIconIndirect(const ICONINFO*){ return nullptr; }
inline BOOL DestroyCursor(HCURSOR){ return TRUE; }
inline HCURSOR SetCursor(HCURSOR){ return nullptr; }
inline int ShowCursor(BOOL){ return 0; }
inline int SaveDC(HDC){ return 0; }
inline BOOL RestoreDC(HDC,int){ return TRUE; }
inline int SetGraphicsMode(HDC,int){ return 0; }
inline BOOL SetWorldTransform(HDC,const void*){ return TRUE; }
inline HWND CreateDialogParamA(HINSTANCE,LPCSTR,HWND,void*,LPARAM){ return nullptr; }
inline HWND CreateDialogParamW(HINSTANCE,LPCWSTR,HWND,void*,LPARAM){ return nullptr; }
#define CreateDialogParam CreateDialogParamA
inline BOOL ComboBox_GetDroppedControlRect(HWND,RECT*){ return FALSE; }
#endif


// --- Batch for winfix.cpp treeview ---
#ifndef HTREEITEM_DEFINED
#define HTREEITEM_DEFINED
typedef void* HTREEITEM;
typedef void* HIMAGELIST;
typedef struct tagNMTREEVIEWA { void* hdr; UINT action; struct { HTREEITEM hItem; UINT state; UINT stateMask; LPSTR pszText; int cchTextMax; int iImage; int iSelectedImage; int cChildren; LPARAM lParam; } itemOld; struct { HTREEITEM hItem; UINT state; UINT stateMask; LPSTR pszText; int cchTextMax; int iImage; int iSelectedImage; int cChildren; LPARAM lParam; } itemNew; POINT ptDrag; } NMTREEVIEWA, *LPNMTREEVIEWA;
typedef NMTREEVIEWA NMTREEVIEW;
typedef NMTREEVIEWA* LPNMTREEVIEW;
#define TreeView_SelectItem(hwnd,item) (TRUE)
#define TreeView_GetIndent(hwnd) (0)
#define TreeView_GetFirstVisible(hwnd) ((HTREEITEM)0)
#define TreeView_SelectDropTarget(hwnd,item) (TRUE)
#define ImageList_DragEnter(hwnd,x,y) (TRUE)
#define ImageList_DragShowNolock(b) (TRUE)
#define ImageList_EndDrag() (TRUE)
#define ImageList_DragLeave(hwnd) (TRUE)
#define ChildWindowFromPoint(hwnd,pt) ((HWND)0)
#define IDC_ARROW ((LPCSTR)32512)
#define IDC_NO ((LPCSTR)32648)
inline HWND ImageList_DragMove(int,int){ return nullptr; }
#endif


// --- Batch for winstub.cpp ---
#ifndef WINSTUB_DEFINED
#define WINSTUB_DEFINED
typedef void* HMENU;
#define WM_XBUTTONDOWN 0x020B
#define WM_XBUTTONUP 0x020C
#define WM_XBUTTONDBLCLK 0x020D
#define WM_NCHITTEST 0x0084
#define HTTRANSPARENT -1
#define WM_EXCEPTION_TEST 0x03E9
#define WM_SHOWWINDOW 0x0018
#define WM_SETCURSOR 0x0020
#define WM_DISPLAYCHANGE 0x007E
#define WM_MOVE 0x0003
#define WM_ACTIVATEAPP 0x001C
#define WM_SYSCOMMAND 0x0112
#define WM_ACTIVATE 0x0006
#define WM_SIZE 0x0005
#define WM_ENTERSIZEMOVE 0x0231
#define WM_EXITSIZEMOVE 0x0232
#define WM_GETMINMAXINFO 0x0024
#define WM_NCDESTROY 0x0082
#define HTCLIENT 1
#define SIZE_MINIMIZED 1
#define SIZE_RESTORED 0
#define SIZE_MAXIMIZED 2
#define SC_CLOSE 0xF060
#define SC_SCREENSAVE 0xF140
#define SC_MONITORPOWER 0xF170
#define VREFRESH 0
#define WS_OVERLAPPEDWINDOW 0x00CF0000L
#define WS_POPUP 0x80000000L
#define WS_VISIBLE 0x10000000L
#define WS_CLIPSIBLINGS 0x04000000L
#define WS_CLIPCHILDREN 0x02000000L
#define WS_CAPTION 0x00C00000L
#define WS_SYSMENU 0x00080000L
#define WS_THICKFRAME 0x00040000L
#define WS_MINIMIZEBOX 0x00020000L
#define WS_MAXIMIZEBOX 0x00010000L
inline HWND SetActiveWindow(HWND){ return nullptr; }
inline HMENU GetMenu(HWND){ return nullptr; }
inline HICON LoadIconA(HINSTANCE,LPCSTR){ return nullptr; }
inline HICON LoadIconW(HINSTANCE,LPCWSTR){ return nullptr; }
#define LoadIcon LoadIconA
inline HCURSOR LoadCursorA(HINSTANCE,LPCSTR){ return nullptr; }
inline HCURSOR LoadCursorW(HINSTANCE,LPCWSTR){ return nullptr; }
#define LoadCursor LoadCursorA
inline HWND GetActiveWindow(){ return nullptr; }
inline HWND GetForegroundWindow(){ return nullptr; }
inline HWND GetTopWindow(HWND){ return nullptr; }
inline BOOL PtInRect(const RECT* r, POINT pt){ return pt.x >= r->left && pt.x < r->right && pt.y >= r->top && pt.y < r->bottom; }
inline BOOL IsChild(HWND, HWND){ return FALSE; }
inline BOOL IsWindow(HWND){ return FALSE; }
inline BOOL IsIconic(HWND){ return FALSE; }
inline BOOL GetTextExtentPoint32A(HDC, LPCSTR, int, void*){ return TRUE; }
#define GetTextExtentPoint32 GetTextExtentPoint32A
inline int GetBkMode(HDC){ return 0; }
inline COLORREF GetBkColor(HDC){ return 0; }
inline COLORREF GetTextColor(HDC){ return 0; }
inline BOOL GetUpdateRect(HWND, LPRECT, BOOL){ return FALSE; }
#define BS_OWNERDRAW 0x0000000BL
#define HOTKEY_CLASS "msctls_hotkey32"
#define GWLP_WNDPROC (-4)
#define WM_SETCURSOR 0x0020
#define WM_NCMOUSEMOVE 0x00A0
#define WM_KEYLAST 0x0108
#define WM_SYSCOMMAND 0x0112
#define WM_SYSCHAR 0x0106
#define WM_TIMER 0x0113
#define LBS_NOSEL -1
inline int ListBox_GetSel(HWND,int){ return 0; }
inline int ListBox_SetSel(HWND,BOOL,int){ return 0; }
inline int ListBox_FindStringExact(HWND,int,LPCSTR){ return -1; }
#endif

// Additional GDI stubs

#include <arpa/inet.h>
// Expose std::min/max/clamp in global namespace
namespace {
using std::min;
using std::max;
using std::clamp;
}

// Also ensure NOMINMAX prevents future min/max macros
#ifdef NOMINMAX
#undef NOMINMAX
#endif
#define NOMINMAX
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif


// --- Link stubs for files we now include on Android ---
#ifndef OWNERDRAW_STUBS
#define OWNERDRAW_STUBS
// Provide minimal definitions so excluded UI still links
// Actual implementations will be in ownrdraw.cpp when it compiles with stubs above
#endif
#ifndef MAINWINDOW_STUB
#define MAINWINDOW_STUB
// MainWindow is defined in win.cpp / main - ensure it exists
extern HWND MainWindow;
#ifndef MAINWINDOW_DEFINED
#define MAINWINDOW_DEFINED
// If not defined elsewhere, define a dummy
// HWND MainWindow = nullptr; // can't define here, but ensure extern exists
#endif
#endif
inline void Video_Present_If_Dirty(){}
inline BOOL Get_Display_Rect(void*, void*){ return FALSE; }
inline BOOL Get_Display_Rect(void*, struct tagRECT*){ return FALSE; }

// Forward declarations for types used in tactical.cpp stubs
struct Coord; struct Point2D; struct ObjectClass; template<typename T> struct TRect; struct Surface;


// --- Stubs for missing symbols on Android ---
unsigned long long __cdecl Get_CPU_Clock();
unsigned int __cdecl Get_CPU_Clock(unsigned int & high);
unsigned int __cdecl Get_CPU_Rate(unsigned int & high);

// Additional intrinsics for bench


// --- OwnrDraw.cpp missing Win32 APIs ---
#ifndef SETBKCOLOR_DEFINED
#define SETBKCOLOR_DEFINED
inline COLORREF SetBkColor(HDC, COLORREF){ return 0; }
inline HFONT CreateFontA(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,LPCSTR){ return nullptr; }
inline HFONT CreateFontW(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,LPCWSTR){ return nullptr; }
#define CreateFont CreateFontA
inline HFONT CreateFontIndirectA(const void*){ return nullptr; }
inline HFONT CreateFontIndirectW(const void*){ return nullptr; }
#define CreateFontIndirect CreateFontIndirectA
inline BOOL GetTextMetricsA(HDC,void*){ return TRUE; }
#define GetTextMetrics GetTextMetricsA

#endif
#ifndef CALLWINDOWPROC_DEFINED
#define CALLWINDOWPROC_DEFINED
inline LRESULT CallWindowProcA(WNDPROC, HWND, UINT, WPARAM, LPARAM){ return 0; }
inline LRESULT CallWindowProcW(WNDPROC, HWND, UINT, WPARAM, LPARAM){ return 0; }
#define CallWindowProc CallWindowProcA
#endif
#ifndef WINDOWPOS_DEFINED
#define WINDOWPOS_DEFINED
typedef struct tagWINDOWPOS { HWND hwnd; HWND hwndInsertAfter; int x; int y; int cx; int cy; UINT flags; } WINDOWPOS, *LPWINDOWPOS, *PWINDOWPOS;
#endif
#define WM_WINDOWPOSCHANGING 0x0046
#define WM_WINDOWPOSCHANGED 0x0047
#define SWP_NOOWNERZORDER 0x0200
#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOZORDER 0x0004
#define WM_KILLFOCUS 0x0008
#define WM_SETFOCUS 0x0007
#define WM_MOUSELAST 0x020D
inline HWND WindowFromPoint(POINT){ return nullptr; }
inline HWND WindowFromPoint(int,int){ return nullptr; }
#ifndef CHAR_DEFINED
#define CHAR_DEFINED
typedef char CHAR;
#endif
inline BOOL IntersectRect(LPRECT, const RECT*, const RECT*){ return FALSE; }
#define DWLP_DLGPROC 4
#define DWL_DLGPROC DWLP_DLGPROC
#define DWLP_MSGRESULT 0
// OwnerDraw is declared in ownrdraw.h - do not redefine here, see android_stubs.cpp for method stubs



// Generic Get_Display_Rect - matches any second param type (void*, RECT*, tagRECT*)


// ---- ANDROID STUBS FOR SKIRMISH LINKER ----
inline int Country_From_Box(HWND) { return 0; }
inline int House_From_Box(HWND) { return 0; }
inline int Color_From_Box(HWND) { return 0; }
inline int Team_From_Box(HWND) { return 0; }
inline int Scenario_From_Box(HWND) { return 0; }
inline int Difficulty_From_Box(HWND) { return 0; }
inline void Fill_Country_Box(HWND) {}
inline void Fill_House_Box(HWND) {}
inline void Fill_Color_Box(HWND) {}
inline void Fill_Team_Box(HWND) {}
inline void Fill_Scenario_Box(HWND) {}
inline void Fill_Difficulty_Box(HWND) {}
inline void Fill_Credits_Box(HWND) {}
inline void Fill_TechLevel_Box(HWND) {}
inline void Fill_GameSpeed_Box(HWND) {}
inline void Select_Country_In_Box(HWND, int) {}
inline void Select_House_In_Box(HWND, int) {}
inline void Select_Color_In_Box(HWND, int) {}
inline void Select_Team_In_Box(HWND, int) {}
inline void Select_Scenario_In_Box(HWND, int) {}
inline void Select_Difficulty_In_Box(HWND, int) {}
inline void Select_Credits_In_Box(HWND, int) {}
inline void Select_TechLevel_In_Box(HWND, int) {}
inline void Select_GameSpeed_In_Box(HWND, int) {}
inline int Get_KeyNum_From_String(const char*) { return 0; }



// --- Android mouse crash fix ---
// Previous macro hack broke xmouse.h virtual declarations.
// Instead, mouse.cpp itself must early-return on Android (see MOUSE_ANDROID_PATCH.txt)
// No macros for Show_Mouse/Hide_Mouse here - keep declarations intact.
#endif // __ANDROID__
#endif // ANDROID_COMPAT_H
