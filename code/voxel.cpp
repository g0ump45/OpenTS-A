/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "_voxel.h"
#include "globals.h"
#include "inline.h"
#include "matrix3d.h"
#include "objtype.h"
#include "quat.h"

#include "ramp.hh"

/// warning C4305: 'argument' : truncation from 'const double' to 'float'
#pragma warning(disable : 4305)

/*
 * These are the orientations a voxel takes on when it stands on each kind of ramp -- the
 * matrix for an object settled on one ramp, the quaternion for one still tilting onto the
 * next. The Screen pair holds the same slopes about axes turned a further 45 degrees,
 * apparently the angle between the map grid and the screen. Nothing reads it.
 */
Matrix3D ScreenSlopeMatrices[RAMP_COUNT];
Matrix3D SlopeMatrices[RAMP_COUNT];

Quaternion ScreenSlopeQuaternions[RAMP_COUNT];
Quaternion SlopeQuaternions[RAMP_COUNT];

Matrix3D BounceMatrices[4];
Matrix3D IsometricViewMatrix;

Vector3 LightDirectionVectors[256];
Vector3 LightTiltVectors[256];
float ExtraLightTiltAngles[6] = { 0.0, 0.08726389, 0.17452778, 0.26179168, 0.17452778, 0.08726389 }; /// 0, 5, 10, 15, 10, 5

int SomeNumbers[17] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 5, 6, 7, 8, 9, 10, 11, 12 };


/// <summary>
/// Fetches the matrix that orients a voxel to the view.
/// This routine hands out the fixed isometric camera transform that the voxel drawing
/// code combines with each object's own orientation.
/// </summary>
/// <returns>Returns with the isometric view matrix.</returns>
Matrix3D Get_Isometric_View_Matrix(void)
{
	return(IsometricViewMatrix);
}


