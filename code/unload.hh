/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

/// Names derived from FA2/FS

enum UnloadType
{
	UNLOAD_KEEP_BOTH,
	UNLOAD_KEEP_TRANSPORTS,
	UNLOAD_KEEP_UNITS,
	UNLOAD_LOSE_BOTH,

	UNLOAD_COUNT,
};
