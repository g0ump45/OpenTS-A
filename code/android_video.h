/*******************************************************************************
 *                                O P E N  T S
 ******************************************************************************/

#pragma once

#ifdef __ANDROID__

class Surface;
void Android_Video_Zoom_Battlefield(Surface * surface);

struct ANativeWindow;

void Android_Video_Get_Game_Size(int & width, int & height);
void Android_Video_Set_Zoom(double zoom);
double Android_Video_Get_Zoom(void);
void Android_Video_Map_Touch(int screen_x, int screen_y, int & x, int & y);
void Android_Video_Set_Window(ANativeWindow * window);
bool Android_Initialize_Engine_Surfaces(void);
void Android_Video_Present(void const * pixels, int width, int height, int pitch);

#endif
