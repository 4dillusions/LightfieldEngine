/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVector2D.h"
#include "LFMath.h"

#include <cmath>

namespace LFCore { namespace Math
{
	LFVector2D &LFVector2D::operator = (const LFVector2D &value)
	{
		x = value.x;
		y = value.y;

		return *this;
	}

	bool LFVector2D::operator == (const LFVector2D &value) const
	{
		return (x == value.x && y == value.y);
	}

	bool LFVector2D::operator != (const LFVector2D &value) const
	{
		return (x != value.x || y != value.y);
	}

	LFVector2D LFVector2D::operator + (const LFVector2D &value) const
	{
		return LFVector2D(x + value.x, y + value.y);
	}

	LFVector2D LFVector2D::operator + (const float size) const
	{
		return LFVector2D(x + size, y + size);
	}

	LFVector2D LFVector2D::operator - (const LFVector2D &value) const
	{
		return LFVector2D(x - value.x, y - value.y);
	}

	LFVector2D LFVector2D::operator - (const float size) const
	{
		return LFVector2D(x - size, y - size);
	}

	LFVector2D LFVector2D::operator * (const LFVector2D &value) const
	{
		return LFVector2D(x * value.x, y * value.y);
	}

	LFVector2D LFVector2D::operator * (const float size) const
	{
		return LFVector2D(x * size, y * size);
	}

	LFVector2D LFVector2D::operator / (const LFVector2D &value) const
	{
		return LFVector2D(x / value.x, y / value.y);
	}

	LFVector2D LFVector2D::operator / (const float size) const
	{
		return LFVector2D(x / size, y / size);
	}

	LFVector2D LFVector2D::operator - () const
	{
		return LFVector2D(-x, -y);
	}

	LFVector2D &LFVector2D::operator ++ ()
	{
		++x;
		++y;

		return *this;
	}

	LFVector2D &LFVector2D::operator ++ (int)
	{
		x++;
		y++;

		return *this;
	}

	LFVector2D &LFVector2D::operator -- ()
	{
		--x;
		--y;

		return *this;
	}

	LFVector2D &LFVector2D::operator -- (int)
	{
		x--;
		y--;

		return *this;
	}

	LFVector2D &LFVector2D::operator += (const LFVector2D &value)
	{
		x += value.x;
		y += value.y;

		return *this;
	}

	LFVector2D &LFVector2D::operator += (const float size)
	{
		x += size;
		y += size;

		return *this;
	}

	LFVector2D &LFVector2D::operator -= (const LFVector2D &value)
	{
		x -= value.x;
		y -= value.y;

		return *this;
	}

	LFVector2D &LFVector2D::operator -= (const float size)
	{
		x -= size;
		y -= size;

		return *this;
	}

	LFVector2D &LFVector2D::operator *= (const LFVector2D &value)
	{
		x *= value.x;
		y *= value.y;

		return *this;
	}

	LFVector2D &LFVector2D::operator *= (const float size)
	{
		x *= size;
		y *= size;

		return *this;
	}

	LFVector2D &LFVector2D::operator /= (const LFVector2D &value)
	{
		x /= value.x;
		y /= value.y;

		return *this;
	}

	LFVector2D &LFVector2D::operator /= (const float size)
	{
		x /= size;
		y /= size;

		return *this;
	}

	bool LFVector2D::operator < (const LFVector2D &value) const
	{
		if (x < value.x && y < value.y) return true;

		return false;
	}

	bool LFVector2D::operator > (const LFVector2D &value) const
	{
		if (x > value.x && y > value.y) return true;

		return false;
	}

	void LFVector2D::Zero()
	{
		x = 0.0f;
		y = 0.0f;
	}

	void LFVector2D::Up()
	{
		x = 0.0f;
		y = -1.0f;
	}

	void LFVector2D::Down()
	{
		x = 0.0f;
		y = 1.0f;
	}

	void LFVector2D::Left()
	{
		x = -1.0f;
		y = 0.0f;
	}

	void LFVector2D::Right()
	{
		x = 1.0f;
		y = 0.0f;
	}

	void LFVector2D::Rotate(float angle)
	{
		angle = -LFMath::ConvertDegreeToRadian(angle);

		float x1 = (x * cosf(angle)) - (y * sinf(angle));
		float y1 = (y * cosf(angle)) + (x * sinf(angle));

		x = x1;
		y = y1;
	}

	void LFVector2D::RotateCeil(float angle)
	{
		angle = -LFMath::ConvertDegreeToRadian(angle);

		float x1 = (x * cosf(angle)) - (y * sinf(angle));
		float y1 = (y * cosf(angle)) + (x * sinf(angle));

		x = ceilf(x1);
		y = ceilf(y1);
	}

    void LFVector2D::Rotate90DegreeForward()
	{
		float x1 = y;
		float y1 = -x;

		x = x1;
		y = y1;
	}

	void LFVector2D::Rotate90DegreeBackward()
	{
		float x1 = -y;
		float y1 = x;

		x = x1;
		y = y1;
	}
}}
