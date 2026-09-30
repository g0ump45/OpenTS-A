/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#include "always.h"

#include "motlib.h"

#include "wwfile.h"

#include "voxel.hh"


/// <summary>
/// Default constructor for the motion library.
/// This creates an empty library, ready to have an animation read into it.
/// </summary>
MotionLibrary::MotionLibrary() :
	LoadFailed(false),
	LayerCount(0),
	FrameCount(0),
	LayerMatrices(NULL)
{

}


/// <summary>
/// Constructor for the motion library that loads from a file.
/// This routine will read the animation held in the file specified.
/// </summary>
/// <remarks>A failure is recorded rather than reported, so check Load_Failed before
/// using the library.</remarks>
MotionLibrary::MotionLibrary(FileClass & file) :
	LoadFailed(false),
	LayerCount(0),
	FrameCount(0),
	LayerMatrices(NULL)
{
	if (!Read_File(file)) {
		LoadFailed = true;
	}
}


/// <summary>
/// Destructor for the motion library.
/// This will free the animation data that the library is holding.
/// </summary>
MotionLibrary::~MotionLibrary()
{
	Clear();
}


/// <summary>
/// Reads a voxel animation from the file specified.
/// This routine loads the per layer transformation matrices for every frame of the
/// animation. Anything this library was previously holding is discarded first, and the
/// file is closed before returning.
/// </summary>
/// <returns>bool; Was the animation read successfully?</returns>
BOOL MotionLibrary::Read_File(FileClass & file)
{
	Clear();

	bool result = file.Open(FileClass::READ) != 0;
	if (!result) {
		return(false);
	}

	VoxelAnimFileHeaderStruct header;

	file.Read(&header, sizeof(header));
	LayerCount = header.LayerCount;
	FrameCount = header.FrameCount;


	int count = LayerCount * FrameCount;
	LayerMatrices = new Matrix3D[count];

	if (LayerMatrices == NULL) {
		LayerMatrices = NULL;
		file.Close();
		return(false);
	}

	file.Seek(MAX_VOXEL_NAME_LENGTH * LayerCount);

	for (unsigned frame = 0; frame < FrameCount; frame++) {
		for (unsigned layer = 0; layer < LayerCount; layer++) {
			float m[12];
			if (file.Read(&m, sizeof(m)) == sizeof(m)) {
				LayerMatrices[layer + frame * LayerCount] = Matrix3D(m);
			} else {
				file.Close();
				Clear();
				return(false);
			}
		}
	}

	file.Close();
	return(true);
}


/// <summary>
/// Scales the translation of every layer matrix.
/// Use this routine to bring an animation into the coordinate scale that the voxel
/// drawer expects. Only the translation part of each matrix is affected, so the layers
/// keep their orientation.
/// </summary>
void MotionLibrary::Scale(float scale)
{
	for (unsigned frame = 0; frame < FrameCount; frame++) {
		for (unsigned layer = 0; layer < LayerCount; layer++) {
			LayerMatrices[layer + frame * LayerCount][0].W = scale * LayerMatrices[layer + frame * LayerCount][0].W;
			LayerMatrices[layer + frame * LayerCount][1].W = scale * LayerMatrices[layer + frame * LayerCount][1].W;
			LayerMatrices[layer + frame * LayerCount][2].W = scale * LayerMatrices[layer + frame * LayerCount][2].W;
		}
	}
}


/// <summary>
/// Frees the layer transformation matrices.
/// This routine is used to release the animation data before another file is read into
/// this library, and by the destructor.
/// </summary>
void MotionLibrary::Clear()
{
	if (LayerMatrices != NULL) {
		delete [] LayerMatrices;
	}
	LayerMatrices = NULL;
}
