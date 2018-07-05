/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"

namespace LFCore { namespace Math
{
	class LFVector2D;

	class LFCORE_LIBRARY LFMatrix4
	{
	private:
		float m[4][4];

	public:
		LFMatrix4();
		LFMatrix4(
			float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);

		LFMatrix4 &operator = (const LFMatrix4 &value);

		float operator() (int indexX, int indexY) const; //float a = matrix(0, 0);
		float &operator() (int indexX, int indexY); //matrix(0, 0) = 22.12;

		LFMatrix4 operator * (const LFMatrix4 &value) const;
		LFMatrix4 operator + (const LFMatrix4 &value) const;
		LFMatrix4 operator - (const LFMatrix4 &value) const;

		bool operator == (const LFMatrix4 &value) const;
		bool operator != (const LFMatrix4 &value) const;

		void Zero();
		void Identity();
		void Translation(const LFVector2D &vector);
	};
}}
