// android_stubs.cpp V9 - no mapgen duplicates, UI stubs only
#include "android_compat.h"
#ifdef __ANDROID__
#include <cstdint>
#include <chrono>
#include "win.h"

HWND MainWindow = nullptr;
HWND UnusedWindow = nullptr;
HINSTANCE ProgramInstance = nullptr;
int ShowCommand = 0;

#include "desyncdlg.h"
DesyncDialogClass DesyncDialog;
void DesyncDialogClass::Notify_Chat(const char*, const char*) {}

#include "ownrdraw.h"
HWND OwnerDraw::Begin_Dialog(int, DLGPROC) { return nullptr; }
void OwnerDraw::Display_Dialog(void*) {}
bool OwnerDraw::Dialog_Message_Handler() { return false; }
void OwnerDraw::End_Dialog(void*) {}
long OwnerDraw::Default_Dialog_Proc(void*, unsigned int, unsigned long, long) { return 0; }
HWND OwnerDraw::Custom_Message_Box(const char * a, const char * b, bool * c) { if(c) *c=false; return nullptr; }
void OwnerDraw::Set_Custom_Message_Box_Text(void*, const char*) {}
void OwnerDraw::Prepare_Resources(void*) {}
int OwnerDraw::Capture_Mouse() { return 0; }
int OwnerDraw::Release_Mouse() { return 0; }

#include "house.h"
HousesType Owner_From_Name(const char*) { return HOUSE_NONE; }
LandType Land_From_Name(const char*) { return (LandType)0; }
const char* Name_From_Land(LandType) { return ""; }
VQType VQ_From_Name(const char*) { return (VQType)0; }
const char* Name_From_VQ(VQType) { return ""; }
SourceType Source_From_Name(const char*) { return (SourceType)0; }
const char* Name_From_Source(SourceType) { return ""; }
CrateType Crate_From_Name(const char*) { return (CrateType)0; }
const char* Name_From_Crate(CrateType) { return ""; }
SpeedType Speed_From_Name(const char*) { return (SpeedType)0; }
const char* Name_From_Speed(SpeedType) { return ""; }

int VideoModeWidth = 640;
int VideoModeHeight = 480;
bool WindowedMode = true;
unsigned short ODRComponentMask=0;
unsigned short ODGComponentMask=0;
unsigned short ODBComponentMask=0;

void* SurfaceCache = nullptr;
COLORREF ODColorText = 0;
int OD_Draw_Text_Remap(Surface & s, const char * str, Rect const & r, char const * n, COLORREF c, int f, int cs) { return 0; }

bool Disk_Space_Available() { return true; }
int Disk_Space_Available_MB() { return 9999; }
unsigned long long Disk_Space_Available_ULL() { return 1024ULL*1024*1024; }
void Sign_Off_Match() {}
void WS_Destroy_Dialog(void*, int) {}
bool Load_Title_Screen(const char*, struct Surface*, class PaletteClass*) { return false; }
void* PacketTransport = nullptr;
void Destroy_Connection(int, int) {}

void Call_Back() {}
void Shake_The_Screen(int) {}
void IPX_Call_Back() {}
void Unselect_All() {}
void Video_Shutdown() {}
void Shutdown_Network() {}
bool On_WM_MOVING(HWND window, WPARAM wparam, LPARAM lparam) { return false; }

class TechnoTypeClass;
TechnoTypeClass * Fetch_Techno_Type(RTTIType, int) { return nullptr; }

void Video_Mark_Dirty() {}
struct VideoScaleInfo{int dummy;}; VideoScaleInfo Video_Get_Scale_Info(){return {};}

bool Win_Cursor_Set(struct ShapeSet const*,int,int,int,bool){return false;}
bool Win_Cursor_Set_Visible(bool){return false;}

void List_Copy(Cell const*, int, Cell*) {}

#include "nettiming.h"
struct MyClock : public NetTiming::MillisecondClock {
    NetTiming::Milliseconds Now(void) const override {
        return (NetTiming::Milliseconds)std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
    }
};
namespace NetTiming {
    static MyClock s_clock;
    MillisecondClock const & Default_Clock(void) { return s_clock; }
}

#include "vqalib/vqaplay.h"
long VQA_Open(char const* name, _VQAConfig* cfg, VQAHandle** handle) {
    if(handle) *handle=nullptr;
    return 0;
}
#include "vqalib/vqaplayp.h"
void VQA_PauseAudio(VQAHandleP* h) {}
void VQA_ResumeAudio(VQAHandleP* h) {}

#include "winfix.h"
int Build_Hotkey_String(KeyNumType,char* b){if(b)b[0]=0;return 0;}
void* WS_Find_Dialog(int){return nullptr;} void* WS_Top_Window(){return nullptr;}
void* WS_Next_Lower_Dialog(void*){return nullptr;} int WS_Top_Window_ID(){return 0;}
void* WS_Create_Dialog(void*,int,void*,long(*)(void*,unsigned int,unsigned long,long),int){return nullptr;}
void* WS_Wait_Dialog(void*,bool(*)(),bool,bool){return nullptr;}
void Center_Window_Within_Window(void*){} void On_WM_NCDESTROY(void*){}
int Net2EncodeGameopt(char*,int){return 0;} int Compute_Name_CRC(char*){return 0;}
void Net2SetAccept(char*,int){} void Net2SetHouseAndColor(char*,int,int){} int Net2GetAccept(char*){return 0;}
void Net2DisplayUsers(){} void Net2Callback(){}

// Stubs for files we still exclude
extern "C" {
    const char* Debug_Directory() { return "./"; }
    int Delete_Files_Older_Than(const char*, const char*, unsigned) { return 0; }
    const char* Last_Error_Text(unsigned long) { return ""; }
}

#endif