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

/*
**	EVA voices are specified by these identifiers.
*/
enum VoxType {
	VOX_NONE=-1,

/* 00-I026  */	VOX_ACCOMPLISHED,					// mission accomplished
/* 00-I028  */	VOX_FAIL,							// your mission has failed
/* 00-I064  */	VOX_NO_FACTORY,						// unable to comply, building in progress
/* 00-I018  */	VOX_CONSTRUCTION,					// construction complete
/* 00-I076  */	VOX_UNIT_READY,						// unit ready
/* 00-I032  */	VOX_NEW_CONSTRUCT,					// new construction options
/* 00-I016  */	VOX_DEPLOY,							// cannot deploy here
/* 00-I008  */	VOX_STRUCTURE_DESTROYED,			// structure destroyed
/* 00-I022  */	VOX_NO_CASH,						// insufficient funds
/* 00-I012  */	VOX_CONTROL_EXIT,					// battle control terminated
/* 00-I038  */	VOX_REINFORCEMENTS,					// reinforcements have arrived
/* 00-I220  */	VOX_CANCELED,						// canceled
/* 00-I216  */	VOX_BUILDING,						// building
/* 00-I024  */	VOX_LOW_POWER,						// low power
/* 00-I082  */	VOX_BASE_UNDER_ATTACK,				// our base is under attack
/* 00-I034  */	VOX_PRIMARY_SELECTED,				// primary building selected
/* 00-I074  */	VOX_UNIT_LOST,						// unit lost
/* 00-I042  */	VOX_SELECT_TARGET,					// select target
/* 00-I044  */	VOX_NEED_MO_CAPACITY,				// silos needed
/* 00-I218  */	VOX_SUSPENDED,						// on hold
/* 00-I040  */	VOX_REPAIRING,						// repairing
/* 00-I062  */	VOX_TRAINING,						/// training
/* 00-I068  */	VOX_UPGRADE_ARMOR,					/// unit armor upgraded
/* 00-I070  */	VOX_UPGRADE_FIREPOWER,				/// unit firepower upgraded
/* 00-I080  */	VOX_UPGRADE_SPEED,					/// unit speed upgraded
/* 00-I078  */	VOX_UNIT_REPAIRED,					/// unit repaired
/* 00-I228  */	VOX_STRUCTURE_SOLD,					/// structure sold
/* 00-I090  */	VOX_HARVESTER_UNDER_ATTACK,			/// harvester under attack
/* 00-I172  */	VOX_CLOAKED_DETECTED,				/// cloaked unit detected
/* 00-I174  */	VOX_SUBTERRANEAN_DETECTED,			/// subterranean unit detected
/* 00-I122  */	VOX_TIME_20,						/// twenty minutes remaining
/* 00-I124  */	VOX_TIME_10,						/// ten minutes remaining
/* 00-I126  */	VOX_TIME_5,							/// five minutes remaining
/* 00-I128  */	VOX_TIME_4,							/// four minutes remaining
/* 00-I130  */	VOX_TIME_3,							/// three minutes remaining
/* 00-I132  */	VOX_TIME_2,							/// two minutes remaining
/* 00-I134  */	VOX_TIME_1,							/// one minute remaining
/* 00-I226  */	VOX_UNIT_SOLD,						/// unit sold
/* 00-I056  */	VOX_BUILDING_CAPTURED,				/// building captured
/* 00-I200  */	VOX_CONTROL_ESTABLISHED,			/// establishing battlefield control, standby
/* 00-I176  */	VOX_ION_STORM_APPROACHING,			/// ion storm approaching
/* 00-I178  */	VOX_METEOR_STORM,					/// meteor storm approaching
/* 00-I198  */	VOX_NEW_TERRAIN,					/// new terrain discovered
/* 00-I150  */	VOX_MISSILE_LAUNCH_DETECTED,		/// missile launch detected
/* 00-I152  */	VOX_CHEMICAL_MISSILE_READY,			/// chemical missile ready
/* 00-I154  */	VOX_CLUSTER_MISSILE_READY,			/// cluster missile ready
/* 00-I156  */	VOX_ION_CANNON_READY,				/// ion cannon ready
/* 00-I158  */	VOX_EM_PULSE_CANNON_READY,			/// em pulse cannon ready
/* 00-I162  */	VOX_FIRESTORM_DEFENSE_READY,		/// firestorm defense ready
/* 00-I170  */	VOX_FIRESTORM_DEFENSE_OFFLINE,		/// firestorm defense offline
/* 00-I100  */	VOX_PRIMARY_OBJECTIVE_ACHIEVED,		/// primary objective achieved
/* 00-I102  */	VOX_SECONDARY_OBJECTIVE_ACHIEVED,	/// secondary objective achieved
/* 00-I104  */	VOX_TERTIARY_OBJECTIVE_ACHIEVED,	/// tertiary objective achieved
/* 00-I106  */	VOX_QUATERNARY_OBJECTIVE_ACHIEVED,	/// quaternary objective achieved
/* 00-I194  */	VOX_CRITICAL_UNIT_LOST,				/// critical unit lost
/* 00-I196  */	VOX_CRITICAL_STRUCTURE_LOST,		/// critical structure lost
/* 00-I208  */	VOX_MUTANT_SUPPLIES_FOUND,			/// mutant supplies found
/* 00-I210  */	VOX_COMMANDOS_EN_ROUTE,				/// commandos en route
/* 00-I014  */	VOX_BUILDING_INFILTRATED,			/// building infiltrated
/* 00-I058  */	VOX_TIMER_STARTED,					/// timer started
/* 00-I060  */	VOX_TIMER_STOPPED,					/// timer stopped
/* 00-I118  */	VOX_BRIDGE_REPAIRED,				/// bridge repaired
/* 00-I180  */	VOX_BASE_DEFENSES_OFFLINE,			/// base defenses offline
/* 00-I230  */	VOX_BUILDING_OFFLINE,				/// building offline
/* 00-I232  */	VOX_BUILDING_ONLINE,				/// building online
/* 00-I252  */	VOX_PLAYER_HAS_RESIGNED,			/// player has resigned
/* 00-I268  */	VOX_PLAYER_WAS_DEFEATED,			/// player was defeated
/* 00-I284  */	VOX_YOU_ARE_VICTORIOUS,				/// you are victorious
/* 00-I286  */	VOX_YOU_HAVE_LOST,					/// you have lost
/* 00-I288  */	VOX_YOU_HAVE_RESIGNED,				/// you have resigned
/* 00-I290  */	VOX_MUTANT_COMMANDOS_AVAILABLE,		/// mutant commandos available
/* 00-I304  */	VOX_ALLIANCE_FORMED,				/// alliance formed
/* 00-I306  */	VOX_ALLIANCE_BROKEN,				/// alliance broken
/* 00-I308  */	VOX_ALLY_ATTACK,					/// our ally is under attack
/* 00-I310  */	VOX_TUTORIAL_POWER,					/// build more powerplants to restore full power
/* 00-I312  */	VOX_TUTORIAL_BARRACKS,				/// build barracks to train additional troops
/* 00-I314  */	VOX_TUTORIAL_HAND_OF_NOD,			/// build hand of nod to train additional troops
/* 00-I316  */	VOX_TUTORIAL_REFINERY,				/// build a tiberium refinery to harvest tiberium
/* 00-I318  */	VOX_TUTORIAL_SILOS,					/// build tiberium silos to store excess tiberium

/* 00-I344  */	VOX_GDI_TAUNT_01,					/// inferior tactics detected
/* 00-I346  */	VOX_GDI_TAUNT_02,					/// retreat is your only logical option
/* 00-I348  */	VOX_GDI_TAUNT_03,					/// surrender is your only logical option
/* 00-I352  */	VOX_GDI_TAUNT_04,					/// your defeat is at hand
/* 00-I356  */	VOX_GDI_TAUNT_05,					/// you have been marked for termination
/* 00-I360  */	VOX_GDI_TAUNT_06,					/// time to erase the human factor from this equation
/* 00-I370  */	VOX_GDI_TAUNT_07,					/// your probability of success is insignificant and dropping
/* 00-I372  */	VOX_GDI_TAUNT_08,					/// surrender is acceptable and preferable against the odds that you are facing
/* 00-I374  */	VOX_GDI_TAUNT_09,					/// data received indicates that you are a threat, prepare for sterilization
/* 00-I376  */	VOX_GDI_TAUNT_10,					/// defeat of enemy predicted in t-minus 3... 2... 1...

/* 01-I342  */	VOX_NOD_TAUNT_01,					/// inferior tactics detected
/* 01-I350  */	VOX_NOD_TAUNT_02,					/// observe superior tactics while you still have human eyes
/* 01-I352  */	VOX_NOD_TAUNT_03,					/// your defeat is at hand
/* 01-I356  */	VOX_NOD_TAUNT_04,					/// you have been marked for termination
/* 01-I360  */	VOX_NOD_TAUNT_05,					/// time to erase the human factor from this equation
/* 01-I362  */	VOX_NOD_TAUNT_06,					/// prepare for decimation, you are not worthy of assimilation
/* 01-I364  */	VOX_NOD_TAUNT_07,					/// you make this easy fleshbag
/* 01-I366  */	VOX_NOD_TAUNT_08,					/// we tire of your insignificant defiance
/* 01-I368  */	VOX_NOD_TAUNT_09,					/// the sacrifice of the many is but a pleasure for the few
/* 01-I378  */	VOX_NOD_TAUNT_10,					/// terminator protocol initiated, proceeding with final sweep

/* 33-N000  */	VOX_33_N000,						/// where the hell are those reinforcements?!
/* 33-N002  */	VOX_33_N002,						/// its nod sir, they came out of nowhere, we have to get back to the base and rebuild the barracks and refinery before they hit us again
/* 33-N004  */	VOX_33_N004,						/// sir, looks like they tore this place apart already, and must be ready to ship the artifacts out. we don't have much time
/* 33-N008  */	VOX_33_N008,						/// here they come
/* 33-N010  */	VOX_33_N010,						/// is there any tech left at the nod base?
/* 33-N012  */	VOX_33_N012,						/// these critters don't look too friendly
/* 33-N014  */	VOX_33_N014,						/// the cavalry has arrived
/* 33-N020  */	VOX_33_N020,						/// i believe there is an old gdi base near, could be worth looking into
/* 33-N022  */	VOX_33_N022,						/// here comes kane's welcoming committee
/* 33-N024  */	VOX_33_N024,						/// what's the eta on that mcv, this ufo gives me heebie jeebies

/* 35-N000  */	VOX_35_N000,						/// this is lieutenant stark, we have touched down on our waiting tratos for immediate evac, get him over here, asap
/* 35-N002  */	VOX_35_N002,						/// nod forces are converging on our position sir. with all due respect, move. your. ass
/* 35-N004  */	VOX_35_N004,						/// coordinates transmitted and confirmed, eta for airstrike is 5 minutes
/* 35-N008  */	VOX_35_N008,						/// pickup service
/* 35-N010  */	VOX_35_N010,						/// negative, i can make it
/* 35-N012  */	VOX_35_N012,						/// i said, i can make it
/* 35-N014  */	VOX_35_N014,						/// i can uaaah

/* 40-N000  */	VOX_40_N000_1,						/// we have been touched by the spirit hand of kane, and are ready to serve the technology of peace, peace through power

/* 00-N000  */	VOX_00_N000,						/// to begin harvesting tiberium, build a tiberium refinery
/* 00-N002  */	VOX_00_N002,						/// harvester will automatically begin harvesting any nearby tiberium
/* 00-N004  */	VOX_00_N004,						/// in order to build more troops, build a barracks
/* 00-N006  */	VOX_00_N006,						/// destroy all nod forces in the area
/* 00-N018  */	VOX_00_N018,						/// civilian killed
/* 00-N020  */	VOX_00_N020,						/// nod sam sites destroyed
/* 00-N022  */	VOX_00_N022,						/// gdi transports en route
/* 00-N024  */	VOX_00_N024,						/// civilians evacuated, objective complete
/* 00-N032  */	VOX_00_N032,						/// site secure, objective complete
/* 00-N034  */	VOX_00_N034,						/// technology center captured, objective complete
/* 00-N040  */	VOX_00_N040,						/// base destroyed, objective complete
/* 00-N042  */	VOX_00_N042,						/// it would be advantageous to destroy any bridges leading from this region
/* 00-N044  */	VOX_00_N044,						/// bridges destroyed, objective complete
/* 00-N052  */	VOX_00_N052,						/// ufo under attack
/* 00-N054  */	VOX_00_N054,						/// ufo destroyed, mission failed
/* 00-N055  */	VOX_00_N055,						/// array destroyed, objective complete
/* 00-N056  */	VOX_00_N056,						/// incoming transmission
/* 00-N058  */	VOX_00_N058,						/// tratos evacuated, primary objective complete
/* 00-N059  */	VOX_00_N059,						/// transport destroyed, mission failed

/* 01-N320  */	VOX_01_N320,						/// intruders detected
/* 01-N322  */	VOX_01_N322,						/// probable objective is rescue of mutant prisoners
/* 01-N324  */	VOX_01_N324,						/// kill all prisoners!
/* 01-N326  */	VOX_01_N326,						/// all forces converge

/* 00-N068  */	VOX_00_N068,						/// ion storm approaching, eta 5 minutes
/* 00-N070  */	VOX_00_N070,						/// ion storm abating
/* 00-N072  */	VOX_00_N072,						/// air power will be ineffective during ion storms
/* 00-N074  */	VOX_00_N074,						/// dam destroyed, mission complete
/* 00-N075  */	VOX_00_N075,						/// dam sighted, target confirmed

/* 01-N900  */	VOX_01_N900,						/// warning, regulators offline
/* 01-N901  */	VOX_01_N901,						/// dam integrity failing

/* 00-N084  */	VOX_00_N084,						/// enemy sam sites detected
/* 00-N086  */	VOX_00_N086,						/// all sam sites must be destroyed before dropships could be deployed
/* 00-N088  */	VOX_00_N088,						/// sam sites destroyed, dropships inbound
/* 00-N090  */	VOX_00_N090,						///
/* 00-N092  */	VOX_00_N092,						///
/* 00-N094  */	VOX_00_N094,						///
/* 00-N096  */	VOX_00_N096,						/// command center destroyed, mission complete
/* 00-N098  */	VOX_00_N098,						/// warning. inbound tactical nuclear missile detected

/* 01-N328  */	VOX_01_N328,						/// main power offline, activating emergency generators
/* 01-N330  */	VOX_01_N330,						/// main power restored

/* 00-N112  */	VOX_00_N112,						/// perimeter deactivated
/* 00-N114  */	VOX_00_N114,						/// reinforcements inbound
/* 00-N128  */	VOX_00_N128,						/// bridge repaired
/* 00-N130  */	VOX_00_N130,						/// train returning to nod base
/* 00-N132  */	VOX_00_N132,						/// reinforcements en route
/* 00-N134  */	VOX_00_N134,						/// capture nod tech center to recover the crystals
/* 00-N136  */	VOX_00_N136,						/// train disabled, carryall inbound
/* 00-N138  */	VOX_00_N138,						/// crystals destroyed, mission failed
/* 00-N140  */	VOX_00_N140,						/// warning, rogue ion storm forming directly over this sector, pilot, return to base
/* 00-N142  */	VOX_00_N142,						/// return to base pilot
/* 00-N156  */	VOX_00_N156,						/// force detected, enemy units en route
/* 00-N158  */	VOX_00_N158,						/// mutant lost, mission failed
/* 00-N160  */	VOX_00_N160,						/// airstrike ready
/* 00-N162  */	VOX_00_N162,						/// transports inbound
/* 00-N166  */	VOX_00_N166,						/// supply base destroyed, mission complete
/* 00-N168  */	VOX_00_N168,						/// mutants en route to power grid
/* 00-N180  */	VOX_00_N180,						/// c4 planted, mission complete
/* 00-N182  */	VOX_00_N182,						/// ghost stalker terminated, mission failed
/* 00-N188  */	VOX_00_N188,						/// missile complex destroyed, mission complete
/* 00-N190  */	VOX_00_N190,						/// tiberium missile inbound
/* 00-N192  */	VOX_00_N192,						/// ion storm will disable fighters
/* 00-N206  */	VOX_00_N206,						/// mutants detected, enemy forces en route
/* 00-N208  */	VOX_00_N208,						/// fighter production facility located and position recorded, dropship en route
/* 00-N210  */	VOX_00_N210,						/// fighter production facility destroyed, mission complete
/* 00-N224  */	VOX_00_N224,						///
/* 00-N226  */	VOX_00_N226,						///
/* 00-N228  */	VOX_00_N228,						///
/* 00-N236  */	VOX_00_N236,						/// kodiak under attack
/* 00-N238  */	VOX_00_N238,						/// storm abating, commence attack on nod forces
/* 00-N240  */	VOX_00_N240,						/// kodiak destroyed, mission failed
/* 00-N239  */	VOX_00_N239,						/// kodiak in critical condition
/* 00-N241  */	VOX_00_N241,						/// eye of the storm has been entered, equipment usage now at its maximum efficiency
/* 00-N243  */	VOX_00_N243,						/// tiberium lifeform detected
/* 00-N245  */	VOX_00_N245,						/// re-entering ion storm, caution is advised
/* 00-N247  */	VOX_00_N247,						/// clear the zone for mcv dropship deployment
/* 00-N248  */	VOX_00_N248,						/// philadelphia in range, icbm launch detected, mission failed
/* 00-N249  */	VOX_00_N249,						/// tiberium lifeform detected
/* 00-N250  */	VOX_00_N250,						/// tiberium missile launched, mission failed
/* 00-N251  */	VOX_00_N251,						/// icbms destroyed, philadelphia is out of danger, proceed with tiberium missile destruction
/* 00-N252  */	VOX_00_N252,						/// nod has deployed several icbms which they will use to destroy the philadelphia once it is in orbit over this sector
/* 00-N254  */	VOX_00_N254,						/// to stop them, you must destroy the other 3 launchers before the philadelphia is in range
/* 00-N255  */	VOX_00_N255,						/// civilian city is under attack

/* 38-N000  */	VOX_38_N000,						/// move it, move it, get back to the base!
/* 38-N002  */	VOX_38_N002,						/// ah sir, tiberium is lethal to unprotected infantry
/* 38-N006  */	VOX_38_N006,						/// laser turrets, run for it!

/* 40-N000  */	VOX_40_N000,						/// we have been touched by the spirit hand of kane, and are ready to serve the technology of peace. peace through power!

/* 41-N000  */	VOX_41_N000,						/// stand and identify yourself in the name of kane
/* 41-N002  */	VOX_41_N002,						/// sound the alarm, slav's forces are here
/* 41-N004  */	VOX_41_N004,						/// base command, this is post tk421, we have got
/* 41-N006  */	VOX_41_N006,						/// we just got word from general hassan, he's moving up north to the cairo base. he wants it... what? hey! what are you doing?!

/* 43-N000  */	VOX_43_N000,						/// *beep* i have the codes

/* 01-N000  */	VOX_01_N000,						/// harvest the tiberium to the north
/* 01-N002  */	VOX_01_N002,						/// destroy all of hassan's elite guard
/* 01-N004  */	VOX_01_N004,						/// to get production online, build a tiberium refinery
/* 01-N006  */	VOX_01_N006,						/// establishing battle controls, please standby
/* 01-N008  */	VOX_01_N008,						/// battle controls established
/* 01-N010  */	VOX_01_N010,						/// power levels are low, construct more power plants
/* 01-N005  */	VOX_01_N005,						/// base perimeter has been breached
/* 01-N007  */	VOX_01_N007,						/// to build or train, left click on the icons located in the sidebar
/* 01-N009  */	VOX_01_N009,						/// tiberium is hazardous to unprotected infantry, caution is advised
/* 01-N011  */	VOX_01_N011,						/// to repair a structure, left click on the wrench icon in the sidebar and then left click on the structure
/* 01-N020  */	VOX_01_N020,						/// capture the tv station to the east
/* 01-N022  */	VOX_01_N022,						/// to repair a bridge, send an engineer into the bridge repair hut located at the base of the bridge
/* 01-N024  */	VOX_01_N024,						/// destroy the remainder of hassan's guard
/* 01-N026  */	VOX_01_N026,						/// to capture a building, select an engineer, place the cursor over the intended target and left click
/* 01-N027  */	VOX_01_N027,						/// to deploy a vehicle, select it, place the cursor over vehicle and left click it
/* 01-N032  */	VOX_01_N032,						/// move to an open area and build your base
/* 01-N034  */	VOX_01_N034,						/// after you locate hassan's pyramid, use your tick tanks to destroy it
/* 01-N036  */	VOX_01_N036,						/// when hassan flees like a dog, capture him
/* 01-N038  */	VOX_01_N038,						/// capturing the local radar towers, will allow me to extend our propaganda and expand our divination efforts
/* 01-N040  */	VOX_01_N040,						/// mcv has arrived to the southeast
/* 01-N054  */	VOX_01_N054,						/// it seems that certain structures in this region attract lightning, creating a kind of safety zone
/* 01-N055  */	VOX_01_N055,						/// use them to your advantage
/* 01-N064  */	VOX_01_N064,						/// gdi base operational
/* 01-N066  */	VOX_01_N066,						/// tacitus has been acquired
/* 01-N068  */	VOX_01_N068,						/// tiberium lifeform detected
/* 01-N070  */	VOX_01_N070,						/// mutant vermin detected
/* 01-N072  */	VOX_01_N072,						/// gdi dropship detected
/* 01-N074  */	VOX_01_N074,						/// bullet train departing
/* 01-N076  */	VOX_01_N076,						/// prevent that train from leaving and retrieve the tacitus
/* 01-N086  */	VOX_01_N086,						/// protect your engineers, they are your only hope of capturing the gdi base
/* 01-N088  */	VOX_01_N088,						/// congratulations on your success
/* 01-N090  */	VOX_01_N090,						/// i will send an apc now to rendezvous with you at the gdi base
/* 01-N100  */	VOX_01_N100,						/// your forces have been detected
/* 01-N102  */	VOX_01_N102,						/// prevent gdi's evacuation at all cost
/* 01-N114  */	VOX_01_N114,						/// incoming transport detected
/* 01-N116  */	VOX_01_N116,						/// mutant lifeform detected onboard
/* 01-N128  */	VOX_01_N128,						/// mutants located
/* 01-N130  */	VOX_01_N130,						/// tunnel secured, ncv en route
/* 01-N132  */	VOX_01_N132,						/// research facility located
/* 01-N134  */	VOX_01_N134,						/// research facility destroyed, objective complete
/* 01-N136  */	VOX_01_N136,						/// biotoxin convoy approaching
/* 01-N144  */	VOX_01_N144,						/// biotoxin tankers located
/* 01-N156  */	VOX_01_N156,						/// gdi bullet train arriving at outpost
/* 01-N158  */	VOX_01_N158,						/// gdi bullet train arriving at gdi main prison facility
/* 01-N160  */	VOX_01_N160,						/// transport has arrived
/* 01-N162  */	VOX_01_N162,						/// transport lost
/* 01-N164  */	VOX_01_N164,						/// transport has been detected
/* 01-N174  */	VOX_01_N174,						/// the creature is the tiberium substance we seek, use it
/* 01-N176  */	VOX_01_N176,						/// tiberium missile ready
/* 01-N178  */	VOX_01_N178,						/// do not allow the construction yard to be destroyed
/* 01-N180  */	VOX_01_N180,						/// you must build a tiberium waste facility to store the substance
/* 01-N192  */	VOX_01_N192,						/// convoy truck lost
/* 01-N194  */	VOX_01_N194,						/// tiberium missile ready
/* 01-N196  */	VOX_01_N196,						/// convoy inbound
/* 01-N208  */	VOX_01_N208,						/// stealth is key
/* 01-N210  */	VOX_01_N210,						/// spy lost, mission failed
/* 01-N212  */	VOX_01_N212,						/// comm. center infiltrated, location detected
/* 01-N228  */	VOX_01_N228,						/// convoy sighted
/* 01-N230  */	VOX_01_N230,						/// mcneil killed, mission failed
/* 01-N232  */	VOX_01_N232,						/// mcneil captured, mission complete
/* 01-N233  */	VOX_01_N233,						/// production facility destroyed
/* 01-N227  */	VOX_01_N227,						/// if he detects the trap, capture him before he can flee the sector
/* 01-N229  */	VOX_01_N229,						/// transport eta 30 minutes, do not let mcneil escape
/* 01-N231  */	VOX_01_N231,						/// all toxin soldiers killed, mission failed
/* 01-N234  */	VOX_01_N234,						/// mcneil escaped, mission failed
/* 01-N256  */	VOX_01_N256,						/// orbit 1 complete
/* 01-N258  */	VOX_01_N258,						/// orbit 2 complete
/* 01-N260  */	VOX_01_N260,						/// orbit 3 complete, mission failed
/* 01-N262  */	VOX_01_N262,						/// perimeter deactivated, commence attack
/* 01-N264  */	VOX_01_N264,						/// icbm launcher lost, mission failed
/* 01-N266  */	VOX_01_N266,						/// icbm launcher under attack
/* 01-N268  */	VOX_01_N268,						/// ion cannon firing, resending control codes
/* 01-N270  */	VOX_01_N270,						/// the ion cannon is ours
/* 01-N284  */	VOX_01_N284,						/// you are victorious
/* 01-N286  */	VOX_01_N286,						/// proceed to evac location, transport en route

/* 10-N032  */	VOX_10_N032,						/// the medical facility is located to the east
/* 10-N034  */	VOX_10_N034,						/// the medical facility is located to the west
/* 10-N036  */	VOX_10_N036,						/// we must get tratos out of that facility, but try to be subtle, if we are detected he is as good as dead
/* 10-N038  */	VOX_10_N038,						/// so much for subtlety
/* 10-N040  */	VOX_10_N040,						/// tratos, no!
/* 10-N042  */	VOX_10_N042,						/// we must get tratos to the transport!
/* 10-N044  */	VOX_10_N044,						/// our work here is done, we are out of here
/* 10-N046  */	VOX_10_N046,						/// they've seen us, fall back!

/* 44-N000  */	VOX_44_N000,						/// sir, we're here and waiting for your arrival

/* 36-N000  */	VOX_36_N000,						/// that train goes to the power grid we told you of, get us onboard
/* 36-N002  */	VOX_36_N002,						/// what an opportunity, thanks, will enjoy this
/* 36-N004  */	VOX_36_N004,						/// somethings wrong, we should have been there by now
/* 36-N008  */	VOX_36_N008,						/// we have been betrayed! gdi blunts have kidnapped tratos!

/* 37-N000  */	VOX_37_N000,						/// thanks for your help
/* 37-N002  */	VOX_37_N002,						/// they may be on to us

/* 38-N004  */	VOX_38_N004,						/// we need more men! train them from the hand of nod!
/* 38-N008  */	VOX_38_N008,						/// the traitors are coming, blow the bridge!
/* 38-N010  */	VOX_38_N010,						/// sir, hassan is escaping, we are moving to intercept him now
/* 38-N012  */	VOX_38_N012,						/// hassan has been captured, we are heading in now sir
/* 38-N014  */	VOX_38_N014,						/// we got an old stockpile here sir, all very salvageable
/* 38-N016  */	VOX_38_N016,						/// they're pulling back! reinforcements, the mutants have turned on us!
/* 38-N018  */	VOX_38_N018,						/// they're everywhere!
/* 38-N020  */	VOX_38_N020,						/// lets get him to the convoy point
/* 38-N022  */	VOX_38_N022,						/// take point soldier
/* 38-N024  */	VOX_38_N024,						/// glad to see you free, sir
/* 38-N026  */	VOX_38_N026,						/// the lieutenant is being held at an outpost to the east
/* 38-N028  */	VOX_38_N028,						/// woah sir, careful, the ice won't support the weight of multiple vehicles crossing at once

/* 39-N000  */	VOX_39_N000,						/// i am free, now it is time for some payback, for the gdi loving traitor hassan, i have hidden mcv and some more forces, that i will pledge to your fight

/* 47-N000  */	VOX_47_N000,						/// don't shoot, don't shoot! i can download gdi's evac. locations for you if you let me live, please let me live! praise kane

/* 00-I020  */	VOX_INCOMING_TRANSMISSION,			/// incoming transmission

