/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "motlib.h"
#include "stbuffer.h"
#include "voxlib.h"

template<class INDEX, class T> class IndexClass;
class Matrix3D;
class Vector3;

struct VoxelDataStruct
{
	VoxelDataStruct(void)
	{
		VoxLib = NULL;
		MotLib = NULL;
	}

	~VoxelDataStruct(void); /// lives in object.cpp

	/*
	 * This points to the voxel model loaded from the object's VXL file, or NULL when the
	 * object has no voxel imagery at all. It holds the voxels themselves, gathered into
	 * the layers that make up the model.
	 */
	VoxelLibrary * VoxLib;

	/*
	 * This points to the layer transforms loaded from the object's HVA file, which place
	 * each of the model's layers for a given frame of animation. An object is only drawn as
	 * a voxel when both libraries are on hand.
	 */
	MotionLibrary * MotLib;
};

struct VoxelCacheStruct
{
	/// Unused
	short X;
	short Y;
	unsigned short Width;
	unsigned short Height;
	void * Buffer;
};

typedef IndexClass<int, StaticBufferClass::Entry *> VoxelIndexClass;

extern bool UseVoxelCache;
extern Vector3 VoxelShadowLightVector;
extern float VoxelLightAngle;
extern Vector3 VoxelLightSource;
extern float VoxelCameraAngle;
extern Matrix3D VoxelCameraMatrix;
extern StaticBufferClass VoxelStaticBuffer;

extern const float DefaultLightAngle;
extern const float DefaultCameraAngle;

inline void Set_Voxel_Camera_Angle(float angle)
{
	VoxelCameraAngle = angle;
	VoxelCameraMatrix.Make_Identity();
}

inline void Set_Voxel_Light_Angle(float angle)
{
	Matrix3D mtx(true);
	VoxelLightAngle = angle;
	mtx.Rotate_Y(angle);
	VoxelLightSource = mtx * Vector3(-1, 0, 0);
	VoxelShadowLightVector = Vector3(-6 * VoxelLightSource.X, 0, 0);
}
