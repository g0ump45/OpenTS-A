#pragma once

#ifdef __ANDROID__
class Surface;
void Android_Show_Import_Button(bool visible);
void Android_Draw_Import_Button(Surface * surface);
bool Android_Import_Button_Hit(int x, int y);
bool Android_Open_Url(char const * url);
bool Android_Open_Game_Importer();
bool Android_Open_Host_Address();
bool Android_Open_Connection_Help();
int Android_Game_Options_Menu(void);
int Android_Main_Menu(void);
bool Android_Has_Saved_Games(void);
#endif
