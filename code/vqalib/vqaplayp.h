#include <cstdint>
#include <cstddef>
/*******************************************************************************
 * vqaplayp.h - Android fix v20 - adds missing Loader fields, WriteIndex, UnusedCallback
 ******************************************************************************/
#ifndef VQAPLAYP_H
#define VQAPLAYP_H
#ifndef _WIN32
#ifndef __cdecl
#define __cdecl
#endif
#endif
#include <stdbool.h>
#include "vqafile.h"
#include "cmp.h"
#ifndef VQAFileHandle
typedef void* VQAFileHandle;
#define VQA_BAD_HANDLE ((VQAFileHandle)(intptr_t)-1)
#endif
#ifndef NULL
#define NULL 0
#endif
#define _VQAConfig _VQAConfigPublic
#define VQAConfig VQAConfigPublic
#include "vqaplay.h"
#undef _VQAConfig
#undef VQAConfig
#ifndef UNVQ_FUNC
typedef void (__cdecl *UNVQ_FUNC)(uint8_t*, uint8_t*, uint8_t*, size_t, size_t, size_t);
#endif
#ifndef VQAHANDLEFUNC
typedef intptr_t (__cdecl *VQAHANDLEFUNC)(VQAHandle* , long, void*, long);
#endif
typedef long (__cdecl *VQAD_FUNC)(VQAHandle*);
typedef long (__cdecl *VQAP_FUNC)(VQAHandle*);
typedef long (__cdecl *VQACALLBACK2)(void*, long);
typedef long (__cdecl *VQA_H_FUNC)(VQAHandle*, long, void*, long);
typedef unsigned long (__cdecl *VQATIMERFUNC)(VQAHandle*);
#ifndef AHANDLEINITPARAMS_DEFINED
#define AHANDLEINITPARAMS_DEFINED


#ifndef VQA_ADPCM_ALIAS
#define VQA_ADPCM_ALIAS
typedef struct _VQA_SOS_COMPRESS_INFO VQA_ADPCM_Info;
typedef struct _VQA_SOS_COMPRESS_INFO _VQA_SOS_COMPRESS_INFO_ALIAS;
#endif

struct AhandleInitParams{ unsigned short SampleRate; unsigned char Channels; unsigned char BitsPerSample; unsigned long Flags; void * Callback1; void * Callback2; };
#endif
#define STATIC
#define _STATIC static
typedef bool VQABool;
#define VQA_VERSION "5.0"
#ifndef VQA_DATE
#define VQA_DATE __DATE__ " " __TIME__
#endif
#if _MSC_VER >= 1200
#undef VQA_DATE
#define VQA_DATE "Nov 12 1999 13:58:22"
#endif
#ifndef VQA_IDSTRING
#define VQA_IDSTRING "VQA playback " VQA_VERSION " (" VQA_DATE ")"
#endif
#ifndef VQA_REQUIRES
#define VQA_REQUIRES "Support library " VQA_VERSION " or better."
#endif
extern char VerTag[];
extern char ReqTag[];
#define BLOCK_DIM(a,b) (((a&0xFF)<<8)|(b&0xFF))
#define BLOCK_2X2 BLOCK_DIM(2,2)
#define BLOCK_2X3 BLOCK_DIM(2,3)
#define BLOCK_4X2 BLOCK_DIM(4,2)
#define BLOCK_4X4 BLOCK_DIM(4,4)
#define VQA_MAX_CBBUFS 10
#define VQA_MAX_FRAMEBUFS 30
#define VQA_MASK_POINTER 0x8000
#define VQAABUFF_ALTCB 0x01
#define VQAABUFF_ALTPTR 0x02
#define VQAABUFF_ALTBC 0x04
#define VQAABUFF_ALTIMG 0x08
#define VQAABUFF_ALTLOOP 0x10
#define VQADATF_ALTIMG 0x02
#define VQADATF_BUFCONFIG 0x04
#define VQADATF_LDONE 0x08
#define VQADATF_LOOPED 0x10
#define VQADATF_LOOPJMP 0x20
#define VQADATF_FRAMESTALL 0x40
#define VQADATF_PRIMED 0x80
#define VQADATF_PAUSED 0x100
#define VQADATF_DDONE 0x200
#define VQADATF_AUDIOSYNC 0x400
#define VQADATF_REFILLED 0x800
#define VQADATF_LSLEEP 0x1000
#define VQAFRMF_LOADED 0x01
#define VQAFRMF_HOLD 0x02
#define VQAFRMF_KEY 0x04
#define VQAFRMF_PALETTE 0x08
#define VQAFRMF_PALCOMP 0x10
#define VQAFRMF_LOOPED 0x20
#define VQAFRMF_LOOPJMP 0x40
#define VQAFRMF_CHUNKS 0x80
#define VQAFRMF_PTCOMP 0x100
#define VQAFRMF_ALTPTR 0x200
#define VQAFRMF_PTRCOMP 0x400
#define VQAFRMF_RSDCOMP 0x800
#define VQAFRMF_11 0x1000
#define VQADRWF_REPAINT 0x01
#define VQADRWF_FORCEDRAW 0x02
#define VQADRWF_HOLD 0x04
#define VQADRWF_STEP 0x08
#define VQADRWF_SETPAL 0x10
#ifdef ALIGNUP
#undef ALIGNUP
#endif
#define ALIGNUP(x,a) (((x)+(a)-1) & ~((a)-1))

