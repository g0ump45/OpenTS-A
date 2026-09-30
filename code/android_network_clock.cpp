// SPDX-License-Identifier: GPL-3.0-or-later
#ifdef __ANDROID__
#include "nettime.h"
#include <chrono>

namespace NetTiming {
namespace {
class AndroidClock final : public MillisecondClock {
public:
	Milliseconds Now() const override
	{
		auto elapsed = std::chrono::steady_clock::now().time_since_epoch();
		return static_cast<Milliseconds>(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count());
	}
};
}

MillisecondClock const & Default_Clock()
{
	static AndroidClock clock;
	return clock;
}
}
#endif
