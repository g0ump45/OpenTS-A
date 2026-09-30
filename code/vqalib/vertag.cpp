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
*
*       C O N F I D E N T I A L  --  W E S T W O O D   S T U D I O S
*
*----------------------------------------------------------------------------
*
* PROJECT
*     VQMisc32 library.
*
* FILE
*     vertag.c (32-Bit protected mode)
*
* DESCRIPTION
*     Embedded version string. This string is prefixed with a tag ("$VER$")
*     which can be search for to find this string.
*
* PROGRAMMER
*     Denzil E. Long, Jr.
*
* DATE
*     Febuary 8, 1995
*
****************************************************************************/

#include "vqaplayp.h"

#ifdef __WATCOMC__
#define DEVNAME "Watcom"
#elif __BORLANDC__
#define DEVNAME "Borland"
#elif _MSC_VER
#define DEVNAME "MSVC"
#else
#define DEVNAME "???????????"
#endif

#if _MSC_VER >= 1200
#undef VQA_DATE
#define VQA_DATE "Nov 12 1999 13:58:22"
#endif

char VerTag[] = { "$VER$" VQA_IDSTRING " " DEVNAME " (" VQA_DATE ")" };
char ReqTag[] = { "$REQ$" VQA_REQUIRES };
