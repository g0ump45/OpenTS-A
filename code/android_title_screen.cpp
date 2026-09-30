#ifdef __ANDROID__
#include "always.h"
#include "winstub.h"
#include "ccfile.h"
#include "convert.h"
#include "draw.h"
#include "pcx.h"
#include "surface.h"
#include "dbgprint.h"

void Load_Title_Screen(char const * name, Surface * surface, PaletteClass * palette)
{
	CCFileClass file(name);
	Surface * image = Read_PCX_File(file, palette);
	if (!image) {
		DebugString("Android title screen: could not load %s\n", name);
		return;
	}
	int const x = (surface->Get_Width() - image->Get_Width()) / 2;
	int const y = (surface->Get_Height() - image->Get_Height()) / 2;
	if (palette && image->Bytes_Per_Pixel() == 1) {
		ConvertClass drawer(*palette, *palette, *surface);
		Blit_Block(*surface, drawer, *image, image->Get_Rect(), Point2D(x, y), surface->Get_Rect());
	} else {
		surface->Blit_From(surface->Get_Rect(), Rect(x, y, image->Get_Width(), image->Get_Height()),
			*image, image->Get_Rect(), image->Get_Rect());
	}
	delete image;
}
#endif
