/*******************************************************************************
 *                                O P E N  T S
 ******************************************************************************/

#include "always.h"

#ifdef __ANDROID__

#include "android_video.h"

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


void Android_Video_Map_Touch(int screen_x, int screen_y, int & x, int & y)
{
    x = screen_x;
    y = screen_y;

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

	int width = 640, height = 480;
	{
		std::lock_guard<std::mutex> lock(AndroidWindowMutex);
		if (AndroidWindow) {
			int const w = ANativeWindow_getWidth(AndroidWindow);
			int const h = ANativeWindow_getHeight(AndroidWindow);
			if (w > 0 && h > 0) width = std::max(640, int((480LL * w + h / 2) / h));
		}
	}
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


void Android_Video_Present(void const * pixels, int width, int height, int pitch)
{
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

	int const dest_width = buffer.width;
	int const dest_height = buffer.height;
	int const scaled_width = std::min(dest_width, width * dest_height / height);
	int const scaled_height = std::min(dest_height, height * dest_width / width);
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

		auto const * source = static_cast<std::uint8_t const *>(pixels);
		for (int y = 0; y < scaled_height; ++y) {
			auto const * source_row = reinterpret_cast<std::uint16_t const *>(source + (y * height / scaled_height) * pitch);
			auto * destination_row = destination + (y + offset_y) * buffer.stride + offset_x;
			for (int x = 0; x < scaled_width; ++x) {
				destination_row[x] = source_row[x * width / scaled_width];
			}
		}


	}

	ANativeWindow_unlockAndPost(window);
        ANativeWindow_release(window);
}

#endif
