/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

/// Names and comments from TLBs

/*
 * Units are classified into one of these categories.
 */
enum CategoryType {
	CATEGORY_NONE = -1,

	CATEGORY_SOLDIER,		/// combat soldier
	CATEGORY_CIVILIAN,		/// civilian
	CATEGORY_VIP,			/// general, agent, or commando type
	CATEGORY_RECON,			/// scout vehicle
	CATEGORY_AFV,			/// armored fighting vehicle
	CATEGORY_IFV,			/// infantry fighting vehicle
	CATEGORY_ARTY,			/// long range firepower
	CATEGORY_SUPPORT,		/// misc support vehicle
	CATEGORY_TRANSPORT,		/// ground infantry transport
	CATEGORY_AIRSUPPORT,	/// air support vehicle
	CATEGORY_AIRTRANSPORT,	/// air transport vehicle

	CATEGORY_COUNT,			/// maximum categories
	CATEGORY_FIRST = 0,
};
