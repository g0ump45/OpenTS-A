#pragma once

#ifdef __ANDROID__
#include <atomic>

enum AndroidControlScheme {
        ANDROID_CONTROL_ORIGINAL = 0,
        ANDROID_CONTROL_MODERN = 1
};

struct AndroidControlSettings {
        std::atomic<int> ControlScheme{ANDROID_CONTROL_MODERN};
	std::atomic<bool> DoubleTapRightClick{true};
	std::atomic<bool> SelectionBox{true};
	std::atomic<bool> EdgeScrolling{true};
	std::atomic<int> PanSpeed{8};
	std::atomic<int> DoubleTapMilliseconds{300};
};

extern AndroidControlSettings AndroidControls;
extern std::atomic<bool> AndroidMenuActive;
void Android_Load_Control_Settings();
bool Android_Save_Control_Settings();
void Android_Reset_Control_Settings();
#endif
