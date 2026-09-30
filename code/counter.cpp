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

#include "counter.h"


/// <summary>
/// Adds one to the counter specified.
/// </summary>
/// <returns>Returns with the counter's new value, or zero if there was no room for
/// the counter.</returns>
int CounterClass::Increment(int index)
{
	if (Reserve(index)) {
		return(++Vector[index]);
	}
	return(0);
}


/// <summary>
/// Subtracts one from the counter specified.
/// </summary>
/// <returns>Returns with the counter's new value, or zero if there was no room for
/// the counter.</returns>
int CounterClass::Decrement(int index)
{
	if (Reserve(index)) {
		return(--Vector[index]);
	}
	return(0);
}


/// <summary>
/// Fetches the current value of the counter specified.
/// </summary>
/// <returns>Returns with the counter's value. A counter never tallied before reads as
/// zero.</returns>
int CounterClass::Value(int index) const
{
	if (index >= 0 && index < VectorMax) {
		return(Vector[index]);
	}
	return(0);
}


/// <summary>
/// Resets every counter back to zero.
/// This routine is used to start a fresh tally without giving up the room already
/// reserved for the counters.
/// </summary>
void CounterClass::Clear(void)
{
	for (int i = 0; i < VectorMax; ++i) {
		Vector[i] = int(0);
	}
}


/// <summary>
/// Fetches the sum of every counter tracked.
/// </summary>
/// <returns>Returns with the total of all the counter values.</returns>
int CounterClass::Total(void) const
{
	int total = 0;
	if (VectorMax > 0) {
		for (int i = 0; i < VectorMax; i++) {
			total += Vector[i];
		}
	}
	return(total);
}


/// <summary>
/// Ensures that the counter specified actually exists.
/// This routine will grow the counter list on demand so that a caller may tally
/// anything it pleases without having to size the object first. Counters brought
/// into existence this way start out at zero.
/// </summary>
/// <param name="index">The counter that must be made available.</param>
/// <returns>bool; Is the counter safe to use now?</returns>
bool CounterClass::Reserve(int index)
{
	if (index < 0) {
		return(false);
	}

	if (index < VectorMax) {
		return(true);
	}

	int oldmax = VectorMax;
	if (Resize(index + GROWTH_STEP)) {
		for (int i = oldmax; i < VectorMax; i++) {
			Vector[i] = int(0);
		}
		return(true);
	}
	return(false);
}
