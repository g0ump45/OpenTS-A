#pragma once
#include "win.h"
#define WSAAPI
typedef int SOCKET;
#define INVALID_SOCKET -1
inline int WSAStartup(int, void*){return 0;}
inline int WSACleanup(){return 0;}

class WinsockInterfaceClass {
public:
    enum PacketDropReasonType { REASON_NONE=0 };
    struct WinsockBufferType { int dummy; };
    WinsockInterfaceClass(){}
    ~WinsockInterfaceClass(){}
    void Close(){}
    bool Init(){return false;}
    void Set_Socket_Options(){}
    void Record_Packet_Drop(PacketDropReasonType){}
    WinsockBufferType* Get_New_Out_Buffer(){return nullptr;}
    WinsockBufferType* Get_New_In_Buffer(){return nullptr;}
    void Close_Socket(){}
    int Read(void*, int&, void*, int&){return 0;}
    int WriteTo(void*, int, void*, int){return 0;}
    void Discard_In_Buffers(){}
    void Discard_Out_Buffers(){}
    void Start_Listening(){}
    void Stop_Listening(){}
    void Service(){}
    void Clear_Error(){}
    void Build_Packet_CRC(WinsockBufferType*){}
    bool Open_Socket(int){return false;}
};