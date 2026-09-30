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

#ifndef VQMVIDEO_H
#define VQMVIDEO_H
/****************************************************************************
*
*        C O N F I D E N T I A L -- W E S T W O O D  S T U D I O S
*
*----------------------------------------------------------------------------
*
* FILE
*     Video.h (32-Bit protected mode)
*
* DESCRIPTION
*     Video manager definitions.
*
* PROGRAMMER
*     Denzil E. Long, Jr.
*
* DATE
*     Febuary 3, 1995
*
****************************************************************************/

//#include <vqm32\vesavid.h>

/*---------------------------------------------------------------------------
 * VGA video modes
 *-------------------------------------------------------------------------*/

#define	TEXT_VIDEO 0x02
#define	MCGA 0x13
#define	XMODE_320X200 0x50
#define	XMODE_320X240 0x51
#define	XMODE_320X400 0x52
#define	XMODE_320X480 0x53
#define	XMODE_360X400 0x54
#define	XMODE_360X480 0x55

#define	XMODE_MIN 0x50
#define	XMODE_MAX 0x55

/*---------------------------------------------------------------------------
 * Structure definitions
 *-------------------------------------------------------------------------*/

/* DisplayInfo - Information about the current display.
 *
 * Mode     - Mode identification.
 * XRes     - X resolution of mode.
 * YRes     - Y resolution of mode.
 * VBIbit   - Polarity of vertical blank bit.
 * Extended - Pointer to mode specific data structure.
 */
typedef struct _DisplayInfo {
	long Mode;
	long XRes;
	long YRes;
	long VBIbit;
	void *Extended;
} DisplayInfo;

/*---------------------------------------------------------------------------
 * Function prototypes
 *-------------------------------------------------------------------------*/

DisplayInfo *SetVideoMode(long mode);
DisplayInfo *GetDisplayInfo(void);
long TestVBIBit(void);
long GetVBIBit(void);

void SetupXPaging(void);
void FlipXPage(void);
unsigned char *GetXHidPage(void);
unsigned char *GetXSeenPage(void);
void DisplayXPage(long page);

#ifdef __cplusplus
extern "C" {
#endif

void __cdecl WaitNoVB(short vbibit);
void __cdecl WaitVB(short vbibit);
void __cdecl ClearVRAM(void);
long __cdecl SetXMode(long mode);
void __cdecl ClearXMode(void);
void __cdecl ShowXPage(unsigned long StartOffset);
void __cdecl Xmode_BufferCopy_320x200(void *buff, void *screen);
void __cdecl Xmode_Blit(void *buffer, void *screen, long imgwidth, long imgheight);
void __cdecl MCGA_BufferCopy(unsigned char *buffer, unsigned char *dummy);
void __cdecl MCGA_Blit(unsigned char *buffer, unsigned char *screen,
		long imgwidth, long imgheight);

#ifdef __cplusplus
}
#endif

#endif /* VQMVIDEO_H */

