/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "wdtnet.h"

using namespace WorldDominationTour;


/// <summary>
/// Creates the ownership history for a tour state.
/// This routine is used by the campaign, which keeps one history and consults it for who
/// held which territory at any point of the current cycle.
/// </summary>
/// <param name="state">The tour state holding the ownership record. It may be NULL, in
/// which case no tick is ever valid.</param>
History::History(WDTState * state) :
	TourState(state)
{
	/// nothing
}


/// <summary>
/// Fetches the ownership snapshot for one tick of the cycle.
/// This routine is used by the tour selection screen, which walks the cycle a tick at a
/// time to show how the territories changed hands. A tick outside the recorded history
/// still yields a usable snapshot, but one in which nobody owns anything.
/// </summary>
/// <param name="tick">The point in the cycle to look at.</param>
/// <returns>Returns with the snapshot of territory ownership at that tick.</returns>
State History::Get_State(unsigned int tick)
{
	return(State(TourState, tick));
}


/// <summary>
/// Is the tick one that the tour has a record for?
/// Use this routine before asking for a state, since the history only reaches as far as
/// the ownership record the server sent down for the current cycle.
/// </summary>
/// <param name="ticks">The point in the cycle to check.</param>
/// <returns>bool; Does the history cover this tick?</returns>
bool History::Is_Tick_Valid(unsigned int ticks)
{
	return(TourState != NULL && ticks < TourState->NumTicks);
}


/// <summary>
/// Destroys the tour history.
/// The tour state that it reads from belongs to the campaign and is left untouched.
/// </summary>
History::~History(void)
{
	/// nothing
}
