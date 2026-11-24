/*******************************************************************************
 *                                O P E N  T S
 ******************************************************************************/

#include "always.h"

#ifdef __ANDROID__

#include "android_video.h"
#include "android_shortcuts.h"
#include "android_cursor.h"
#include "android_controls.h"
#include "_keyboar.h"
#include "movies.h"
#include "android_pointer_layout.h"
#include <fstream>
#include <string>
#include <cstdio>

#include <android/native_window.h>

#include "_alpha.h"
#include "_rect.h"
#include "_surface.h"
#include "dsurface.h"
#include "dbgprint.h"
#include "globals.h"
#include "goptions.h"
#include "init.h"
#include "misc.h"
#include "sidebar.h"
#include "zbuffer.h"

#include <algorithm>
#include <cstdint>
#include <mutex>
#include <vector>


static ANativeWindow * AndroidWindow = nullptr;
static std::mutex AndroidWindowMutex;
static double AndroidVideoZoom = 1.0;
static std::mutex AndroidViewMutex;
static android_pointer::View AndroidInputView{0,0,0,0};
static bool AndroidInputBattlefield = false;
static void Android_Remap_Mouse(android_pointer::View view, int width, int height, bool battlefield)
{
    if (!Keyboard || !Keyboard->AndroidMousePresent.load()) return;
    auto const point = android_pointer::map_window(view, width, height,
        Keyboard->AndroidPointerWindowX.load(), Keyboard->AndroidPointerWindowY.load());
    Keyboard->AndroidTouchX = point.width; Keyboard->AndroidTouchY = point.height;
    int x = point.width, y = point.height;
    if (battlefield) Android_Video_Map_Touch(x, y, x, y);
    Keyboard->Set_Mouse_Position(x, y);
}
void Android_Video_Reset_Input_View()
{
    android_pointer::View const view{0,0,VideoModeWidth,VideoModeHeight};
    { std::lock_guard<std::mutex> lock(AndroidViewMutex); AndroidInputView = view; AndroidInputBattlefield = true; }
    int width = 0, height = 0;
    if (Android_Video_Window_Size(width, height)) Android_Remap_Mouse(view, width, height, true);
}
void Android_Video_Get_Input_View(int & x, int & y, int & width, int & height)
{
    std::lock_guard<std::mutex> lock(AndroidViewMutex);
    auto const view = AndroidInputView.width > 0 ? AndroidInputView : android_pointer::View{0,0,VideoModeWidth,VideoModeHeight};
    x = view.x; y = view.y; width = view.width; height = view.height;
}



static std::string AndroidDisplayPath;
static int AndroidDisplayPreset = 0;
static int AndroidCustomWidth = 1280, AndroidCustomHeight = 720;
void Android_Video_Init_Display(char const * data_path)
{
    AndroidDisplayPath = std::string(data_path ? data_path : "/sdcard/Android/data/com.opents.game/files") + "/ANDROID-DISPLAY.cfg";
    AndroidDisplayPreset = 0;
    std::ifstream file(AndroidDisplayPath);
    int value = 0, width = 0, height = 0;
    if (!(file >> value)) return;
    if (value >= 0 && value <= 3) AndroidDisplayPreset = value;
    else if (value == 4 && (file >> width >> height) && android_pointer::valid_custom_resolution(width, height)) {
        AndroidDisplayPreset = 4; AndroidCustomWidth = width; AndroidCustomHeight = height;
    }
}
int Android_Video_Resolution_Preset() { return AndroidDisplayPreset; }
bool Android_Video_Window_Size(int & width, int & height)
{
    std::lock_guard<std::mutex> lock(AndroidWindowMutex);
    if (!AndroidWindow) return false;
    width = ANativeWindow_getWidth(AndroidWindow); height = ANativeWindow_getHeight(AndroidWindow);
    return width > 0 && height > 0;
}
void Android_Video_Pending_Resolution(int & width, int & height)
{
    if (AndroidDisplayPreset == 4) { width = AndroidCustomWidth; height = AndroidCustomHeight; return; }
    int window_width = 0, window_height = 0;
    Android_Video_Window_Size(window_width, window_height);
    auto const size = android_pointer::resolution(AndroidDisplayPreset, window_width, window_height);
    width = size.width; height = size.height;
}
static bool Android_Save_Display(int preset, int width, int height)
{
    if (AndroidDisplayPath.empty()) return false;
    std::string const temporary = AndroidDisplayPath + ".tmp";
    std::ofstream file(temporary, std::ios::trunc);
    file << preset;
    if (preset == 4) file << ' ' << width << ' ' << height;
    file << '\n'; file.close();
    if (!file || std::rename(temporary.c_str(), AndroidDisplayPath.c_str()) != 0) return false;
    AndroidDisplayPreset = preset;
    if (preset == 4) { AndroidCustomWidth = width; AndroidCustomHeight = height; }
    return true;
}
bool Android_Video_Save_Resolution(int preset)
{
    return preset >= 0 && preset <= 3 && Android_Save_Display(preset, 0, 0);
}
bool Android_Video_Save_Custom_Resolution(int width, int height)
{
    return android_pointer::valid_custom_resolution(width, height) && Android_Save_Display(4, width, height);
}

