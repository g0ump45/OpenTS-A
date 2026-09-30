/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/

#pragma once

#include "matrix3d.h"
#include "rgb.h"
#include "voxdrsys.h"
#include "voxel.h"
#include "win.h"

#include "voxel.hh"

class FileClass;
class Vector3;


class VoxelLibrary
{
	public:
		struct LayerStruct
		{
			/*
			 * This is the index of the layer's first info record within the library's info
			 * table. Any further records belonging to the layer follow it in sequence.
			 */
			int InfoIndex;

			/// Unused
			int Unused1;
			unsigned char Unused2;
		};

		struct LayerInfoStruct
		{
			/*
			 * This points to the layer's table of span offsets, one entry per column of its
			 * X by Y footprint, with -1 marking an empty column. The file stores it as an
			 * offset from the start of the voxel body, which loading rebases onto the data.
			 */
			unsigned char * StartOffset;

			/*
			 * This points to the matching span table used when the drawing order walks the
			 * layer in reverse. The shadow drawer reads this one alone, only to learn which
			 * columns hold any voxels at all.
			 */
			unsigned char * EndOffset;

			/*
			 * This points to the run length encoded voxel data itself. The span tables give
			 * each column's position within it.
			 */
			unsigned char * DataOffset;

			/*
			 * This is the scale the layer was built at. The object's motion library is
			 * scaled by it at load time, which brings the animation into voxel scale.
			 */
			float Scale;

			/*
			 * This is the layer's placement transform, converted into the engine's matrix
			 * layout as the file is read. The animation supplies a matrix per layer per
			 * frame, so nothing consults this copy.
			 */
			Matrix3D Transform;

			/*
			 * These are the eight corners of the layer's bounding box, expanded at load time
			 * from the two opposite corners the file stores. The drawer transforms them to
			 * find the anchor corner, which decides the order the voxels are walked in.
			 */
			Vector3 BoxCorner[VOXEL_BOUNDS_COUNT];

			/*
			 * These are the dimensions of the layer, measured in voxels.
			 */
			unsigned char XSize;
			unsigned char YSize;
			unsigned char ZSize;

			/*
			 * This specifies which of the normal tables the layer's voxels index (1 - 4). If
			 * it is zero, then the layer has no usable normals and is drawn without lighting.
			 */
			unsigned char NormalType;
		};

	public:
		VoxelLibrary(void);
		VoxelLibrary(FileClass & file, int load_file_palette = false);
		~VoxelLibrary(void);

		void Clear(void);
		int Read_File(FileClass & file, int load_file_palette = false);

		LayerStruct const & Get_Layer(int layer);
		LayerInfoStruct const & Get_Layer_Info(int layer, int info);

		Vector3 Get_Bounding_Box_Center(int layer, int info);
		int Memory_Used(void);
		void Render_Object(VoxelRenderStruct & voxel, Vector3 & center);
		void Render_Shadow(VoxelShadowRenderStruct & voxel, Vector3 & center);
		void Compute_Bounding_Box(void);

		bool Load_Failed(void) const { return(LoadFailed); }
		unsigned int Get_Layer_Count(void) const { return(LayerCount); }
		unsigned int Get_Layer_Info_Count(void) const { return(LayerInfoCount); }
		int Get_Data_Size(void) const { return(DataSize); }

	private:
		/*
		 * If the voxel object could not be read out of its file, then this flag will be true.
		 * The library is left empty in that case, so a caller must check it before drawing.
		 */
		bool LoadFailed;

		unsigned int LayerCount;		/// Layer header count.
		unsigned int LayerInfoCount;	/// Layer info count (these info can be reused).
		int DataSize;					/// Size of body data.
		LayerStruct * LayerHeaders;		/// Layer headers.
		LayerInfoStruct * LayerInfos;	/// Layer info data.
		unsigned char * Data;			/// Section body data.
};

void Precalculate_Normal_Lookup(Vector3 const & light, int normal_type);
void Precalculate_Normal_Lookup(Vector3 const & light, Vector3 const & viewer, float specular_strength, int normal_type);
int Find_Closest_Normal(Vector3 const & surface_normal, int normal_type);
void Init_Normal_Lookup(void);

class VoxelPaletteLibrary
{
	friend class VoxelLibrary;

	public:
		VoxelPaletteLibrary(RGBStruct * rgb, void * lut);
		~VoxelPaletteLibrary(void);

		int Read_Colors(FileClass & file);

		int Read_File(FileClass & file);
		int Write_File(FileClass & file);

	private:
		void Calculate_Lookup_Table(float *scale = NULL, int lut_count = 0);
		unsigned char Closest_Color(float red, float green, float blue) const;
		unsigned char Closest_Color(float red, float green, float blue, bool is_remap) const;

	public:
		/*
		 * This is the header of the palette library. It names the palette range reserved for
		 * house colors and the number of brightness steps the shading tables hold.
		 */
		VPLHeaderStruct Header;
	private:
		/*
		 * This points to the 256 color palette that every voxel is drawn from. It is either
		 * the buffer the creator supplied or one the library allocated for itself.
		 */
		RGBStruct * Colors;

		/*
		 * This points to the shading tables, one run of 256 palette entries per brightness
		 * step. The drawing routines shade a voxel by looking its color up in the run its
		 * lighting picks, rather than computing the shaded color a pixel at a time.
		 */
		unsigned char *LUT;

		/*
		 * These flags record which of the two buffers this library allocated for itself. A
		 * buffer the creator supplied is left alone when the library is destroyed.
		 */
		BOOL ColorsAllocated;
		BOOL LUTAllocated;

	enum {
		VPL_NUM_COLORS = 256,
		VPL_NUM_ENTRIES = 32,
	};
};

extern "C" {
extern short VoxelPixelDeltaTable[VOXEL_BITMAP_WIDTH][2];
extern unsigned char VoxelNormalTranslateTable[VOXEL_PALETTE_SIZE];
}
