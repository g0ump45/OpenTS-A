/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "alphalighting.h"

#include "vector.h"


DynamicVectorClass<AlphaLightingRemapClass *> AlphaLightingRemapClass::AlphaLightingRemaps;


/// <summary>
/// Constructs the alpha lighting remap manager.
/// </summary>
AlphaLightingRemapInitClass::AlphaLightingRemapInitClass(void)
{

}


/// <summary>
/// Destroys the alpha lighting remap manager.
/// The remap tables are shared and counted, so none of them are released here.
/// </summary>
AlphaLightingRemapInitClass::~AlphaLightingRemapInitClass(void)
{

}


/// <summary>
/// Fetches the alpha remap table for the specified band count.
/// This routine is used by the alpha blitters as they are created. The tables are large,
/// so any blitter asking for a band count that has already been built is handed the
/// existing table to share rather than a copy of its own.
/// </summary>
/// <param name="count">The number of shading bands the table must cover.</param>
/// <returns>Returns with a pointer to the remap table to draw through.</returns>
/// <remarks>Every table fetched must be handed back to Deinit or it will never be freed.</remarks>
AlphaLightingRemapClass *AlphaLightingRemapInitClass::Init(int count)
{
	for (int i = 0; i < AlphaLightingRemapClass::AlphaLightingRemaps.Count(); i++) {
		if (AlphaLightingRemapClass::AlphaLightingRemaps[i]->Count == count) {
			AlphaLightingRemapClass::AlphaLightingRemaps[i]->RefCount++;
			return(AlphaLightingRemapClass::AlphaLightingRemaps[i]);
		}
	}

	AlphaLightingRemapClass *ptr = new AlphaLightingRemapClass(count);
	AlphaLightingRemapClass::AlphaLightingRemaps.Add(ptr);
	ptr->RefCount++;
	return(ptr);
}


/// <summary>
/// Releases a remap table fetched from Init.
/// This routine is used by the alpha blitters as they are destroyed. Since the tables
/// are shared, one is only really thrown away when the last blitter using it lets go.
/// </summary>
void AlphaLightingRemapInitClass::Deinit(AlphaLightingRemapClass *ptr)
{
	if (ptr != NULL) {
		AlphaLightingRemapClass *remap = ptr;
		remap->RefCount--;
		if (remap->RefCount == 0) {
			AlphaLightingRemapClass::AlphaLightingRemaps.Delete(remap);
			delete remap;
		}
	}
}


/// <summary>
/// Builds an alpha lighting remap table.
/// This routine fills in the lookup that the alpha blitters draw through. A row is
/// fetched for the lighting level in force and indexed with the alpha buffer value, and
/// the result picks which shading band of the blitter's translation table the pixel is
/// drawn from.
/// </summary>
/// <param name="count">The number of shading bands the translation table provides.</param>
AlphaLightingRemapClass::AlphaLightingRemapClass(int count)
{
	Count = count;
	RefCount = 0;

	for (int i = 0; i <= BUFFER_SIZE - 1; i++) {
		int n2 = (int)((i & 0xFF) * (i >> 8) * (count - 1)) / 32258;
		if (n2 > count - 1) {
			n2 = count - 1;
		}
		Buffer[0][i] = (unsigned char)n2 << 8;
	}
}


/// <summary>
/// Destroys the alpha lighting remap table.
/// </summary>
AlphaLightingRemapClass::~AlphaLightingRemapClass(void)
{
}
