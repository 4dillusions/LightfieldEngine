/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVector3D.h"

#include <cmath>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	LFVector3D::LFVector3D(const float scale) : x(scale), y(scale), z(scale) 
	{}

	LFVector3D::LFVector3D(const float x, const float y, float z) : x(x), y(y), z(z) 
	{}

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

	float LFVector3D::Length() const
	{
		return static_cast<float>(sqrt(x * x + y * y + z * z));
	}

	float LFVector3D::Distance(const LFVector3D &value) const
	{
		return (*this - value).Length();
	}

	float LFVector3D::DotProduct(const LFVector3D &value) const
	{
		return x * value.x + y * value.y + z * value.z;
	}

	LFVector3D LFVector3D::CrossProduct(const LFVector3D &value) const
	{
		return LFVector3D(y * value.z - z * value.y, z * value.x - x * value.z, x * value.y - y * value.x);
	}

	float LFVector3D::Normalise()
	{
		float result = sqrt(x * x + y * y + z * z);

		if (result > 1e-08)
		{
			float length = 1.0 / result;
			x *= length;
			y *= length;
			z *= length;
		}

		return result;
	}

	void LFVector3D::Normalizing()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;
	}

	LFVector3D LFVector3D::MidPoint(const LFVector3D &value) const
	{
		return LFVector3D((x + value.x) * 0.5, (y + value.y) * 0.5, (z + value.z) * 0.5);
	}
}}}}
