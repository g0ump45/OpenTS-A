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
/// Creates an empty ownership snapshot.
/// The snapshot refers to no tour state at all, so every territory reports as UNASSIGNED
/// until it is assigned from a real one.
/// </summary>
State::State(void) :
	TourState(0),
	Owners(NULL)
{
	//nothing
}


/// <summary>
/// Creates a snapshot of the tour at one tick of its cycle.
/// This routine is used by the tour history to hand out a view of who held what at some
/// earlier point in the current cycle. A tick the tour has no record for still yields a
/// usable snapshot, but every territory will report as UNASSIGNED.
/// </summary>
/// <param name="state">The tour state to take the snapshot from.</param>
/// <param name="tick">The point in the cycle's ownership history to look at.</param>
State::State(WDTState * state, unsigned int tick) :
	TourState(state),
	Owners(NULL)
{
	if (state != NULL) {
		if (tick < state->NumTicks) {
			Owners = state->OwnerHistory[tick];
		}
	}
}


/// <summary>
/// Creates a copy of an ownership snapshot.
/// The copy shares the original's tour state and ownership row; it does not take a
/// duplicate of either, so the tour state must outlive both snapshots.
/// </summary>
State::State(State const & that)
{
	TourState = that.TourState;
	Owners = that.Owners;
}


/// <summary>
/// Assigns one ownership snapshot to another.
/// The tour state and the ownership row are shared rather than duplicated, so both
/// snapshots go on referring to the same tour data.
/// </summary>
/// <returns>Returns with a reference to this snapshot.</returns>
State & State::operator=(State const & that)
{
	TourState = that.TourState;
	Owners = that.Owners;
	return(*this);
}


/// <summary>
/// Determines if two snapshots refer to the same moment.
/// This routine is used to notice when a refreshed tour state has left the displayed
/// snapshot unchanged, so that no needless redraw is performed.
/// </summary>
/// <returns>bool; Do both snapshots describe the same tour state and tick?</returns>
bool State::operator==(State const & that)
{
	return(TourState == that.TourState && Owners == that.Owners);
}


/// <summary>
/// Fetches who holds a territory in this snapshot.
/// This routine is used by the tour map display to color each territory according to the
/// side that owned it at the moment the snapshot was taken.
/// </summary>
/// <param name="territory">Index of the territory to examine.</param>
/// <returns>Returns with the owning side of that territory. A territory nobody has claimed
/// yet, or an index this snapshot cannot answer for, comes back as UNASSIGNED.</returns>
State::TerritoryState State::Get_Territory_State(unsigned int territory)
{
	if (TourState != NULL && Owners != NULL && territory < TourState->NumTerritories) {
		switch (Owners[territory]) {
			case WDTState::CONTESTED:
				return(State::DISPUTED);
			case WDTState::GDI:
				return(State::GDI);
			case WDTState::NOD:
				return(State::NOD);
		}
	}
	return(State::UNASSIGNED);
}


/// <summary>
/// Destroys the ownership snapshot.
/// A snapshot merely refers to the tour state and to one row of its ownership history, so
/// there is nothing here for it to release.
/// </summary>
State::~State(void)
{
	//nothing
}


/// <summary>
/// Counts the territories held by one side.
/// This routine is used by the tour front end to report how much of the map a player's
/// side controls at this point in the cycle. Contested territories count for nobody.
/// </summary>
/// <param name="player_faction">The side to tally territories for.</param>
/// <returns>Returns with the number of territories owned by that side. An empty snapshot
/// yields zero.</returns>
int State::Count_Owned_Territories(int player_faction)
{
	if (TourState && Owners) {
		int count = 0;
		unsigned char * owners = Owners;
		unsigned int i = TourState->NumTerritories;

		while (i--) {
			unsigned int owner = *owners;
			owners++;
			switch (owner) {
				case WDTState::CONTESTED:
					break;

				case WDTState::GDI:
					if (player_faction == 2) {
						count++;
					}
					break;

				case WDTState::NOD:
					if (player_faction == 3) {
						count++;
					}
					break;
			}
		}
		return(count);
	}
	return(0);
}
