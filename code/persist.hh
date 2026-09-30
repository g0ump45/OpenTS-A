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

#pragma once

enum PersistentType {
	/*
	** trigger destroys itself immediately after going off, and removes
	** itself from all objects it's attached to
	*/
	VOLATILE = 0,

	/*
	** trigger is "Semi-Persistent"; it maintains a count of all objects
	** it's attached to, and only actually "springs" after its been
	** triggered from all the objects; then, it removes itself.
	*/
	SEMIPERSISTENT = 1,

	/*
	** trigger is Fully Persistent; it just won't go away.
	*/
	PERSISTENT = 2
};
