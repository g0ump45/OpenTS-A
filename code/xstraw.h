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
 *                     $Archive:: /G/wwlib/XSTRAW.H                                           $*
 *                                                                                             *
 *                      $Author:: Eric_c                                                      $*
 *                                                                                             *
 *                     $Modtime:: 4/02/99 12:01p                                              $*
 *                                                                                             *
 *                    $Revision:: 2                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include "buff.h"
#include "straw.h"
#include "wwfile.h"

#include <cstddef>

/*
**	This class is used to manage a buffer as a data source. Data requests will draw from the
**	buffer supplied until the buffer is exhausted.
*/
class BufferStraw : public Straw
{
		typedef Straw BASECLASS;

	public:
		BufferStraw(Buffer const & buffer) : BufferPtr(buffer), Index(0) {}
		BufferStraw(void const * buffer, int length) : BufferPtr((void*)buffer, length), Index(0) {}
		virtual int Get(void * source, int slen) override;

	private:
		Buffer BufferPtr;
		int Index;
//		void const * BufferPtr;
//		int Length;

		bool Is_Valid(void) {return(BufferPtr.Is_Valid());}
		BufferStraw(BufferStraw & rvalue);
		BufferStraw & operator = (BufferStraw const & pipe);
};

/*
**	This class is used to manage a file as a data source. Data requests will draw from the
**	file until the file has been completely read.
*/
class FileStraw : public Straw
{
		typedef Straw BASECLASS;

	public:
		FileStraw(FileClass * file) : File(file), HasOpened(false) {}
		FileStraw(FileClass & file) : File(&file), HasOpened(false) {}
		virtual ~FileStraw(void) override;
		virtual int Get(void * source, int slen) override;

	private:
		FileClass * File;
		bool HasOpened;

		bool Valid_File(void) {return(File != NULL);}
		FileStraw(FileStraw & rvalue);
		FileStraw & operator = (FileStraw const & pipe);
};
