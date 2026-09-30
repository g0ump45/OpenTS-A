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

#ifndef VQAMEM_H
#define VQAMEM_H
/****************************************************************************
*
*        C O N F I D E N T I A L -- W E S T W O O D  S T U D I O S
*
*---------------------------------------------------------------------------
*
* FILE
*     mem.h
*
* DESCRIPTION
*     Memory management definitions.
*
* PROGRAMMER
*     Phil Gorrow
*     Denzil E. Long, Jr.
*
* DATE
*     July 5, 1995
*
****************************************************************************/

/* Definitions */
#define DPMI_INT    0x0031
#define DPMI_LOCK   0x0600
#define DPMI_UNLOCK 0x0601

/* Prototypes */
#ifdef __WATCOMC__
void DPMI_Lock(void const *ptr, long const size);
void DPMI_Unlock(void const *ptr, long const size);
#else
#define DPMI_Lock(a,b)
#define DPMI_Unlock(a,b)
#endif

#endif /* VQAMEM_H */
