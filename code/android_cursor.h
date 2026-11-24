#pragma once
#ifdef __ANDROID__
#include <cstdint>
class ShapeSet;
void Android_Cursor_Set(ShapeSet const * shape, int frame, int hotx, int hoty);
void Android_Cursor_Draw(std::uint16_t * pixels, int stride, int width, int height,
    int game_width, int game_height, int scaled_width, int scaled_height, int offset_x, int offset_y, bool battlefield);
bool Android_System_Pointer(bool hidden);
#endif
