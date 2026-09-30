/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once


enum ParticleType {
	PARTICLE_NONE=-1,

	PARTICLE_GAS_CLOUD1,
	PARTICLE_GAS_CLOUD2,
	PARTICLE_FIRE_STREAM,
	PARTICLE_SPARK,
	PARTICLE_FIRESTORM_SPARK,
	PARTICLE_LARGE_GREY_SMOKE,
	PARTICLE_SMALL_GREY_SMOKE,
	PARTICLE_TEST_SMOKE,
	PARTICLE_GAS_CLOUD_D1,
	PARTICLE_GAS_CLOUD_D2,
	PARTICLE_SMALL_RAILGUN_PART,
	PARTICLE_LARGE_RAILGUN_PART,
	PARTICLE_GAS_CLOUD_M1,
	PARTICLE_GAS_CLOUD_M2,
	PARTICLE_WELDING_SPARK,
	PARTICLE_LARGE_SPARK,

	/*
	 * Firestorm additions start here
	 */
	PARTICLE_WEB,
	PARTICLE_WEAK_GAS_CLOUD,
	PARTICLE_WEAK_GAS_CLOUD_D,
	PARTICLE_SMOKE_STACK_PUFF,
	PARTICLE_WEAK_GAS_CLOUD_M2,

	PARTICLE_COUNT,
	PARTICLE_FIRST=0
};


enum ParticleBehaviorType
{
	BEHAVIOR_GAS,
	BEHAVIOR_SMOKE,
	BEHAVIOR_FIRE,
	BEHAVIOR_SPARK,
	BEHAVIOR_RAILGUN,
	BEHAVIOR_WEB,
	BEHAVIOR_WEAKGAS,

	BEHAVIOR_COUNT,
	BEHAVIOR_NONE = -1,
	BEHAVIOR_FIRST = 0
};


enum AttachedParticleType
{
	ATTACHED_PARTICLE_FIRE,
	ATTACHED_PARTICLE_SPARK,
	ATTACHED_PARTICLE_NATURAL,
	ATTACHED_PARTICLE_DAMAGE,
	ATTACHED_PARTICLE_RAILGUN,

	ATTACHED_PARTICLE_COUNT,

	ATTACHED_PARTICLE_FIRST = 0
};
