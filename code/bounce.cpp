/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "bounce.h"

#include "_map.h"
#include "_tactica.h"
#include "building.h"
#include "builtype.h"
#include "ccrand.h"
#include "cell.h"
#include "map.h"
#include "tactical.h"
#include "vector3.h"

/// <summary>
/// Sets the bouncing object into motion in a random direction.
/// This routine is used when the caller has no particular direction in mind and just
/// wants the debris flung somewhere. A speed is picked from the range supplied and aimed
/// along a random heading and pitch before the object is launched.
/// </summary>
/// <param name="elasticity">How much speed the object keeps when it strikes something.</param>
/// <param name="min_speed">The low end of the speed range to launch the object at.</param>
/// <param name="max_speed">The high end of the speed range to launch the object at.</param>
void BounceClass::Init(Coord const & coord, double elasticity, double, double min_speed, double max_speed)
{
	Vector3 launch_velocity;

	double launch_speed = Random_Double(min_speed,max_speed) * 3.0;
	double azimuth = Random_Double(0.0, 1.0) * DEG_TO_RAD(360);
	double elevation = Random_Double(1.0, 2.0) * DEG_TO_RAD(45);

	launch_velocity.X = std::cos(elevation) * std::cos(azimuth) * launch_speed;
	launch_velocity.Y = std::cos(elevation) * std::sin(azimuth) * launch_speed;
	launch_velocity.Z = std::sin(elevation) * launch_speed;

	Init(coord, elasticity, 3.0, 0.0, launch_velocity, 0.0);
}


/// <summary>
/// Sets the bouncing object into motion.
/// This routine is called by the animation and voxel animation objects when a piece of
/// debris is thrown. The axis the object tumbles about is picked at random, so two pieces
/// launched with the same velocity will still spin differently.
/// </summary>
/// <param name="elasticity">How much speed the object keeps when it strikes something.</param>
/// <param name="gravity">The gravity to pull the object down by each frame.</param>
/// <param name="max_velocity">The fastest the object is allowed to travel. Use zero for no limit.</param>
/// <param name="rotation">How quickly the object tumbles about its spin axis.</param>
void BounceClass::Init(Coord const & coord, double elasticity, double gravity, double max_velocity, Vector3 const & velocity, double rotation)
{
	Elasticity = elasticity;
	Gravity = gravity;
	MaxVelocity = max_velocity;
	MyCoord.X = coord.X;
	MyCoord.Y = coord.Y;
	MyCoord.Z = coord.Z;
	Velocity = velocity;

	Vector3 rotation_axis(
		Random_Pick(-65535, 65535) * (1.0f / 65535.0f),
		Random_Pick(-65535, 65535) * (1.0f / 65535.0f),
		Random_Pick(-65535, 65535) * (1.0f / 65535.0f)
	);

	rotation_axis = Normalize(rotation_axis);
	AngularVelocity = Axis_To_Quat(rotation_axis, rotation);
	Matrix3D identity_matrix;
	identity_matrix.Make_Identity();
	Rotation = Build_Quaternion(identity_matrix);
}


/// <summary>
/// Fetches the current position of the bouncing object.
/// This routine is how the owning object finds out where its debris has got to, whether
/// to damage what it landed on or to place an effect there.
/// </summary>
/// <returns>Returns with the position of the object in map coordinates.</returns>
Coord BounceClass::Get_Bounce_Coord(void) const
{
	return(Coord(MyCoord.X, MyCoord.Y, MyCoord.Z));
}


/// <summary>
/// Fetches the orientation of the bouncing object.
/// This routine is used by the draw code so that a tumbling piece of debris can be
/// rendered at whatever angle it has spun to.
/// </summary>
/// <returns>Returns with the transformation matrix for the object's current orientation.</returns>
Matrix3D BounceClass::Get_Matrix(void) const
{
	return(Build_Matrix3D(Rotation));
}


/// <summary>
/// Determines how much motion the object has left in it.
/// This routine weighs the object's speed together with how far it is still standing off
/// the ground, so that a bouncer caught in mid air is never mistaken for one that has
/// settled. The bounce logic uses this to decide when the object has come to rest.
/// </summary>
/// <returns>Returns with the residual motion of the object. A small value means it has all
/// but stopped.</returns>
double BounceClass::Get_Remaining_Motion(void) const
{
	Coord coord(MyCoord.X, MyCoord.Y, MyCoord.Z);

	int height = MyCoord.Z - Map.Get_Height_GL(coord);
	if (Map[coord].IsUnderBridge && height >= BRIDGE_LEPTON_HEIGHT) {
		height -= BRIDGE_LEPTON_HEIGHT;
	}
	return(Point3D(Velocity.X, Velocity.Y, height * Gravity + Velocity.Z).Length());
}