/// <summary>
/// Builds the fixed matrix tables that the voxel renderer works from.
/// This routine prepares the orientation of every ramp type, the lighting direction and
/// tilt vector of every facing, the isometric view transform, and the bounce matrices.
/// </summary>
/// <remarks>Call this routine before any voxel is drawn.</remarks>
void Init_Voxel_Matrices(void)
{
	/// The two angles are used the wrong way round below, in both sets. Ramps 1-4 rise
	/// along a cell axis, so their pitch is CELL_SLOPE_ANGLE, and ramps 5-12 rise along the
	/// cell diagonal, so theirs is CELL_DIAG_SLOPE_ANGLE -- but the code swaps them, tilting
	/// units about 8 degrees too far on the plain ramps and 8 short on the corner ones.
	/// Ramps 13-16 share 5-12's gradient yet are given the diagonal angle, which is what
	/// gives the swap away.
	float slope_angle = CELL_SLOPE_ANGLE;
	float slope_diag_angle = CELL_DIAG_SLOPE_ANGLE;

	const double pi = 3.1415;

	Vector3 north_east = Matrix3D(Vector3(0, 0, 1), pi / 4) * Vector3(1, 0, 0);
	Vector3 north_west = Matrix3D(Vector3(0, 0, 1), 3 * pi / 4) * Vector3(1, 0, 0);
	Vector3 south_west = Matrix3D(Vector3(0, 0, 1), 5 * pi / 4) * Vector3(1, 0, 0);
	Vector3 south_east = Matrix3D(Vector3(0, 0, 1), 7 * pi / 4) * Vector3(1, 0, 0);

	Vector3 east(1, 0, 0);
	Vector3 north(0, 1, 0);
	Vector3 west(-1, 0, 0);
	Vector3 south(0, -1, 0);

	ScreenSlopeMatrices[0].Make_Identity();

	ScreenSlopeMatrices[1] = Matrix3D(5 * pi / 4, slope_diag_angle);
	ScreenSlopeMatrices[2] = Matrix3D(3 * pi / 4, slope_diag_angle);
	ScreenSlopeMatrices[3] = Matrix3D(pi / 4, slope_diag_angle);
	ScreenSlopeMatrices[4] = Matrix3D(7 * pi / 4, slope_diag_angle);

	ScreenSlopeQuaternions[1] = Axis_To_Quat(south_west, slope_diag_angle);
	ScreenSlopeQuaternions[2] = Axis_To_Quat(north_west, slope_diag_angle);
	ScreenSlopeQuaternions[3] = Axis_To_Quat(north_east, slope_diag_angle);
	ScreenSlopeQuaternions[4] = Axis_To_Quat(south_east, slope_diag_angle);

	ScreenSlopeMatrices[5] = Matrix3D(pi, slope_angle);
	ScreenSlopeMatrices[6] = Matrix3D(pi / 2, slope_angle);
	ScreenSlopeMatrices[7] = Matrix3D(0.0, slope_angle);
	ScreenSlopeMatrices[8] = Matrix3D(3 * pi / 2, slope_angle);

	ScreenSlopeQuaternions[5] = Axis_To_Quat(west, slope_angle);
	ScreenSlopeQuaternions[6] = Axis_To_Quat(north, slope_angle);
	ScreenSlopeQuaternions[7] = Axis_To_Quat(east, slope_angle);
	ScreenSlopeQuaternions[8] = Axis_To_Quat(south, slope_angle);

	ScreenSlopeMatrices[9] = Matrix3D(pi, slope_angle);
	ScreenSlopeMatrices[10] = Matrix3D(pi / 2, slope_angle);
	ScreenSlopeMatrices[11] = Matrix3D(0.0, slope_angle);
	ScreenSlopeMatrices[12] = Matrix3D(3 * pi / 2, slope_angle);

	ScreenSlopeQuaternions[9] = Axis_To_Quat(west, slope_angle);
	ScreenSlopeQuaternions[10] = Axis_To_Quat(north, slope_angle);
	ScreenSlopeQuaternions[11] = Axis_To_Quat(east, slope_angle);
	ScreenSlopeQuaternions[12] = Axis_To_Quat(south, slope_angle);

	ScreenSlopeMatrices[13] = Matrix3D(pi, slope_diag_angle);
	ScreenSlopeMatrices[14] = Matrix3D(pi / 2, slope_diag_angle);
	ScreenSlopeMatrices[15] = Matrix3D(0.0, slope_diag_angle);
	ScreenSlopeMatrices[16] = Matrix3D(3 * pi / 2, slope_diag_angle);

	ScreenSlopeQuaternions[13] = Axis_To_Quat(west, slope_diag_angle);
	ScreenSlopeQuaternions[14] = Axis_To_Quat(north, slope_diag_angle);
	ScreenSlopeQuaternions[15] = Axis_To_Quat(east, slope_diag_angle);
	ScreenSlopeQuaternions[16] = Axis_To_Quat(south, slope_diag_angle);

	ScreenSlopeMatrices[17].Make_Identity();
	ScreenSlopeMatrices[18].Make_Identity();
	ScreenSlopeMatrices[19].Make_Identity();
	ScreenSlopeMatrices[20].Make_Identity();

	ScreenSlopeQuaternions[17].Make_Identity();
	ScreenSlopeQuaternions[18].Make_Identity();
	ScreenSlopeQuaternions[19].Make_Identity();
	ScreenSlopeQuaternions[20].Make_Identity();

	for (int i = 0; i < ARRAY_SIZE(LightDirectionVectors); i++) {
		Matrix3D direction_matrix;
		direction_matrix.Make_Identity();
		float theta = i * (float)(2 * pi / 256);
		direction_matrix.Rotate_Z(theta);

		Vector3 & direction_vec = LightDirectionVectors[i];
		Vector3 & tilt_vec = LightTiltVectors[i];

		direction_vec = direction_matrix * Vector3(1, 0, 0);

		tilt_vec = Vector3::Cross_Product(direction_vec, Vector3(0, 0, 1));

		Matrix3D tilt_matrix(tilt_vec, VoxelLightAngle);
		direction_vec = tilt_matrix * direction_vec;
	}

	SlopeMatrices[0].Make_Identity();

	SlopeMatrices[1] = Matrix3D(3 * pi / 2, slope_diag_angle);
	SlopeMatrices[2] = Matrix3D(pi, slope_diag_angle);
	SlopeMatrices[3] = Matrix3D(pi / 2, slope_diag_angle);
	SlopeMatrices[4] = Matrix3D(0.0, slope_diag_angle);

	SlopeMatrices[5] = Matrix3D(5 * pi / 4, slope_angle);
	SlopeMatrices[6] = Matrix3D(3 * pi / 4, slope_angle);
	SlopeMatrices[7] = Matrix3D(pi / 4, slope_angle);
	SlopeMatrices[8] = Matrix3D(7 * pi / 4, slope_angle);

	SlopeMatrices[9] = Matrix3D(5 * pi / 4, slope_angle);
	SlopeMatrices[10] = Matrix3D(3 * pi / 4, slope_angle);
	SlopeMatrices[11] = Matrix3D(pi / 4, slope_angle);
	SlopeMatrices[12] = Matrix3D(7 * pi / 4, slope_angle);

	SlopeMatrices[13] = Matrix3D(5 * pi / 4, slope_diag_angle);
	SlopeMatrices[14] = Matrix3D(3 * pi / 4, slope_diag_angle);
	SlopeMatrices[15] = Matrix3D(pi / 4, slope_diag_angle);
	SlopeMatrices[16] = Matrix3D(7 * pi / 4, slope_diag_angle);

	SlopeQuaternions[0].Make_Identity();

	SlopeQuaternions[1] = Axis_To_Quat(south, slope_diag_angle);
	SlopeQuaternions[2] = Axis_To_Quat(west, slope_diag_angle);
	SlopeQuaternions[3] = Axis_To_Quat(north, slope_diag_angle);
	SlopeQuaternions[4] = Axis_To_Quat(east, slope_diag_angle);

	SlopeQuaternions[5] = Axis_To_Quat(south_west, slope_angle);
	SlopeQuaternions[6] = Axis_To_Quat(north_west, slope_angle);
	SlopeQuaternions[7] = Axis_To_Quat(north_east, slope_angle);
	SlopeQuaternions[8] = Axis_To_Quat(south_east, slope_angle);

	SlopeQuaternions[9] = Axis_To_Quat(south_west, slope_angle);
	SlopeQuaternions[10] = Axis_To_Quat(north_west, slope_angle);
	SlopeQuaternions[11] = Axis_To_Quat(north_east, slope_angle);
	SlopeQuaternions[12] = Axis_To_Quat(south_east, slope_angle);

	SlopeQuaternions[13] = Axis_To_Quat(south_west, slope_diag_angle);
	SlopeQuaternions[14] = Axis_To_Quat(north_west, slope_diag_angle);
	SlopeQuaternions[15] = Axis_To_Quat(north_east, slope_diag_angle);
	SlopeQuaternions[16] = Axis_To_Quat(south_east, slope_diag_angle);

	SlopeMatrices[17].Make_Identity();
	SlopeMatrices[18].Make_Identity();
	SlopeMatrices[19].Make_Identity();
	SlopeMatrices[20].Make_Identity();

	SlopeQuaternions[17].Make_Identity();
	SlopeQuaternions[18].Make_Identity();
	SlopeQuaternions[19].Make_Identity();
	SlopeQuaternions[20].Make_Identity();

	IsometricViewMatrix.Make_Identity();
	IsometricViewMatrix.Rotate_X(-RAD_60);
	IsometricViewMatrix.Rotate_Z(-RAD_45);

	for (int j = 0; j < ARRAY_SIZE(BounceMatrices); j++) {
		BounceMatrices[j].Make_Identity();
	}

	/// Flip Y
	BounceMatrices[0][1].Y = -1.0;

	/// Rotate 90 degrees CCW
	BounceMatrices[1][0].X = 0.0;
	BounceMatrices[1][0].Y = 1.0;
	BounceMatrices[1][1].X = 1.0;
	BounceMatrices[1][1].Y = 0.0;

	/// Flip X
	BounceMatrices[2][0].X = -1.0;

	// Rotate 90 degrees CW
	BounceMatrices[3][0].X = 0.0;
	BounceMatrices[3][0].Y = -1.0;
	BounceMatrices[3][1].X = -1.0;
	BounceMatrices[3][1].Y = 0.0;
}


