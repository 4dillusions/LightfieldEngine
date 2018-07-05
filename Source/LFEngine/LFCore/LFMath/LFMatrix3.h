/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	class LFVector3D;

	/**
		@brief
		3*3 Matrix and math calculations
	*/
	class LFMatrix3 final
	{
		float m[3][3] = {};

	public:
		LFMatrix3() = default;
		LFMatrix3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22);
		LFMatrix3 (const LFMatrix3 &value) = default;

		LFMatrix3 &operator = (const LFMatrix3 &value);

		float operator() (int indexX, int indexY) const; //float a = matrix(0, 0);
		float &operator() (int indexX, int indexY); //matrix(0, 0) = 22.12;

		LFMatrix3 operator * (const LFMatrix3 &value) const;
		LFMatrix3 operator + (const LFMatrix3 &value) const;
		LFMatrix3 operator - (const LFMatrix3 &value) const;

		bool operator == (const LFMatrix3 &value) const;
		bool operator != (const LFMatrix3 &value) const;

		LFVector3D operator * (const LFVector3D &vector) const;
		LFMatrix3 operator * (float scalar) const;
		bool Inverse(LFMatrix3 &inverse, float tolerance = 1e-06) const;
		LFMatrix3 Inverse(float tolerance = 1e-06) const;
		LFMatrix3 Transpose() const;
		float Determinant() const;
		void Orthonormalize();

		void Zero();
		void Identity();
	};
}}}}
