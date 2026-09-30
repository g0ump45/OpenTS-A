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
 *                     $Archive:: /G/wwlib/PIPE.H                                             $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 12:00p                                              $*
 *                                                                                             *
 *                    $Revision:: 3                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include <cstddef>


/*
**	A "push through" pipe interface abstract class used for such purposes as compression
**	and translation of data. In STL terms, this is functionally similar to an output
**	iterator but with a few enhancements. A pipe class object that is not derived into
**	another useful class serves only as a pseudo null-pipe. It will accept data but
**	just throw it away but pretend that it sent it somewhere.
*/
class Pipe
{
	public:
		Pipe(void) : ChainTo(0), ChainFrom(0) {}
		virtual ~Pipe(void);

		virtual int Flush(void);
		virtual int End(void) {return(Flush());}
		virtual void Put_To(Pipe * pipe);
		void Put_To(Pipe & pipe) {Put_To(&pipe);}
		virtual int Put(void const * source, int slen);

		/*
		**	Pointer to the next pipe segment in the chain.
		*/
		Pipe * ChainTo;
		Pipe * ChainFrom;

	private:

		/*
		**	Disable the copy constructor and assignment operator.
		*/
		Pipe(Pipe & rvalue);
		Pipe & operator = (Pipe const & pipe);
};
