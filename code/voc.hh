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

/**********************************************************************
**	These are the sound effect digitized sample file names.
*/
enum VocType {
	VOC_NONE=-1,

/* FIRSTRM1 */	VOC_FIRSTRM1,			/// Firestorm defense burning
/* FACBLD1  */	VOC_FACBLD1,			/// <FACTORY GOES ONLINE>
/* ION1     */	VOC_ION1,				/// Ion cannon strike
/* PLSECAN2 */	VOC_PLSECAN2,			/// <PULSE CANNON FIRES>

/* METEOR1  */	VOC_METEOR1,			/// LARGE METEOR
/* METEOR2  */	VOC_METEOR2,			/// SMALL METEOR
/* METHIT1  */	VOC_METHIT1,			/// METEOR HITS GROUND

/* ICBM1    */	VOC_ICBM1,				/// BIG, HUGE, ICBM ROCKET

/* DEDMAN1  */	VOC_DEDMAN1,
/* DEDMAN2  */	VOC_DEDMAN2,
/* DEDMAN3  */	VOC_DEDMAN3,
/* DEDMAN4  */	VOC_DEDMAN4,

/* Notify   */	VOC_NOTIFY,
/* Gun18    */	VOC_GUN18,				/// Civilian gun

/* SSPLASH1 */	VOC_SSPLASH1,			/// <SMALL WATER SPLASH>
/* SSPLASH2 */	VOC_SSPLASH2,			/// <SMALL WATER SPLASH>
/* SSPLASH3 */	VOC_SSPLASH3,			/// <SMALL WATER SPLASH>

/* DSAPING1 */	VOC_DSAPING1,			/// Deployable sensor array ping

/* DEDMAN5  */	VOC_DEDMAN5,

/* ORCAUP1  */	VOC_ORCAUP1,			/// ORCA TAKES OFF
/* ORCADWN1 */	VOC_ORCADWN1,			/// ORCA LANDS

/* DROPUP1  */	VOC_DROPUP1,			/// DROPSHIP TAKES OFF
/* DROPDWN1 */	VOC_DROPDWN1,			/// DROPSHIP LANDS

/* CRMBLE2  */	VOC_CRMBLE2,			/// Building crumbling
/* HOVRMIS1 */	VOC_HOVRMIS1,			/// HOVERMLRS ROCKET FIRE
/* GLNCH4   */	VOC_GLNCH4,				/// RPG launch
/* REPAIR11 */	VOC_REPAIR11,			/// REPAIR VEHICLE
/* OBELPOWR */	VOC_OBELPOWR,			/// obelisk
/* SQUISHY2 */	VOC_SQUISHY2,			/// placeholder for real guy squish
/* SCOLD8   */	VOC_SCOLD8,				/// Scold sound
/* COMMUP1  */	VOC_COMMUP1,			/// COMMUNICATIONS CENTER GOES ONLINE
/* RADARDN1 */	VOC_RADARDN1,			/// placeholder for communication failure
/* PLACE2   */	VOC_PLACE2,				/// PLACE A BUILDING DOWN

/* EXPNEW01 */	VOC_EXPNEW01,			/// <BIG BUILDING EXPLOSION WITH GLASS>
/* EXPNEW02 */	VOC_EXPNEW02,			/// <BIG BUILDING EXPLOSION WITH GLASS>
/* EXPNEW03 */	VOC_EXPNEW03,			/// <BIG BUILDING EXPLOSION WITH GLASS>
/* EXPNEW04 */	VOC_EXPNEW04,			/// <BIG BUILDING EXPLOSION WITH GLASS>
/* EXPNEW05 */	VOC_EXPNEW05,			/// <MEDIUM EXPLOSION FOR VEHICLE OR STRUCTURE>
/* EXPNEW06 */	VOC_EXPNEW06,			/// <MEDIUM EXPLOSION GOOD FOR ALL AND LAND DESTRUCTION>
/* EXPNEW07 */	VOC_EXPNEW07,			/// <MEDIUM EXPLOSION WITH GLASS>
/* EXPNEW08 */	VOC_EXPNEW08,			/// <LG/MD EXPLOSION WITH GLASS>
/* EXPNEW09 */	VOC_EXPNEW09,			/// <MEDIUM EXPLOSION GENERAL>
/* EXPNEW10 */	VOC_EXPNEW10,			/// <MEDIUM EXPLOSION GENERAL AND VEHICLE>
/* EXPNEW11 */	VOC_EXPNEW11,			/// <MEDIUM EXPLOSION WITH GLASS>
/* EXPNEW12 */	VOC_EXPNEW12,			/// <SMALL EXPLOSION GENERAL>
/* EXPNEW13 */	VOC_EXPNEW13,			/// <SMALL EXPLOSION GENERAL>
/* EXPNEW14 */	VOC_EXPNEW14,			/// <SMALL EXPLOSION GENERAL>
/* EXPNEW15 */	VOC_EXPNEW15,			/// <SMALL EXPLOSION GENERAL>

/* CASHTURN */	VOC_CASHTURN,			/// placeholder for cashturn
/* CREDUP1  */	VOC_CREDUP1,			/// CREDIT POSITIVE
/* CREDDWN1 */	VOC_CREDDWN1,			/// CREDIT NEGATIVE

/* GATEDWN1 */	VOC_GATEDWN1,			/// Gate going down
/* GATEUP1  */	VOC_GATEUP1,			/// Gate going up

/* SUBDRIL1 */	VOC_SUBDRIL1,			/// Subterranean drill
/* SONIC4   */	VOC_SONIC4,				/// Sonic weapon fire
/* OBELRAY1 */	VOC_OBELRAY1,			/// Obelisk firing laser
/* 120MMF   */	VOC_120MMF,				/// Artillery sound
/* INFGUN3  */	VOC_INFGUN3,			/// Infantry gun
/* VICER1   */	VOC_VICER1,				/// <TWO VICEROIDS COMBINE>
/* CHAINGN1 */	VOC_CHAINGN1,			/// BUGGY FIRES GUN/APACHE FIRES GUNS
/* CYGUN1   */	VOC_CYGUN1,				/// CYBORG FIRES GUN
/* RKETINF1 */	VOC_RKETINF1,			/// ROCKET INFANTRY FIRE
/* JUMPJET1 */	VOC_JUMPJET1,			/// JUMP JET FIRES GUN
/* ORCAMIS1 */	VOC_ORCAMIS1,			/// ORCA FIGHTER ATTACK
/* SAMSHOT1 */	VOC_SAMSHOT1,			/// SAM SITE MISSILE
/* TSGUN4   */	VOC_TSGUN4,
/* SILENCER */	VOC_SILENCER,			/// Sniper gun
/* 120MMX9  */	VOC_120MMX9,			/// Artillery sound two-shooter
/* BLEEP1   */	VOC_BLEEP1,				/// Generic beep
/* CLICKY1  */	VOC_CLICKY1,			/// Generic click
/* CLOAK5   */	VOC_CLOAK5,				/// Cloaking sound
/* GAMEFRM1 */	VOC_GAMEFRM1,			/// Game forming
/* GOSTGUN1 */	VOC_GOSTGUN1,			/// Ghost talker
/* HEALER1  */	VOC_HEALER1,			/// Healing units
/* MESSAGE1 */	VOC_MESSAGE1,			/// Incoming message

/* ICECRAK1 */	VOC_ICECRAK1,
/* ICECRAK2 */	VOC_ICECRAK2,
/* ICECRAK3 */	VOC_ICECRAK3,

/* MISL1    */	VOC_MISL1,
/* SCRIN5B  */	VOC_SCRIN5B,
/* BIGGGUN1 */	VOC_BIGGGUN1,
/* SLVKGUN1 */	VOC_SLVKGUN1,
/* SQUISH6  */	VOC_SQUISH6,
/* SANDBAG1 */	VOC_SANDBAG1,
/**/       /// VOC_BLANK_1,			// BLANK (index 85) in rules
/* FIEND1   */	VOC_FIEND1,
/* FIEND2   */	VOC_FIEND2,
/* EXPDIRT1 */	VOC_EXPDIRT1,
/* ELECTRO1 */	VOC_ELECTRO1,

/* EXPNEW16 */	VOC_EXPNEW16,
/* EXPNEW17 */	VOC_EXPNEW17,
/* EXPNEW18 */	VOC_EXPNEW18,
/* EXPNEW19 */	VOC_EXPNEW19,

