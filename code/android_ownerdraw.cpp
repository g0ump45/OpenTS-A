/*******************************************************************************
 *                                O P E N  T S
 ******************************************************************************/

#include "srfcache.h"
#include "ownrdraw.h"

#ifdef __ANDROID__

SurfaceCacheClass SurfaceCache;

void OwnerDraw::Prepare_Resources(HWND)
{
    static bool initialized = false;
    if (initialized) {
        return;
    }

    SurfaceCache.CachePCX("bue_li30.pcx");
    SurfaceCache.CachePCX("bue_mi30.pcx");
    SurfaceCache.CachePCX("bue_ri30.pcx");
    SurfaceCache.CachePCX("bde_li30.pcx");
    SurfaceCache.CachePCX("bde_mi30.pcx");
    SurfaceCache.CachePCX("bde_ri30.pcx");

    SurfaceCache.CachePCX("bue_li24.pcx");
    SurfaceCache.CachePCX("bue_mi24.pcx");
    SurfaceCache.CachePCX("bue_ri24.pcx");
    SurfaceCache.CachePCX("bde_li24.pcx");
    SurfaceCache.CachePCX("bde_mi24.pcx");
    SurfaceCache.CachePCX("bde_ri24.pcx");

    initialized = true;
}

#endif