/// <summary>
/// Fetches the screen-aligned orientation matrix of the ramp specified.
/// </summary>
/// <param name="matrix">The matrix to fill in with the ramp orientation.</param>
void Get_Screen_Slope_Matrix(int ramp, Matrix3D & matrix)
{
	matrix = ScreenSlopeMatrices[ramp];
}


/// <summary>
/// Fetches the orientation matrix of the ramp specified.
/// </summary>
/// <returns>Returns with the orientation to draw an object resting on that ramp.</returns>
Matrix3D Get_Slope_Matrix(int ramp)
{
	return(SlopeMatrices[ramp]);
}


/// <summary>
/// Fetches a screen-aligned orientation part way between two ramps.
/// This routine is used to tilt an object smoothly as it travels from one ramp onto
/// another. When both ramps are alike there is nothing to blend and the ramp's own
/// orientation is handed back.
/// </summary>
/// <param name="oldramp">The ramp being left behind.</param>
/// <param name="newramp">The ramp being moved onto.</param>
/// <param name="matrix">The matrix to fill in with the blended orientation.</param>
/// <param name="time">How far the transition has progressed, from zero to one.</param>
void Get_Screen_Slope_Transition_Matrix(int oldramp, int newramp, Matrix3D & matrix, double time)
{
	if (oldramp == newramp) {
		Get_Screen_Slope_Matrix(newramp, matrix);
	} else {
		matrix = Build_Matrix3D(Slerp(ScreenSlopeQuaternions[oldramp], ScreenSlopeQuaternions[newramp], time));
	}
}


