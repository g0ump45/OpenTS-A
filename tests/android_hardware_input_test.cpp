#include "../code/android_hardware_input.h"
#include <cassert>
int main() {
    using namespace android_hardware;
    for (int i=0;i<26;++i) assert(virtual_key(AKEYCODE_A+i)=='A'+i);
    for (int i=0;i<10;++i) assert(virtual_key(AKEYCODE_0+i)=='0'+i);
    assert(virtual_key(AKEYCODE_CTRL_LEFT)==0x11);
    assert(virtual_key(AKEYCODE_CTRL_RIGHT)==0x11);
    assert(virtual_key(AKEYCODE_F12)==0x7b);
    assert(virtual_key(AKEYCODE_DPAD_LEFT)==0x25);
    assert(virtual_key(AKEYCODE_DPAD_UP)==0x26);
    assert(virtual_key(AKEYCODE_DPAD_RIGHT)==0x27);
    assert(virtual_key(AKEYCODE_DPAD_DOWN)==0x28);
    assert(virtual_key(AKEYCODE_ESCAPE)==0x1b);
    assert(virtual_key(AKEYCODE_VOLUME_UP)==0);
    assert(ascii('A',false,false)=='a');
    assert(ascii('A',true,false)=='A');
    assert(ascii('A',false,true)=='A');
    assert(ascii('A',true,true)=='a');
    assert(ascii('1',true,false)=='!');
    assert(ascii(virtual_key(AKEYCODE_APOSTROPHE),false,false)==39);
    assert(ascii(virtual_key(AKEYCODE_BACKSLASH),false,false)==92);
    assert(ascii(virtual_key(AKEYCODE_SLASH),true,false)=='?');
}