void Android_Video_Map_Touch(int screen_x, int screen_y, int & x, int & y)
{
    x = screen_x;
    y = screen_y;
    if (AndroidMenuActive.load() || !ScenarioActive) return;

    double const zoom = AndroidVideoZoom;
    if (zoom <= 1.0) {
        return;
    }

    int const tactical_screen_x = Options.IsSidebarOnRight ? TacticalRect.X : SidebarRect.Width;
    int const tactical_screen_y = TacticalRect.Y;

    if (screen_x < tactical_screen_x ||
        screen_x >= tactical_screen_x + TacticalRect.Width ||
        screen_y < tactical_screen_y ||
        screen_y >= tactical_screen_y + TacticalRect.Height) {
        return;
    }

    int const crop_width = std::max(1, static_cast<int>(TacticalRect.Width / zoom));
    int const crop_height = std::max(1, static_cast<int>(TacticalRect.Height / zoom));
    int const crop_x = tactical_screen_x + (TacticalRect.Width - crop_width) / 2;
    int const crop_y = tactical_screen_y + (TacticalRect.Height - crop_height) / 2;

    x = crop_x + (screen_x - tactical_screen_x) * crop_width / TacticalRect.Width;
    y = crop_y + (screen_y - tactical_screen_y) * crop_height / TacticalRect.Height;
}


void Android_Video_Set_Zoom(double zoom)
{
	AndroidVideoZoom = std::clamp(zoom, 1.0, 2.0);
}


double Android_Video_Get_Zoom(void)
{
	return AndroidVideoZoom;
}


void Android_Video_Set_Window(ANativeWindow * window)
{
        DebugString("ANDROID VIDEO: locking window mutex\n");
std::lock_guard<std::mutex> lock(AndroidWindowMutex);

        if (window != nullptr) {
                ANativeWindow_acquire(window);
        }

        ANativeWindow * old_window = AndroidWindow;
        AndroidWindow = window;

        if (AndroidWindow != nullptr) {
                ANativeWindow_setBuffersGeometry(AndroidWindow, 0, 0, WINDOW_FORMAT_RGB_565);
        }

        if (old_window != nullptr) {
                ANativeWindow_release(old_window);
        }
}


bool Android_Initialize_Engine_Surfaces(void)
{
	if (VisibleSurface != nullptr) {
		return true;
	}

	int width = 640, height = AndroidDisplayPreset == 2 ? 600 : AndroidDisplayPreset == 3 ? 720 : 480;
	{
		std::lock_guard<std::mutex> lock(AndroidWindowMutex);
		if (AndroidWindow) {
			int const w = ANativeWindow_getWidth(AndroidWindow);
			int const h = ANativeWindow_getHeight(AndroidWindow);
			if (AndroidDisplayPreset != 4 && w > 0 && h > 0) {
                auto const size = android_pointer::resolution(AndroidDisplayPreset, w, h);
                width = size.width; height = size.height;
            }
		}
	}
    if (AndroidDisplayPreset == 4) { width = AndroidCustomWidth; height = AndroidCustomHeight; }
	Options.ScreenWidth = width;
	Options.ScreenHeight = height;
	DebugString("Android battlefield resolution: %dx%d\n", width, height);
	VideoModeWidth = Options.ScreenWidth;
	VideoModeHeight = Options.ScreenHeight;
	VisibleRect = Rect(0, 0, VideoModeWidth, VideoModeHeight);

	VisibleSurface = DSurface::Create_Primary();
	if (VisibleSurface == nullptr) {
		return false;
	}
	VisibleSurface->Fill(0);

	Rect const sidebar_rect(0, 0, SidebarClass::SIDE_WIDTH, VisibleRect.Height);
	Rect const tactical_rect(0, 0, VisibleRect.Width - sidebar_rect.Width, VisibleRect.Height);
	TacticalRect = Rect(0, 16, VisibleRect.Width - sidebar_rect.Width, VisibleRect.Height - 16);
	if (!Allocate_Surfaces(VisibleRect, tactical_rect, tactical_rect, sidebar_rect, false)) {
		return false;
	}
	LogicalSurface = HiddenSurface;

	DepthBuffer = new ZBuffer(TacticalRect);
	DepthBuffer->Set_Scroll(ZBUFFER_MAX);
	AlphaBuffer = new ABuffer(TacticalRect);

	DSurface * const visible = static_cast<DSurface *>(VisibleSurface);
	Android_Video_Present(visible->Get_Buffer(), visible->Get_Width(), visible->Get_Height(), visible->Stride());
	return true;
}


void Android_Video_Get_Game_Size(int & width, int & height)
{
	width = VideoModeWidth;
	height = VideoModeHeight;
}

