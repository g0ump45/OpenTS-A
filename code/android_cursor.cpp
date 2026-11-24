#include "always.h"
#ifdef __ANDROID__
#include "android_cursor.h"
#include "android_pointer_layout.h"
#include "win.h"
#include "_convert.h"
#include "_keyboar.h"
#include "_xmouse.h"
#include "convert.h"
#include "globals.h"
#include "keyboard.h"
#include "mouse.h"
#include "movies.h"
#include "shapeset.h"
#include <algorithm>
#include <mutex>
#include <vector>

namespace {
std::mutex cursor_mutex;
ShapeSet const * selected_shape = nullptr;
int selected_frame = 0, selected_hotx = 0, selected_hoty = 0;
ShapeSet const * cached_shape = nullptr;
ConvertClass const * cached_drawer = nullptr;
int cached_frame = -1, cursor_width = 0, cursor_height = 0;
std::vector<unsigned char> cursor_indices;
}

void Android_Cursor_Set(ShapeSet const * shape, int frame, int hotx, int hoty)
{
    std::lock_guard<std::mutex> lock(cursor_mutex);
    selected_shape = shape; selected_frame = frame;
    selected_hotx = hotx; selected_hoty = hoty;
}

void Android_Cursor_Draw(std::uint16_t * pixels, int stride, int width, int height,
    int game_width, int game_height, int scaled_width, int scaled_height, int offset_x, int offset_y, bool battlefield)
{
    std::lock_guard<std::mutex> lock(cursor_mutex);
    ShapeSet const * shape = battlefield ? selected_shape : MouseClass::MouseShapes;
    int const frame = battlefield ? selected_frame : 0;
    bool const ready = Keyboard && Keyboard->AndroidMousePresent.load() && GameInFocus &&
        shape && MouseDrawer && frame >= 0 && frame < shape->Get_Count();
    if (!ready) { Android_System_Pointer(false); return; }
    if (shape != cached_shape || frame != cached_frame || MouseDrawer != cached_drawer) {
        cursor_width = shape->Get_Width(); cursor_height = shape->Get_Height();
        if (cursor_width <= 0 || cursor_height <= 0 || cursor_width > 512 || cursor_height > 512) { Android_System_Pointer(false); return; }
        Rect const rect = shape->Get_Rect(frame);
        auto const * data = static_cast<unsigned char const *>(shape->Get_Data(frame));
        if (!data || !rect.Is_Valid()) { Android_System_Pointer(false); return; }
        cursor_indices.assign(cursor_width * cursor_height, 0);
        for (int y = 0; y < rect.Height; ++y) for (int x = 0; x < rect.Width; ++x) {
            int const dx = rect.X + x, dy = rect.Y + y;
            if (dx >= 0 && dx < cursor_width && dy >= 0 && dy < cursor_height)
                cursor_indices[dy * cursor_width + dx] = data[y * rect.Width + x];
        }
        cached_shape = shape; cached_frame = frame; cached_drawer = MouseDrawer;
    }
    if (!Android_System_Pointer(true) || Movie_Is_Playing()) return;
    int const hotx = battlefield ? selected_hotx : 0, hoty = battlefield ? selected_hoty : 0;
    int const left = Keyboard->AndroidPointerWindowX.load() - hotx * scaled_width / game_width;
    int const top = Keyboard->AndroidPointerWindowY.load() - hoty * scaled_height / game_height;
    int const draw_width = std::max(1, cursor_width * scaled_width / game_width);
    int const draw_height = std::max(1, cursor_height * scaled_height / game_height);
    auto const * palette = static_cast<unsigned short const *>(MouseDrawer->Get_Translate_Table());
    if (!palette) { Android_System_Pointer(false); return; }
    android_pointer::draw_cursor(pixels, stride, width, height, cursor_indices.data(),
        cursor_width, cursor_height, palette, left, top, draw_width, draw_height);
}
#endif