	/// Generic Infantry
/* 15-I000  */	VOC_15_I000,            /// Infantry reporting
/* 15-I002  */	VOC_15_I002,            /// Unit ready!
/* 15-I004  */	VOC_15_I004,            /// Awaiting order
/* 15-I006  */	VOC_15_I006,            /// Sir?
/* 15-I008  */	VOC_15_I008,            /// Sir, yes sir!
/* 15-I010  */	VOC_15_I010,            // Ready
/* 15-I012  */	VOC_15_I012,            /// Yes sir
/* 15-I014  */	VOC_15_I014,            /// Yes sir!
/* 15-I016  */	VOC_15_I016,            /// Orders received
/* 15-I018  */	VOC_15_I018,            /// Moving out
/* 15-I020  */	VOC_15_I020,            /// Advancing
/* 15-I022  */	VOC_15_I022,            /// On my way
/* 15-I024  */	VOC_15_I024,            /// You got it
/* 15-I026  */	VOC_15_I026,            /// No problem
/**/                                    /// VOC_BLANK_2,			// BLANK (index 108) in rules
/**/                                    /// VOC_BLANK_3,			// BLANK (index 109) in rules
/* 15-I032  */	VOC_15_I032,            /// Ready for action

/* FLAMTNK1 */	VOC_FLAMTNK1,			/// Flame tank fire
/* RAILUSE5 */	VOC_RAILUSE5,			/// Heavy mech railgun

