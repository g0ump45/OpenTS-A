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

/*
**	Performance benchmark tracking identifiers.
*/
enum BenchType {
	BENCH_GAME_FRAME,       // Whole game frame (used for normalizing).
	BENCH_FINDPATH,         // Find path calls.
	BENCH_GREATEST_THREAT,  // Greatest threat calculation.
	BENCH_AI,               // Object AI calls.
	BENCH_CELL,             // Cell draw it function.
	BENCH_SIDEBAR,          // Sidebar (just cameo section) drawing.
	BENCH_RADAR,            // Radar map drawing.
	BENCH_TACTICAL,         // Whole tactical map.
	BENCH_PCP,              // Per cell process.
	BENCH_EVAL_OBJECT,      // Evaluate object as potential target.
	BENCH_EVAL_CELL,        // Evaluate entire cell for potential targets.
	BENCH_EVAL_WALL,        // Evaluate wall in cell as potential target.

	BENCH_POWER,            // Power bar drawing.
	BENCH_TABS,             // Tab section (top) drawing.
	BENCH_SHROUD,           // Shroud layer drawing.
	BENCH_ANIMS,            // Animations drawing.
	BENCH_OBJECTS,          // All game object drawing.
	BENCH_PALETTE,          // Color cycling palette adjustments.
	BENCH_GSCREEN_RENDER,   // Rendering of the whole map layered system (with blits).
	BENCH_BLIT_DISPLAY,     // DirectX or shadow blit of hidpage to seenpage.
	BENCH_MISSION,          // Mission list processing.

	BENCH_RULES,    // Processing of the rules.ini file.
	BENCH_SCENARIO, // Processing of the scenario.ini file.

	BENCH_COUNT,
	BENCH_FIRST=0
};
