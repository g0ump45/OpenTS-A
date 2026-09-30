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
**	When a moving object moves, the Per_Cell_Process function is called
**	at various times during the move. Certain operations must be
**	performed at different stages of the move. This enum specifies the
**	different conditions under which the Per_Cell_Process function is
**	called.
*/
enum PCPType {
	PCP_ROTATION,   // When sitting in place and performing rotations.
	PCP_DURING,     // While moving between two cells.
	PCP_END,        // When the 'center' of a cell is reached during movement.
};
