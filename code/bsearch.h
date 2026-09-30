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

#include <cstddef>


/*
**	Binary searching template. It can be faster than the built in C library
**	version since the comparison function can be inlined. If the comparison
**	process is significantly more time consuming than the overhead of
**	a function call, then using the C library version would be appropriate.
*/
template<class T>
T * Binary_Search(T * A, int n, T const & target)
{
	const T * pointer = A;
	int stride = n;

	/*
	**	Keep binary searching until a match has been found
	**	or the search has resulted in no match.
	*/
	while (0 < stride) {
		int const pivot = stride / 2;
		T const * const tryptr = pointer + pivot;

		/*
		**	Binary stride forward or backward depending on if the candidate
		**	element is smaller or larger than the target element. If
		**	smaller, then merely adjusting the stride is required. If larger,
		**	then the base pointer must be adjusted and the stride must be
		**	moved backward.
		*/
		if (target < *tryptr) {
			stride = pivot;
		} else {

			/*
			**	An exact match results in the pointer being found
			**	and returned to the caller. This check is performed
			**	here since 50% of the time, the first compare will
			**	be true and thus the equality comparison would be
			**	called less often -- should be faster as a result.
			*/
			if (*tryptr == target) {
				return((T *) tryptr);
			}

			pointer = tryptr + 1;
			stride -= pivot + 1;
		}
	}
	return(NULL);
}
