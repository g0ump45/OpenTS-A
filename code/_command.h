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
template<class INDEX, class T> class IndexClass;

class CommandClass;

extern DynamicVectorClass<CommandClass const *> AllCommands;
extern IndexClass<int, CommandClass const *> HotkeyCommands;
