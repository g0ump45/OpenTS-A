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


/****************************************************************************
**	These are the various radio message that can be transmitted between
**	units and buildings. Some of these require a response from the receiver
**	and some don't.
*/
enum RadioMessageType {
	RADIO_STATIC,           // "hisssss" -- non-message
	RADIO_ROGER,            // "Roger."
	RADIO_HELLO,            // "Come in. I wish to talk."
	RADIO_OVER_OUT,         // "Something came up, bye."
	RADIO_PICK_UP,          // "Please pick me up."
	RADIO_ATTACH,           // "Attach to transport."
	RADIO_DELIVERY,         // "I've got a delivery for you."
	RADIO_HOLD_STILL,       // "I'm performing load/unload maneuver. Be careful."
	RADIO_UNLOADED,         // "I'm clear."
	RADIO_UNLOAD,           // "You are clear to unload. Please start driving off now."
	RADIO_NEGATIVE,         // "Am unable to comply."
	RADIO_BUILDING,         // "I'm starting construction now... act busy."
	RADIO_COMPLETE,         // "I've finished construction. You are free."
	RADIO_REDRAW,           // "Oops, sorry. I might have bumped you a little."
	RADIO_DOCKING,          // "I'm trying to load up now."
	RADIO_CAN_LOAD,         // "May I become a passenger?"
	RADIO_ARE_REFINERY,     // "Are you a refinery ready to take shipment?"
	RADIO_TRYING_TO_LOAD,   // "Are you trying to become a passenger?"
	RADIO_MOVE_HERE,        // "Move to location X."
	RADIO_NEED_TO_MOVE,     // "Do you need to move somewhere?"
	RADIO_YEA_NOW_WHAT,     // "All right already. Now what?"
	RADIO_IM_IN,            // "I'm a passenger now."
	RADIO_BACKUP_NOW,       // "Begin backup into refinery now."
	RADIO_RUN_AWAY,         // "Run away! Run away!"
	RADIO_TETHER,           // "Establish tether contact."
	RADIO_UNTETHER,         // "Break tether contact."
	RADIO_REPAIR,           // "Repair one step."
	RADIO_PREPARED,         // "Are you prepared to fight?"
	RADIO_ATTACK_THIS,      // "Attack this target please."
	RADIO_RELOAD,           // "Reload one step please."
	RADIO_CANT,             // "Circumstances prevent success."
	RADIO_ALL_DONE,         // "I have completed the task."
	RADIO_NEED_REPAIR,      // "Are you in need of service depot work?"
	RADIO_ON_DEPOT,         // "Are you sitting on a service depot?"
	RADIO_WANT_RIDE,        /// "Gimme a ride!"

	RADIO_COUNT
};

