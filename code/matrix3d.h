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

#include "vector3.h"
#include "vector4.h"
#include "visualc.h"

#include <cassert>
#include <cmath>
#include <cstring>

class Matrix3D
{
	friend class Quaternion;

	public:
		// Constructors
		Matrix3D(void) {}

		explicit Matrix3D(bool init) { if (init) Make_Identity(); }

		explicit Matrix3D(float m[12]);

		explicit Matrix3D(
			float m11,float m12,float m13,float m14,
			float m21,float m22,float m23,float m24,
			float m31,float m32,float m33,float m34
		);

		explicit Matrix3D(
			const Vector3	&x,     // x-axis unit vector
			const Vector3	&y,     // y-axis unit vector
			const Vector3	&z,     // z-axis unit vector
			const Vector3	&pos    // position
		);

		explicit Matrix3D(
			const Vector3	&axis,
			float angle
		);

		explicit Matrix3D(
			const Vector3	&axis,
			float sine,
			float cosine
		);

		explicit Matrix3D(float zrot, float xrot);

		// Creates identity rotation w. given position.
		explicit Matrix3D(const Vector3 & position);


		// Assignment operator
		Matrix3D & operator=(Matrix3D const & that) { memcpy(this, &that, sizeof(*this)); return(*this);}


		Vector4 & operator [] (int i) {
			return(Row[i]);
		}
		const Vector4 & operator [] (int i) const {
			return(Row[i]);
		}

		void Get_Translation(Vector3 * set) const { set->X = Row[0].W; set->Y = Row[1].W; set->Z = Row[2].W; }
		Vector3 Get_Translation(void) const { return(Vector3(Row[0].W,Row[1].W,Row[2].W)); }
		float Get_X_Translation(void) const { return(Row[0].W); };
		float Get_Y_Translation(void) const { return(Row[1].W); };
		float Get_Z_Translation(void) const { return(Row[2].W); };

		void Make_Identity(void);

		void Translate(float x,float y,float z);
		void Translate(Vector3 const & t);

		void Translate_X(float x);
		void Translate_Y(float y);
		void Translate_Z(float z);

		// Init functions
		void Set(float m[12]);

		void Set(
			float m11,float m12,float m13,float m14,
			float m21,float m22,float m23,float m24,
			float m31,float m32,float m33,float m34
		);

		void Set(
			const Vector3	&x,		// x-axis unit vector
			const Vector3	&y,		// y-axis unit vector
			const Vector3	&z,		// z-axis unit vector
			const Vector3	&pos	// position
		);

		void Set(const Vector3 & axis,float angle);

		void Set(const Vector3 & axis,float sine,float cosine);

		//void Set(const Quaternion & rotation,const Vector3 & position);

		// Creates identity rotation w. given position.
		void Set(const Vector3 & position);

		void Scale(float scale);
		void Scale(float x, float y, float z);

		void Scale_X(float scale);
		void Scale_Y(float scale);
		void Scale_Z(float scale);

		void Shear_YZ(float y, float z);
		void Shear_XY(float x, float y);
		void Shear_XZ(float x, float z);

		void Pre_Rotate_X(float theta);
		void Pre_Rotate_Y(float theta);
		void Pre_Rotate_Z(float theta);

		void Rotate_X(float theta);
		void Rotate_Y(float theta);
		void Rotate_Z(float theta);

		void Rotate_X(float s,float c);
		void Rotate_Y(float s,float c);
		void Rotate_Z(float s,float c);

		float Get_X_Val(void);
		float Get_Y_Val(void);
		float Get_Z_Val(void);

		float Get_X_Rotation(void);
		float Get_Y_Rotation(void);
		float Get_Z_Rotation(void);

		void Look_At(const Vector3 &p, const Vector3 &t, float roll);
		void Obj_Look_At(const Vector3 &p, const Vector3 &t, float roll);

		Vector3 Rotate_Vector(Vector3 const& vect);

		friend Vector3 operator * (const Matrix3D &A,const Vector3 &a);
		friend Matrix3D operator * (const Matrix3D & a, const Matrix3D & b);

		static void Multiply(const Matrix3D & A, const Matrix3D & B, Matrix3D * set_result);

		static Matrix3D Orthogonal_Inverse(Matrix3D const & src);


	protected:
		Vector4 Row[3];

};


/***********************************************************************************************
 * Matrix3D::Set -- init a Matrix3D from an arrray of 12 floats                                *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/24/98    GTH : Created.                                                                 *
 *=============================================================================================*/
inline void Matrix3D::Set(float m[12])
{
	Row[0].Set(m[0],m[1],m[2],m[3]);
	Row[1].Set(m[4],m[5],m[6],m[7]);
	Row[2].Set(m[8],m[9],m[10],m[11]);
}


/***********************************************************************************************
 * Matrix3D::Set -- Init a Matrix3D from 12 individual floats                                  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/24/98    GTH : Created.                                                                 *
 *=============================================================================================*/
inline void Matrix3D::Set(	float m11,float m12,float m13,float m14,
							float m21,float m22,float m23,float m24,
							float m31,float m32,float m33,float m34)
{
	Row[0].Set(m11,m12,m13,m14);
	Row[1].Set(m21,m22,m23,m24);
	Row[2].Set(m31,m32,m33,m34);
}


/***********************************************************************************************
 * Matrix3D::Set -- Init a matrix from 3 axis vectors and a position                           *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/24/98    GTH : Created.                                                                 *
 *=============================================================================================*/
inline void Matrix3D::Set(	const Vector3	&x,		// x-axis unit vector
							const Vector3	&y,		// y-axis unit vector
							const Vector3	&z,		// z-axis unit vector
							const Vector3	&pos)	// position
{
	Row[0].Set(x[0],y[0],z[0],pos[0]);
	Row[1].Set(x[1],y[1],z[1],pos[1]);
	Row[2].Set(x[2],y[2],z[2],pos[2]);
}


/***********************************************************************************************
 * Matrix3D::Set -- init a matrix to be a rotation about the given axis                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/24/98    GTH : Created.                                                                 *
 *=============================================================================================*/
inline void Matrix3D::Set(const Vector3 & axis,float angle)
{
	float c = std::cos((double)angle);
	float s = std::sin((double)angle);

	Set(axis,s,c);
}

/***********************************************************************************************
 * Matrix3D::Set -- init a matrix to be a rotation about the given axis                        *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   2/24/98    GTH : Created.                                                                 *
 *=============================================================================================*/
inline void Matrix3D::Set(const Vector3 & axis,float s,float c)
{
	Row[0].X = axis.X*axis.X + c*(1 - axis.X*axis.X);
	Row[0].Y = axis.X*axis.Y*(1 - c) - axis.Z*s;
	Row[0].Z = axis.Z*axis.X*(1 - c) + axis.Y*s;
	Row[0].W = 0.0;

	Row[1].X = axis.X*axis.Y*(1 - c) + axis.Z*s;
	Row[1].Y = axis.Y*axis.Y + c*(1 - axis.Y*axis.Y);
	Row[1].Z = axis.Y*axis.Z*(1 - c) - axis.X*s;
	Row[1].W = 0.0;

	Row[2].X = axis.Z*axis.X*(1 - c) - axis.Y*s;
	Row[2].Y = axis.Y*axis.Z*(1 - c) + axis.X*s;
	Row[2].Z = axis.Z*axis.Z + c*(1 - axis.Z*axis.Z);
	Row[2].W = 0.0;
}

Vector3 operator * (const Matrix3D & m, const Vector3 & v);
Matrix3D operator * (const Matrix3D & a, const Matrix3D & b);
