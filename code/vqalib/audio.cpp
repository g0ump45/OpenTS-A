/*******************************************************************************
 * audio.cpp - Android fix FINAL - fixes return types and duplicate tempbuf
 ******************************************************************************/
#include "vqaplayp.h"
#include <stdio.h>
#include <memory.h>
#include "audio/audiomovie.h"
#include "vqamem.h"

#ifndef _WIN32
#ifndef __cdecl
#define __cdecl
#endif
#endif

static void StartAddr(void);
static void EndAddr(void);

static void StartAddr(void)
{
}

long VQA_OpenAudio(VQAHandleP *vqap)
{
        VQAAudio *audio;
        long rc;

        audio = &vqap->Audio;

        if (audio->Buffer == NULL) {
                return(VQAERR_AUDIO);
        }

        audio->Block1 = 0;
        audio->Block2 = -1;
        audio->BufferPosition = 0;
        vqap->RepeatedBuffers = 0;

        AhandleInitParams params;
        params.SampleRate = vqap->SampleRate;
        params.Channels = vqap->Channels;
        params.BitsPerSample = vqap->BitsPerSample;
        params.Flags = 0;
        params.Callback1 = (void*)VQA_AudioFillCallback;
        params.Callback2 = (void*)VQA_AudioDoneCallback;

        rc = (long)vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_OPEN, &params, sizeof(params));
        if (rc >= VQAERR_OK || rc == VQAERR_NONE) {
                if ((audio->Flags & VQAAUDF_MODLOCKED) == 0) {
                        audio->Flags |= VQAAUDF_MODLOCKED;
                }
                return(VQAERR_NONE);
        }
        return(rc);
}

void VQA_CloseAudio(VQAHandleP *vqap)
{
        VQAAudio *audio;
        audio = &vqap->Audio;
        if (audio->Flags & VQAAUDF_ISPLAYING) {
                VQA_StopAudio(vqap);
        }
        vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_CLOSE, NULL, 0);
        if ((audio->Flags & VQAAUDF_MODLOCKED) == 1) {
                audio->Flags &= ~VQAAUDF_MODLOCKED;
        }
}

void VQA_StartAudio(VQAHandleP *vqap)
{
        VQAAudio *audio;
        audio = &vqap->Audio;
        if (audio->Flags & VQAAUDF_ISPLAYING) {
                return;
        }
        vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_START, NULL, 0);
        audio->Flags |= VQAAUDF_ISPLAYING;
}

void VQA_PauseAudio(VQAHandleP *vqap)
{
    vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_PAUSE, NULL, 0);
    vqap->Audio.Flags &= ~VQAAUDF_ISPLAYING;
}

void VQA_StopAudio(VQAHandleP *vqap)
{
        VQAAudio *audio;
        audio = &vqap->Audio;
        if (audio->Flags & VQAAUDF_ISPLAYING) {
                vqap->Config.AudioHandler((VQAHandle *)vqap, VQAAUDIO_STOP, NULL, 0);
                audio->Flags &= ~VQAAUDF_ISPLAYING;
        }
}

