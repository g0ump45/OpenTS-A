/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "storage.h"

#include "tiberium.h"
#include "vector.h"


/// <summary>
/// Creates an empty storage object.
/// Every tiberium slot starts out holding nothing.
/// </summary>
StorageClass::StorageClass(void)
{
	for (int i = 0; i < ARRAY_SIZE(Values); i++) {
		Values[i] = 0;
	}
}


/// <summary>
/// Fetches the credit value of everything in storage.
/// Each tiberium type carries its own credit value, so this routine weighs every slot
/// against its type. This is what a refinery uses to decide how much to pay out for a
/// harvester load.
/// </summary>
/// <returns>Returns with the total credit value of the tiberium held.</returns>
int StorageClass::Get_Total_Value(void) const
{
	int value = 0;
	for (int i = 0; i < ARRAY_SIZE(Values); i++) {
		if (Values[i] > 0) {
			value += Values[i] * Tiberiums[i]->CreditValue;
		}
	}

	return(value);
}


/// <summary>
/// Fetches the total quantity held in storage.
/// This is a plain count of everything stored, with no regard for what the various
/// tiberium types happen to be worth. Use it when the question is "how full is this?"
/// rather than "how much is this worth?".
/// </summary>
/// <returns>Returns with the sum of every storage slot.</returns>
int StorageClass::Get_Total_Amount(void) const
{
	int amount = 0;
	for (int i = 0; i < ARRAY_SIZE(Values); i++) {
		amount += Values[i];
	}

	return(amount);
}


/// <summary>
/// Fetches the amount held in one storage slot.
/// </summary>
/// <returns>Returns with the quantity of that tiberium type currently stored.</returns>
int StorageClass::Get_Amount(int slot) const
{
	return(Values[slot]);
}


/// <summary>
/// Adds tiberium to one of the storage slots.
/// The caller is responsible for keeping the storage within whatever capacity the
/// owning object has -- this routine imposes no limit of its own.
/// </summary>
/// <param name="by">The amount to add to the slot.</param>
/// <returns>Returns with the new total held in that slot.</returns>
int StorageClass::Increase_Amount(int by, int slot)
{
	Values[slot] += by;
	return(Values[slot]);
}


/// <summary>
/// Removes tiberium from one of the storage slots.
/// This routine will never draw out more than the slot actually holds, so the caller
/// may ask for any amount and let the storage decide what it can spare.
/// </summary>
/// <param name="by">The amount that the caller would like to remove.</param>
/// <returns>Returns with the amount actually removed, which may be less than asked for.</returns>
int StorageClass::Decrease_Amount(int by, int slot)
{
	int amount;
	if (Values[slot] < by) {
		amount = Values[slot];
	} else {
		amount = by;
	}
	Values[slot] -= amount;
	return(amount);
}


/// <summary>
/// Adds two storage objects together.
/// Neither of the two objects is disturbed; the sum is returned as a fresh storage
/// object.
/// </summary>
/// <returns>Returns with the slot by slot sum of the two storage objects.</returns>
StorageClass StorageClass::operator+(StorageClass &that) const
{
	StorageClass tmp;

	for (int i = 0; i < ARRAY_SIZE(Values); i++) {
		tmp.Values[i] = Values[i] + that.Values[i];
	}

	return(tmp);
}


/// <summary>
/// Adds another storage object into this one.
/// Every slot is increased by the matching slot of the other object.
/// </summary>
/// <returns>Returns with a copy of this storage object as it stands after the addition.</returns>
StorageClass StorageClass::operator+=(StorageClass &that)
{
	for (int i = 0; i < ARRAY_SIZE(Values); i++) {
		Values[i] += that.Values[i];
	}

	return(*this);
}


/// <summary>
/// Subtracts one storage object from another.
/// Neither of the two objects is disturbed; the difference is returned as a fresh
/// storage object.
/// </summary>
/// <returns>Returns with the slot by slot difference of the two storage objects.</returns>
StorageClass StorageClass::operator-(StorageClass &that) const
{
	StorageClass tmp;

	for (int i = 0; i < ARRAY_SIZE(Values); i++) {
		tmp.Values[i] = Values[i] - that.Values[i];
	}

	return(tmp);
}


/// <summary>
/// Subtracts another storage object from this one.
/// Every slot is reduced by the matching slot of the other object.
/// </summary>
/// <returns>Returns with a copy of this storage object as it stands after the
/// subtraction.</returns>
StorageClass StorageClass::operator-=(StorageClass &that)
{
	for (int i = 0; i < ARRAY_SIZE(Values); i++) {
		Values[i] -= that.Values[i];
	}

	return(*this);
}


/// <summary>
/// Fetches the first storage slot that holds anything.
/// This routine is used when the holder of the storage only cares about one tiberium
/// type -- a harvester picking the graphic for its load, for example.
/// </summary>
/// <returns>Returns with the slot of the first tiberium type present, or -1 if the storage
/// is empty.</returns>
int StorageClass::First_Used_Slot(void) const
{
	for (int i = 0; i < ARRAY_SIZE(Values); i++) {
		if (Values[i] > 0) {
			return(i);
		}
	}

	return(-1);
}
