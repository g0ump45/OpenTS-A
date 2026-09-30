/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

enum SyncRandomKind {
	SYNC_RANDOM_CRITICAL,
	SYNC_RANDOM_NONCRITICAL,
};

// A ranged draw is one call to the generator; each plain draw it makes internally is inner.
enum SyncRandomShape {
	SYNC_DRAW_PLAIN,
	SYNC_DRAW_RANGED,
	SYNC_DRAW_INNER,
};

enum SyncFacingKind {
	SYNC_FACING_SET,
};

enum SyncMissionKind {
	SYNC_MISSION_ASSIGN,
	SYNC_MISSION_OVERRIDE,
};

enum SyncEventSource {
	SYNC_EVENT_EXECUTED,
	SYNC_EVENT_QUEUED,
};