/// <summary>
/// Fetches an orientation part way between two ramps.
/// This routine is used by the drive locomotor to tilt a unit smoothly as it crosses
/// from one ramp onto another.
/// </summary>
/// <param name="oldramp">The ramp being left behind.</param>
/// <param name="newramp">The ramp being moved onto.</param>
/// <param name="time">How far the transition has progressed, from zero to one.</param>
/// <returns>Returns with the orientation to draw the object at.</returns>
Matrix3D Get_Slope_Transition_Matrix(int oldramp, int newramp, double time)
{
	if (oldramp != newramp) {
		return(Build_Matrix3D(Slerp(SlopeQuaternions[oldramp], SlopeQuaternions[newramp], time)));
	} else {
		return(SlopeMatrices[newramp]);
	}
}


/// <summary>
/// Fetches the voxel number that the index specified maps to.
/// </summary>
/// <returns>Returns with the voxel number the index maps to.</returns>
int Get_Some_Voxel_Number(int index)
{
	return(SomeNumbers[index]);
}


/// <summary>
/// Determines the voxel facing between two coordinates.
/// This routine converts the direction from one coordinate to the other into the facing
/// that the voxel artwork and the lighting tables are indexed by.
/// </summary>
/// <param name="coord1">The coordinate to measure the direction from.</param>
/// <param name="coord2">The coordinate to measure the direction to.</param>
/// <returns>Returns with the facing, expressed in 256ths of a circle.</returns>
unsigned char _Direction256(Coord const & coord1, Coord const & coord2)
{
	DirType dir = Direction(coord1, coord2);
	unsigned char facing = DIR_NE - dir.As_Dir256();
	return(facing);
}


/// <summary>
/// Tilts and offsets a matrix towards the lighting specified.
/// </summary>
/// <param name="matrix">The matrix to transform in place.</param>
/// <param name="axis">The lighting facing to tilt about.</param>
/// <param name="angle">Index of the extra tilt angle to apply.</param>
void Apply_Light_Transform(Matrix3D & matrix, int axis, int angle)
{
	Matrix3D mtx(LightTiltVectors[axis], ExtraLightTiltAngles[angle]);
	matrix = matrix * mtx;
	matrix.Translate(-3 * LightDirectionVectors[axis]);
	matrix.Translate(0, 0, 3);
}


/// <summary>
/// Fetches the lighting vector for the direction specified.
/// </summary>
/// <returns>Returns with the scaled light direction vector.</returns>
Vector3 Get_Light_Vector(Dir256 dir, int)
{
	Vector3& vec = LightDirectionVectors[dir];
	return(Vector3(vec.X * 1.5f, vec.Y * 1.5f, vec.Z * 1.5f));
}


/// <summary>
/// Clears the cached voxel indexes of every object type.
/// </summary>
void Clear_Voxel_Indexes(void)
{
	ObjectTypeClass::Clear_Voxel_Indexes();
}


/// <summary>
/// Fetches the mirror matrix for the facing specified.
/// This routine is used by the bounce logic to flip an object's artwork about, so that
/// opposing facings can share the same prepared matrix.
/// </summary>
/// <param name="facing">The facing the object is bouncing towards.</param>
/// <returns>Returns with the matrix to mirror the object's orientation by.</returns>
Matrix3D Get_Bounce_Matrix(FacingType facing)
{
	if (facing >= FACING_S) {
		facing = FacingType(facing - FACING_S);
	}
	return(BounceMatrices[facing]);
}
