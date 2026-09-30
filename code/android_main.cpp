#include "android_compat.h"
#ifdef __ANDROID__
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/window.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>
#include <cmath>
#include <thread>
#include <string_view>
#include "android_video.h"
#include "android_controls.h"
#include "keyboard.h"
#include "_xmouse.h"
#include "wwmouse.h"
#include "classfactory.h"
#include "_map.h"
#include "_rect.h"
#include "_tactica.h"
#include "tactical.h"
#include "display.h"
#include "movies.h"
#include "init.h"
#include "audio/audioengine.h"

#define LOG_TAG "OpenTS"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern void Main_Game(int argc, char * argv[]);
extern WWKeyboardClass* Keyboard;
extern bool GameInFocus;
static android_app * AndroidApp = nullptr;

static bool Android_Open_Activity(char const * activityName)
{
    if (!AndroidApp || !AndroidApp->activity) return false;
    ANativeActivity * activity = AndroidApp->activity;
    JNIEnv * env = nullptr;
    bool const attached = activity->vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK;
    if (attached && activity->vm->AttachCurrentThread(&env, nullptr) != JNI_OK) return false;
    jclass intentClass = env->FindClass("android/content/Intent");
    jobject intent = env->NewObject(intentClass, env->GetMethodID(intentClass, "<init>", "()V"));
    jstring packageName = env->NewStringUTF("com.opents.game");
    jstring className = env->NewStringUTF(activityName);
    jobject namedIntent = env->CallObjectMethod(intent, env->GetMethodID(intentClass, "setClassName",
        "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;"), packageName, className);
    jclass activityClass = env->GetObjectClass(activity->clazz);
    env->CallVoidMethod(activity->clazz, env->GetMethodID(activityClass, "startActivity", "(Landroid/content/Intent;)V"), intent);
    bool const success = !env->ExceptionCheck();
    if (!success) { env->ExceptionDescribe(); env->ExceptionClear(); }
    env->DeleteLocalRef(namedIntent); env->DeleteLocalRef(intent); env->DeleteLocalRef(intentClass);
    env->DeleteLocalRef(activityClass); env->DeleteLocalRef(packageName); env->DeleteLocalRef(className);
    if (attached) activity->vm->DetachCurrentThread();
    return success;
}

