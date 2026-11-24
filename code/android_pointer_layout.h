#pragma once
#include <algorithm>
#include <cstdint>

namespace android_pointer {
struct Size { int width, height; };
struct View { int x, y, width, height; };
inline View presentation_view(int width, int height, bool menu, bool top_aligned) {
    if (!menu || width < 640 || height < 480) return {0, 0, width, height};
    return {(width - 640) / 2, top_aligned ? 0 : (height - 480) / 2, 640, 480};
}
inline Size map_window(View view, int window_width, int window_height, int x, int y) {
    if (view.width <= 0 || view.height <= 0 || window_width <= 0 || window_height <= 0) return {view.x, view.y};
    int const sw = std::min(window_width, view.width * window_height / view.height);
    int const sh = std::min(window_height, view.height * window_width / view.width);
    if (sw <= 0 || sh <= 0) return {view.x, view.y};
    return {view.x + (x - (window_width - sw) / 2) * view.width / sw,
        view.y + (y - (window_height - sh) / 2) * view.height / sh};
}

inline bool valid_custom_resolution(int width, int height) {
    return width >= 640 && height >= 480 && width >= height && width <= 3840 && height <= 2400 &&
        std::int64_t(width) * height <= 8294400;
}

inline Size resolution(int preset, int window_width, int window_height) {
    int height = preset == 2 ? 600 : preset == 3 ? 720 : 480;
    if (window_width <= 0 || window_height <= 0) return {640, height};
    int width = int((std::int64_t(height) * window_width + window_height / 2) / window_height);
    if (width < 640) { width = 640; height = std::max(height, int((640LL * window_height + window_width / 2) / window_width)); }
    return {width, height};
}
// Hardware scrolling is confined to the visible battlefield's outermost pixels.
inline unsigned edges(int x, int y, int left, int top, int width, int height) {
    if (width <= 0 || height <= 0 || x < left || y < top || x >= left + width || y >= top + height) return 0;
    unsigned result = 0;
    if (x == left) result |= 1;
    if (x == left + width - 1) result |= 2;
    if (y == top) result |= 4;
    if (y == top + height - 1) result |= 8;
    return result;
}
inline void draw_cursor(std::uint16_t * pixels, int stride, int width, int height,
    unsigned char const * indices, int source_width, int source_height,
    unsigned short const * palette, int left, int top, int draw_width, int draw_height) {
    if (!pixels || !indices || !palette || stride < width || width <= 0 || height <= 0 ||
        source_width <= 0 || source_height <= 0 || draw_width <= 0 || draw_height <= 0) return;
    for (int y = std::max(0, -top); y < draw_height && top + y < height; ++y) {
        for (int x = std::max(0, -left); x < draw_width && left + x < width; ++x) {
            unsigned char const index = indices[(y * source_height / draw_height) * source_width + x * source_width / draw_width];
            if (index) pixels[(top + y) * stride + left + x] = palette[index];
        }
    }
}

}
