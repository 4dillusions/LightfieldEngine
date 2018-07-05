/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	/**
		@brief
		2D Vector and math calculations
	*/
	class LFVector2D final
	{
	public:
		float x = 0.0f, y = 0.0f;

		LFVector2D() = default;
		explicit LFVector2D(const float scale);
		LFVector2D(const float x, const float y);
		LFVector2D(const LFVector2D &other) = default;

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

		float Length() const;
		float Distance(const LFVector2D &value) const;
		float DotProduct(const LFVector2D &value) const;
		float CrossProduct(const LFVector2D &value) const;
		float Normalise();
		void Normalizing();
		LFVector2D MidPoint(const LFVector2D &value) const;
	};
}}}}