bool Android_Open_Url(char const * url)
{
    if (!url || std::string_view(url).substr(0, 8) != "https://" || !AndroidApp || !AndroidApp->activity) return false;
    ANativeActivity * activity = AndroidApp->activity;
    JNIEnv * env = nullptr;
    bool const attached = activity->vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK;
    if (attached && activity->vm->AttachCurrentThread(&env, nullptr) != JNI_OK) return false;
    bool success = false;
    if (env->PushLocalFrame(16) == JNI_OK) {
        success = [&]() {
            jclass uriClass = env->FindClass("android/net/Uri");
            if (!uriClass || env->ExceptionCheck()) return false;
            jmethodID parse = env->GetStaticMethodID(uriClass, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");
            if (!parse || env->ExceptionCheck()) return false;
            jstring address = env->NewStringUTF(url);
            if (!address || env->ExceptionCheck()) return false;
            jobject uri = env->CallStaticObjectMethod(uriClass, parse, address);
            if (!uri || env->ExceptionCheck()) return false;
            jclass intentClass = env->FindClass("android/content/Intent");
            if (!intentClass || env->ExceptionCheck()) return false;
            jmethodID constructor = env->GetMethodID(intentClass, "<init>", "(Ljava/lang/String;Landroid/net/Uri;)V");
            if (!constructor || env->ExceptionCheck()) return false;
            jstring action = env->NewStringUTF("android.intent.action.VIEW");
            if (!action || env->ExceptionCheck()) return false;
            jobject intent = env->NewObject(intentClass, constructor, action, uri);
            if (!intent || env->ExceptionCheck()) return false;
            jclass activityClass = env->GetObjectClass(activity->clazz);
            if (!activityClass || env->ExceptionCheck()) return false;
            jmethodID start = env->GetMethodID(activityClass, "startActivity", "(Landroid/content/Intent;)V");
            if (!start || env->ExceptionCheck()) return false;
            env->CallVoidMethod(activity->clazz, start, intent);
            return !env->ExceptionCheck();
        }();
        if (env->ExceptionCheck()) env->ExceptionClear();
        env->PopLocalFrame(nullptr);
    } else if (env->ExceptionCheck()) env->ExceptionClear();
    if (attached) activity->vm->DetachCurrentThread();
    return success;
}

bool Android_Open_Game_Importer() { return Android_Open_Activity("com.opents.game.GameFilesActivity"); }
bool Android_Open_Connection_Help() { return Android_Open_Activity("com.opents.game.ConnectionHelpActivity"); }
bool Android_Open_Host_Address() { return Android_Open_Activity("com.opents.game.HostAddressActivity"); }

static void Android_End_Selection(bool complete, int x, int y);

static void Handle_App_Command(struct android_app * app, int32_t cmd)
{
    switch (cmd) {
        case APP_CMD_PAUSE:
        case APP_CMD_STOP:
            Android_End_Selection(false, 0, 0);
            GameInFocus = false;
            LOGI("Android lifecycle: paused/stopped");
            break;

        case APP_CMD_RESUME:
        case APP_CMD_START:
            GameInFocus = true;
            LOGI("Android lifecycle: resumed/started");
            break;

        case APP_CMD_TERM_WINDOW:
            Android_End_Selection(false, 0, 0);
            GameInFocus = false;
            Android_Video_Set_Window(nullptr);
            LOGI("Android lifecycle: window terminated");
            break;

        case APP_CMD_INIT_WINDOW:
            if (app->window != nullptr) {
                Android_Video_Set_Window(app->window);
                GameInFocus = true;
                LOGI("Android lifecycle: window initialized");
            }
            break;

        default:
            break;
    }
}
static int64_t AndroidLastTapTime = 0;
static int AndroidLastTapX = -1000;
static int AndroidLastTapY = -1000;
static bool AndroidRightTap = false;
static bool AndroidTouchDragging = false;
static bool AndroidSelectionDragging = false;
static int AndroidTouchStartX = 0;
static int AndroidTouchStartY = 0;
static int AndroidTouchLastX = 0;
static int AndroidTouchLastY = 0;
static int64_t AndroidTouchDownTime = 0;
static constexpr int AndroidTouchDragThreshold = 12;
static constexpr int64_t AndroidLongPressMilliseconds = 500;
static bool AndroidPinching = false;
static float AndroidPinchLastDistance = 0.0f;
static bool AndroidMovieTouchActive = false;
static bool AndroidTwoFingerTap = false;
static constexpr int64_t AndroidTwoFingerTapMilliseconds = 250;
static int AndroidTapPointerIds[2] = {-1, -1};
static float AndroidTapPointerX[2] = {};
static float AndroidTapPointerY[2] = {};

static void Android_End_Selection(bool complete, int x, int y)
{
    if (!AndroidSelectionDragging) return;
    AndroidSelectionDragging = false;
    Keyboard->AndroidLeftMouseDown = false;
    if (complete) {
        Map.Message_Handler(MainWindow, WM_LBUTTONUP, 0, MAKELPARAM(x, y));
    }
    if (TacticalMap != nullptr) Map.Abort_Drag_Select();
    Keyboard->Put_Mouse_Message(VK_LBUTTON, x, y, true);
    AndroidRightTap = false;
    AndroidLastTapTime = 0;
    AndroidLastTapX = -1000;
    AndroidLastTapY = -1000;
}

static int32_t Handle_Input(struct android_app * app, AInputEvent * event)
{
    __android_log_print(ANDROID_LOG_INFO, "OpenTS-InputEntry", "called type=%d keyboard=%p window=%p", AInputEvent_getType(event), Keyboard, app->window);
    if (Keyboard == nullptr || AInputEvent_getType(event) != AINPUT_EVENT_TYPE_MOTION || app->window == nullptr) {
        return 0;
    }

    int const action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
    if (action == AMOTION_EVENT_ACTION_CANCEL || action == AMOTION_EVENT_ACTION_DOWN) {
        Android_End_Selection(false, AndroidTouchLastX, AndroidTouchLastY);
    }


    if (Movie_Is_Playing()) {
        if (action == AMOTION_EVENT_ACTION_DOWN) {
            AndroidMovieTouchActive = true;
            Keyboard->AndroidLeftMouseDown = true;
        } else if (action == AMOTION_EVENT_ACTION_UP ||
                   action == AMOTION_EVENT_ACTION_CANCEL) {
            Keyboard->AndroidLeftMouseDown = false;
            AndroidMovieTouchActive = false;
        }
        return 1;
    }

    // A movie can finish immediately on ACTION_DOWN. Swallow the rest of
    // that same physical touch so it cannot leak into the next menu/game.
    if (AndroidMovieTouchActive) {
        if (action == AMOTION_EVENT_ACTION_UP ||
            action == AMOTION_EVENT_ACTION_CANCEL) {
            Keyboard->AndroidLeftMouseDown = false;
            AndroidMovieTouchActive = false;
        }
        return 1;
    }

    int const pointer_count = AMotionEvent_getPointerCount(event);
    __android_log_print(ANDROID_LOG_INFO, "OpenTS-Touch", "action=%d raw=(%.1f,%.1f)", action, AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));
    if (action != AMOTION_EVENT_ACTION_DOWN && action != AMOTION_EVENT_ACTION_MOVE && action != AMOTION_EVENT_ACTION_POINTER_DOWN && action != AMOTION_EVENT_ACTION_POINTER_UP && action != AMOTION_EVENT_ACTION_UP && action != AMOTION_EVENT_ACTION_CANCEL) {
        return 0;
    }

    int const window_width = ANativeWindow_getWidth(app->window);
    int const window_height = ANativeWindow_getHeight(app->window);
    if (window_width <= 0 || window_height <= 0) {
        return 0;
    }

    int game_width, game_height;
    Android_Video_Get_Game_Size(game_width, game_height);
    int const scaled_width = std::min(window_width, game_width * window_height / game_height);
    int const scaled_height = std::min(window_height, game_height * window_width / game_width);
    int const offset_x = (window_width - scaled_width) / 2;
    int const offset_y = (window_height - scaled_height) / 2;
    float const raw_x = AMotionEvent_getX(event, 0);
    float const raw_y = AMotionEvent_getY(event, 0);
    if (raw_x < offset_x || raw_x >= offset_x + scaled_width || raw_y < offset_y || raw_y >= offset_y + scaled_height) {
        AndroidTwoFingerTap = false;
        if (action == AMOTION_EVENT_ACTION_UP || action == AMOTION_EVENT_ACTION_CANCEL) {
            Android_End_Selection(action == AMOTION_EVENT_ACTION_UP, AndroidTouchLastX, AndroidTouchLastY);
            Keyboard->AndroidLeftMouseDown = false;
            AndroidPinching = false;
            AndroidPinchLastDistance = 0.0f;
        }
        return 0;
    }

    int x = std::clamp(static_cast<int>((raw_x - offset_x) * game_width / scaled_width), 0, game_width - 1);
    int y = std::clamp(static_cast<int>((raw_y - offset_y) * game_height / scaled_height), 0, game_height - 1);
    int const screen_x = x;
    int const screen_y = y;
    Android_Video_Map_Touch(screen_x, screen_y, x, y);

   __android_log_print(ANDROID_LOG_INFO, "OpenTS-TouchMap", "window=%dx%d scaled=%dx%d offset=(%d,%d) game=(%d,%d)", window_width, window_height, scaled_width, scaled_height, offset_x, offset_y, x, y);
    Keyboard->Set_Mouse_Position(x, y);
    Keyboard->AndroidTouchX = x;
    Keyboard->AndroidTouchY = y;

    if (AndroidControls.ControlScheme.load() == ANDROID_CONTROL_ORIGINAL) {
        if (action == AMOTION_EVENT_ACTION_POINTER_DOWN ||
            action == AMOTION_EVENT_ACTION_POINTER_UP) {
            return 1;
        }

        if (action == AMOTION_EVENT_ACTION_DOWN) {
            int64_t const now = AMotionEvent_getEventTime(event);
            int const dx = x - AndroidLastTapX;
            int const dy = y - AndroidLastTapY;
            bool const close_enough = (dx * dx + dy * dy) <= (24 * 24);
            bool const quick_enough = AndroidLastTapTime > 0 &&
                (now - AndroidLastTapTime) <=
                    int64_t(AndroidControls.DoubleTapMilliseconds.load()) * 1000000LL;

            AndroidRightTap = !AndroidMenuActive.load() &&
                AndroidControls.DoubleTapRightClick.load() &&
                quick_enough && close_enough;

            if (AndroidRightTap) {
                Keyboard->AndroidLeftMouseDown = false;
                Map.Message_Handler(MainWindow, WM_RBUTTONDOWN, 0, MAKELPARAM(x, y));
                Keyboard->Put_Mouse_Message(VK_RBUTTON, x, y, false);

                AndroidLastTapTime = 0;
                AndroidLastTapX = -1000;
                AndroidLastTapY = -1000;
            } else {
                Keyboard->AndroidLeftMouseDown = true;
                Map.Message_Handler(MainWindow, WM_LBUTTONDOWN, 0, MAKELPARAM(x, y));
                Keyboard->Put_Mouse_Message(VK_LBUTTON, x, y, false);
            }
        }

        if (action == AMOTION_EVENT_ACTION_MOVE) {
            Map.Message_Handler(MainWindow, WM_MOUSEMOVE, 0, MAKELPARAM(x, y));
        }

        if (action == AMOTION_EVENT_ACTION_UP || action == AMOTION_EVENT_ACTION_CANCEL) {
            Keyboard->AndroidLeftMouseDown = false;

            if (AndroidRightTap) {
                if (action == AMOTION_EVENT_ACTION_UP) {
                    Map.Message_Handler(MainWindow, WM_RBUTTONUP, 0, MAKELPARAM(x, y));
                    Keyboard->Put_Mouse_Message(VK_RBUTTON, x, y, true);
                }
                AndroidRightTap = false;
            } else if (action == AMOTION_EVENT_ACTION_UP) {
                Map.Message_Handler(MainWindow, WM_LBUTTONUP, 0, MAKELPARAM(x, y));
                Keyboard->Put_Mouse_Message(VK_LBUTTON, x, y, true);

                AndroidLastTapTime = AMotionEvent_getEventTime(event);
                AndroidLastTapX = x;
                AndroidLastTapY = y;
            }
        }

        return 1;
    }
    if (AndroidTwoFingerTap) {
        for (int i = 0; i < pointer_count; ++i) {
            int const id = AMotionEvent_getPointerId(event, i);
            int const slot = id == AndroidTapPointerIds[0] ? 0 :
                id == AndroidTapPointerIds[1] ? 1 : -1;
            if (slot < 0) {
                AndroidTwoFingerTap = false;
                break;
            }
            float const dx = (AMotionEvent_getX(event, i) - AndroidTapPointerX[slot]) * game_width / scaled_width;
            float const dy = (AMotionEvent_getY(event, i) - AndroidTapPointerY[slot]) * game_height / scaled_height;
            if (dx * dx + dy * dy > AndroidTouchDragThreshold * AndroidTouchDragThreshold) {
                AndroidTwoFingerTap = false;
            }
        }
        if (AMotionEvent_getEventTime(event) - AndroidTouchDownTime >
            AndroidTwoFingerTapMilliseconds * 1000000LL) {
            AndroidTwoFingerTap = false;
        }
    }
    if (action == AMOTION_EVENT_ACTION_POINTER_DOWN && pointer_count >= 2) {
        AndroidTwoFingerTap = !AndroidPinching && pointer_count == 2 &&
            !AndroidMenuActive.load() && !AndroidTouchDragging && !AndroidSelectionDragging &&
            AMotionEvent_getEventTime(event) - AndroidTouchDownTime <=
                AndroidTwoFingerTapMilliseconds * 1000000LL;
        float const first_dx = (raw_x - AndroidTapPointerX[0]) * game_width / scaled_width;
        float const first_dy = (raw_y - AndroidTapPointerY[0]) * game_height / scaled_height;
        AndroidTwoFingerTap = AndroidTwoFingerTap &&
            first_dx * first_dx + first_dy * first_dy <= AndroidTouchDragThreshold * AndroidTouchDragThreshold;
        AndroidTapPointerIds[1] = AMotionEvent_getPointerId(event, 1);
        AndroidTapPointerX[1] = AMotionEvent_getX(event, 1);
        AndroidTapPointerY[1] = AMotionEvent_getY(event, 1);
        float const pinch_dx = AMotionEvent_getX(event, 1) - AMotionEvent_getX(event, 0);
        float const pinch_dy = AMotionEvent_getY(event, 1) - AMotionEvent_getY(event, 0);
        AndroidPinchLastDistance = std::sqrt(pinch_dx * pinch_dx + pinch_dy * pinch_dy);
        Android_End_Selection(false, AndroidTouchLastX, AndroidTouchLastY);
        AndroidPinching = true;
        AndroidTouchDragging = false;
        AndroidSelectionDragging = false;
        AndroidRightTap = false;
        AndroidLastTapTime = 0;
        AndroidLastTapX = -1000;
        AndroidLastTapY = -1000;
        Keyboard->AndroidLeftMouseDown = false;
        return 1;
    }
    if (action == AMOTION_EVENT_ACTION_DOWN) {
        AndroidTouchDragging = false;
        AndroidSelectionDragging = false;
        AndroidPinching = false;
        AndroidTwoFingerTap = false;
        AndroidTapPointerIds[0] = AMotionEvent_getPointerId(event, 0);
        AndroidTapPointerX[0] = raw_x;
        AndroidTapPointerY[0] = raw_y;
        AndroidTouchStartX = x;
        AndroidTouchStartY = y;
        AndroidTouchLastX = x;
        AndroidTouchLastY = y;
        AndroidTouchDownTime = AMotionEvent_getEventTime(event);
        Keyboard->AndroidLeftMouseDown = false;

        int64_t const now = AndroidTouchDownTime;
        int const dx = x - AndroidLastTapX;
        int const dy = y - AndroidLastTapY;
        bool const close_enough = (dx * dx + dy * dy) <= (24 * 24);
        bool const quick_enough = AndroidLastTapTime > 0 &&
            (now - AndroidLastTapTime) <= int64_t(AndroidControls.DoubleTapMilliseconds.load()) * 1000000LL;

        AndroidRightTap = !AndroidMenuActive.load() &&
            AndroidControls.DoubleTapRightClick.load() &&
            quick_enough && close_enough;
    }

    if (action == AMOTION_EVENT_ACTION_MOVE && AndroidPinching && pointer_count >= 2) {
        float const pinch_dx = AMotionEvent_getX(event, 1) - AMotionEvent_getX(event, 0);
        float const pinch_dy = AMotionEvent_getY(event, 1) - AMotionEvent_getY(event, 0);
        float const pinch_distance = std::sqrt(pinch_dx * pinch_dx + pinch_dy * pinch_dy);

        if (AndroidTwoFingerTap) return 1;
        if (AndroidPinchLastDistance > 0.0f && pinch_distance > 0.0f) {
            double const scale = static_cast<double>(pinch_distance / AndroidPinchLastDistance);
            Android_Video_Set_Zoom(Android_Video_Get_Zoom() * scale);
        }

        AndroidPinchLastDistance = pinch_distance;
        return 1;
    }

    if (action == AMOTION_EVENT_ACTION_MOVE && AndroidPinching) {
        return 1;
    }

    if (action == AMOTION_EVENT_ACTION_MOVE) {
        int const total_dx = x - AndroidTouchStartX;
        int const total_dy = y - AndroidTouchStartY;

        if (!AndroidTouchDragging && !AndroidSelectionDragging &&
            (total_dx * total_dx + total_dy * total_dy) >
                (AndroidTouchDragThreshold * AndroidTouchDragThreshold)) {
            if (AndroidRightTap) {
                AndroidTouchDragging = true;
                AndroidRightTap = false;
                AndroidLastTapTime = 0;
                AndroidLastTapX = -1000;
                AndroidLastTapY = -1000;
            } else {
                AndroidSelectionDragging = true;
                Keyboard->AndroidLeftMouseDown = true;
                Map.Message_Handler(MainWindow, WM_LBUTTONDOWN, 0, MAKELPARAM(AndroidTouchStartX, AndroidTouchStartY));
                Keyboard->Put_Mouse_Message(VK_LBUTTON, AndroidTouchStartX, AndroidTouchStartY, false);
            }
        }

        if (AndroidTouchDragging) {
            int const move_dx = x - AndroidTouchLastX;
            int const move_dy = y - AndroidTouchLastY;
            int const pan_speed = AndroidControls.PanSpeed.load();

            int distx = std::abs(move_dx) * pan_speed / 8;
            int disty = std::abs(move_dy) * pan_speed / 8;

            if (move_dx > 0 && distx > 0) {
                Map.Scroll_Map(FACING_W, distx, true);
            } else if (move_dx < 0 && distx > 0) {
                Map.Scroll_Map(FACING_E, distx, true);
            }

            if (move_dy > 0 && disty > 0) {
                Map.Scroll_Map(FACING_N, disty, true);
            } else if (move_dy < 0 && disty > 0) {
                Map.Scroll_Map(FACING_S, disty, true);
            }
        } else {
            Map.Message_Handler(MainWindow, WM_MOUSEMOVE, 0, MAKELPARAM(x, y));
        }

        AndroidTouchLastX = x;
        AndroidTouchLastY = y;
    }

    if (AndroidPinching &&
        (action == AMOTION_EVENT_ACTION_POINTER_UP ||
         action == AMOTION_EVENT_ACTION_UP ||
         action == AMOTION_EVENT_ACTION_CANCEL)) {
        Keyboard->AndroidLeftMouseDown = false;
        AndroidTouchDragging = false;
        AndroidRightTap = false;

        if (action == AMOTION_EVENT_ACTION_UP || action == AMOTION_EVENT_ACTION_CANCEL) {
            if (action == AMOTION_EVENT_ACTION_UP && AndroidTwoFingerTap && !AndroidMenuActive.load()) {
                int const click_x = AndroidTouchStartX;
                int const click_y = AndroidTouchStartY;
                Keyboard->Set_Mouse_Position(click_x, click_y);
                Keyboard->AndroidTouchX = click_x;
                Keyboard->AndroidTouchY = click_y;
                Map.Message_Handler(MainWindow, WM_RBUTTONDOWN, 0, MAKELPARAM(click_x, click_y));
                Keyboard->Put_Mouse_Message(VK_RBUTTON, click_x, click_y, false);
                Map.Message_Handler(MainWindow, WM_RBUTTONUP, 0, MAKELPARAM(click_x, click_y));
                Keyboard->Put_Mouse_Message(VK_RBUTTON, click_x, click_y, true);
            }
            AndroidTwoFingerTap = false;
            AndroidPinching = false;
            AndroidPinchLastDistance = 0.0f;
        }
        return 1;
    }

    if (AndroidPinching) {
        return 1;
    }
    if (action == AMOTION_EVENT_ACTION_UP || action == AMOTION_EVENT_ACTION_CANCEL) {
        Keyboard->AndroidLeftMouseDown = false;

        if (action == AMOTION_EVENT_ACTION_UP && AndroidSelectionDragging) {
            Android_End_Selection(true, x, y);
            return 1;
        }

        if (action == AMOTION_EVENT_ACTION_UP && !AndroidTouchDragging) {
            bool const sidebar_long_press = !AndroidMenuActive.load() &&
                Map.IsSidebarActive && !AndroidSelectionDragging &&
                AMotionEvent_getEventTime(event) - AndroidTouchDownTime >=
                    AndroidLongPressMilliseconds * 1000000LL &&
                AndroidTouchStartX >= SidebarRect.X &&
                AndroidTouchStartX < SidebarRect.X + SidebarRect.Width &&
                AndroidTouchStartY >= SidebarRect.Y &&
                AndroidTouchStartY < SidebarRect.Y + SidebarRect.Height &&
                x >= SidebarRect.X && x < SidebarRect.X + SidebarRect.Width &&
                y >= SidebarRect.Y && y < SidebarRect.Y + SidebarRect.Height;

            if (sidebar_long_press) {
                int const click_x = AndroidTouchStartX;
                int const click_y = AndroidTouchStartY;
                Keyboard->Set_Mouse_Position(click_x, click_y);
                Keyboard->AndroidTouchX = click_x;
                Keyboard->AndroidTouchY = click_y;
                Map.Message_Handler(MainWindow, WM_RBUTTONDOWN, 0, MAKELPARAM(click_x, click_y));
                Keyboard->Put_Mouse_Message(VK_RBUTTON, click_x, click_y, false);
                Map.Message_Handler(MainWindow, WM_RBUTTONUP, 0, MAKELPARAM(click_x, click_y));
                Keyboard->Put_Mouse_Message(VK_RBUTTON, click_x, click_y, true);
                AndroidLastTapTime = 0;
                AndroidLastTapX = -1000;
                AndroidLastTapY = -1000;
            } else if (AndroidRightTap) {
                Execute_Command("SelectType");

                AndroidLastTapTime = 0;
                AndroidLastTapX = -1000;
                AndroidLastTapY = -1000;
            } else {
                int64_t const held_milliseconds =
                    (AMotionEvent_getEventTime(event) - AndroidTouchDownTime) / 1000000LL;
                bool const long_press =
                    !AndroidMenuActive.load() &&
                    held_milliseconds >= AndroidLongPressMilliseconds &&
                    screen_x >= TacticalRect.X &&
                    screen_x < TacticalRect.X + TacticalRect.Width &&
                    screen_y >= TacticalRect.Y &&
                    screen_y < TacticalRect.Y + TacticalRect.Height;

                if (long_press) {
                    Cell const cell = TacticalMap->Pixel_To_Cell(Point2D(x, y));
                    Map.Active_Click(NULL, cell, ACTION_PATROL_WAYPOINT);

                    AndroidLastTapTime = 0;
                    AndroidLastTapX = -1000;
                    AndroidLastTapY = -1000;
                } else {
                    Map.Message_Handler(MainWindow, WM_LBUTTONDOWN, 0, MAKELPARAM(x, y));
                    Keyboard->Put_Mouse_Message(VK_LBUTTON, x, y, false);
                    Map.Message_Handler(MainWindow, WM_LBUTTONUP, 0, MAKELPARAM(x, y));
                    Keyboard->Put_Mouse_Message(VK_LBUTTON, x, y, true);

                    AndroidLastTapTime = AMotionEvent_getEventTime(event);
                    AndroidLastTapX = x;
                    AndroidLastTapY = y;
                }
            }
        }

        AndroidRightTap = false;
        AndroidTouchDragging = false;
    }

    return 1;
}

