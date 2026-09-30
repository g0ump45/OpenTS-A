#pragma once

#include "xmouse.h"

extern Mouse * MouseCursor;

#ifdef __ANDROID__
inline void Hide_Mouse(void) { if (MouseCursor) MouseCursor->Hide_Mouse(); }
inline void Show_Mouse(void) { if (MouseCursor) MouseCursor->Show_Mouse(); }
inline void Conditional_Hide_Mouse(Rect rect) { if (MouseCursor) MouseCursor->Conditional_Hide_Mouse(rect); }
inline void Conditional_Show_Mouse(void) { if (MouseCursor) MouseCursor->Conditional_Show_Mouse(); }
inline int Get_Mouse_State(void) { if (MouseCursor) return(MouseCursor->Get_Mouse_State()); return 0; }
inline void Set_Mouse_Cursor(Point2D const & hotspot, ShapeSet const * cursor, int shape) { if (MouseCursor) MouseCursor->Set_Cursor(hotspot, cursor, shape); }
inline int Get_Mouse_X(void) { if (MouseCursor) return(MouseCursor->Get_Mouse_X()); return 0; }
inline int Get_Mouse_Y(void) { if (MouseCursor) return(MouseCursor->Get_Mouse_Y()); return 0; }
inline Point2D Get_Mouse_Point(void) { if (MouseCursor) return(MouseCursor->Get_Mouse_Point()); return Point2D(0,0); }
#else
inline void Hide_Mouse(void) {MouseCursor->Hide_Mouse();}
inline void Show_Mouse(void) {MouseCursor->Show_Mouse();}
inline void Conditional_Hide_Mouse(Rect rect) {MouseCursor->Conditional_Hide_Mouse(rect);}
inline void Conditional_Show_Mouse(void) {MouseCursor->Conditional_Show_Mouse();}
inline int Get_Mouse_State(void) {return(MouseCursor->Get_Mouse_State());}
inline void Set_Mouse_Cursor(Point2D const & hotspot, ShapeSet const * cursor, int shape) {MouseCursor->Set_Cursor(hotspot, cursor, shape);}
inline int Get_Mouse_X(void) {return(MouseCursor->Get_Mouse_X());}
inline int Get_Mouse_Y(void) {return(MouseCursor->Get_Mouse_Y());}
inline Point2D Get_Mouse_Point(void) {return(MouseCursor->Get_Mouse_Point());}
#endif