#pragma pack(push,1)
struct VQASN2J {
    int16_t index;
    int32_t predicted;
    int16_t index2;
    int32_t predicted2;
};
#pragma pack(pop)
static_assert(sizeof(VQASN2J) == 12, "the SN2J chunk is 12 bytes on disk");

#define VQA_TIMETICKS 100
#define VQAEVENT_LOOPED 1
#define VQAEVENT_LOOPJUMP 2
#define VQALOOPF_DATAVALID 0x01
#define VQALOOPF_2 0x02
#pragma pack(push,1)
typedef struct _ChunkHeader { uint32_t id; uint32_t size; } ChunkHeader;
typedef struct _ZAPHeader { unsigned short UnCompSize; unsigned short CompSize; } ZAPHeader;
typedef struct _VQAClipper { unsigned long Width; unsigned long Height; } VQAClipper;
typedef struct _VQACBNode { unsigned char *Buffer; struct _VQACBNode *Next; struct _VQACBNode *Prev; unsigned long Flags; unsigned long CBOffset; int CodebookSize; } VQACBNode;
#define VQACBB_DOWNLOADED 0
#define VQACBB_CBCOMP 1
#define VQACBB_ALTPTR 2
#define VQACBB_CBFULL 3
#define VQACBF_DOWNLOADED (1<<VQACBB_DOWNLOADED)
#define VQACBF_CBCOMP (1<<VQACBB_CBCOMP)
#define VQACBF_ALTPTR (1<<VQACBB_ALTPTR)
#define VQACBF_CBFULL (1<<VQACBB_CBFULL)
typedef struct _VQAFrameNode { unsigned char *Pointers; VQACBNode *Codebook; unsigned char *Palette; struct _VQAFrameNode *Next; struct _VQAFrameNode *Prev; unsigned long Flags; unsigned long PrevFlags; long FrameNum; unsigned long PtrOffset; unsigned long PalOffset; unsigned long PaletteSize; } VQAFrameNode;
#define VQAFB_NONLOAD 0
#define VQAFB_NOFLIP 1
#define VQAFB_HASDATA 2
#define VQAFB_PTCOMP 3
#define VQAFB_PALCOMP 4
#define VQAFB_MASKED 5
#define VQAFB_PRELOAD 6
#define VQAFB_STREAMING 7
#define VQAFBF_NONLOAD (1<<VQAFB_NONLOAD)
#define VQAFBF_NOFLIP (1<<VQAFB_NOFLIP)
#define VQAFBF_HASDATA (1<<VQAFB_HASDATA)
#define VQAFBF_PTCOMP (1<<VQAFB_PTCOMP)
#define VQAFBF_PALCOMP (1<<VQAFB_PALCOMP)
#define VQAFBF_MASKED (1<<VQAFB_MASKED)
#define VQAFBF_PRELOAD (1<<VQAFB_PRELOAD)
#define VQAFBF_STREAMING (1<<VQAFB_STREAMING)
#define VQAFLG_STARTED 0
#define VQAFLG_AUDIOREQUESTED 1
#define VQAFLG_HIPRIORITY 2
#define VQAFLG_WAITNOSKIP 3
#define VQAFLG_PAUSED 4
#define VQAFLG_NOSKIP 5
#define VQAFLG_HMIINITED 6
#define VQAFLG_MODLOCKED 7
#define VQAFLG_MODLOCKED 7
#define VQAFLG_PALETTEINITED 8
#define VQAFLG_PALDATASTORED 9
#define VQAF_STARTED (1<<VQAFLG_STARTED)
#define VQAF_AUDIOREQUESTED (1<<VQAFLG_AUDIOREQUESTED)
#define VQAF_HIPRIORITY (1<<VQAFLG_HIPRIORITY)
#define VQAF_WAITNOSKIP (1<<VQAFLG_WAITNOSKIP)
#define VQAF_PAUSED (1<<VQAFLG_PAUSED)
#define VQAF_NOSKIP (1<<VQAFLG_NOSKIP)
#define VQAF_HMIINITED (1<<VQAFLG_HMIINITED)
#define VQAF_MODLOCKED (1<<VQAFLG_MODLOCKED)
#define VQAF_PALETTEINITED (1<<VQAFLG_PALETTEINITED)
#define VQAF_PALDATASTORED (1<<VQAFLG_PALDATASTORED)
#define VQAAUDF_STARTED 0
#define VQAAUDF_STOPPED 1
#define VQAAUDF_ISPLAYING (1<<2)
#define VQAAUDF_ISDONE (1<<3)
#define VQAAUDF_ISREPEATING (1<<4)
#define VQAAUDF_ISENDOFFILE (1<<5)
#define VQAAUDF_ISSTARVED (1<<6)
#define VQAAUDF_MODLOCKED (1<<7)
#define VQAAUDF_MEMLOCKED VQAAUDF_MODLOCKED
#define VQAAUDF_ISPAUSED (1<<8)
#define VQAAUDF_ISFILLED (1<<9)
#define VQADRAWB_LOCKED 0
#define VQADRAWF_LOCKED (1<<VQADRAWB_LOCKED)
#define VQALOADB_LOCKED 0
#define VQALOADF_LOCKED (1<<VQALOADB_LOCKED)
typedef struct _VQAFrameBuffer { long Frame; long Flags; long FilePos; int IsCB; int IsPalette; int LoopID; } VQAFrameBuffer;
typedef struct _VQALoader {
        VQAFileHandle FileHandle; VQAFileHandle AltFileHandle; unsigned long BufferOffset;
        long ReadBytes; long Flags; long FilePos;
        int FrameIndex; int CodebookIndex;
        VQACBNode *CBNode; VQAFrameNode *FrameNode;
        int CurLoopID; long CurByte; int PaletteIndex;
        unsigned char TempPalette[768];
        VQACBNode *CurCB; VQACBNode *FullCB; VQACBNode *PrevCB;
        long NumPartialCB; long PartialCBSize; long CBSize;
        VQAFrameNode *CurFrame;
        long CurFrameNum; long LastFrameNum;
        long FrameSize; long MaxFrameSize;
        ChunkHeader CurChunkHdr;
        VQA_H_FUNC VQA_H_Func;
        void *StreamFunc;
        long ID; long Min; long WaitsOnDrawer;
} VQALoader;
typedef struct _VQADrawer { long FrameNum; long Flags; int X1; int Y1; int X2; int Y2; int ImageWidth; int ImageHeight; long DrawnFrames; long LastFrameNum; int BlocksPerRow; int NumRows; int NumBlocks; int DrawFlags; VQAFrameNode *CurFrame; long WaitsOnLoader; unsigned char Palette_24[768]; long CurPalSize; unsigned char *ImageBuf; long ScreenOffset; } VQADrawer;
typedef struct _VQAFlipper { long FrameNum; long Flags; int TimerMethod; VQAFrameNode *CurFrame; long LastFrameNum; } VQAFlipper;
typedef struct _VQAAudio { unsigned char *Buffer; unsigned char *TempBuf; long TempBufSize; long TempBufLen; long BufferOffset; long BufferPosition; long PlayPosition; long AudBufPos; char *HMIBuffer; bool *IsLoaded; short *BlockRepeats; unsigned long Block1; long Block2; long Flags; unsigned long NumAudBlocks; long BytesPerSec; struct _VQA_SOS_COMPRESS_INFO ADPCM_Info; } VQAAudio;
typedef struct _VQALoopCache { short Count; short Max; long Bytes; long Offset; long FileOffset; long Size; unsigned char *Ptr; long ID; long Min; long CurFrameNum; } VQALoopCache;
typedef struct _VQALoopInfo { short ID; short Flags; short Iterations; short StartFrame; short EndFrame; short EndFrameMode2; short EndFrameJump; short IterationsJump; short EndFrameNormal; struct HEADER { int Count; int Groupsize; int Flags; } Header; struct DATA { int StartFrame; int EndFrame; } *Data; } VQALoopInfo;
struct VQAMFC_DATA { long ChunkID; long KeyFrame; long Frame; long Size; int StartFrame; int EndFrame; char *Buffer; int Count; };
struct VQAMFC_DATA2_DATA { int StartFrame; int EndFrame; int Frame; char *Buffer; long Size; int Count; long ChunkID; long KeyFrame; };
struct VQAMFC_DATA2 { int Count; int WriteIndex; VQAMFC_DATA2_DATA *Data; typedef VQAMFC_DATA2_DATA DATA; };
struct VQAMFC_TABLE_DATA { int StartFrame; int EndFrame; };
struct VQAMFC_TABLE { long EntrySize; long ChunkID; long FrameInterval; char *Buffer; long Count; VQAMFC_TABLE_DATA *Data; };
struct VQAMFC_STATICDATA { long ChunkID; long KeyFrame; long Frame; long Size; int StartFrame; };