	/// Generic Unit
/* 15-I038  */	VOC_15_I038,            /// Standing by
/* 15-I040  */	VOC_15_I040,            /// Yeah
/* 15-I042  */	VOC_15_I042,            /// Orders?
/* 15-I044  */	VOC_15_I044,            /// Load and clear
/* 15-I046  */	VOC_15_I046,            /// I'm on it
/* 15-I048  */	VOC_15_I048,            /// Sir!
/* 15-I050  */	VOC_15_I050,            /// Good as done
/**/                                    /// VOC_BLANK_4,			// BLANK (index 120) in rules
/**/                                    /// VOC_BLANK_5,			// BLANK (index 121) in rules
/* 15-I058  */	VOC_15_I058,            /// I'm taking heavy fire
/* 15-I060  */	VOC_15_I060,            /// Move! Move! Move!
/**/                                    /// VOC_BLANK_6,			// BLANK (index 124) in rules
/* 15-I064  */	VOC_15_I064,            /// MEDIC!

	/// Oxanna
/* 11-I000  */	VOC_11_I000,			// Yes
/* 11-I002  */	VOC_11_I002,			/// Direct me
/* 11-I004  */	VOC_11_I004,			/// Awaiting orders
/* 11-I006  */	VOC_11_I006,			/// I'm ready
/* 11-I008  */	VOC_11_I008,			/// Of course
/* 11-I010  */	VOC_11_I010,			/// Immediately
/* 11-I012  */	VOC_11_I012,			/// Yes!
/* 11-I014  */	VOC_11_I014,			/// For Kane
/* 11-I016  */	VOC_11_I016,			/// They will pay for this
/* 11-I018  */	VOC_11_I018,			/// For the brotherhood

