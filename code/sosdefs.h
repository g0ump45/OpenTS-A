/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

/****************************************************************************

   File              : sosdefs.h

   Programmer(s)     : Don Fowler, Nick Skrepetos
   Date              :

   Purpose           : Include Files For Zortech C++ Compiler

   Last Updated      :

****************************************************************************
               Copyright(c) 1993,1994 Human Machine Interfaces
                            All Rights Reserved
****************************************************************************/


#ifndef  _SOSDEFS_DEFINED
#define  _SOSDEFS_DEFINED

#undef   _TRUE
#undef   _FALSE
#undef   _NULL
enum
      {
         _FALSE,
         _TRUE
      };

#define  _NULL  0

#ifndef  VOID
#define  VOID           void
#endif
typedef  int            BOOL;
typedef  unsigned int   UINT;
typedef  unsigned char  BYTE;
typedef  unsigned       WORD;
#ifndef  LONG
typedef  signed long    LONG;
#endif
typedef  unsigned long  DWORD;

typedef  BYTE  *        PBYTE;
typedef  char near *    PSTR;
typedef  WORD  *        PWORD;
typedef  LONG  *        PLONG;
typedef  VOID  *        PVOID;

typedef  BYTE  far   *  LPBYTE;
typedef  BYTE  far   *  LPSTR;
typedef  WORD  far   *  LPWORD;
typedef  LONG  far   *  LPLONG;
typedef  VOID  far   *  LPVOID;

typedef  BYTE  huge  *  HPBYTE;
typedef  BYTE  huge  *  HPSTR;
typedef  WORD  huge  *  HPWORD;
typedef  LONG  huge  *  HPLONG;
typedef  VOID  huge  *  HPVOID;

typedef  unsigned       HANDLE;

#endif
