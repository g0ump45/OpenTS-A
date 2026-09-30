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

/* $Header: /CounterStrike/BENCH.CPP 1     3/03/97 10:24a Joe_bostic $ */
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                    File Name : BENCH.CPP                                                    *
 *                                                                                             *
 *                   Programmer : Joe L. Bostic                                                *
 *                                                                                             *
 *                   Start Date : 07/17/96                                                     *
 *                                                                                             *
 *                  Last Update : July 18, 1996 [JLB]                                          *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Benchmark::Begin -- Start the benchmark operation.                                        *
 *   Benchmark::Benchmark -- Constructor for the benchmark object.                             *
 *   Benchmark::End -- Mark the end of a benchmarked operation                                 *
 *   Benchmark::Reset -- Clear out the benchmark statistics.                                   *
 *   Benchmark::Value -- Fetch the current average benchmark time.                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "bench.h"



/***********************************************************************************************
 * Benchmark::Benchmark -- Constructor for the benchmark object.                               *
 *                                                                                             *
 *    This will construct the benchmark object.                                                *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
Benchmark::Benchmark(void) :
	Average(0),
	Counter(0),
	TotalCount(0)
{
}


/***********************************************************************************************
 * Benchmark::Reset -- Clear out the benchmark statistics.                                     *
 *                                                                                             *
 *    Use this routine to clear out all the accumulated statistics within this benchmark       *
 *    object. The object is set just as if it was freshly constructed.                         *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void Benchmark::Reset(void)
{
	Average = 0;
	Counter = 0;
	TotalCount = 0;
}


/***********************************************************************************************
 * Benchmark::Begin -- Start the benchmark operation.                                          *
 *                                                                                             *
 *    Call this routine before the operation to be benchmarked is begun. The corresponding     *
 *    End() function must be called after the operation has completed.                         *
 *                                                                                             *
 * INPUT:   reset -- Should the entire benchmark object be reset at this time as well?         *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   The Begin() and End() functions are NOT nestable.                               *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void Benchmark::Begin(bool reset)
{
	if (reset) Reset();
	Clock = 0;
}


/***********************************************************************************************
 * Benchmark::End -- Mark the end of a benchmarked operation                                   *
 *                                                                                             *
 *    This routine is called at the end of the operation that is being benchmarked. It is      *
 *    important to call this routine as soon as possible after the event being benchmarked     *
 *    has completed.                                                                           *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   The Being() and End() functions are NOT nestable.                               *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void Benchmark::End(void)
{
	unsigned int value = Clock;

	if (Counter == MAXIMUM_EVENT_COUNT) {
		Average -= Average / MAXIMUM_EVENT_COUNT;
		Average += value;
	} else {
		Average += value;
		Counter++;
	}
	TotalCount++;
}


/// <summary>
/// Records a benchmark sample and fetches the running event count.
/// Use this routine in place of End() when the caller needs to know how many events have
/// been tracked so far. The elapsed time is folded into the running average and the event
/// tallied.
/// </summary>
/// <returns>Returns with the total number of events recorded by this object.</returns>
unsigned int Benchmark::Step(void)
{
	unsigned int value = Clock;

	Average += value;

	Counter++;
	TotalCount++;

	return(TotalCount);
}


/***********************************************************************************************
 * Benchmark::Value -- Fetch the current average benchmark time.                               *
 *                                                                                             *
 *    This routine will take the statistics already accumulated and determine the average      *
 *    time recorded. This value will be returned.                                              *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the average time that all events tracked by this object.              *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/18/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
unsigned int Benchmark::Value(void) const
{
	if (Counter) {
		return(Average / Counter);
	}
	return(0);
}