	/// Slavik
/* 12-I000  */	VOC_12_I000,			/// Yes CABAL?
/* 12-I002  */	VOC_12_I002,			/// Where to?
/* 12-I004  */	VOC_12_I004,			// Yes
/* 12-I006  */	VOC_12_I006,			// Yes
/* 12-I008  */	VOC_12_I008,			/// For Kane
/* 12-I010  */	VOC_12_I010,			/// I will
/* 12-I012  */	VOC_12_I012,			/// We must find Oxanna
/* 12-I014  */	VOC_12_I014,			/// Leave no enemy standing
/* 12-I016  */	VOC_12_I016,			/// Kill them

	/// Tratos
/* 13-I000  */	VOC_13_I000,			// Huh?
/* 13-I002  */	VOC_13_I002,			/// What?
/* 13-I004  */	VOC_13_I004,			/// Ah
/* 13-I006  */	VOC_13_I006,			/// Lead me
/* 13-I008  */	VOC_13_I008,			/// Arrows from the sky
/* 13-I010  */	VOC_13_I010,			/// Green becomes brown
/* 13-I012  */	VOC_13_I012,			/// Teh
/* 13-I014  */	VOC_13_I014,			// Yes
/* 13-I016  */	VOC_13_I016,			/// Be careful
/* 13-I018  */	VOC_13_I018,			/// Nod is everywhere
/* 13-I020  */	VOC_13_I020,			/// Where's the Tacitus?

	/// Ghost Stalker
/* 14-I000  */	VOC_14_I000,			/// Yes?
/* 14-I002  */	VOC_14_I002,			/// Over here
/* 14-I004  */	VOC_14_I004,			/// Give me a target
/* WRONG1   */	VOC_WRONG1,				/// Build queue full
/* 14-I008  */	VOC_14_I008,			/// It will be done
/* 14-I010  */	VOC_14_I010,			/// Very well
/* 14-I012  */	VOC_14_I012,			/// Any time
/* 14-I014  */	VOC_14_I014,			/// You got it
/* 14-I016  */	VOC_14_I016,			/// There could be trouble

	/// Chameleon Spy
/* 21-I000  */	VOC_21_I000,			/// Hahahah
/* 21-I002  */	VOC_21_I002,			/// Over here
/* 21-I004  */	VOC_21_I004,			/// Sshh
/* KLAX1    */	VOC_KLAX1,				/// Klaxon
/* 27-I002  */	VOC_27_I002,			/// Unit deploy response
/* 21-I010  */	VOC_21_I010,			// Yes
/* 21-I012  */	VOC_21_I012,			/// Excellent
/* HUNTER2  */	VOC_HUNTER2,
/* 21-I016  */	VOC_21_I016,			/// Moving
/* LASTUR1  */	VOC_LASTUR1,
/**/                            /// VOC_BLANK_7,			// BLANK (index 175) in rules
/* 21-I022  */	VOC_21_I022,    /// It's yours

	/// Cyborg
/* 22-I000  */	VOC_22_I000,            /// Input directive
/* 22-I002  */	VOC_22_I002,            /// Comlink open
/**/                                    /// VOC_BLANK_8,			// BLANK (index 179) in rules
/* 22-I006  */	VOC_22_I006,            /// Unit ready
/* 22-I008  */	VOC_22_I008,            /// Affirmative
/* 22-I010  */	VOC_22_I010,            /// By your command
/* 22-I012  */	VOC_22_I012,            /// Target acquired
/* 22-I014  */	VOC_22_I014,            /// Scan initiated
/* 22-I016  */	VOC_22_I016,            /// Proceeding
/* 22-I018  */	VOC_22_I018,            /// Unit engaged
/* 22-I020  */	VOC_22_I020,            // Processing

	/// Cyborg Commando
/* 23-I000  */	VOC_23_I000,			/// Your command
/* 23-I002  */	VOC_23_I002,			/// Standing by
/* 23-I004  */	VOC_23_I004,			/// Directive?
/* 23-I006  */	VOC_23_I006,			/// Status?
/* 23-I008  */	VOC_23_I008,			/// I obey
/* 23-I010  */	VOC_23_I010,			/// Affirmative
/* 23-I012  */	VOC_23_I012,			/// Executing
/* 23-I014  */	VOC_23_I014,			/// Terminated
/* 23-I016  */	VOC_23_I016,			/// Stand clear
/* 23-I018  */	VOC_23_I018,			/// They will know fear
/* 23-I020  */	VOC_23_I020,			/// For the brotherhood
/* 23-I022  */	VOC_23_I022,			/// I can smell their fear