typedef struct _VQAMFCInfo {
        long NumChunks; long CurChunk; long *Sizes;
        struct HEADER { int Count; int StaticCount; } Header;
        VQAMFC_DATA *Data;
        VQAMFC_DATA2 *Data2;
        VQAMFC_TABLE *Table;
        VQAMFC_DATA *StaticData;
        typedef VQAMFC_DATA DATA;
        typedef VQAMFC_DATA2 DATA2;
        typedef VQAMFC_TABLE TABLE;
        typedef VQAMFC_STATICDATA STATICDATA;
} VQAMFCInfo;
typedef struct _VQAMSCInfo { long NumChunks; long CurChunk; long *Sizes; struct HEADER { int Count; } Header; struct DATA2 { int Count; int WriteIndex; struct DATA { int StartFrame; int EndFrame; int Frame; char *Buffer; long Size; int Count; } *Data; } *Data2; struct TABLE { long EntrySize; long ChunkID; char *Buffer; long Count; struct DATA { int StartFrame; int EndFrame; } *Data; } *Table; } VQAMSCInfo;
typedef struct _VQACodebookInfo { long NumChunks; long CurChunk; long *Sizes; void* HeaderPtr; struct HeaderStruct { int Count; int Groupsize; } Header; struct DATA { int Frame; int32_t Size; } *Data; } VQACodebookInfo;
struct VQAPalData { int Frame; int StartFrame; int EndFrame; unsigned char Palette[768]; };
typedef struct _VQAPaletteInfo {
        long NumChunks; long CurChunk; long *Sizes; void* HeaderPtr;
        struct PalHdr { int Count; } Header;
        struct PalHdr2 { int Count; } Header2;
        struct DATA { int Frame; int StartFrame; int EndFrame; unsigned char Palette[768]; } *Data;
} VQAPaletteInfo;
#define VQAPaletteInfo_DATA PALDATA
/* VQASN2J - Android: use fixed 32-bit types, guard redefinition */

