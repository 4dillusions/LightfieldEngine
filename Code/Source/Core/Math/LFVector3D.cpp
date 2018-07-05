/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVector3D.h"
#include "LFMath.h"

#include <cmath>

namespace LFCore { namespace Math
{
	LFVector3D &LFVector3D::operator = (const LFVector3D &value)
	{
		x = value.x;
		y = value.y;
		z = value.z;

		return *this;
	}

	bool LFVector3D::operator == (const LFVector3D &value) const
	{
		return (x == value.x && y == value.y && z == value.z);
	}

	bool LFVector3D::operator != (const LFVector3D &value) const
	{
		return (x != value.x || y != value.y || z != value.z);
	}

	LFVector3D LFVector3D::operator + (const LFVector3D &value) const
	{
		return LFVector3D(x + value.x, y + value.y, z + value.z);
	}

	LFVector3D LFVector3D::operator + (const float size) const
	{
		return LFVector3D(x + size, y + size, z + size);
	}

	LFVector3D LFVector3D::operator - (const LFVector3D &value) const
	{
		return LFVector3D(x - value.x, y - value.y, z - value.z);
	}

	LFVector3D LFVector3D::operator - (const float size) const
	{
		return LFVector3D(x - size, y - size, z - size);
	}

	LFVector3D LFVector3D::operator * (const LFVector3D &value) const
	{
		return LFVector3D(x * value.x, y * value.y, z * value.z);
	}

	LFVector3D LFVector3D::operator * (const float size) const
	{
		return LFVector3D(x * size, y * size, z * size);
	}

	LFVector3D LFVector3D::operator / (const LFVector3D &value) const
	{
		return LFVector3D(x / value.x, y / value.y, z / value.z);
	}

	LFVector3D LFVector3D::operator / (const float size) const
	{
		return LFVector3D(x / size, y / size, z / size);
	}

	LFVector3D LFVector3D::operator - () const
	{
		return LFVector3D(-x, -y, -z);
	}

	LFVector3D &LFVector3D::operator ++ ()
	{
		++x;
		++y;
		++z;

		return *this;
	}

	LFVector3D &LFVector3D::operator ++ (int)
	{
		x++;
		y++;
		z++;

		return *this;
	}

	LFVector3D &LFVector3D::operator -- ()
	{
		--x;
		--y;
		--z;

		return *this;
	}

	LFVector3D &LFVector3D::operator -- (int)
	{
		x--;
		y--;
		z--;

		return *this;
	}

	LFVector3D &LFVector3D::operator += (const LFVector3D &value)
	{
		x += value.x;
		y += value.y;
		z += value.z;

		return *this;
	}

	LFVector3D &LFVector3D::operator += (const float size)
	{
		x += size;
		y += size;
		z += size;

		return *this;
	}

	LFVector3D &LFVector3D::operator -= (const LFVector3D &value)
	{
		x -= value.x;
		y -= value.y;
		z -= value.z;

		return *this;
	}

	LFVector3D &LFVector3D::operator -= (const float size)
	{
		x -= size;
		y -= size;
		z -= size;

		return *this;
	}

	LFVector3D &LFVector3D::operator *= (const LFVector3D &value)
	{
		x *= value.x;
		y *= value.y;
		z *= value.z;

		return *this;
	}

	LFVector3D &LFVector3D::operator *= (const float size)
	{
		x *= size;
		y *= size;
		z *= size;

		return *this;
	}

	LFVector3D &LFVector3D::operator /= (const LFVector3D &value)
	{
		x /= value.x;
		y /= value.y;
		z /= value.z;

		return *this;
	}

	LFVector3D &LFVector3D::operator /= (const float size)
	{
		x /= size;
		y /= size;
		z /= size;

		return *this;
	}

	bool LFVector3D::operator < (const LFVector3D &value) const
	{
		if (x < value.x && y < value.y && z < value.z) return true;

		return false;
	}

	bool LFVector3D::operator > (const LFVector3D &value) const
	{
		if (x > value.x && y > value.y && z > value.z) return true;

		return false;
	}

	void LFVector3D::Zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
}}