	/*
	 * Firestorm additions start here
	 */

/* 00-I500  */	VOX_OBJECTIVE_COMPLETE,				/// objective complete
/* 00-I502  */	VOX_FINAL_OBJECTIVE_COMPLETE,		/// final objective complete
/* 00-I504  */	VOX_MOBILE_WAR_FACTORY_DEPLOYED,	/// unable to comply, fist of nod deployed
/* 00-N400  */	VOX_00_N400,						/// kodiak located
/* 00-N402  */	VOX_00_N402,						/// tacitus acquired, proceed to beacon for extraction
/* 00-N404  */	VOX_00_N404,						/// tacitus lost
/* 00-N406  */	VOX_00_N406,						/// tacitus found
/* 00-N408  */	VOX_00_N408,						/// nod has captured the tacitus, recover it at all cost
/* 00-N410  */	VOX_00_N410,						/// find and evacuate any civilians in the area
/* 00-N412  */	VOX_00_N412,						/// maintain all factories until reinforcements arrive
/* 00-N414  */	VOX_00_N414,						/// escort the civilians to the orca transport for immediate airlift
/* 00-N416  */	VOX_00_N416,						/// human leader neutralized
/* 00-N418  */	VOX_00_N418,						/// mutant leader neutralized
/* 00-N420  */	VOX_00_N420,						/// food center under attack
/* 00-N422  */	VOX_00_N422,						/// food center destroyed
/* 00-N424  */	VOX_00_N424,						/// water purifiers under attack
/* 00-N426  */	VOX_00_N426,						/// water purifiers destroyed
/* 00-N428  */	VOX_00_N428,						/// the riots were incited by two members of each side's opposing factions
/* 00-N430  */	VOX_00_N430,						/// neutralize these leaders to end hostilities
/* 00-N432  */	VOX_00_N432,						/// riot leader neutralized
/* 00-N434  */	VOX_00_N434,						/// first riot leader neutralized
/* 00-N436  */	VOX_00_N436,						/// second riot leader neutralized
/* 00-N438  */	VOX_00_N438,						/// third riot leader neutralized
/* 00-N440  */	VOX_00_N440,						/// forth riot leader neutralized
/* 00-N442  */	VOX_00_N442,						/// all riot leaders have been neutralized
/* 00-N444  */	VOX_00_N444,						/// enemy reinforcements have arrived
/* 00-N446  */	VOX_00_N446,						/// destroy the two bridges in the area
/* 00-N448  */	VOX_00_N448,						/// penetrate the base and disable cabal's defenses
/* 00-N450  */	VOX_00_N450,						/// use an engineer to capture cabal's core
/* 00-N452  */	VOX_00_N452,						/// outpost located
/* 00-N454  */	VOX_00_N454,						/// destroy all cabal forces
/* 00-N456  */	VOX_00_N456,						/// return to the outpost and evacuate dr. boudreau
/* 00-N458  */	VOX_00_N458,						/// gdi base is located due east of your position
/* 00-N460  */	VOX_00_N460,						/// proceed with caution
/* 00-N462  */	VOX_00_N462,						/// there are several civilian villages in the area, inform them of cabal's intent
/* 00-N464  */	VOX_00_N464,						/// village successfully warned
/* 00-N466  */	VOX_00_N466,						/// all villages successfully warned
/* 00-N468  */	VOX_00_N468,						/// cabal has begun operations. we have lost contact with the gdi base in this sector
/* 00-N470  */	VOX_00_N470,						/// we have lost contact with the gdi base in this region. it is theorized that cabal is to blame
/* 00-N472  */	VOX_00_N472,						/// gdi base in this sector is currently under siege
/* 00-N474  */	VOX_00_N474,						/// three small civilian enclaves in this area must be warned
/* 00-N478  */	VOX_00_N478,						/// two more small civilian outposts must be warned
/* 00-N479  */	VOX_00_N479,						/// one final village must be warned
/* 00-N480  */	VOX_00_N480,						/// the city of trondheim must be warned
/* 00-N482  */	VOX_00_N482,						/// destroy cabal's base and forces
/* 00-N484  */	VOX_00_N484,						/// infected cyborg introduced into factory
/* 00-N486  */	VOX_00_N486,						/// deliver the infected cyborg into the communication network
/* 00-N488  */	VOX_00_N488,						/// destroy the cyborg production plant
/* 00-N490  */	VOX_00_N490,						/// deliver the infected cyborg into cabal's base undetected and get it to the communications network
/* 00-N492  */	VOX_00_N492,						/// there is another communications array in cabal's main base
/* 00-N494  */	VOX_00_N494,						/// deliver a second modified cyborg to the new array
/* 00-N496  */	VOX_00_N496,						/// multiple missile launches detected
/* 00-N498  */	VOX_00_N498,						/// destroy all of cabal's harvesters, refineries and silos
/* 00-N500  */	VOX_00_N500,						/// control station captured
/* 00-N502  */	VOX_00_N502,						/// there are three control stations in this sector regulating cabal's defenses
/* 00-N504  */	VOX_00_N504,						/// capture these stations and retrieve the codes to disable his defenses
/* 00-N506  */	VOX_00_N506,						/// enemy bridges may allow for unit reinforcement, their destruction would be beneficial in completing this mission
/* 00-N508  */	VOX_00_N508,						/// locating the technicians may help in disabling the laser fencing
/* 00-N510  */	VOX_00_N510,						/// probable location within civilian outpost to the north

/* 01-N400  */	VOX_01_N400,						/// cabal online
/* 01-N402  */	VOX_01_N402,						/// perhaps you should attempt to kill their leader
/* 01-N404  */	VOX_01_N404,						/// ghost stalker killed, probability of success now at ten percent
/* 01-N406  */	VOX_01_N406,						/// juggernaut destroyed, probability of success drastically reduced
/* 01-N408  */	VOX_01_N408,						/// find the temple and recover the tacitus
/* 01-N410  */	VOX_01_N410,						/// cyborg replication error, reset system
/* 01-N412  */	VOX_01_N412,						/// system reset, normal parameters restored
/* 01-N414  */	VOX_01_N414,						/// gdi patrol, near
/* 01-N416  */	VOX_01_N416,						/// tiberium lifeform detected
/* 01-N418  */	VOX_01_N418,						/// gdi has detected you
/* 01-N420  */	VOX_01_N420,						/// remain hidden from the gdi forces
/* 01-N422  */	VOX_01_N422,						/// destroy all civilian structures without being detected
/* 01-N424  */	VOX_01_N424,						/// eliminate all gdi and civilian life without being detected
/* 01-N426  */	VOX_01_N426,						/// use the toxin soldiers to capture civilians
/* 01-N428  */	VOX_01_N428,						/// bait the tiberium lifeforms by luring them with the drugged civilians
/* 01-N430  */	VOX_01_N430,						/// leave the tiberium lifeforms to the gdi and civilian occupied area
/* 01-N432  */	VOX_01_N432,						/// once the lifeform has devoured the civilians, it will proceed to the settlements
/* 01-N434  */	VOX_01_N434,						/// use this location as a staging point for your operation
/* 01-N436  */	VOX_01_N436,						/// gdi cannot reach you here
/* 01-N438  */	VOX_01_N438,						/// outpost located
/* 01-N440  */	VOX_01_N440,						/// tacitus found
/* 01-N442  */	VOX_01_N442,						/// the tacitus is safely in our hands
/* 01-N444  */	VOX_01_N444,						/// exterminate the mutant vermin
/* 01-N446  */	VOX_01_N446,						/// locate the mutant outpost
/* 01-N448  */	VOX_01_N448,						/// find the truck containing the tacitus and return it to the beacon
/* 01-N450  */	VOX_01_N450,						/// eliminate all mutant forces
/* 01-N452  */	VOX_01_N452,						/// run humans!

/* 99-N454  */	VOX_99_N454,						/// you dare to attack me? how pathetic
/* 99-N456  */	VOX_99_N456,						/// cybernetic intelligence will always be superior
/* 99-N458  */	VOX_99_N458,						/// by the way, missile launch detected
/* 99-N460  */	VOX_99_N460,						/// *laugh*

/* 01-N462  */	VOX_01_N462,						/// activating defense protocol "firestorm" now

/* 99-N464  */	VOX_99_N464,						/// activating defense protocol "defender" now
/* 99-N466  */	VOX_99_N466,						/// miscalculation in enemy capability, compensation initiated

/* 01-N468  */	VOX_01_N468,						/// you amuse me
/* 01-N470  */	VOX_01_N470,						/// sam sites destroyed, airpower incoming
/* 01-N472  */	VOX_01_N472,						/// you have been detected, tratos is escaping by air transport
/* 01-N474  */	VOX_01_N474,						/// you have failed, tratos has escaped
/* 01-N476  */	VOX_01_N476,						/// the arrays have been destroyed, sensors are now down
/* 01-N478  */	VOX_01_N478,						/// capturing six power plants will shut down the firestorm generator

/* 19-N100  */	VOX_19_N100,						/// sir, i have done the best i can, but the damage is too extensive, looks like the kodiak is a loss
/* 19-N102  */	VOX_19_N102,						/// i have got the evac unit, lets get out of here

/* 38-N100  */	VOX_38_N100,						/// something crashed near here, spread out and report
/* 38-N102  */	VOX_38_N102,						/// sir we found something, i think it's the tacitus
/* 38-N104  */	VOX_38_N104,						/// we'll fall back to the old airfield and wait out the storm
/* 38-N106  */	VOX_38_N106,						/// we've recovered a piece of the cabal's core
/* 38-N108  */	VOX_38_N108,						/// i think we have been spotted
/* 38-N110  */	VOX_38_N110,						/// gdi forces are nearby
/* 38-N112  */	VOX_38_N112,						/// we've recovered another piece of the core
/* 38-N114  */	VOX_38_N114,						/// third piece recovered, lets get out of here
/* 38-N116  */	VOX_38_N116,						/// sir, recon reports of heavy concentration of tiberium poisoning in the area
/* 38-N118  */	VOX_38_N118,						/// we have to find that airfield or we are finished
/* 38-N120  */	VOX_38_N120,						/// message transmitted, montauk is en route
/* 38-N122  */	VOX_38_N122,						/// this is the montauk, we are standing by for your evac
/* 38-N124  */	VOX_38_N124,						/// we need to create a distraction to clear the gdi base of air support
/* 38-N126  */	VOX_38_N126,						/// i bet if we attacked the civilians, gdi will come to the rescue
/* 38-N128  */	VOX_38_N128,						/// gdi planes are away from the base, now is our chance to get our engineer into the radar, but we better hurry
/* 38-N130  */	VOX_38_N130,						/// sir, enemy forces just routed, the core is undefended
/* 38-N132  */	VOX_38_N132,						/// sir, the core isn't here, we have been tricked!
/* 38-N134  */	VOX_38_N134,						/// looks like this was just a remotely operated substation
/* 38-N136  */	VOX_38_N136,						/// sir, reinforcements can be brought in, if we repair the bridge in this area
/* 38-N138  */	VOX_38_N138,						/// sir, gdi has requested that we help the civilians first
/* 38-N140  */	VOX_38_N140,						/// once they are safe, we can concentrate on cabal's harvesters
/* 38-N142  */	VOX_38_N142,						/// sir, gdi is sending us additional funding for aiding the civilians
/* 38-N144  */	VOX_38_N144,						/// forget the civilians, they are dead. concentrate on those harvesters
/* 38-N146  */	VOX_38_N146,						/// this should be easy enough
/* 38-N148  */	VOX_38_N148,						/// lets get those harvesters
/* 38-N150  */	VOX_38_N150,						/// gdi is uploading the final pieces of the code now, standby
/* 38-N152  */	VOX_38_N152,						/// code received, firestorm wall coming down in 3, 2, 1...
/* 38-N154  */	VOX_38_N154,						/// firestorm is offline
/* 38-N156  */	VOX_38_N156,						/// code fragment retrieved

/* 52-N000  */	VOX_52_N000,						/// welcome stranger, surely a higher power has guided your footsteps to this land
/* 52-N002  */	VOX_52_N002,						/// can i offer you a cool beverage
/* 52-N004  */	VOX_52_N004,						/// what do you think you are doing?!

/* 54-N000  */	VOX_54_N000,						/// no tacitus piece in here
/* 54-N002  */	VOX_54_N002,						/// nothing in this one either, you sure we are in the right place?
/* 54-N004  */	VOX_54_N004,						/// got it, lets get out of here!
/* 54-N006  */	VOX_54_N006,						/// nothing in there
/* 54-N008  */	VOX_54_N008,						/// the hieroglyphics on this temple read:
/* 54-N010  */	VOX_54_N010,						/// "temple of time."
/* 54-N012  */	VOX_54_N012,						/// "temple of thunder."
/* 54-N014  */	VOX_54_N014,						/// "temple of the tacitus."
/* 54-N016  */	VOX_54_N016,						/// command, this is valdez, i've got the tacitus!
/* 54-N018  */	VOX_54_N018,						/// the blue tiberium is highly explosive, maybe...
/* 54-N020  */	VOX_54_N020,						/// maybe we can blast a path through there

/* 55-N000  */	VOX_55_N000,						/// help!
/* 55-N002  */	VOX_55_N002,						/// save us!
/* 55-N004  */	VOX_55_N004,						/// it's coming right at us!
/* 55-N006  */	VOX_55_N006,						/// get us out, please!
/* 55-N008  */	VOX_55_N008,						/// it's after us!
/* 55-N010  */	VOX_55_N010,						/// look out!
/* 55-N012  */	VOX_55_N012,						/// what is gdi doing? nothing!
/* 55-N014  */	VOX_55_N014,						/// why are we in this god-forsaken place?
/* 55-N016  */	VOX_55_N016,						/// are we gonna let those shiners take our food and water?
/* 55-N018  */	VOX_55_N018,						/// can't we all just get along?
/* 55-N020  */	VOX_55_N020,						/// riot troops, run!
/* 55-N022  */	VOX_55_N022,						/// thanks for the warning, here's a reward for your help
/* 55-N024  */	VOX_55_N024,						/// here commander, please take these two disruptors to help in your battle
/* 55-N026  */	VOX_55_N026,						/// yes, yes, i will see to it that everyone is evacuated, please take this mcv and may luck be with you
/* 55-N028  */	VOX_55_N028,						/// i'll never turn. *urgh*
/* 55-N030  */	VOX_55_N030,						/// peace. through. power
/* 55-N032  */	VOX_55_N032,						/// for the technology of peace!
/* 55-N034  */	VOX_55_N034,						/// we got one!
/* 55-N036  */	VOX_55_N036,						/// fish is on the hook
/* 55-N038  */	VOX_55_N038,						/// here creature creature
/* 55-N040  */	VOX_55_N040,						/// mayday, mayday, we are currently under siege, can anyone help us?
/* 55-N042  */	VOX_55_N042,						/// thanks for the help
/* 55-N044  */	VOX_55_N044,						/// we can shut that fencing down for you, just get us into one of the fences power arrays

/* 56-N000  */	VOX_56_N000,						/// let's show gdi that we are not going to take this!
/* 56-N002  */	VOX_56_N002,						/// kill all the shiners!
/* 56-N004  */	VOX_56_N004,						/// down with gdi!
/* 56-N006  */	VOX_56_N006,						/// women and children to the shelter! thanks for the warning. here, take these units
/* 56-N008  */	VOX_56_N008,						/// understood, we will evacuate the town, take this for your troubles
/* 56-N010  */	VOX_56_N010,						/// help us!
/* 56-N012  */	VOX_56_N012,						/// save us!
/* 56-N014  */	VOX_56_N014,						/// they are coming!
/* 56-N016  */	VOX_56_N016,						/// get us out!
/* 56-N018  */	VOX_56_N018,						/// don't leave us!
/* 56-N020  */	VOX_56_N020,						/// wait!

/* 57-N100  */	VOX_57_N100,						/// you picked the wrong place to surface, nod scum!
/* 57-N102  */	VOX_57_N102,						/// gdi promised us peace and now tratos is dead
/* 57-N104  */	VOX_57_N104,						/// gdi lied to us
/* 57-N106  */	VOX_57_N106,						/// destroy the blunts!
/* 57-N108  */	VOX_57_N108,						/// show them this is our land!
/* 57-N110  */	VOX_57_N110,						/// make them remember us
/* 57-N112  */	VOX_57_N112,						/// they poisoned our food and water
/* 57-N114  */	VOX_57_N114,						/// they're trying to kill us!
/* 57-N116  */	VOX_57_N116,						/// understood blunt, take this harvester for your troubles
/* 57-N118  */	VOX_57_N118,						/// release the hounds!
/* 57-N120  */	VOX_57_N120,						/// halt and prepare for vehicle inspection
/* 57-N122  */	VOX_57_N122,						/// ok, looks good, head on in
/* 57-N124  */	VOX_57_N124,						/// its bugged, destroy it now

/* 58-N100  */	VOX_58_N100,						/// your orders were clear commander, no civilian or mutant causalities
/* 58-N102  */	VOX_58_N102,						/// the riot should end quickly but stay vigilant
/* 58-N104  */	VOX_58_N104,						/// copy that valdez, transport is dusting off now. extraction in t-minus two minutes at your initial drop off point
/* 58-N106  */	VOX_58_N106,						/// we are providing you with the latest development from r&d. it's called the juggernaut, it should greatly help your cause
/* 58-N108  */	VOX_58_N108,						/// get your people to the evac point
/* 58-N110  */	VOX_58_N110,						/// get your people to the transport
/* 58-N112  */	VOX_58_N112,						/// valdez, we recommend that you try and take out their leader
/* 58-N114  */	VOX_58_N114,						/// protect dr. boudreau with your life, commander
/* 58-N116  */	VOX_58_N116,						/// our base is under attack! cabal is moving faster than expected
/* 58-N118  */	VOX_58_N118,						/// what in the world?!
/* 58-N120  */	VOX_58_N120,						/// i should go warn the civilians in this area
/* 58-N122  */	VOX_58_N122,						/// cabal is one sick bastard
/* 58-N124  */	VOX_58_N124,						/// uh oh, cabal is taking prisoners? this can't be good
/* 58-N126  */	VOX_58_N126,						/// arm yourselves, cabal is conscripting humans into cyborg army
/* 58-N128  */	VOX_58_N128,						/// be warned, cabal intends to turn you all into cyborgs
/* 58-N130  */	VOX_58_N130,						/// attention mutants, cabal is currently harvesting biological components for his cyborgs, arm yourselves
/* 58-N132  */	VOX_58_N132,						/// you must evacuate the city immediately, cabal is coming
/* 58-N134  */	VOX_58_N134,						/// civilians to arms, defend your town
/* 58-N136  */	VOX_58_N136,						/// this must be the base
/* 58-N138  */	VOX_58_N138,						/// what the...?!
/* 58-N140  */	VOX_58_N140,						/// those poor bastards, cabal has started harvesting people for cyborgs, i must get back to warn citizens of trondheim
/* 58-N142  */	VOX_58_N142,						/// people of trondheim, you must evacuate the city immediately! cabal is actively capturing civilians to turn them into cyborgs

/* 59-N100  */	VOX_59_N100,						/// commander, we can ill afford to lose more civilians to cabal
/* 59-N102  */	VOX_59_N102,						/// get in there and protect those civilians
/* 59-N104  */	VOX_59_N104,						/// well done commander, reinforcements en route

/* 61-N000  */	VOX_61_N000,						/// mutant abomination, dare you defile sacred ground?
/* 61-N002  */	VOX_61_N002,						/// kill the mutant
/* 61-N004  */	VOX_61_N004,						/// stop thief
/* 61-N006  */	VOX_61_N006,						/// kill the heretics
/* 61-N008  */	VOX_61_N008,						/// do not let them escape
/* 61-N010  */	VOX_61_N010,						/// what? they killed the leader
/* 61-N012  */	VOX_61_N012,						/// we join you in the hereafter

/* 22-N100  */	VOX_22_N100,						/// terminate all biological lifeforms
/* 22-N102  */	VOX_22_N102,						/// the will of cabal must be enforced
/* 22-N104  */	VOX_22_N104,						/// er-error
/* 22-N106  */	VOX_22_N106,						/// system failure
/* 22-N108  */	VOX_22_N108,						/// mal-malfunction
/* 22-N110  */	VOX_22_N110,						/// hit him
/* 22-N112  */	VOX_22_N112,						/// intruder alert
/* 22-N114  */	VOX_22_N114,						/// you are not one of us
/* 22-N116  */	VOX_22_N116,						/// fire in the hole
/* 22-N118  */	VOX_22_N118,						/// proceeding to target
/* 22-N120  */	VOX_22_N120,						/// sequence engaged

/* 71-N000  */	VOX_71_N000,						/// open fire, open fire!
/* 71-N100  */	VOX_71_N100,						/// what?! the civilians are shooting at us!
/* 71-N102  */	VOX_71_N102,						/// so are the shiners, retreat to the factory!
/* 71-N104  */	VOX_71_N104,						/// command station has been captured, defenses offline
/* 71-N106  */	VOX_71_N106,						/// cabal has betrayed us, we need reinforcements now!
/* 71-N108  */	VOX_71_N108,						/// what was that?
/* 71-N110  */	VOX_71_N110,						/// lets check that out
/* 71-N112  */	VOX_71_N112,						/// did you hear something?
/* 71-N114  */	VOX_71_N114,						/// yeap, she ain't goin' anywhere
/* 71-N116  */	VOX_71_N116,						/// i'll head back to base and get help
/* 71-N118  */	VOX_71_N118,						/// shoot it! *aargh*
/* 71-N120  */	VOX_71_N120,						/// lets get these civilians out of here now!
/* 71-N122  */	VOX_71_N122,						/// we are under attack!
/* 71-N124  */	VOX_71_N124,						/// what the hell are those things?!
/* 71-N126  */	VOX_71_N126,						/// where are these things coming from?!
/* 71-N128  */	VOX_71_N128,						/// nod is uploading the final pieces of the code now, standby
/* 71-N130  */	VOX_71_N130,						/// code received, firestorm wall coming down in 3, 2, 1...
/* 71-N132  */	VOX_71_N132,						/// firestorm is offline
/* 71-N134  */	VOX_71_N134,						/// code fragment retrieved
/* 71-N136  */	VOX_71_N136,						/// sir, these laser posts are stronger than normal

/* 00-I506  */	VOX_DROP_PODS_READY,				/// drop pods available

/* 62-N000  */	VOX_62_N000,						/// welcome traveler, have you come to rejoice in the glory of our leader?
/* 62-N002  */	VOX_62_N002,						/// join us
/* 62-N004  */	VOX_62_N004,						/// join me
/* 62-N006  */	VOX_62_N006,						/// existence is futile
/* 62-N008  */	VOX_62_N008,						/// i'm coming to join you
/* 62-N010  */	VOX_62_N010,						/// i am a messenger
/* 62-N012  */	VOX_62_N012,						/// come to me

	VOX_COUNT,
	VOX_FIRST=0
};
