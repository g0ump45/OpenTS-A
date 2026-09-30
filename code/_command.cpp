/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "_command.h"

#include "index.h"
#include "vector.h"

class CommandClass;

IndexClass<int, CommandClass const *> HotkeyCommands;
DynamicVectorClass<CommandClass const *> AllCommands;
