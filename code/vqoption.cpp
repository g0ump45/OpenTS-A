/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2025 Electronic Arts Inc.
 * Copyright 2026 OpenTS contributors
 *
 * Contains material derived from Electronic Arts source code.
 * Modified by OpenTS contributors, 2026.
 * EA's GPLv3 Section 7 additional terms and supplemental warranty
 * disclaimers apply; see LICENSE.md.
 ******************************************************************************/

#include "always.h"

#include "vqoption.h"

unsigned char VQOptions[OPTION_SLOTS];

void Initialize_Options(void)
{
	for (int flag = 0; flag < VQ_OPTION_COUNT; flag++) {
		Clear_Option(flag);
	}
	Set_Option(OPTION_6);
}


void Set_Option(int flag)
{
	int v = (1 << (unsigned char)flag % (unsigned)OPTION_SLOTS);
	int pos = flag >> OPTION_SHIFT;
	VQOptions[pos] |= v;
}


void Clear_Option(int flag)
{
	int v = (1 << (unsigned char)flag % (unsigned)OPTION_SLOTS);
	int pos = flag >> OPTION_SHIFT;
	VQOptions[pos] &= ~v;
}


bool Get_Option(int flag)
{
	int v = (1 << (unsigned char)flag % (unsigned)OPTION_SLOTS);
	int pos = flag >> OPTION_SHIFT;
	if (VQOptions[pos] & v) {
		return(true);
	}
	return(false);
}


int Toggle_Option(int flag)
{
	if (Get_Option(flag)) {
		Clear_Option(flag);
		return(false);
	}
	Set_Option(flag);
	return(true);
}
