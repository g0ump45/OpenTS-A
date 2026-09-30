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

#include	"vqaplayp.h"
#include	<stdio.h>


/****************************************************************************
*
* NAME
*     VQA_SetTimer - Resets current time to given tick value.
*
* SYNOPSIS
*     VQA_SetTimer(Time, Method)
*
*     void VQA_SetTimer(long, long);
*
* FUNCTION
*     Sets 'TickOffset' to a value that will make the current time look like
*     the time passed in. This function allows the player to be "paused",
*     by recording the time of the pause, and then setting the timer to
*     that time. The timer method used by the player is also set. The method
*     selected is not neccesarily the method that will be used because some
*     timer methods work with only certain playback conditions. (EX: The
*     audio DMA timer method cannot be used if there is not any audio
*     playing.)
*
* INPUTS
*     Time   - Value to set current time to.
*     Method - Timer method to use.
*
* RESULT
*     NONE
*
****************************************************************************/

void VQA_SetTimer(VQAHandleP *vqap, long time)
{
	vqap->TickOffset = 0;
	unsigned long curtime = VQA_GetTime(vqap);
	vqap->TickOffset = (time - curtime);
}


void VQA_StepTimer(VQAHandleP *vqap, long step)
{
	vqap->TickOffset += step;
}


/****************************************************************************
*
* NAME
*     VQA_GetTime - Return current time.
*
* SYNOPSIS
*     Time = VQA_GetTime()
*
*     unsigned long VQA_GetTime(void);
*
* FUNCTION
*     This routine returns timer ticks computed one of 3 ways:
*
*     1) If audio is playing, the timer is based on the DMA buffer position:
*        Compute the number of audio samples that have actually been played.
*        The following internal HMI variables are used:
*
*          _lpSOSDMAFillCount[drv_handle]: current DMA buffer position
*          _lpSOSSampleList[drv_handle][samp_handle]:
*          sampleTotalBytes: total bytes sent by HMI to the DMA buffer
*          sampleLastFill: HMI's last fill position in DMA buffer
*
*        So, the number of samples actually played is:
*
*          sampleTotalBytes - <DMA_diff>
*          where <DMA_diff> is how far ahead sampleLastFill is in front of
*          _lpSOSDMAFillCount: (sampleLastFill - _lpSOSDMAFillCount)
*
*        These values are indices into a circular DMA buffer, so:
*
*          if (sampleLastFill >= _lpSOSDMAFillCount)
*            <DMA_diff> = sampleLastFill - _lpSOSDMAFillCount
*          else
*            <DMA_diff> = (DMA_BUF_SIZE - lpSOSDMAFillCount) + sampleLastFill
*
*        Note that, if using the stereo driver with mono data, you must
*        divide LastFill & FillCount by 2, but not TotalBytes. If using the
*        stereo driver with stereo data, you must divide all 3 variables
*        by 2.
*
*     2) If no audio is playing, but the timer interrupt is running,
*        VQATickCount is used as the timer
*
*     3) If no audio is playing & no timer interrupt is going, the DOS 18.2
*        system timer is used.
*
*     Regardless of the method, TickOffset is used as an offset from the
*     computed time.
*
* INPUTS
*     NONE
*
* RESULT
*     Time - Time in VQA_TIMETICKS
*
****************************************************************************/

unsigned long VQA_GetTime(VQAHandleP *vqap)
{
	// MEG 09.25.95 - changed from long to unsigned long
	unsigned long ticks;

	/* The elapsed ticks is calculated by the number of samples
	 * processed times the tick resolution per second divided by the
	 * sample rate.
	 */
	ticks = (vqap->Config.TimerCallback((VQAHandle *)vqap) * VQA_TIMETICKS) / vqap->Config.RefreshRate;
	ticks += vqap->TickOffset;

	return(ticks);
}


unsigned long VQA_GetMovieTime(VQAHandle *vqa)
{
	VQAHandleP *vqap = (VQAHandleP *)vqa;

	VQAConfig *config;

	config = &vqap->Config;

	unsigned long rate = config->RefreshRate;

	unsigned long ticks;

	/* The elapsed ticks is calculated by the number of samples
	 * processed times the tick resolution per second divided by the
	 * sample rate.
	 */
	ticks = (config->TimerCallback((VQAHandle *)vqap) * VQA_TIMETICKS) / rate;
	ticks += vqap->TickOffset;

	return(ticks);
}