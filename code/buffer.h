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
 *                 Project Name : Westwood 32 Bit Library                  *
 *                                                                         *
 *                    File Name : GBUFFER.H                                *
 *                                                                         *
 *                   Programmer : Phil W. Gorrow                           *
 *                                                                         *
 *                   Start Date : May 26, 1994                             *
 *                                                                         *
 *                  Last Update : July 5, 1994   [PWG]                     *
 *                                                                         *
 *-------------------------------------------------------------------------*
 * Functions:                                                              *
 *   BC::Get_Size -- Returns the buffer size of the BufferClass instance   *
 *   BC::Get_Buffer -- Returns pointer to buffer inherent to BufferClass   *
 *   BC::BufferClass -- inline constructor for BufferClass with size only  *
 *   BC::To_Page -- Copys a buffer class to a page with definable x, y, w, h*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

/*=========================================================================*/
/* BufferClass - A base class which holds buffer information including a   */
/*      pointer and the size of the buffer.                                */
/*=========================================================================*/
class BufferClass {
	public:
		/*===================================================================*/
		/* Define the base constructor and destructors for the class         */
		/*===================================================================*/
		BufferClass(void *ptr, int size);
		BufferClass(int size);
		BufferClass(void);
		~BufferClass(void);

		/*===================================================================*/
		/* define functions to get at the protected data members             */
		/*===================================================================*/
		void	*Get_Buffer(void);
		int	Get_Size(void);

	private:
		/*===================================================================*/
		/* Define the operators we do not want to happen which are the copy  */
		/* and equal constructors.  These are bad because the Allocated flag */
		/* could be copied and the associated buffer freed.  If this were to */
		/* gappen it could cause weird general protection fault.             */
		/*===================================================================*/
		BufferClass(BufferClass const &);
		BufferClass &operator=(BufferClass const &);

	protected:
		void	*Buffer;
		int	Size;
		bool	Allocated;
};
/***************************************************************************
 * BC::GET_SIZE -- Returns the buffer size of the BufferClass instance     *
 *                                                                         *
 * INPUT:      none                                                        *
 *                                                                         *
 * OUTPUT:     long the size of the buffer                                 *
 *                                                                         *
 * HISTORY:                                                                *
 *   06/01/1994 PWG : Created.                                             *
 *=========================================================================*/
inline int BufferClass::Get_Size(void)
{
	return(Size);
}
/***************************************************************************
 * BC::GET_BUFFER -- Returns pointer to buffer inherent to BufferClass     *
 *                                                                         *
 * INPUT:         none                                                     *
 *                                                                         *
 * OUTPUT:        void * to the inherent buffer.                           *
 *                                                                         *
 * HISTORY:                                                                *
 *   06/01/1994 PWG : Created.                                             *
 *=========================================================================*/
inline void *BufferClass::Get_Buffer(void)
{
	return(Buffer);
}