typedef struct _VQAConfigPrivate {
        VQAHANDLEFUNC EventHandler; VQA_DC_FUNC DrawerCallback; long DrawFlags; long OptionFlags; long ImageWidth; long ImageHeight; long ImageRate; long X1; long Y1; long X2; long Y2; unsigned char* ImageBuf; unsigned char* DrawBuffer; long Time; long Buffers; long MaxCBBufSize; long MaxVPTBufSize; long TimerMethod; long MicroTimer; void* MonoCallback; long FromCurrent; VQA_H_FUNC StreamHandler; char* StreamFileName; int StreamFileHandle; int field_68; VQAClass* Owner; int InitialLoopID; int InitialLoopIterations; int StreamFileHandle2; int field_7C; int field_80; unsigned long LatencyAdjustment; long NumFrameBufs; long NumCBBufs; intptr_t (__cdecl *MemoryHandler)(VQAHandle*, long, void*, long); long SampleRate; long Channels; long BitsPerSample; long BitRate; long Quality; long Flags; long HMIBufSize; long AudioBufSize; long NumAudBlocks; long AudioRate; long Volume; VQAHANDLEFUNC AudioHandler; VQAHANDLEFUNC AudioHandler2; void* Callback1; void* Callback2; unsigned char* AudioBuf; long DrawRate; long FrameRate; long RefreshRate; VQATIMERFUNC TimerCallback;
        VQA_UC_FUNC UnusedCallback; void* UnusedCallback2;
} VQAConfigPrivate;
typedef struct { long ConfigIndex; long FilePos; long Flags; long IsCB; long IsPalette; long LoopID; long Frame; } VQAFrameInfo;
typedef struct _VQAHandleP {
        unsigned short Version; unsigned short ImageWidth; unsigned short ImageHeight; short field_6; void *ImageBuf; unsigned short ColorMode; unsigned short FrameRate; long NumFrames; int LoadedFrames; int DrawnFrames; int SkippedFrames; int StartTime; int EndTime; int LastCallbackCount; int MaxCallbackDelta; int MemUsed; int AudioHandleIndex; int RepeatedBuffers; unsigned short SampleRate; unsigned char Channels; unsigned char BitsPerSample; VQAConfigPrivate Config; char Filename[32]; VQAHeader Header; VQAClipper Clipper; short field_11A; int StopFrame; int LoopID; int LoopIterations; int LoopStartFrame0; int LoopEndFrameMode2; int LoopEndFrameJump; int LoopIterationsJump; int LoopEndFrameNormal; int LoopStartFrame1; int LoopEndFrame2; int LoopStartFrame2; int TickOffset; int field_14C; unsigned long Flags; unsigned long AltBufferFlags; void *AltImageBuf; int AltImageWidth; int AltImageHeight; VQALoader Loader; VQADrawer Drawer; VQAFlipper Flipper; VQAFrameNode *FrameData; void *AltPtrBuffer; VQACBNode *CBData; void *AltCBBuffer; VQALoopCache LoopCache; VQALoopInfo LoopInfo; VQAMFCInfo MFCInfo; VQAMSCInfo MSCInfo; VQACodebookInfo CodebookInfo; VQAPaletteInfo PaletteInfo; uint32_t *Foff; long Max_CB_Size; long Max_Ptr_Size; long Max_Pal_Size; int CBBufferSize; int PtrBufferSize; VQAD_FUNC Draw_Frame; VQAP_FUNC Page_Flip; UNVQ_FUNC UnVQ1; UNVQ_FUNC UnVQ2;
#if(VQAAUDIO_ON)
        VQAAudio Audio;
#endif
} VQAHandleP;
#pragma pack(pop)
#ifdef VQAConfig
#undef VQAConfig
#endif
#ifdef _VQAConfig
#undef _VQAConfig
#endif
#define VQAConfig VQAConfigPrivate
#define _VQAConfig VQAConfigPrivate
#define VQALOADB_NOPAL 0
#define VQALOADB_NOSND 1
#define VQALOADB_NOPTR 2
#define VQALOADB_NOPCB 3
#define VQALOADB_NOFULL 4
#define VQALOADB_NOLFR 5
#define VQALOADF_NOPAL (1<<VQALOADB_NOPAL)
#define VQALOADF_NOSND (1<<VQALOADB_NOSND)
#define VQALOADF_NOPTR (1<<VQALOADB_NOPTR)
#define VQALOADF_NOPCB (1<<VQALOADB_NOPCB)
#define VQALOADF_NOFCB (1<<VQALOADB_NOFULL)
#define VQALOADF_NOLFR (1<<VQALOADB_NOLFR)
long VQA_LoadFrame(VQAHandle *vqa);
long VQA_Configure_Drawer(VQAHandleP *vqap);
long User_Update(VQAHandle *vqa);
void VQA_SetTimer(VQAHandleP *vqap, long time);
void VQA_StepTimer(VQAHandleP *vqap, long step);
unsigned long VQA_GetTime(VQAHandleP *vqap);
unsigned long VQA_GetMovieTime(VQAHandle *vqa);
#if(VQAAUDIO_ON)
long VQA_OpenAudio(VQAHandleP *vqap);
void VQA_CloseAudio(VQAHandleP *vqap);
void VQA_StartAudio(VQAHandleP *vqap);
void VQA_PauseAudio(VQAHandleP *vqap);
void VQA_StopAudio(VQAHandleP *vqap);
long CopyAudio(VQAHandleP *vqap);
long __cdecl VQA_AudioFillCallback(VQAHandleP *vqap);
long __cdecl VQA_AudioDoneCallback(VQAHandleP *vqap, void *);
#endif
void VQA_InitMono(VQAHandleP *vqap);
void VQA_UpdateMono(VQAHandleP *vqap);
long AllocBuffers(VQAHandleP *vqap);
void FreeBuffers(VQAHandleP *vqap);



#ifndef VQA_SOSCODEC_DECLARED
#define VQA_SOSCODEC_DECLARED
#ifdef __cplusplus
extern "C" {
#endif
void __cdecl VQA_sosCODECDecompressData(void *src, void *dst, unsigned short wBitSize, unsigned short wChannels, uint32_t dwUnCompSize, struct _VQA_SOS_COMPRESS_INFO *sosinfo);
void __cdecl VQA_sosCODECInitStream(struct _VQA_SOS_COMPRESS_INFO *sosinfo);
#ifdef __cplusplus
}
#endif
#endif

#endif



