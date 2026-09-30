/*******************************************************************************
 * dstream.cpp - Android fixed order for stat
 ******************************************************************************/
#include "vqaplayp.h"
#include <sys/stat.h>
#ifndef O_BINARY
#define O_BINARY 0
#endif
static int filelength(int fh){ struct stat st; if(fstat(fh,&st)==0) return (int)st.st_size; return 0; }
#include <stdio.h>
#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <string.h>

intptr_t __cdecl Disk_VQA_Stream_Handler(VQAHandle *vqa, long action, void *buffer, long nbytes)
{
        long fh;
        long error = 0;
        int temp;
        fh = ((VQAHandleP*)vqa)->Config.StreamFileHandle;
        switch (action) {
                case VQACMD_OPEN:
                        error = open((char *)buffer, (O_RDONLY|O_BINARY));
                        if (error != -1) {
                                ((VQAHandleP*)vqa)->Config.StreamFileHandle = error;
                                error = 0;
                        }
                        break;
                case VQACMD_READ:
                        error = (read(fh, buffer, nbytes) != nbytes);
                        break;
                case VQACMD_WRITE:
                        error = 1;
                        break;
                case VQACMD_SEEK:
                        error = (lseek(fh, nbytes, (int)(intptr_t)buffer) == -1);
                        break;
                case VQACMD_SEEKPEEK:
                        if (nbytes > 0) {
                                error = lseek(fh, nbytes - 1, (int)(intptr_t)buffer) == -1;
                                if (error == 0) {
                                        error = read(fh, &temp, 1) != 1;
                                }
                        } else {
                                error = lseek(fh, nbytes, (int)(intptr_t)buffer) == -1;
                                if (error == 0) {
                                        error = read(fh, &temp, 1) != 1;
                                }
                                if (error == 0) {
                                        error = lseek(fh, -1, 1) == -1;
                                }
                        }
                        break;
                case VQACMD_SIZE:
                        *((unsigned int *)buffer) = filelength(fh);
                        error = 0;
                        break;
                case VQACMD_CLOSE:
                        close(fh);
                        error = 0;
                        break;
                case VQACMD_INIT:
                        error = 0;
                        break;
                case VQACMD_CLEANUP:
                        error = 0;
                        break;
        }
        return(error);
}

intptr_t __cdecl Memory_VQA_Stream_Handler(VQAHandle *vqa, long action, void *buffer, long nbytes)
{
        long error = 0;
        int p;
        int bytes;
        VQAHandleP *vqap = (VQAHandleP *)vqa;
        VQALoopCache *cache = &vqap->LoopCache;
        switch (action) {
                case VQACMD_OPEN:
                        error = 0;
                        break;
                case VQACMD_READ:
                        bytes = cache->Bytes;
                        p = cache->Offset;
                        if (p + nbytes <= bytes) {
                                memcpy(buffer, &cache->Ptr[p], nbytes);
                                cache->Offset += nbytes;
                                error = 0;
                                break;
                        }
                        error = 1;
                        break;
                case VQACMD_SEEK:
                case VQACMD_SEEKPEEK:
                        switch ((intptr_t)buffer) {
                                case 1:
                                        cache->Offset += nbytes;
                                        error = 0;
                                        break;
                                case 0:
                                        p = cache->FileOffset;
                                        if (nbytes >= p) {
                                                cache->Offset = nbytes - p;
                                                break;
                                        }
                                default:
                                        error = 1;
                                        break;
                        }
                        break;
                case VQACMD_SIZE:
                        error = 0;
                        break;
                case VQACMD_CLOSE:
                        error = 0;
                        break;
                case VQACMD_INIT:
                case VQACMD_CLEANUP:
                        error = 0;
                        break;
                case VQACMD_WRITE:
                        error = 1;
                        break;
                default:
                        break;
        }
        return(error);
}
