#include "../code/android_shortcuts.h"
#include <cstdlib>
#include <iostream>

using namespace touch_shortcuts;

static void check(bool value, int line) {
	if (!value) {
		std::cerr << "Shortcut check failed on line " << line << '\n';
		std::exit(1);
	}
}
#define CHECK(value) check((value), __LINE__)

int main() {
	for (int direction : {-1, 1}) {
		Panel p;
		auto layout = p.frame(true, 80, 200, direction);
		auto press = [&](int id, std::int64_t duration) {
			int x = layout.left(id) + 1, y = layout.top(id) + 1;
			CHECK(p.touch(Phase::Down, x, y, 0));
			CHECK(p.touch(Phase::Up, x, y, duration));
		};
		CHECK(layout.hit(layout.left(1), layout.top(1)) == 0);
		CHECK(!p.touch(Phase::Down, 0, 0, 0));
		CHECK(!p.touch(Phase::Move, 81, 201, 1));
		CHECK(!p.touch(Phase::Up, 81, 201, 2));
		press(Groups, 1);
		press(Base, 1);
		for (int n = 1; n <= 9; ++n) {
			press(n, 499999999);
			press(n, 500000000);
		}
		auto commands = p.take();
		CHECK(commands.size() == 19 && commands[0] == "CenterBase");
		for (int n = 1; n <= 9; ++n) {
			CHECK(commands[n*2-1] == "TeamSelect_" + std::to_string(n));
			CHECK(commands[n*2] == "TeamCreate_" + std::to_string(n));
		}
		for (auto phase : {Phase::Extra, Phase::Move, Phase::Cancel}) {
			CHECK(p.touch(Phase::Down, 81, 201, 0));
			CHECK(p.touch(phase, 96, 201, 1));
			CHECK(p.touch(Phase::Up, 81, 201, 2) == (phase != Phase::Cancel));
			CHECK(p.frame(true, 80, 200, direction).expanded);
		}
		press(Base, 2);
		CHECK(p.touch(Phase::Down, 81, 201, 0));
		p.frame(false);
		CHECK(p.touch(Phase::Up, 81, 201, 1));
		CHECK(!p.touch(Phase::Down, 81, 201, 2));
		CHECK(p.take().empty());
	}
}
