/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"

namespace LFCore { namespace Math
{
	class LFCORE_LIBRARY LFVector2D
	{
	public:
		float x, y;

		LFVector2D() : x(0.0f), y(0.0f) {}
		LFVector2D(const float x, const float y) : x(x), y(y) {}
		explicit LFVector2D(const float scale) : x(scale), y(scale) {}

		LFVector2D &operator = (const LFVector2D &value);

		bool operator == (const LFVector2D &value) const;
		bool operator != (const LFVector2D &value) const;

		LFVector2D operator + (const LFVector2D &value) const;
		LFVector2D operator + (const float size) const;

		LFVector2D operator - (const LFVector2D &value) const;
		LFVector2D operator - (const float size) const;

		LFVector2D operator * (const LFVector2D &value) const;
		LFVector2D operator * (const float size) const;

		LFVector2D operator / (const LFVector2D &value) const;
		LFVector2D operator / (const float size) const;

		LFVector2D operator - () const;

		LFVector2D &operator ++ ();
		LFVector2D &operator ++ (int);
		LFVector2D &operator -- ();
		LFVector2D &operator -- (int);

		LFVector2D &operator += (const LFVector2D &value);
		LFVector2D &operator += (const float size);

		LFVector2D &operator -= (const LFVector2D &value);
		LFVector2D &operator -= (const float size);

		LFVector2D &operator *= (const LFVector2D &value);
		LFVector2D &operator *= (const float size);

		LFVector2D &operator /= (const LFVector2D &value);
		LFVector2D &operator /= (const float size);

		bool operator < (const LFVector2D &value) const;
		bool operator > (const LFVector2D &value) const;

		void Zero();
		void Up();
		void Down();
		void Left();
		void Right();
		void Rotate(float angle);
		void RotateCeil(float angle);
		void Rotate90DegreeForward();
		void Rotate90DegreeBackward();
	};
}}
