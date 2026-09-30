// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#ifdef __ANDROID__
#include "android_lan.h"

std::array<unsigned char, 20> Android_LAN_Content(std::string const & map);
bool Android_LAN_Open_Transport(AndroidLanProbe const & lobby);
bool Android_LAN_Check_Transport(AndroidLanProbe const & lobby, uint64_t now);
bool Android_LAN_Launch(std::unique_ptr<AndroidLanProbe> lobby);
void Android_LAN_Service();
void Android_LAN_Reset();
bool Android_LAN_Active();
std::string Android_LAN_Take_Error();
#endif
