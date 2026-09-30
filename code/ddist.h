/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

template<typename T>
class DiscreteDistributionClass
{
	public:
		template<typename U>
		class DistributionObject
		{
			public:
				DistributionObject(void) : Weight(0) {}
				DistributionObject(DistributionObject const & that) : Object(that.Object), Weight(that.Weight) {}
				~DistributionObject(void) {} /// Declared rather than left implicit.

				bool operator == (DistributionObject const & that) const { return(Object == that.Object && Weight == that.Weight); }
				bool operator != (DistributionObject const & that) const { return(Object != that.Object || Weight != that.Weight); }

				/*
				 * This is the candidate this entry stands for, and what the Sample function
				 * returns when the entry is the one picked.
				 */
				U Object;

				/*
				 * This is the share of the distribution the candidate holds. The larger it is
				 * relative to the other entries, the more often the candidate is picked.
				 */
				unsigned int Weight;
		};

		typedef DistributionObject<T *> DIST_OBJ;

		DiscreteDistributionClass(void);
		~DiscreteDistributionClass(void) {}

		void Add(T * obj, unsigned int weight);
		void Clear(void);
		int Count(void) const {return(Objects.Count());};
		T * Sample(void);

		/// The three accessors below are additions. They cost nothing where they are not
		/// called.
		bool Is_Empty(void) const {return(Objects.Count() == 0);};
		unsigned int Get_Total_Weight(void) const {return(TotalWeight);};
		DIST_OBJ const & operator[](int index) const {return(Objects[index]);};

	private:
		/*
		 * These are the candidate objects and their weights, in the order they were added.
		 * The Sample function walks the list accumulating weight until it passes the value
		 * it picked, so the order decides nothing but which entry a given value lands on.
		 */
		DynamicVectorClass<DIST_OBJ> Objects;

		/*
		 * This is the running sum of every candidate's weight, kept in step as objects are
		 * added. It is the upper bound a sample is picked from.
		 */
		unsigned int TotalWeight;
};


/// <summary>
/// Constructor for the discrete distribution class.
/// </summary>
template<typename T>
inline DiscreteDistributionClass<T>::DiscreteDistributionClass(void)
{
	Clear();
}


/// <summary>
/// Adds a candidate to the distribution.
/// The weight is relative rather than absolute -- it is the candidate's share of the running
/// total, so how often the candidate is picked depends on what else has been added.
/// </summary>
/// <param name="obj">Pointer to the candidate object to add.</param>
/// <param name="weight">The share of the distribution to give the candidate.</param>
template<typename T>
inline void DiscreteDistributionClass<T>::Add(T * obj, unsigned int weight)
{
	DIST_OBJ entry;
	entry.Object = obj;
	entry.Weight = weight;
	Objects.Add(entry);
	TotalWeight += weight;
}


/// <summary>
/// Empties the distribution of every candidate.
/// Use this routine to reuse a distribution for a fresh set of candidates rather than
/// building a new one.
/// </summary>
template<typename T>
inline void DiscreteDistributionClass<T>::Clear(void)
{
	TotalWeight = 0;
	Objects.Clear();
}


/// <summary>
/// Picks a candidate at random, weighted by the shares the candidates were added with.
/// This routine is not a query -- it draws from the game's random number generator, so
/// calling it affects the sequence every other caller sees.
/// </summary>
/// <returns>Returns with a pointer to the candidate picked. Otherwise, if the distribution
/// is empty or carries no weight at all, NULL is returned.</returns>
template<typename T>
inline T * DiscreteDistributionClass<T>::Sample(void)
{
	unsigned int cumulative = 0;
	if (TotalWeight >= 1 && Count() != 0) {
		unsigned int pick = Random_Pick<unsigned int>(1, TotalWeight);
		for (int index = 0; index < Objects.Count(); index++) {
			cumulative += Objects[index].Weight;
			if (cumulative >= pick) {
				return(Objects[index].Object);
			}
		}
	}
	return(NULL);
}
