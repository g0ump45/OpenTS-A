#pragma once

#include <cstdint>
#include <cstdlib>
#include <vector>
#include <mutex>
#include <string>

// Coordinates are in unzoomed game pixels, shared by drawing and touch input.
namespace touch_shortcuts {
constexpr int Groups = 10, Base = 11, Size = 40, Step = 42;
enum class Phase { Down, Move, Up, Cancel, Extra };
struct Layout {
	int x = 0, y = 0, direction = 1;
	bool visible = false, expanded = false;
	int left(int id) const {
		if (id == Groups) return x;
		if (id == Base) return x + Step;
		return x + ((id - 1) % 3) * Step;
	}
	int top(int id) const {
		return id >= Groups ? y : y + direction * Step * (1 + (id - 1) / 3);
	}
	int hit(int px, int py) const {
		if (visible) for (int id = expanded ? 1 : Groups; id <= Base; ++id) {
			if (px >= left(id) && px < left(id) + Size &&
			    py >= top(id) && py < top(id) + Size) return id;
		}
		return 0;
	}
};

class Panel {
	std::mutex mutex;
	Layout layout;
	bool captured = false;
	int pressed = 0, startX = 0, startY = 0;
	std::int64_t startTime = 0;
	std::vector<std::string> pending;
public:
	Layout frame(bool visible, int x = 0, int y = 0, int direction = 1) {
		std::lock_guard<std::mutex> lock(mutex);
		if (!visible || x != layout.x || y != layout.y || direction != layout.direction) {
			pressed = 0;
			layout.expanded = false;
			pending.clear();
		}
		layout.visible = visible;
		layout.x = x;
		layout.y = y;
		layout.direction = direction;
		return layout;
	}
	bool touch(Phase phase, int x, int y, std::int64_t time) {
		std::lock_guard<std::mutex> lock(mutex);
		if (phase == Phase::Down) {
			pressed = layout.hit(x, y);
			captured = pressed != 0;
			startX = x;
			startY = y;
			startTime = time;
		}
		if (!captured) return false;
		if (phase == Phase::Cancel || phase == Phase::Extra ||
		    layout.hit(x, y) != pressed || std::abs(x-startX) > 12 || std::abs(y-startY) > 12) pressed = 0;
		if (phase == Phase::Up) {
			if (pressed == Groups) layout.expanded = !layout.expanded;
			else if (pressed == Base) pending.emplace_back("CenterBase");
			else if (pressed) {
				bool assign = time - startTime >= 500000000LL;
				pending.push_back((assign ? "TeamCreate_" : "TeamSelect_") + std::to_string(pressed));
			}
		}
		if (phase == Phase::Up || phase == Phase::Cancel) captured = false;
		return true;
	}
	std::vector<std::string> take() {
		std::lock_guard<std::mutex> lock(mutex);
		std::vector<std::string> result;
		result.swap(pending);
		return result;
	}
};
inline Panel panel;
}