	/// Mutant Hijacker
/* 24-I000  */	VOC_24_I000,			/// Need a ride?
/* 24-I002  */	VOC_24_I002,			/// Sir?
/* 24-I004  */	VOC_24_I004,			/// Yeah?
/* 24-I006  */	VOC_24_I006,			/// What?
/* 24-I008  */	VOC_24_I008,			/// Hot wired
/* 24-I010  */	VOC_24_I010,			/// Hit it
/* 24-I012  */	VOC_24_I012,			/// Four on the floor
/* 24-I014  */	VOC_24_I014,			/// Cool
/* 24-I016  */	VOC_24_I016,			/// Where do you want it
/* 24-I018  */	VOC_24_I018,			/// Going my way?
/* 24-I020  */	VOC_24_I020,			/// No keys, no problem
/* 24-I022  */	VOC_24_I022,			/// Jack em' up
/* 24-I024  */	VOC_24_I024,			/// Always wanted one of these

	/// Banshee
/* 32-I000  */	VOC_32_I000,			/// Affirmative
/* 32-I002  */	VOC_32_I002,			/// Target sighted
/* 32-I004  */	VOC_32_I004,			/// Orders received
/* 32-I006  */	VOC_32_I006,			/// Engaging
/* 32-I008  */	VOC_32_I008,			/// Whoops

	/// Drugged Jake McNeil
/* 09-I000  */	VOC_09_I000,			/// Yes?
/* 09-I002  */	VOC_09_I002,			// OK
/* 09-I004  */	VOC_09_I004,			/// Ooooh
/* 09-I006  */	VOC_09_I006,			/// Aaah

	// Engineer
/* 19-I000  */	VOC_19_I000,            /// Engineering
/* 19-I002  */	VOC_19_I002,            /// Yes sir?
/**/                                    /// VOC_BLANK_9,			// BLANK (index 224) in rules
/* 19-I006  */	VOC_19_I006,            /// Awaiting orders
/**/                                    /// VOC_BLANK_10,			// BLANK (index 226) in rules
/* 19-I010  */	VOC_19_I010,            /// Affirmative
/**/                                    /// VOC_BLANK_11,			// BLANK (index 228) in rules
/**/                                    /// VOC_BLANK_12,			// BLANK (index 229) in rules
/* 19-I016  */	VOC_19_I016,            /// No problem
/* 19-I018  */	VOC_19_I018,            /// I can fix that

	/// Umagon
/* 10-I000  */	VOC_10_I000,			/// Give me a order
/* 10-I002  */	VOC_10_I002,			/// What do you want?
/* 10-I004  */	VOC_10_I004,			/// You talking to me?
/* 10-I006  */	VOC_10_I006,			/// What?
/* 10-I016  */	VOC_10_I016,			/// Stay low
/* 10-I020  */	VOC_10_I020,			// OK
/* 10-I022  */	VOC_10_I022,			/// Already there
/* 10-I024  */	VOC_10_I024,			/// Right between the eyes
/* 10-I026  */	VOC_10_I026,			/// I only need one shot
/* 10-I028  */	VOC_10_I028,			/// This is too easy
/* 10-I030  */	VOC_10_I030,			/// Good as done

/* DEDMAN6  */	VOC_DEDMAN6,

/* DEDGIRL1 */	VOC_DEDGIRL1,
/* DEDGIRL2 */	VOC_DEDGIRL2,
/* DEDGIRL3 */	VOC_DEDGIRL3,
/* DEDGIRL4 */	VOC_DEDGIRL4,