/// <summary>
/// Handles the physics of the bouncing object for one frame.
/// This routine will pull the object down with gravity, move it along its velocity, and
/// then settle it onto whatever it lands on -- the ground, a bridge deck, or a building
/// or wall that gets in the way. An impact reflects the velocity off the slope of the
/// cell and reverses the tumble. An object that runs off a cliff edge is put back where
/// it started and bounced away from the drop instead.
/// </summary>
/// <returns>Returns BOUNCE_IMPACT if the object struck a surface this frame,
/// BOUNCE_SETTLED if it has come to rest, or BOUNCE_MOVING if it is still traveling.</returns>
/// <remarks>Only call this routine once per bouncing object per game logic loop.</remarks>
BounceResultType BounceClass::AI(void)
{
	BounceResultType bounce_result = BOUNCE_MOVING;

	/*
	 * Remember the pre-move position and velocity so the off-cliff handler can
	 * restore them. The saved velocity is the value before gravity is applied below.
	 */
	Vector3 & position = MyCoord;
	Vector3 & velocity = Velocity;
	Vector3 old_position = position;
	Vector3 old_velocity = velocity;
	double elasticity = Elasticity;
	double max_velocity = MaxVelocity;

	/*
	 * Apply gravity to the vertical velocity component.
	 */
	velocity.Z = Velocity.Z - Gravity;

	/*
	 * Clamp the velocity to the maximum allowed.
	 */
	if (max_velocity > 0.0) {
		double speed = velocity.Length();
		if (speed > max_velocity) {
			velocity *= (float)(speed / speed);
		}
	}

	/*
	 * Advance the position by the velocity. Remember the integer cell positions
	 * before and after the move.
	 */
	Point3D previous_coord(position.X, position.Y, position.Z);
	position += velocity;
	Coord current_coord(position.X, position.Y, position.Z);

	int ground_height = Map.Get_Height_GL(current_coord);
	int bridge_height = BRIDGE_LEPTON_HEIGHT + ground_height;
	CellClass * cellptr = &Map[current_coord];

	/*
	 * Determine if the object passed through a bridge surface this frame.
	 */
	bool hit_bridge_top = false;
	bool hit_bridge_bottom = false;
	if (cellptr->IsUnderBridge || Map[(Coord const &)previous_coord].IsUnderBridge) {
		if (current_coord.Z >= bridge_height) {
			if (previous_coord.Z < bridge_height) {
				hit_bridge_bottom = true;
			}
		} else if (previous_coord.Z >= bridge_height) {
			hit_bridge_top = true;
		}
	}

	/*
	 * Determine if the object struck a building, wall or gate that should stop it.
	 */
	bool hit_obstacle = false;
	if (!hit_bridge_top && !hit_bridge_bottom) {
		if (ground_height <= position.Z && position.Z - 150.0f < ground_height) {
			BuildingClass * building = cellptr->Cell_Building();
			if (building == NULL && !cellptr->Has_Wall_Or_Gate(OVERLAY_NONE, FACING_NONE)) {
				hit_obstacle = false;
			} else {
				hit_obstacle = true;
				if (building != NULL) {
					if (building->Class->IsLaserFence && building->LaserFenceFrame >= 8) {
						hit_obstacle = false;
					}
					if (building->Considered_Vehicle()) {
						hit_obstacle = false;
					}
				}
			}

		}
	}

	/*
	 * Decide whether this frame reached a surface, then snap the vertical position
	 * to the ground, bridge or obstacle. A bridge crossing or obstacle counts even
	 * when the final position remains above the ground.
	 */
	float ground_z = (float)ground_height;
	bool has_impact = true;
	if (position.Z >= ground_z) {
		if (!hit_bridge_top && !hit_bridge_bottom && !hit_obstacle) {
			has_impact = false;
		}
	}
	if (has_impact) {
		if (hit_bridge_top) {
			position.Z = (float)bridge_height;
		} else if (hit_bridge_bottom) {
			position.Z = (float)(bridge_height - 20);
		} else {
			if ((ground_height - 100) < position.Z) {
				position.Z = ground_z;
			}
		}

		/*
		 * Reflect the velocity off the cell slope. The velocity is rotated into the
		 * slope's local space, scaled by elasticity, flipped vertically, then rotated
		 * back out.
		 */
		{
			Matrix3D slope_matrix;
			Matrix3D inverse_slope_matrix = Matrix3D::Orthogonal_Inverse(
				slope_matrix = Get_Slope_Matrix(TacticalMap->Get_Cell_Ramp(current_coord)));
			Vector3 bounce_velocity(velocity.X, -velocity.Y, velocity.Z);
			bounce_velocity = inverse_slope_matrix.Rotate_Vector(bounce_velocity);
			bounce_velocity *= (float)elasticity;
			bounce_velocity.Z = -bounce_velocity.Z;
			bounce_velocity = slope_matrix.Rotate_Vector(bounce_velocity);
			velocity.X = bounce_velocity.X;
			velocity.Y = -bounce_velocity.Y;
			velocity.Z = bounce_velocity.Z;
		}

		/*
		 * Invert the spin axis of the angular velocity (but not the W component).
		 */
		AngularVelocity[0] = -AngularVelocity[0];
		AngularVelocity[1] = -AngularVelocity[1];
		AngularVelocity[2] = -AngularVelocity[2];

		/*
		 * If the object fell off a cliff edge, restore its pre-move state and bounce
		 * off the slope of the cell it would have fallen into.
		 */
		{
			Coord impact_coord(MyCoord.X, MyCoord.Y, MyCoord.Z);
			Coord previous_impact_coord(old_position.X, old_position.Y, old_position.Z);
			int previous_cell_height = Map[(Coord const &)previous_impact_coord].Height;
			if (Map[(Coord const &)impact_coord].Height - previous_cell_height >= 2) {
				if (old_velocity.Z < -0.0002 && MyCoord.Z > old_position.Z
					|| old_velocity.Z >= -0.0003 && (old_velocity.Z + old_position.Z + 1.0f < MyCoord.Z)) {

					position = old_position;
					velocity = old_velocity;

					FacingType bounce_facing = Map[(Coord const &)impact_coord].Bounce_Direction((Coord const &)previous_impact_coord);
					if (bounce_facing != FACING_NONE) {
						Matrix3D bounce_matrix = Get_Bounce_Matrix(bounce_facing);
						velocity = bounce_matrix * velocity;
						velocity *= Elasticity;
					}
				}
			}
		}

		bounce_result = BOUNCE_IMPACT;
	}

	Rotation = Rotation * AngularVelocity;

	double remaining_motion = Get_Remaining_Motion();
	if (remaining_motion < 2.5) {
		bounce_result = BOUNCE_SETTLED;
	}
	return(bounce_result);
}
