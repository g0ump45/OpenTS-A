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

/***************************************************************************
 **   C O N F I D E N T I A L --- W E S T W O O D   A S S O C I A T E S   **
 ***************************************************************************
 *                                                                         *
 *                 Project Name : LIBRARY                                  *
 *                                                                         *
 *                    File Name : DELAY.C                                  *
 *                                                                         *
 *                   Programmer : Christopher Yates                        *
 *                                                                         *
 *                  Last Update : 27 March, 1991   [CY]                    *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "delay.h"

#include "stimer.h"
#include "timer.h"


/// <summary>
/// Pauses for the specified length of time.
/// This routine will spin on the system timer until the delay has elapsed. It exists for
/// the brief hardware and startup waits that predate any game loop worth returning to.
/// </summary>
/// <param name="duration">The length of the pause, in system timer ticks.</param>
/// <remarks>This is a busy wait. Nothing else gets a chance to run while it is in
/// progress.</remarks>
void Delay(int duration)
{
	CDTimerClass<SystemTimerClass> timer(duration);

	while (timer() != 0) {
		;
	}

#if (FALSE)
	while (duration--)
		Wait_Vert_Blank(VertBlank);
#endif
}

#if (FALSE)
void Vsync(void)
{
	Wait_Vert_Blank(VertBlank);
}
#endif


/// <summary>
/// Creates a delay timer in its idle state.
/// The new timer is not counting in either direction and reports itself as having
/// already ended, so an owner may safely query it before ever starting a count.
/// </summary>
DelayTimerClass::DelayTimerClass(void) :
	Timer(0),
	IsActive(false),
	IsToCountUp(false)
{
}


/// <summary>
/// Is a count up currently running?
/// This is the query behind a door reporting itself as opening.
/// </summary>
/// <returns>bool; Is the timer running forwards?</returns>
bool DelayTimerClass::Is_Count_Up_Active(void) const
{
	if (IsActive && IsToCountUp) {
		return(true);
	}
	return(false);
}


/// <summary>
/// Is a count down currently running?
/// This is the query behind a door reporting itself as closing.
/// </summary>
/// <returns>bool; Is the timer running backwards?</returns>
bool DelayTimerClass::Is_Count_Down_Active(void) const
{
	if (IsActive && !IsToCountUp) {
		return(true);
	}
	return(false);
}


/// <summary>
/// Determines if the delay has run its course.
/// This routine is polled by the timer's own AI; when it answers true the count is
/// ended and the timer settles at whichever extreme it was heading for.
/// </summary>
/// <returns>bool; Is the timer either idle or expired?</returns>
bool DelayTimerClass::Has_Ended(void) const
{
	if (!IsActive || Timer.Has_Completed()) {
		return(true);
	}

	return(false);
}


/// <summary>
/// Has the count up finished?
/// This is the query behind a door reporting itself fully open.
/// </summary>
/// <returns>bool; Is the timer idle at the top of its travel?</returns>
bool DelayTimerClass::Is_Count_Up_Complete(void) const
{
	if (!IsActive && IsToCountUp == true) {
		return(true);
	}
	return(false);
}


/// <summary>
/// Has the count down finished?
/// A timer that has never been started answers true, since a door that was never opened
/// is closed as far as the game is concerned.
/// </summary>
/// <returns>bool; Is the timer idle at the bottom of its travel?</returns>
bool DelayTimerClass::Is_Count_Down_Complete(void) const
{
	if (!IsActive && !IsToCountUp) {
		return(true);
	}
	return(false);
}


/// <summary>
/// Starts the timer counting up.
/// This routine is used to begin a delay that runs forwards -- a building door swinging
/// open, for example. The count runs until the duration is used up, at which point the
/// timer reports its count up as complete.
/// </summary>
/// <param name="duration">The length of the count, expressed in game minutes.</param>
void DelayTimerClass::Count_Up(double duration)
{
	if (IsActive || IsToCountUp != true) {
		IsActive = true;
		Duration = duration * TICKS_PER_MINUTE;
		Timer = Duration;
		IsToCountUp = true;
	}
}


/// <summary>
/// Starts the timer counting down.
/// This routine is used to begin a delay that runs backwards -- a building door swinging
/// shut, for example. The count runs until the duration is used up, at which point the
/// timer reports its count down as complete.
/// </summary>
/// <param name="duration">The length of the count, expressed in game minutes.</param>
void DelayTimerClass::Count_Down(double duration)
{
	if (IsActive || IsToCountUp) {
		IsActive = true;
		Duration = duration * TICKS_PER_MINUTE;
		Timer = Duration;
		IsToCountUp = false;
	}
}


/// <summary>
/// Reverses the direction of the running count.
/// Use this routine when something changes its mind part way through. A door told to
/// close while it is still opening backs out from wherever it happened to get to,
/// rather than snapping to the far end of its travel.
/// </summary>
/// <remarks>A timer that is not running is left alone.</remarks>
void DelayTimerClass::Reverse(void)
{
	if (IsActive) {
		Timer.Reverse();
		IsToCountUp = !IsToCountUp;
	}
}


/// <summary>
/// Ends the count up immediately.
/// The timer stops and thereafter reports its count up as complete, however much of the
/// delay was still outstanding.
/// </summary>
void DelayTimerClass::End_Count_Up(void)
{
	IsActive = false;
	IsToCountUp = true;
}


/// <summary>
/// Ends the count down immediately.
/// The timer stops and thereafter reports its count down as complete, however much of
/// the delay was still outstanding.
/// </summary>
void DelayTimerClass::End_Count_Down(void)
{
	IsActive = false;
	IsToCountUp = false;
}


/// <summary>
/// Fetches how far the delay has progressed.
/// This routine is used by the animation code that rides on the timer, so that it can
/// pick the stage of its sequence to display.
/// </summary>
/// <returns>Returns with the progress through the delay, from 0.0 to 1.0. An idle timer
/// reports itself as fully complete.</returns>
double DelayTimerClass::Percent_Complete(void) const
{
	if (IsActive) {
		return(Timer.Progress());
	}
	return(1.0);
}


/// <summary>
/// Ends whichever count is currently running.
/// This routine is used to settle the timer into its finished state once the delay has
/// run out. Whatever the count was driving -- a building door, most commonly -- is left
/// fully open or fully closed to match the direction it was traveling.
/// </summary>
void DelayTimerClass::End_Count(void)
{
	if (Is_Count_Up_Active()) {
		End_Count_Up();
	}

	if (Is_Count_Down_Active()) {
		End_Count_Down();
	}
}