	/// Medic
/* 20-I000  */	VOC_20_I000,			/// Medic reporting
/* 20-I004  */	VOC_20_I004,			/// Yes sir?
/* 20-I006  */	VOC_20_I006,			/// Awaiting orders
/* 20-I008  */	VOC_20_I008,			/// Affirmative
/* 20-I010  */	VOC_20_I010,			/// Acknowledged
/* 20-I012  */	VOC_20_I012,			/// Moving out
/* 20-I016  */	VOC_20_I016,			/// Stat!
/* 20-I018  */	VOC_20_I018,			/// Clear!
/* 20-I020  */	VOC_20_I020,			/// Give me some room!

	/// Generic Unit
/* 25-I000  */	VOC_25_I000,			/// Unit reporting
/* 25-I002  */	VOC_25_I002,			/// Unit ready
/* 25-I004  */	VOC_25_I004,			/// Awaiting orders
/* 25-I006  */	VOC_25_I006,			/// Sir?
/* 25-I012  */	VOC_25_I012,			/// Yes sir?
/* 25-I014  */	VOC_25_I014,			/// Yes sir!
/* 25-I016  */	VOC_25_I016,			/// Orders received
/* 25-I018  */	VOC_25_I018,			/// Moving out
/* 25-I022  */	VOC_25_I022,			/// On my way
/* 25-I024  */	VOC_25_I024,			/// You got it
/* 25-I026  */	VOC_25_I026,			/// No problem

	/// Generic Aircraft
/* 30-I000  */	VOC_30_I000,			/// Pilot reporting
/* 30-I002  */	VOC_30_I002,			// Ready
/* 30-I004  */	VOC_30_I004,			/// Awaiting orders
/* 30-I006  */	VOC_30_I006,			/// Sir?
/* 30-I014  */	VOC_30_I014,			/// Yes sir
/* 30-I016  */	VOC_30_I016,			/// Orders received
/* 30-I018  */	VOC_30_I018,			/// Over and out
/* 30-I022  */	VOC_30_I022,			/// On my way
/* 30-I030  */	VOC_30_I030,			/// Death from above
/* 30-I034  */	VOC_30_I034,			/// Form up
/* 30-I036  */	VOC_30_I036,			/// Away we go

	/// Toxin Soldier
/* 42-I000  */	VOC_42_I000,			/// I'm ready
/* 42-I002  */	VOC_42_I002,			// Yes
/* 42-I004  */	VOC_42_I004,			/// I'm all ears
/* 42-I006  */	VOC_42_I006,			/// Of course
/* 42-I008  */	VOC_42_I008,			/// I think I can be persuaded
/* 42-I010  */	VOC_42_I010,			/// On it
/* 42-I012  */	VOC_42_I012,			/// Knockout

/**/        /// VOC_BOOP,				// NOTE, conflict with FS 60-N100 as that maps to VOC_BOOP in TS

	/*
	 * Firestorm additions start here
	 */

	/// Cyborg Reaper
/* 60-N100  */	VOC_60_N100,			/// System ready
/* 60-N102  */	VOC_60_N102,			/// Instructions?
/* 60-N104  */	VOC_60_N104,			/// Awaiting NavCom
/* 60-N106  */	VOC_60_N106,			/// Moving
/* 60-N108  */	VOC_60_N108,			/// Receiving course
/* 60-N110  */	VOC_60_N110,			/// As ordered
/* 60-N112  */	VOC_60_N112,			/// Exterminate
/* 60-N114  */	VOC_60_N114,			/// Target locked
/* 60-N116  */	VOC_60_N116,			/// Weapons armed

	/// Doctor Boudreau
/* 53-I000  */	VOC_53_I000,			/// What?
/* 53-I002  */	VOC_53_I002,			/// Ready to go
/* 53-I004  */	VOC_53_I004,			/// Shall we go?
/* 53-I006  */	VOC_53_I006,			// Yes
/* 53-I008  */	VOC_53_I008,			/// On my way
/* 53-I010  */	VOC_53_I010,			/// That seems logical
/* 53-I012  */	VOC_53_I012,			/// Oooh

