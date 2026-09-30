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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Command & Conquer                                            *
 *                                                                                             *
 *                     $Archive:: /G/wwlib/PIPE.CPP                                           $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/15/99 10:15a                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *   Pipe::Put_To -- Connect a pipe to flow data into from this pipe.                          *
 *   Pipe::Flush -- Flush all pending data out the pipe.                                       *
 *   Pipe::Put -- Feed some data through the pipe.                                             *
 *   Pipe::~Pipe -- Destructor for pipe class object.                                          *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "always.h"

#include "pipe.h"

#include <cstddef>
#include <cstring>


/***********************************************************************************************
 * Pipe::~Pipe -- Destructor for pipe class object.                                            *
 *                                                                                             *
 *    This destructor will unlink itself from any other pipes that it may be chained to. In    *
 *    the process, it will flush any output it may have pending.                               *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
Pipe::~Pipe(void)
{
	if (ChainTo != NULL) {
		ChainTo->ChainFrom = ChainFrom;
	}
	if (ChainFrom != NULL) {
		ChainFrom->Put_To(ChainTo);
	}

	ChainFrom = NULL;
	ChainTo = NULL;
}


/***********************************************************************************************
 * Pipe::Put_To -- Connect a pipe to flow data into from this pipe.                            *
 *                                                                                             *
 *    This routine will link two pipes together. The specified pipe will be fed data from      *
 *    this pipe.                                                                               *
 *                                                                                             *
 * INPUT:   pipe  -- Pointer to the pipe that data will flow to.                               *
 *                                                                                             *
 * OUTPUT:  none                                                                               *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
void Pipe::Put_To(Pipe * pipe)
{
	if (ChainTo != pipe) {
		if (pipe != NULL && pipe->ChainFrom != NULL) {
			pipe->ChainFrom->Put_To(NULL);
			pipe->ChainFrom = NULL;
		}

		if (ChainTo != NULL) {
			ChainTo->ChainFrom = NULL;
			ChainTo->Flush();
		}

		ChainTo = pipe;
		if (ChainTo != NULL) {
			ChainTo->ChainFrom = this;
		}
	}
}


/***********************************************************************************************
 * Pipe::Put -- Feed some data through the pipe.                                               *
 *                                                                                             *
 *    Use this to force feed data through the pipe. It is guaranteed to accept data as fast    *
 *    as you can supply it.                                                                    *
 *                                                                                             *
 * INPUT:   source   -- Pointer to the data to feed to this routine.                           *
 *                                                                                             *
 *          length   -- The number of bytes of data to submit.                                 *
 *                                                                                             *
 * OUTPUT:  Returns with the number of bytes actually output at the other far distant final    *
 *          end of the pipe.                                                                   *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int Pipe::Put(void const * source, int length)
{
	if (ChainTo != NULL) {
		return(ChainTo->Put(source, length));
	}
	return(length);
}


/***********************************************************************************************
 * Pipe::Flush -- Flush all pending data out the pipe.                                         *
 *                                                                                             *
 *    Then the pipe needs to be flushed, this routine will be called. Since pipe segments      *
 *    might have internal staging buffer for the data, this routine is necessary to force      *
 *    all staging buffers to be clear. This routine is called when the pipe is being           *
 *    destroyed.                                                                               *
 *                                                                                             *
 * INPUT:   none                                                                               *
 *                                                                                             *
 * OUTPUT:  Returns with the number of bytes output at the far distant final end of the pipe   *
 *          chain.                                                                             *
 *                                                                                             *
 * WARNINGS:   none                                                                            *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/03/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
int Pipe::Flush(void)
{
	if (ChainTo != NULL) {
		return(ChainTo->Flush());
	}
	return(0);
}
