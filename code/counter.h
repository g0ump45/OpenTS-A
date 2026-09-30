/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "vector.h"
#include "win.h"

class CounterClass : protected VectorClass<int>
{
public:
	int Increment(int index);
	int Decrement(int index);

	int Value(int index) const;

	void Clear(void);

	int Total(void) const;

	bool Reserve(int index);

	/*
	 * Carries the counters, which are only the elements of the vector underneath. This
	 * reaches that past the protected inheritance.
	 */
	template<typename S>
	void Serialize(S & stream)
	{
		VectorClass<int>::Serialize(stream);
	}

	int operator[](int index) {return(Vector[index]);};

	enum {
		GROWTH_STEP = 10,
	};
};