void android_main(struct android_app* app) {
    AndroidApp = app;
    LOGI("OpenTS android_main started");
    app_dummy();
    ANativeActivity_setWindowFlags(app->activity, AWINDOW_FLAG_FULLSCREEN, 0);
	app->onInputEvent = Handle_Input;
    app->onAppCmd = Handle_App_Command;

    while (app->window == nullptr && !app->destroyRequested) {
        int events;
        android_poll_source * source;
        if (ALooper_pollOnce(-1, nullptr, &events, reinterpret_cast<void **>(&source)) >= 0 && source != nullptr) {
            source->process(app, source);
        }
    }
    if (app->destroyRequested) {
        return;
    }
    Android_Video_Set_Window(app->window);
    if (!Android_Initialize_Engine_Surfaces()) {
        LOGE("Unable to initialize engine drawing surfaces");
        return;
    }

#if defined(OPENTS_ANDROID_ASAN)
    // NativeActivity is created outside ASan instrumentation. Avoid dereferencing
    // its framework-owned fields while collecting an engine memory report.
    const char* dataPath = "/sdcard/Android/data/com.opents.game/files";
#else
    const char* dataPath = app->activity->externalDataPath;
#endif
    LOGI("externalDataPath = %s", dataPath);
    if (dataPath) {
        chdir(dataPath);
    } else {
        chdir("/sdcard/Android/data/com.opents.game/files");
    }

    char cwd[512];
    getcwd(cwd, sizeof(cwd));
    LOGI("Current dir now: %s", cwd);

    if (!Keyboard) {
        Keyboard = new WWKeyboardClass();
        LOGI("Creating Keyboard stub");
    }
    if (!MouseCursor) {
        MouseCursor = new WWMouseClass(MainWindow);
        MouseCursor->Capture_Mouse();
        LOGI("Creating MouseCursor stub");
    }
    GameInFocus = true;

#if !defined(OPENTS_ANDROID_ASAN)
    // --- NEW FILE LISTING THAT SHOWS IN LOGCAT ---
    DIR* d = opendir(".");
    if (d) {
        LOGI("--- Listing files in %s ---", cwd);
        struct dirent* ent;
        int count = 0;
        while ((ent = readdir(d))!= NULL && count < 60) {
            struct stat st;
            if (stat(ent->d_name, &st) == 0) {
                LOGI("FILE: %s (%lld bytes)", ent->d_name, (long long)st.st_size);
            } else {
                LOGI("FILE: %s", ent->d_name);
            }
            count++;
        }
        closedir(d);
        LOGI("--- End listing: %d files ---", count);
    } else {
        LOGE("opendir failed!");
    }
#endif

    FILE* f = fopen("SUN.INI", "r");
    LOGI(f? "FOUND SUN.INI" : "SUN.INI NOT FOUND");
    if (f) fclose(f);

    FILE* f2 = fopen("TIBSUN.MIX", "r");
    LOGI(f2? "FOUND TIBSUN.MIX" : "TIBSUN.MIX NOT FOUND");
    if (f2) fclose(f2);

    FILE* f3 = fopen("LANGUAGE.MIX", "r");
    LOGI(f3? "FOUND LANGUAGE.MIX" : "LANGUAGE.MIX NOT FOUND");
    if (f3) fclose(f3);

    char* argv[] = {(char*)"OpenTS"};
    LOGI("Initializing audio...");
    bool audio_ok = AudioEngine.Init();
    LOGI("Audio init result: %s", audio_ok ? "success" : "failed");
    LOGI("Calling Main_Game...");
    RegisterClasses();
    LOGI("Engine classes registered");
    std::thread([=]() mutable {
        Main_Game(1, argv);
        LOGI("Main_Game returned");
        ANativeActivity_finish(app->activity);
    }).detach();

    while (!app->destroyRequested) {
        int events;
        android_poll_source * source;
        if (ALooper_pollOnce(-1, nullptr, &events, reinterpret_cast<void **>(&source)) >= 0 && source != nullptr) {
            source->process(app, source);
        }
    }
}
#endif
