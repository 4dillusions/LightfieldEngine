/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVector4D.h"

#include <cmath>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	LFVector4D::LFVector4D(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w)
	{}

	LFVector4D::LFVector4D(const float scale) : x(scale), y(scale), z(scale), w(scale)
	{}

	LFVector4D &LFVector4D::operator = (const LFVector4D &value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;

		return *this;
	}

	bool LFVector4D::operator == (const LFVector4D &value) const
	{
		return (x == value.x && y == value.y && z == value.z && w == value.w);
	}

	bool LFVector4D::operator != (const LFVector4D &value) const
	{
		return (x != value.x || y != value.y || z != value.z || w != value.w);
	}

	LFVector4D LFVector4D::operator + (const LFVector4D &value) const
	{
		return LFVector4D(x + value.x, y + value.y, z + value.z, w + value.w);
	}

	LFVector4D LFVector4D::operator + (const float size) const
	{
		return LFVector4D(x + size, y + size, z + size, w + size);
	}

	LFVector4D LFVector4D::operator - (const LFVector4D &value) const
	{
		return LFVector4D(x - value.x, y - value.y, z - value.z, w - value.w);
	}

	LFVector4D LFVector4D::operator - (const float size) const
	{
		return LFVector4D(x - size, y - size, z - size, w - size);
	}

	LFVector4D LFVector4D::operator * (const LFVector4D &value) const
	{
		return LFVector4D(x * value.x, y * value.y, z * value.z, w * value.w);
	}

	LFVector4D LFVector4D::operator * (const float size) const
	{
		return LFVector4D(x * size, y * size, z * size, w * size);
	}

	LFVector4D LFVector4D::operator / (const LFVector4D &value) const
	{
		return LFVector4D(x / value.x, y / value.y, z / value.z, w / value.w);
	}

	LFVector4D LFVector4D::operator / (const float size) const
	{
		return LFVector4D(x / size, y / size, z / size, w / size);
	}

	LFVector4D LFVector4D::operator - () const
	{
		return LFVector4D(-x, -y, -z, -w);
	}

	LFVector4D &LFVector4D::operator ++ ()
	{
		++x;
		++y;
		++z;
		++w;

		return *this;
	}

	LFVector4D &LFVector4D::operator ++ (int)
	{
		x++;
		y++;
		z++;
		w++;

		return *this;
	}

	LFVector4D &LFVector4D::operator -- ()
	{
		--x;
		--y;
		--z;
		--w;

		return *this;
	}

	LFVector4D &LFVector4D::operator -- (int)
	{
		x--;
		y--;
		z--;
		w--;

		return *this;
	}

	LFVector4D &LFVector4D::operator += (const LFVector4D &value)
	{
		x += value.x;
		y += value.y;
		z += value.z;
		w += value.w;

		return *this;
	}

	LFVector4D &LFVector4D::operator += (const float size)
	{
		x += size;
		y += size;
		z += size;
		w += size;

		return *this;
	}

	LFVector4D &LFVector4D::operator -= (const LFVector4D &value)
	{
		x -= value.x;
		y -= value.y;
		z -= value.z;
		w -= value.w;

		return *this;
	}

	LFVector4D &LFVector4D::operator -= (const float size)
	{
		x -= size;
		y -= size;
		z -= size;
		w -= size;

		return *this;
	}

	LFVector4D &LFVector4D::operator *= (const LFVector4D &value)
	{
		x *= value.x;
		y *= value.y;
		z *= value.z;
		w *= value.w;

		return *this;
	}

	LFVector4D &LFVector4D::operator *= (const float size)
	{
		x *= size;
		y *= size;
		z *= size;
		w *= size;

		return *this;
	}

	LFVector4D &LFVector4D::operator /= (const LFVector4D &value)
	{
		x /= value.x;
		y /= value.y;
		z /= value.z;
		w /= value.w;

		return *this;
	}

	LFVector4D &LFVector4D::operator /= (const float size)
	{
		x /= size;
		y /= size;
		z /= size;
		w /= size;

		return *this;
	}

	bool LFVector4D::operator < (const LFVector4D &value) const
	{
		if (x < value.x && y < value.y && z < value.z && w < value.w) return true;

		return false;
	}

	bool LFVector4D::operator > (const LFVector4D &value) const
	{
		if (x > value.x && y > value.y && z > value.z && w > value.w) return true;

		return false;
	}

	void LFVector4D::Zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	float LFVector4D::DotProduct(const LFVector4D &value) const
	{
		return x * value.x + y * value.y + z * value.z + w * value.w;
	}
}}}}