void Android_Video_Zoom_Battlefield(Surface * surface)
{
	if (surface == nullptr || AndroidVideoZoom <= 1.0) return;
	int const crop_width = std::max(1, static_cast<int>(TacticalRect.Width / AndroidVideoZoom));
	int const crop_height = std::max(1, static_cast<int>(TacticalRect.Height / AndroidVideoZoom));
	int const tactical_x = Options.IsSidebarOnRight ? TacticalRect.X : SidebarRect.Width;
	int const crop_x = tactical_x + (TacticalRect.Width - crop_width) / 2;
	int const crop_y = TacticalRect.Y + (TacticalRect.Height - crop_height) / 2;
	static std::vector<std::uint16_t> crop;
	crop.resize(static_cast<size_t>(crop_width) * crop_height);
	auto * pixels = static_cast<std::uint16_t *>(surface->Lock());
	if (pixels == nullptr) return;
	int const stride = surface->Stride() / 2;
	for (int y = 0; y < crop_height; ++y) {
		std::copy_n(pixels + (crop_y + y) * stride + crop_x, crop_width, crop.data() + y * crop_width);
	}
	for (int y = 0; y < TacticalRect.Height; ++y) {
		auto * row = pixels + (TacticalRect.Y + y) * stride + tactical_x;
		auto const * source = crop.data() + (y * crop_height / TacticalRect.Height) * crop_width;
		for (int x = 0; x < TacticalRect.Width; ++x) {
			row[x] = source[x * crop_width / TacticalRect.Width];
		}
	}
	surface->Unlock();
}


void Android_Video_Present(void const * pixels, int width, int height, int pitch, bool battlefield, bool menu)
{
	if (!battlefield) touch_shortcuts::panel.frame(false);
	if (pixels == nullptr || width <= 0 || height <= 0 || pitch < width * 2) {
        return;
}

ANativeWindow * window = nullptr;
{
        DebugString("ANDROID VIDEO: locking window mutex\n");
std::lock_guard<std::mutex> lock(AndroidWindowMutex);
        window = AndroidWindow;
        if (window != nullptr) {
                ANativeWindow_acquire(window);
        }
}

if (window == nullptr) {
        return;
}

ANativeWindow_Buffer buffer{};
if (ANativeWindow_lock(window, &buffer, nullptr) != 0 || buffer.bits == nullptr) {
        ANativeWindow_release(window);
        return;
}

    bool const menu_frame = !Movie_Is_Playing() && (menu || !ScenarioActive);
    auto const view = android_pointer::presentation_view(width, height, menu_frame, menu);
    bool changed;
    {
        std::lock_guard<std::mutex> lock(AndroidViewMutex);
        changed = AndroidInputView.x != view.x || AndroidInputView.y != view.y ||
            AndroidInputView.width != view.width || AndroidInputView.height != view.height || AndroidInputBattlefield != battlefield;
        AndroidInputView = view; AndroidInputBattlefield = battlefield;
    }
    if (changed) Android_Remap_Mouse(view, buffer.width, buffer.height, battlefield);
	int const dest_width = buffer.width;
	int const dest_height = buffer.height;
	int const scaled_width = std::min(dest_width, view.width * dest_height / view.height);
	int const scaled_height = std::min(dest_height, view.height * dest_width / view.width);
	int const offset_x = (dest_width - scaled_width) / 2;
	int const offset_y = (dest_height - scaled_height) / 2;

	static unsigned int present_probe = 0;
	if ((present_probe++ % 30U) == 0U) {
		DebugString("[FMV-PRESENT] src=%dx%d pitch=%d dst=%dx%d stride=%d format=%d scaled=%dx%d offset=%d,%d\n",
			width, height, pitch, dest_width, dest_height, buffer.stride, buffer.format,
			scaled_width, scaled_height, offset_x, offset_y);
	}

	if (buffer.format == WINDOW_FORMAT_RGB_565) {
		auto * destination = static_cast<std::uint16_t *>(buffer.bits);
		for (int y = 0; y < dest_height; ++y) {
			std::fill_n(destination + y * buffer.stride, dest_width, 0);
		}

		auto const * source = static_cast<std::uint8_t const *>(pixels) + view.y * pitch + view.x * 2;
		for (int y = 0; y < scaled_height; ++y) {
			auto const * source_row = reinterpret_cast<std::uint16_t const *>(source + (y * view.height / scaled_height) * pitch);
			auto * destination_row = destination + (y + offset_y) * buffer.stride + offset_x;
			for (int x = 0; x < scaled_width; ++x) {
				destination_row[x] = source_row[x * view.width / scaled_width];
			}
		}


        Android_Cursor_Draw(destination, buffer.stride, dest_width, dest_height,
            view.width, view.height, scaled_width, scaled_height, offset_x, offset_y, battlefield);
    }

    ANativeWindow_unlockAndPost(window);
        ANativeWindow_release(window);
}

#endif
