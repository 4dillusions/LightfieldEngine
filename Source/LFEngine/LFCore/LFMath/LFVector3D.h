/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	/**
		@brief
		3D Vector and math calculations
	*/
	class LFVector3D final
	{
	public:
		float x = 0, y = 0, z = 0;

		LFVector3D() = default;
		LFVector3D(const LFVector3D &other) = default;
		explicit LFVector3D(const float scale);
		LFVector3D(const float x, const float y, float z);

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
		float Length() const;
		float Distance(const LFVector3D &value) const;
		float DotProduct(const LFVector3D &value) const;
		LFVector3D CrossProduct(const LFVector3D &value) const;
		float Normalise();
		void Normalizing();
		LFVector3D MidPoint(const LFVector3D &value) const;
	};
}}}}