long CopyAudio(VQAHandleP *vqap)
{
	VQAAudio  *audio;
	VQAConfig *config;

	unsigned long startblock;
	unsigned long endblock;
	unsigned long len1,len2;
	unsigned long i;

	unsigned char *tempbuf;
	unsigned long tempbuflen;

	/* Dereference commonly used data members for quicker access. */
	audio = &vqap->Audio;
	config = &vqap->Config;

	/* If audio is disabled, or if we're playing from a VOC file, or if
	 * there's no Audio Buffer, or if there's no data to copy, just return 0
	 */
	#if(VQAVOC_ON && VQAAUDIO_ON)
	if (((config->OptionFlags & VQAOPTF_AUDIO) == 0) || (vqap->vocfh != -1)
			|| (audio->Buffer == NULL) || (audio->TempBufLen == 0)) {
	#else  /* VQAVOC_ON */
	if (((config->OptionFlags & VQAOPTF_AUDIO) == 0) || (audio->Buffer == NULL)
			|| (audio->TempBufLen == 0)) {
	#endif /* VQAVOC_ON */

		return(VQAERR_NONE);
	}

	tempbuf = audio->TempBuf + audio->BufferOffset;
	tempbuflen = audio->TempBufLen - audio->BufferOffset;

	/* Compute start & end blocks to copy into */
	startblock = (audio->AudBufPos / config->HMIBufSize);
	endblock = (audio->AudBufPos + tempbuflen) / config->HMIBufSize;

	if (endblock >= audio->NumAudBlocks) {
		endblock -= audio->NumAudBlocks;
	}

	/* If 'endblock' hasn't played yet, return VQAERR_SLEEPING */
	if (audio->IsLoaded[endblock] == 1) {
		return(VQAERR_SLEEPING);
	}

	/* Copy the data:
	 *
	 *  - If 'startblock' < 'endblock', copy the entire buffer
	 *  - Otherwise, fill to the end of the buffer with part of the data, then
	 *    copy the rest to the beginning of the buffer
	 */
	if (startblock <= endblock) {

		/* Copy data */
		memcpy((audio->Buffer + audio->AudBufPos), tempbuf,
				tempbuflen);

		/* Adjust current load position */
		audio->AudBufPos += tempbuflen;

		/* Mark buffer as empty */
		audio->TempBufLen = 0;

		audio->BufferOffset = 0;

		/* Set all blocks to loaded */
		for (i = startblock; i < endblock; i++) {
			audio->IsLoaded[i] = 1;
		}

	} else {

		/* Compute length of each piece */
		len1 = config->AudioBufSize - audio->AudBufPos;

		len2 = tempbuflen - len1;

		/* Copy 1st piece into end of Audio Buffer */
		memcpy((audio->Buffer + audio->AudBufPos), tempbuf, len1);

		/* Copy 2nd piece into start of Audio Buffer */
		memcpy(audio->Buffer, tempbuf + len1, len2);


		/* Adjust load position */
		audio->AudBufPos = len2;

		/* Mark buffer as empty */
		audio->TempBufLen = 0;

		audio->BufferOffset = 0;

		/* Set blocks to loaded */
		for (i = startblock; i < audio->NumAudBlocks; i++) {
			audio->IsLoaded[i] = 1;
		}

		for (i = 0; i < endblock; i++) {
			audio->IsLoaded[i] = 1;
		}
	}

	return(VQAERR_NONE);
}


long __cdecl VQA_AudioFillCallback(VQAHandleP *vqap)
{
        VQAAudio *audio;
        VQAConfig *config;

        audio = &vqap->Audio;
        config = &vqap->Config;

        long size = config->HMIBufSize;

        if (audio->Flags & VQAAUDF_ISDONE) {
                return(0);
        }

        long pos = audio->BufferPosition;
        unsigned long block = audio->Block1;

        if (config->OptionFlags & VQAOPTF_WAITFILL) {
                long nblock = block + 1;
                if ((unsigned)nblock >= audio->NumAudBlocks) {
                        nblock = 0;
                }
                if (!(audio->Flags & VQAAUDF_ISENDOFFILE)) {
                        if (audio->IsLoaded[nblock] == 0) {
                                audio->Flags |= VQAAUDF_ISSTARVED;
                        }
                }
        }

        bool repeating = false;
        if (audio->IsLoaded[block] == 1) {
                if (audio->Block2 == -1) {
                        audio->Block2 = block;
                        audio->PlayPosition = pos;
                }
                audio->BlockRepeats[block] = 0;
                block++;
                long npos = pos + size;
                if (npos >= config->AudioBufSize) {
                        npos = 0;
                        block = 0;
                }
                audio->BufferPosition = npos;
                audio->Block1 = block;
        } else {
                if (audio->Flags & VQAAUDF_ISENDOFFILE) {
                        audio->Flags |= VQAAUDF_ISDONE;
                        if ((unsigned)pos < audio->AudBufPos) {
                                size = audio->AudBufPos - pos;
                        } else {
                                size = 0;
                        }
                } else {
                        audio->Flags |= VQAAUDF_ISREPEATING;
                        repeating = true;
                        vqap->RepeatedBuffers++;
                        pos -= size;
                        block--;
                        if (pos < 0) {
                                pos = config->AudioBufSize - size;
                                block = audio->NumAudBlocks - 1;
                        }
                        audio->BlockRepeats[block]++;
                }
        }

        if (size > 0) {
                if (repeating == true) {
                        config->AudioHandler((VQAHandle *)vqap, VQAAUDIO_LOAD, audio->HMIBuffer, size);
                } else {
                        config->AudioHandler((VQAHandle *)vqap, VQAAUDIO_LOAD, audio->Buffer + pos, size);
                }
        }
        return(size);
}

long __cdecl VQA_AudioDoneCallback(VQAHandleP *vqap, void *buffer)
{
        VQAConfig *config;
        VQAAudio *audio;
        unsigned long  block;

        audio = &vqap->Audio;
        config = &vqap->Config;

        if (buffer == audio->Buffer + audio->PlayPosition || buffer == audio->HMIBuffer) {
                block = audio->Block2;
                if (block != (unsigned long)-1) {
                        if (!audio->BlockRepeats[block]) {
                                audio->IsLoaded[block] = 0;
                                block++;
                                if (block >= audio->NumAudBlocks) {
                                        block = 0;
                                }
                                if (audio->IsLoaded[block] == 1) {
                                        audio->PlayPosition += config->HMIBufSize;
                                        if (audio->PlayPosition >= (unsigned)config->AudioBufSize) {
                                                audio->PlayPosition = 0;
                                        }
                                        audio->Block2 = block;
                                } else {
                                        audio->Block2 = -1;
                                }
                        } else {
                                audio->BlockRepeats[block]--;
                        }
                        return(VQAERR_NONE);
                }
                return(VQAERR_BADBLOCK);
        }
        return(VQAERR_AUDSYNC);
}

static void EndAddr(void)
{
}