	/// Archaeologist
/* 54-N022  */	VOC_54_N022,			/// Understood
/* 54-N024  */	VOC_54_N024,			/// Going in
/* 54-N026  */	VOC_54_N026,			/// Yes sir
/* 54-N028  */	VOC_54_N028,			/// Moving out
/* 54-N030  */	VOC_54_N030,			/// On my way

	/// Civilian #1
/* 67-N100  */	VOC_67_N100,			/// You talking to me?
/* 67-N102  */	VOC_67_N102,			/// Can I help you?
/* 67-N104  */	VOC_67_N104,			/// Whatever
/* 67-N106  */	VOC_67_N106,			/// I'm goin'
/* 67-N108  */	VOC_67_N108,			/// Out of my way

	/// Civilian #2
/* 68-N100  */	VOC_68_N100,			/// Yeah?
/* 68-N102  */	VOC_68_N102,			// Huh?
/* 68-N104  */	VOC_68_N104,			/// What?
/* 68-N106  */	VOC_68_N106,			/// Sure
/* 68-N108  */	VOC_68_N108,			/// Alright
/* 68-N110  */	VOC_68_N110,			/// Here I go

	/// Civilian #3
/* 69-N100  */	VOC_69_N100,			/// Not meee!
/* 69-N102  */	VOC_69_N102,			/// Oooh
/* 69-N104  */	VOC_69_N104,			/// Yeah?
/* 69-N106  */	VOC_69_N106,			/// Do I gotta'?
/* 69-N108  */	VOC_69_N108,			/// I gotta' walk?
/* 69-N110  */	VOC_69_N110,			/// Are you sure?

	// Technician
/* 70-N000  */	VOC_70_N000,			/// Yes sir
/* 70-N002  */	VOC_70_N002,			/// Need assistance?
/* 70-N004  */	VOC_70_N004,			/// I'm your man!
/* 70-N006  */	VOC_70_N006,			/// Be glad to
/* 70-N008  */	VOC_70_N008,			/// On the job
/* 70-N010  */	VOC_70_N010,			// OK
/* 70-N012  */	VOC_70_N012,			/// Looks like overtime
/* 70-N014  */	VOC_70_N014,			/// Looks like overtime
/* 70-N016  */	VOC_70_N016,			/// Take that!
/* 70-N018  */	VOC_70_N018,			/// Hope I'm covered

/* COREFIR1 */	VOC_COREFIR1,
/* COREUP1  */	VOC_COREUP1,
/* FIREWEB1 */	VOC_FIREWEB1,
/* FLOATMOV */	VOC_FLOATMOV,
/* JUGGER1  */	VOC_JUGGER1,
/* LIMPBOM1 */	VOC_LIMPBOM1,
/* LIMPC3   */	VOC_LIMPC3,
/* LIMPQ3   */	VOC_LIMPQ3,
/* SPIDDIE1 */	VOC_SPIDDIE1,
/* MOBEMP1  */	VOC_MOBEMP1,
/* MSG1     */	VOC_MSG1,
/* OBELMOD1 */	VOC_OBELMOD1,
/* 22-N104  */	VOC_22_N104,
/* 22-N106  */	VOC_22_N106,
/* 22-N108  */	VOC_22_N108,
/* LIMPC4   */	VOC_LIMPC4,
/* LIMPQ4   */	VOC_LIMPQ4,
/* FLOTMOV2 */	VOC_FLOTMOV2,
/* FLOTMOV3 */	VOC_FLOTMOV3,
/* FLOTMOV4 */	VOC_FLOTMOV4,
/* FLOATK1  */	VOC_FLOATK1,
/* OBELCOR3 */	VOC_OBELCOR3,

/* BOOP     */	VOC_BOOP,				/// Stub sound used for all unsigned sound triggers

	VOC_COUNT,
	VOC_FIRST=0
};
