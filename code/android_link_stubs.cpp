// android_link_stubs.cpp V19 - V18 plus missing Destroy_Connection etc
struct Cell { int X,Y; };
struct Surface { int dummy; };
struct PaletteClass { int dummy; };
struct ShapeSet { int dummy; };
struct NativeWindow { void* ptr=nullptr; };
template<typename T> struct TRect { T X=0,Y=0,W=0,H=0; };
struct Rect { int X=0,Y=0,W=0,H=0; };

HWND MainWindow = nullptr;
HINSTANCE ProgramInstance = nullptr;
HWND UnusedWindow = nullptr;
int ShowCommand = 0;
int VideoModeWidth = 640;
int VideoModeHeight = 480;
bool WindowedMode = true;
unsigned short ODRComponentMask=0, ODGComponentMask=0, ODBComponentMask=0;
COLORREF ODColorText = 0;

struct _VQAConfig { int dummy; };
struct _VQAHandle { int dummy; };
struct _VQAHandleP { int dummy; };
struct GlobalPacketType { int dummy; };
struct IPXAddressClass { int dummy; };

// Win32 / video / dialog
void Video_Shutdown() {}
void Video_Mark_Dirty() {}

void WS_Destroy_Dialog(void*,int){}
void* WS_Find_Dialog(int){return nullptr;}
HWND WS_Top_Window(){return nullptr;}
void* WS_Next_Lower_Dialog(void*){return nullptr;}
int WS_Top_Window_ID(){return 0;}
void* WS_Create_Dialog(void*,int,void*,long(*)(void*,unsigned int,unsigned long,long),int){return nullptr;}
void* WS_Wait_Dialog(void*,bool(*)(),bool,bool){return nullptr;}
void Center_Window_Within_Window(void*){}
void Center_Window_Within_Window(void*,void*){}
void On_WM_NCDESTROY(void*){}
int Net2EncodeGameopt(char*,int){return 0;}
int Compute_Name_CRC(char*){return 0;}
void Net2SetAccept(char*,int){}
void Net2SetHouseAndColor(char*,int,int){}
int Net2GetAccept(char*){return 0;}
void Net2DisplayUsers(){}
void Net2Callback(){}
void* Video_Get_Scale_Info(){static int d=0; return &d;}
bool Win_Cursor_Set(ShapeSet const*,int,int,int,bool){return false;}
bool Win_Cursor_Set_Visible(bool){return false;}

void VQA_ResumeAudio(_VQAHandleP*){}
BOOL On_WM_MOVING(HWND,WPARAM,LPARAM){return FALSE;}
BOOL On_WM_CONTEXTMENU(WPARAM){return FALSE;}
BOOL On_WM_HELP(LPARAM){return FALSE;}
void EnumDisplayModes(int,int,int,int){}
void Video_Set_Mode(int,int){}
HWND Create_Main_Window(void*,int,int,int){return nullptr;}
int Win_Window_Refresh_Rate(void*){return 60;}
void* Win_Native_Window(void*){return nullptr;}
void Win_Window_Drawable_Size(void*,int& w,int& h){w=640;h=480;}
bool Video_Init(NativeWindow const&,int,int,int){return true;}
void Net2Init_Network(){}
void Net2Remote_Connect(){}
void* WS_Get_Font(void*,const char*,int,int,int){return nullptr;}

int OD_Draw_Text_Remap(Surface&,const char*,Rect const&,const char*,COLORREF,int,int){return 0;}
int OD_Draw_Text_Remap(Surface&,const char*,TRect<int> const&,const char*,unsigned int,int,int){return 0;}
int OD_Draw_Text(unsigned int,void*,TRect<int> const&,const char*,int,int,int,Surface*){return 0;}

namespace OwnerDraw {
    struct CellData { CellData(); };
    HWND Begin_Dialog(int,DLGPROC){return nullptr;}
    void Display_Dialog(void*){}
    int Dialog_Message_Handler(){return 0;}
    long Default_Dialog_Proc(void*,unsigned int,unsigned long,long){return 0;}
    HWND Custom_Message_Box(const char*,const char*,bool* c){if(c) *c=false; return nullptr;}
    void Set_Custom_Message_Box_Text(void*,const char*){}
    int Capture_Mouse(){return 0;}
    int Release_Mouse(){return 0;}
    void End_Dialog(void*){}
    void Subclass_Dialog(void*,long){}
    void Draw_Item(LPDRAWITEMSTRUCT){}
    void Draw_Dialog_Back(void*){}
    void Move_Dialog(void*,int,int){}
}
OwnerDraw::CellData::CellData(){}

// Game logic stubs that are NOT in conquer.cpp
bool Process_Global_Packet(GlobalPacketType*,IPXAddressClass*){return false;}
