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
 *                     $Archive:: /VSS_Sync/wwlib/mpmath.h                                    $*
 *                                                                                             *
 *                      $Author:: Vss_sync                                                    $*
 *                                                                                             *
 *                     $Modtime:: 3/21/01 12:01p                                              $*
 *                                                                                             *
 *                    $Revision:: 4                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#pragma once

//lint -e740 -e534 -e537 -e760
//lint -d_LINT=1

#include "straw.h"

#include <cstdlib>


#define	UNITSIZE					32
#define	MAX_BIT_PRECISION		2048
#define	MAX_UNIT_PRECISION	(MAX_BIT_PRECISION/UNITSIZE)
#define	signeddigit	signed int
#define	LOG_UNITSIZE			5

//#define	digit	unsigned int
typedef unsigned int digit;


int XMP_Fetch_Prime_Size(void);
unsigned short const * XMP_Fetch_Prime_Table(void);
int XMP_Significance(const digit * r, int precision);
void XMP_Inc(digit * r, int precision);
void XMP_Dec(digit * r, int precision);
void XMP_Neg(digit * r, int precision);
void XMP_Abs(digit * r, int precision);
void XMP_Shift_Right_Bits(digit * r1, int bits, int precision);
void XMP_Shift_Left_Bits(digit * r1, int bits, int precision);
bool XMP_Rotate_Left(digit * r1, bool carry, int precision);
void XMP_Not(digit * digit_ptr, int precision);
int XMP_Prepare_Modulus(const digit * n_modulus, int precision);
void XMP_Init(digit * r, digit value, int precision);
unsigned XMP_Count_Bits(const digit * r, int precision);
int XMP_Count_Bytes(const digit * r, int precision);
void XMP_Move(digit * dest, digit const * source, int precision);
int XMP_Compare(const digit * r1, const digit * r2, int precision);
bool XMP_Add(digit * result, const digit * r1, const digit * r2, bool carry, int precision);
bool XMP_Add_Int(digit * result, const digit * r1, digit r2, bool carry, int precision);
bool XMP_Test_Eq_Int(digit const * r, int i, int p);
bool XMP_Sub(digit * result, const digit * r1, const digit * r2, bool borrow, int precision);
bool XMP_Sub_Int(digit * result, const digit * r1, unsigned short r2, bool borrow, int precision);
int XMP_Unsigned_Mult(digit * prod, const digit * multiplicand, const digit * multiplier, int precision);
int XMP_Unsigned_Mult_Int(digit * prod, const digit * multiplicand, short multiplier, int precision);
int XMP_Signed_Mult_Int(digit * prod, const digit * multiplicand, signed short multiplier, int precision);
int XMP_Signed_Mult(digit * prod, const digit * multiplicand, const digit * multiplier, int precision);
unsigned short XMP_Unsigned_Div_Int(digit * quotient, digit const * dividend, unsigned short divisor, int precision);
int XMP_Unsigned_Div(digit * remainder, digit * quotient, digit const * dividend, digit const * divisor, int precision);
void XMP_Signed_Div(digit * remainder, digit * quotient, digit const * dividend, digit const * divisor, int precision);
int XMP_Reciprocal(digit * quotient, const digit * divisor, int precision);
void XMP_Decode_ASCII(char const * str, digit * mpn, int precision);
//void xmp_single_mul(unsigned short * prod, unsigned short * multiplicand, unsigned short multiplier, int precision);
void XMP_Double_Mul(digit * prod, const digit * multiplicand, const digit * multiplier, int precision);
//int xmp_stage_modulus(const digit * n_modulus, int precision);
int XMP_Mod_Mult(digit * prod, const digit * multiplicand, const digit * multiplier, int precision);
void XMP_Mod_Mult_Clear(int precision);
int xmp_exponent_mod(digit * expout, const digit * expin, const digit * exponent_ptr, const digit * modulus, int precision);
bool XMP_Is_Small_Prime(const digit * candidate, int precision);
bool XMP_Small_Divisors_Test(const digit * candidate, int precision);
bool XMP_Fermat_Test(const digit * candidate_prime, unsigned rounds, int precision);
void XMP_Inverse_A_Mod_B(digit * result, digit const * number, digit const * modulus, int precision);
void XMP_Signed_Decode(digit * result, const unsigned char * from, int frombytes, int precision);
void XMP_Unsigned_Decode(digit * result, const unsigned char * from, int frombytes, int precision);
unsigned XMP_Encode(unsigned char * to, digit const * from, int precision);
unsigned XMP_Encode(unsigned char * to, unsigned tobytes, digit const * from, int precision);
void XMP_Randomize(digit * result, Straw & rng, int nbits, int precision);
void XMP_Randomize(digit * result, Straw & rng, digit const * min, digit const * max, int precision);
bool XMP_Is_Prime(digit const * prime, int precision);
bool XMP_Rabin_Miller_Test(Straw & rng, digit const * w, int rounds, int precision);
int XMP_DER_Length_Encode(unsigned int length, unsigned char * output);
int XMP_DER_Encode(digit const * from, unsigned char * output, int precision);
void XMP_DER_Decode(digit * result, unsigned char const * input, int precision);


/// <summary>
/// Converts a digit count into a bit count.
/// </summary>
/// <returns>Returns with the number of bits the digits specified occupy.</returns>
inline int XMP_Digits_To_Bits(int digits)
{
	return(digits << LOG_UNITSIZE);
}


/// <summary>
/// Converts a bit count into a digit count.
/// The count is rounded up, so the digits reported will always be enough to hold the bits
/// specified.
/// </summary>
/// <returns>Returns with the number of MP digits required.</returns>
inline int XMP_Bits_To_Digits(int bits)
{
	return((bits + (UNITSIZE-1)) / UNITSIZE);
}


/// <summary>
/// Builds a mask for the last bit of the bit count specified.
/// This routine is used when an MP number must be walked one bit at a time. The mask it
/// returns selects that bit's position within the digit it lands in.
/// </summary>
/// <returns>Returns with the bit mask, or zero if no bits were specified.</returns>
inline digit XMP_Bits_To_Mask(int bits)
{
	if (!bits) return(0);
	return(1 << ((bits-1) % UNITSIZE));
}


/// <summary>
/// Is the MP number negative?
/// Signed MP numbers are held in two's complement form, so the sign is carried by the top
/// bit of the most significant digit.
/// </summary>
/// <returns>bool; Is the number negative?</returns>
inline bool XMP_Is_Negative(const digit * r, int precision)
{
	return((signeddigit) *(r + (precision-1)) < 0);
}


/// <summary>
/// Sets the bit specified in the MP number.
/// </summary>
/// <param name="bit">The zero-based index of the bit to set.</param>
inline void XMP_Set_Bit(digit * r, unsigned bit)
{
	r[bit >> LOG_UNITSIZE] |= ((digit)1 << (bit & (UNITSIZE-1)));
}


/// <summary>
/// Determines if the bit specified is set in the MP number.
/// </summary>
/// <param name="bit">The zero-based index of the bit to examine.</param>
/// <returns>bool; Is the bit set?</returns>
inline bool XMP_Test_Bit(const digit * r, unsigned bit)
{
	return((r[bit >> LOG_UNITSIZE] & ((digit)1 << (bit & (UNITSIZE-1)))) != 0);
}
