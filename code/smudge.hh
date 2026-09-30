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

/**********************************************************************
**	Smudges are enumerated here. Smudges are transparent icons that are
**	drawn over the underlying terrain in order to give the effect of
**	alterations to the terrain. Craters are a good example of this.
*/
enum SmudgeType {
	SMUDGE_NONE=-1,

	SMUDGE_CR1,
	SMUDGE_CR2,
	SMUDGE_CR3,
	SMUDGE_CR4,
	SMUDGE_CR5,
	SMUDGE_CR6,
	SMUDGE_BURN01,
	SMUDGE_BURN02,
	SMUDGE_BURN03,
	SMUDGE_BURN04,
	SMUDGE_BURN05,
	SMUDGE_BURN06,
	SMUDGE_BURN07,
	SMUDGE_BURN08,
	SMUDGE_BURN09,
	SMUDGE_BURN10,
	SMUDGE_BURN11,
	SMUDGE_BURN12,
	SMUDGE_BURN13,
	SMUDGE_BURN14,
	SMUDGE_BURN15,
	SMUDGE_BURN16,
	SMUDGE_BURNT01,
	SMUDGE_BURNT02,
	SMUDGE_BURNT03,
	SMUDGE_BURNT04,
	SMUDGE_BURNT05,
	SMUDGE_BURNT06,
	SMUDGE_BURNT07,
	SMUDGE_BURNT08,
	SMUDGE_BURNT09,
	SMUDGE_BURNT10,
	SMUDGE_BURNT11,
	SMUDGE_BURNT12,
	SMUDGE_CRATER01,
	SMUDGE_CRATER02,
	SMUDGE_CRATER03,
	SMUDGE_CRATER04,
	SMUDGE_CRATER05,
	SMUDGE_CRATER06,
	SMUDGE_CRATER07,
	SMUDGE_CRATER08,
	SMUDGE_CRATER09,
	SMUDGE_CRATER10,
	SMUDGE_CRATER11,
	SMUDGE_CRATER12,

	SMUDGE_COUNT,
	SMUDGE_FIRST=0
};
