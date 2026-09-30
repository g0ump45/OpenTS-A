/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "missile.h"

#include "_map.h"
#include "cell.h"
#include "coord.h"
#include "face.h"
#include "globals.h"
#include "mouse.h"
#include "velocity.h"


/// <summary>
/// Handles one frame of guided missile flight.
/// This routine is used by the bullet logic to fly a homing projectile. It advances the
/// projectile along its current velocity, swings that velocity toward the target by no more
/// than the allowed turn rate, and flies the missile over the intervening terrain so that it
/// clears hills and bridges before it stoops onto its target.
/// </summary>
/// <param name="coord">The projectile position; advanced to its new position.</param>
/// <param name="velocity">The projectile velocity; steered toward the target.</param>
/// <param name="target_coord">The coordinate to home on, or COORD_NONE to merely level
/// out.</param>
/// <param name="rot">The greatest amount the projectile may turn during this frame.</param>
/// <param name="aircraft">Is the projectile chasing an aircraft?</param>
/// <param name="airburst">Should the projectile detonate in the air rather than stoop?</param>
/// <param name="veryhigh">Should the projectile cruise at extra altitude?</param>
/// <returns>Returns with the distance still to be covered, with the vertical component
/// discounted. A projectile with nothing to home on returns a nominal short distance.</returns>
int Projectile_Motion(Coord & coord, TVelocity3D<double> & velocity, Coord const & target_coord, DirType const & rot, bool aircraft, bool airburst, bool veryhigh)
{
	if (target_coord == COORD_NONE) {
		/*
		 * Nothing to home on -- just level out (0x4200 is the level-out pitch).
		 */
		DirType pitch = velocity.Get_Pitch();
		pitch.Turn(DirType(Dir256(DIR_E + DIR_STEP_128)), rot);
		velocity.Set_Pitch(pitch);
		return(1);
	}

	TVelocity3D<double> frame_velocity(velocity);
	coord = coord + Point3D(frame_velocity.X, frame_velocity.Y, frame_velocity.Z);
	int target_distance = coord.Distance_To(target_coord);
	int horizontal_distance = Point2D(coord).Distance_To(Point2D(target_coord));

	Coord delta = target_coord - coord;

	/*
	 * Declared and then assigned, not copy-initialized: the temporary is built
	 * and block-copied into the local.
	 */
	TVelocity3D<double> target_direction;
	target_direction = TVelocity3D<double>(delta.X, delta.Y, delta.Z);

	DirType desired_yaw = velocity.Get_Yaw();
	desired_yaw.Turn(target_direction.Get_Yaw(), rot);
	velocity.Set_Yaw(desired_yaw);

	DirType desired_pitch = velocity.Get_Pitch();

	if (!aircraft && (airburst || horizontal_distance > ((veryhigh ? 6 : 3) * CELL_LEPTON)) && rot.As_Dir256() > 1) {
		TVelocity3D<double> lookahead_velocity(velocity);
		Coord lookahead_coord = coord + Point3D(lookahead_velocity.X, lookahead_velocity.Y, lookahead_velocity.Z) * 6;

		int terrain_height = Map.Get_Height_GL(lookahead_coord);
		if (Map[lookahead_coord].IsUnderBridge) {
			terrain_height += BRIDGE_LEPTON_HEIGHT;
		}

		int cell_distance = target_distance / CELL_LEPTON;
		if (airburst || veryhigh) {
			cell_distance = 10;
		} else if (cell_distance >= 5) {
			cell_distance = 5;
		}

		int height_delta = coord.Z - LEVEL_LEPTON_H * cell_distance - terrain_height;
		if (height_delta < -20) {
			coord.Z += 18;
		} else if (height_delta > 20) {
			coord.Z -= 18;
		}

		if (height_delta < -(LEVEL_LEPTON_H / 2)) {
			desired_pitch.Turn(DirType(DIR_NE), rot / 2);
		} else if (height_delta > LEVEL_LEPTON_H / 2) {
			desired_pitch.Turn(DirType(Dir256(DIR_E + DIR_STEP_32)), rot / 2);
		} else {
			DirType level_pitch(DIR_E);
			DirType turn_rate = rot / 2;
			desired_pitch.Turn(level_pitch, turn_rate);
		}
	} else {
		DirType turn_rate = (rot + 256);
		desired_pitch.Turn(target_direction.Get_Pitch(), turn_rate / 2);
	}

	velocity.Set_Pitch(desired_pitch);

	if (airburst) {
		delta.Z = 0;
	} else {
		delta.Z /= 4;
	}

	return(delta.Length());
}
