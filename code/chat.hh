/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/


#pragma once


// Who an in-game message is for. It travels in the message packet, so the values are fixed.
enum class ChatScopeType : unsigned char {
	Everyone,
	Allies,
	Player,
	Observers,
};
