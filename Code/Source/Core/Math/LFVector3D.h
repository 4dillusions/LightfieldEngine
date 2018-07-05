/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"

namespace LFCore { namespace Math
{
	class LFCORE_LIBRARY LFVector3D
	{
	public:
		float x, y, z;

		LFVector3D() : x(0.0f), y(0.0f), z(0.0f) {}
		LFVector3D(const float x, const float y, float z) : x(x), y(y), z(z) {}
		explicit LFVector3D(const float scale) : x(scale), y(scale), z(scale) {}

		LFVector3D &operator = (const LFVector3D &value);

		bool operator == (const LFVector3D &value) const;
		bool operator != (const LFVector3D &value) const;

		LFVector3D operator + (const LFVector3D &value) const;
		LFVector3D operator + (const float size) const;

		LFVector3D operator - (const LFVector3D &value) const;
		LFVector3D operator - (const float size) const;

		LFVector3D operator * (const LFVector3D &value) const;
		LFVector3D operator * (const float size) const;

		LFVector3D operator / (const LFVector3D &value) const;
		LFVector3D operator / (const float size) const;

		LFVector3D operator - () const;

		LFVector3D &operator ++ ();
		LFVector3D &operator ++ (int);
		LFVector3D &operator -- ();
		LFVector3D &operator -- (int);

		LFVector3D &operator += (const LFVector3D &value);
		LFVector3D &operator += (const float size);

		LFVector3D &operator -= (const LFVector3D &value);
		LFVector3D &operator -= (const float size);

		LFVector3D &operator *= (const LFVector3D &value);
		LFVector3D &operator *= (const float size);

		LFVector3D &operator /= (const LFVector3D &value);
		LFVector3D &operator /= (const float size);

		bool operator < (const LFVector3D &value) const;
		bool operator > (const LFVector3D &value) const;

		void Zero();
	};
}}
