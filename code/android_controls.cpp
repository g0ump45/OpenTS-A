#include "always.h"

#ifdef __ANDROID__
#include "android_controls.h"
#include "gamedirs.h"
#include <algorithm>
#include <cstdio>

AndroidControlSettings AndroidControls;
std::atomic<bool> AndroidMenuActive{false};

void Android_Reset_Control_Settings()
{
        AndroidControls.ControlScheme = ANDROID_CONTROL_MODERN;
	AndroidControls.DoubleTapRightClick = true;
	AndroidControls.SelectionBox = true;
	AndroidControls.EdgeScrolling = true;
	AndroidControls.PanSpeed = 8;
	AndroidControls.DoubleTapMilliseconds = 300;
}

void Android_Load_Control_Settings()
{
        Android_Reset_Control_Settings();
        FILE * file = std::fopen(User_File_Write_Name("ANDROID-CONTROLS.cfg").c_str(), "r");
        if (!file) return;

        int version = 0;
        if (std::fscanf(file, "%d", &version) != 1) {
                std::fclose(file);
                return;
        }

        int scheme = ANDROID_CONTROL_MODERN;
        int right, box, edge, speed, delay;
        int count = 0;

        if (version == 1) {
                count = std::fscanf(file, "%d %d %d %d %d", &right, &box, &edge, &speed, &delay);
        } else if (version == 2) {
                count = std::fscanf(file, "%d %d %d %d %d %d", &scheme, &right, &box, &edge, &speed, &delay);
        }

        std::fclose(file);

        if ((version == 1 && count != 5) || (version == 2 && count != 6)) return;
        if (version != 1 && version != 2) return;

        AndroidControls.ControlScheme = ANDROID_CONTROL_MODERN;
        AndroidControls.DoubleTapRightClick = right != 0;
        AndroidControls.SelectionBox = box != 0;
        AndroidControls.EdgeScrolling = edge != 0;
        AndroidControls.PanSpeed = std::clamp(speed, 1, 16);
        AndroidControls.DoubleTapMilliseconds = std::clamp(delay, 150, 500);
}

bool Android_Save_Control_Settings()
{
        std::string const path = User_File_Write_Name("ANDROID-CONTROLS.cfg");
        std::string const temporary = path + ".tmp";
        FILE * file = std::fopen(temporary.c_str(), "w");
        if (!file) return false;
        bool const written = std::fprintf(file, "2 %d %d %d %d %d %d\n",
                AndroidControls.ControlScheme.load(),
                int(AndroidControls.DoubleTapRightClick.load()),
                int(AndroidControls.SelectionBox.load()),
                int(AndroidControls.EdgeScrolling.load()),
                AndroidControls.PanSpeed.load(),
                AndroidControls.DoubleTapMilliseconds.load()) > 0;
        bool const closed = std::fclose(file) == 0;
        if (!written || !closed) return false;
        return std::rename(temporary.c_str(), path.c_str()) == 0;
}
#endif
