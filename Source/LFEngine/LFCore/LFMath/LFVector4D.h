/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	/**
		@brief
		4D Vector and math calculations
	*/
	class LFVector4D final
	{
	public:
		float x = 0, y = 0, z = 0, w = 0;

		LFVector4D() = default;
		explicit LFVector4D(const float scale);
		LFVector4D(const float x, const float y, float z, float w);
		LFVector4D(const LFVector4D &other) = default;

		LFVector4D &operator = (const LFVector4D &value);

		bool operator == (const LFVector4D &value) const;
		bool operator != (const LFVector4D &value) const;

		LFVector4D operator + (const LFVector4D &value) const;
		LFVector4D operator + (const float size) const;

		LFVector4D operator - (const LFVector4D &value) const;
		LFVector4D operator - (const float size) const;

		LFVector4D operator * (const LFVector4D &value) const;
		LFVector4D operator * (const float size) const;

		LFVector4D operator / (const LFVector4D &value) const;
		LFVector4D operator / (const float size) const;

		LFVector4D operator - () const;

		LFVector4D &operator ++ ();
		LFVector4D &operator ++ (int);
		LFVector4D &operator -- ();
		LFVector4D &operator -- (int);

		LFVector4D &operator += (const LFVector4D &value);
		LFVector4D &operator += (const float size);

		LFVector4D &operator -= (const LFVector4D &value);
		LFVector4D &operator -= (const float size);

		LFVector4D &operator *= (const LFVector4D &value);
		LFVector4D &operator *= (const float size);

		LFVector4D &operator /= (const LFVector4D &value);
		LFVector4D &operator /= (const float size);

		bool operator < (const LFVector4D &value) const;
		bool operator > (const LFVector4D &value) const;

		void Zero();
		float DotProduct(const LFVector4D &value) const;
	};
}}}}
