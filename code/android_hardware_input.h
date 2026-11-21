#pragma once
#include <android/keycodes.h>

namespace android_hardware {
inline int virtual_key(int key) {
    if (key >= AKEYCODE_A && key <= AKEYCODE_Z) return 'A' + key - AKEYCODE_A;
    if (key >= AKEYCODE_0 && key <= AKEYCODE_9) return '0' + key - AKEYCODE_0;
    if (key >= AKEYCODE_F1 && key <= AKEYCODE_F12) return 0x70 + key - AKEYCODE_F1;
    if (key >= AKEYCODE_NUMPAD_0 && key <= AKEYCODE_NUMPAD_9) return 0x60 + key - AKEYCODE_NUMPAD_0;
    switch (key) {
        case AKEYCODE_ESCAPE: return 0x1b;
        case AKEYCODE_ENTER: case AKEYCODE_NUMPAD_ENTER: return 0x0d;
        case AKEYCODE_DEL: return 0x08;
        case AKEYCODE_FORWARD_DEL: return 0x2e;
        case AKEYCODE_TAB: return 0x09;
        case AKEYCODE_SPACE: return 0x20;
        case AKEYCODE_DPAD_LEFT: return 0x25;
        case AKEYCODE_DPAD_UP: return 0x26;
        case AKEYCODE_DPAD_RIGHT: return 0x27;
        case AKEYCODE_DPAD_DOWN: return 0x28;
        case AKEYCODE_MOVE_HOME: return 0x24;
        case AKEYCODE_MOVE_END: return 0x23;
        case AKEYCODE_PAGE_UP: return 0x21;
        case AKEYCODE_PAGE_DOWN: return 0x22;
        case AKEYCODE_INSERT: return 0x2d;
        case AKEYCODE_SHIFT_LEFT: case AKEYCODE_SHIFT_RIGHT: return 0x10;
        case AKEYCODE_CTRL_LEFT: case AKEYCODE_CTRL_RIGHT: return 0x11;
        case AKEYCODE_ALT_LEFT: case AKEYCODE_ALT_RIGHT: return 0x12;
        case AKEYCODE_CAPS_LOCK: return 0x14;
        case AKEYCODE_NUM_LOCK: return 0x90;
        case AKEYCODE_SCROLL_LOCK: return 0x91;
        case AKEYCODE_BREAK: return 0x13;
        case AKEYCODE_MINUS: return 0xbd;
        case AKEYCODE_EQUALS: return 0xbb;
        case AKEYCODE_LEFT_BRACKET: return 0xdb;
        case AKEYCODE_RIGHT_BRACKET: return 0xdd;
        case AKEYCODE_BACKSLASH: return 0xdc;
        case AKEYCODE_SEMICOLON: return 0xba;
        case AKEYCODE_APOSTROPHE: return 0xde;
        case AKEYCODE_COMMA: return 0xbc;
        case AKEYCODE_PERIOD: return 0xbe;
        case AKEYCODE_SLASH: return 0xbf;
        case AKEYCODE_GRAVE: return 0xc0;
        case AKEYCODE_NUMPAD_ADD: return 0x6b;
        case AKEYCODE_NUMPAD_SUBTRACT: return 0x6d;
        case AKEYCODE_NUMPAD_MULTIPLY: return 0x6a;
        case AKEYCODE_NUMPAD_DIVIDE: return 0x6f;
        case AKEYCODE_NUMPAD_DOT: return 0x6e;
        default: return 0;
    }
}
inline int ascii(int key, bool shift, bool caps) {
    if (key >= 'A' && key <= 'Z') return (shift != caps) ? key : key + 'a' - 'A';
    if (key >= '0' && key <= '9') return shift ? ")!@#$%^&*("[key - '0'] : key;
    if (key >= 0x60 && key <= 0x69) return '0' + key - 0x60;
    if (key == 0x08 || key == 0x09 || key == 0x0d || key == 0x20 || key == 0x1b) return key;
    switch (key) {
        case 0xbd: return shift ? '_' : '-'; case 0xbb: return shift ? '+' : '=';
        case 0xdb: return shift ? '{' : '['; case 0xdd: return shift ? '}' : ']';
        case 0xdc: return shift ? '|' : '\\'; case 0xba: return shift ? ':' : ';';
        case 0xde: return shift ? '"' : '\''; case 0xbc: return shift ? '<' : ',';
        case 0xbe: return shift ? '>' : '.'; case 0xbf: return shift ? '?' : '/';
        case 0xc0: return shift ? '~' : '`'; case 0x6b: return '+';
        case 0x6d: return '-'; case 0x6a: return '*'; case 0x6f: return '/'; case 0x6e: return '.';
        default: return 0;
    }
}
}
