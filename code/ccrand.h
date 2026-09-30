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

#include "_rand.h"
#include "globals.h"
#include "random.h"
#include "scenario.h"

#include <climits>

/***********************************************************************************************
 * Random_Pick -- Pick a random number in a specified range.                                   *
 *                                                                                             *
 *    This routine is used to pick a game influencing random number between (inclusive) the    *
 *    range specified.                                                                         *
 *                                                                                             *
 * INPUT:   a  -- Low limit of range to pick from.                                             *
 *                                                                                             *
 *          b  -- High limit of range to pick from.                                            *
 *                                                                                             *
 * OUTPUT:  Returns with a random number picked between (inclusive) the range of values        *
 *          specified.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/30/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
template<class T> inline T Random_Pick(T a, T b)
{
	return(T(Scen->RandomNumber((int)a, (int)b)));
};


/***********************************************************************************************
 * Percent_Chance -- Calculate a percentage chance event.                                      *
 *                                                                                             *
 *    This will calculate a percentage chance and return with 'true' as likely as the          *
 *    chance value would occur (or less) on a random pick from 1 to 100. Thus a                *
 *    Percent_Chance(50) would return 'true' 50 percent of the time. Percent_Chance(25) would  *
 *    return 'true' 25% of the time, etc.                                                      *
 *                                                                                             *
 * INPUT:   percent  -- The percent value to calculate the chance upon.                        *
 *                                                                                             *
 * OUTPUT:  Returns with 'true' in the same percentage as the percentage number supplied.      *
 *                                                                                             *
 * WARNINGS:   This affects the game syncronization random number generator and should be used *
 *             for those events that could affect the game engine.                             *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline bool Percent_Chance(int percent)
{
	return(Scen->RandomNumber(0, 99) < percent);
}


/// <summary>
/// Calculates a chance event from a fractional probability.
/// This is the fine grained counterpart to Percent_Chance, which cannot express odds of less
/// than one percent. A probability of 0.5 returns true half the time, one of 0.004 four times
/// in a thousand.
/// </summary>
/// <param name="probability">The fractional chance to calculate the event upon.</param>
/// <returns>bool; Did the event occur?</returns>
/// <remarks>This draws from the synchronized random number generator, so it must only be called
/// from game logic that every machine performs. The draw is quantized to ten thousandths, so a
/// probability finer than that never fires.</remarks>
inline bool Probability_Of(double probability)
{
	return((abs(Scen->RandomNumber()) % 10000) / 10000.0 < probability);
}


/***********************************************************************************************
 * Sim_Random_Pick -- Picks a random number that will not affect the game.                     *
 *                                                                                             *
 *    Use this routine to pick a random number such that it will be used so that it won't      *
 *    actually affect the outcome of the game. It is critical to use this routine for any      *
 *    random need that won't be needed on other machines in a multiplayer game. The result     *
 *    can be freely used as long as it doesn't affect the outcome of the game.                 *
 *                                                                                             *
 * INPUT:   a  -- Low range of the random number to pick.                                      *
 *                                                                                             *
 *          b  -- High range of the random number to pick.                                     *
 *                                                                                             *
 * OUTPUT:  Returns with a random number between (inclusive) the range limit values            *
 *          specified.                                                                         *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   09/30/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
template<class T> inline T Sim_Random_Pick(T a, T b)
{
	return(T(NonCriticalRandomNumber((int)a, (int)b)));
};


/***********************************************************************************************
 * Sim_Percent_Chance -- Calculates a percentage chance event for local events.                *
 *                                                                                             *
 *    This routine is similar to the normal Percent_Chance() routine except that it doesn't    *
 *    alter the main random number gerenator sequence. As such, this routine should be used    *
 *    for those events that should have a random character, but will either not affect the     *
 *    game engine or are only calculated on one machine in a multiplayer game.                 *
 *                                                                                             *
 * INPUT:   percent  -- The percent chance to calculate the possible return of 'true' on.      *
 *                                                                                             *
 * OUTPUT:  Returns 'true' with the same percentage chance as the percent number specified.    *
 *          A percent value of 50 means 50%, 25 means 25%, etc.                                *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   08/26/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
inline bool Sim_Percent_Chance(int percent)
{
	return(NonCriticalRandomNumber(0, 99) < percent);
}


/// <summary>
/// Picks a random real number between the two values specified.
/// Unlike Random_Pick, which chooses from the whole numbers in the range, this picks from the
/// continuous span between them. Use it for the fractional chances and the perturbation amounts
/// that the animation and particle logic deal in.
/// </summary>
/// <param name="a">The lower value of the range.</param>
/// <param name="b">The upper value of the range.</param>
/// <returns>Returns with a random number between the two values specified.</returns>
/// <remarks>This draws from the synchronized random number generator, so it must only be called
/// from game logic that every machine performs.</remarks>
inline double Random_Double(double a, double b)
{
	int num = Scen->RandomNumber(0, INT_MAX - 1);
	return((b - a) * (num / double(INT_MAX - 1)) + a);
}

/// The integer-argument spelling, used by the house AI to weigh a percentage chance. Note
/// that the two are an overload pair, so a call meant for the form above must spell both of
/// its arguments as real numbers or it will silently land here instead.
inline double Random_Double(int a, int b)
{
	int num = Scen->RandomNumber(a, b);
	return(num * double(a + 1)/double(b));
}
