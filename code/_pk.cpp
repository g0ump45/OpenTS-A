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

#include "_pk.h"

#include "pk.h"

/***************************************************************************
**	Encryption keys.
*/
PKey FastKey;
#ifdef _DEBUG
PKey SlowKey;
#endif


//char const Keys[] =
//	"[PublicKey]\n"
//	"1=AgkCbXo9sKMHOBk=\n"
//#ifdef _DEBUG
//	"[PrivateKey]\n"
//	"1=AggxFU55vc7LYQ==\n"
//#endif
//	"\n";

char const Keys[] =
"[PublicKey]\n"
"1=AihRvNoIbTn85FZRYNZRcT+i6KpU+maCsEqr3Q5q+LDB5tH7Tz2qQ38V\n"
#ifdef _DEBUG
"[PrivateKey]\n"
"1=AigKVje8mROcR8QixnxUEF5b29Curkq01DNDWCdOG99XBqH79OaCiTCB\n"
#endif
"\n";
