// SPDX-License-Identifier: GPL-3.0-or-later
#include "nettime.h"
#include <cassert>
#include <chrono>
#include <cstdio>
#include <thread>

int main()
{
	auto const & clock = NetTiming::Default_Clock();
	auto start = clock.Now();
	std::this_thread::sleep_for(std::chrono::milliseconds(30));
	assert(NetTiming::Milliseconds_Have_Elapsed(start, clock.Now(), 20));
	assert(NetTiming::Elapsed_Milliseconds(0xfffffff0u, 0x10u) == 32);
	puts("PASS: Android network clock advances and handles wrapping elapsed time");
}
