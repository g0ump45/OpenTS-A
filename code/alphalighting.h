/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

template<class T> class DynamicVectorClass;

class AlphaLightingRemapClass;

class AlphaLightingRemapInitClass
{
public:
	AlphaLightingRemapInitClass(void);
	~AlphaLightingRemapInitClass(void);
	AlphaLightingRemapClass *Init(int count);
	void Deinit(AlphaLightingRemapClass *ptr);
};

class AlphaLightingRemapClass
{
public:
	AlphaLightingRemapClass(int count);
	~AlphaLightingRemapClass(void);

	unsigned short *Get_Table(int level)
	{
		int shade = level > 0 ? level : 0;
		shade = (261 * shade) >> 11;
		if (shade > 254) {
			shade = 254;
		}
		return(Buffer[shade]);
	}

	enum {
		BUFFER_SIZE = 256 * 256,
	};

	/*
	 * This is the remap lookup that the alpha blitters draw through. A row is picked by the
	 * lighting level in force and indexed by the alpha buffer value; the result is the shading
	 * band, already shifted into place to be combined with the pixel's color index.
	 */
	unsigned short Buffer[256][256];

	/*
	 * This is the number of shading bands the table was built for, and it doubles as the key
	 * the table is shared by -- a blitter asking for a band count already built is handed this
	 * table rather than a copy of its own.
	 */
	int Count;

	/*
	 * This is the number of blitters currently drawing through this table. The table is large,
	 * so it is only thrown away once the last of them has let go.
	 */
	int RefCount;

	/*
	 * This is the list of every remap table built so far. It is searched whenever a blitter
	 * asks for one, so that tables covering the same band count are shared rather than copied.
	 */
	static DynamicVectorClass<AlphaLightingRemapClass *> AlphaLightingRemaps;
};
