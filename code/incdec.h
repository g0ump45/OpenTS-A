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
 *                     $Archive:: /Commando/Library/incdec.h                                  $*
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 7/22/97 11:37a                                              $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

#include <type_traits>

/*
**	These templates allow enumeration types to have simple bitwise
**	arithmatic performed. The operators must be instatiated for the
**	enumerated types desired.
*/
template<class T> requires std::is_enum_v<T> inline T operator ++(T & a)
{
	a = (T)((int)a + (int)1);
	return(a);
}
template<class T> requires std::is_enum_v<T> inline T operator ++(T & a, int)
{
	T aa = a;
	a = (T)((int)a + (int)1);
	return(aa);
}
template<class T> requires std::is_enum_v<T> inline T operator --(T & a)
{
	a = (T)((int)a - (int)1);
	return(a);
}
template<class T> requires std::is_enum_v<T> inline T operator --(T & a, int)
{
	T aa = a;
	a = (T)((int)a - (int)1);
	return(aa);
}
