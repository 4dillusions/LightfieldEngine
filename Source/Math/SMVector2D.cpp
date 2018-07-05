#include "SMVector2D.h"
#include "SMMath.h"
#include <cmath>

namespace SMEngine { namespace Math
{
	SMVector2D &SMVector2D::operator = (const SMVector2D &value)
	{
		x = value.x;
		y = value.y;

		return *this;
	}

	bool SMVector2D::operator == (const SMVector2D &value) const
	{
		return (x == value.x && y == value.y);
	}

	bool SMVector2D::operator != (const SMVector2D &value) const
	{
		return (x != value.x || y != value.y);
	}

	SMVector2D SMVector2D::operator + (const SMVector2D &value) const
	{
		return SMVector2D(x + value.x, y + value.y);
	}

	SMVector2D SMVector2D::operator + (const float size) const
	{
		return SMVector2D(x + size, y + size);
	}

	SMVector2D SMVector2D::operator - (const SMVector2D &value) const
	{
		return SMVector2D(x - value.x, y - value.y);
	}

	SMVector2D SMVector2D::operator - (const float size) const
	{
		return SMVector2D(x - size, y - size);
	}

	SMVector2D SMVector2D::operator * (const SMVector2D &value) const
	{
		return SMVector2D(x * value.x, y * value.y);
	}

	SMVector2D SMVector2D::operator * (const float size) const
	{
		return SMVector2D(x * size, y * size);
	}

	SMVector2D SMVector2D::operator / (const SMVector2D &value) const
	{
		return SMVector2D(x / value.x, y / value.y);
	}

	SMVector2D SMVector2D::operator / (const float size) const
	{
		return SMVector2D(x / size, y / size);
	}

	SMVector2D SMVector2D::operator - () const
	{
		return SMVector2D(-x, -y);
	}

	SMVector2D &SMVector2D::operator ++ ()
	{
		++x;
		++y;

		return *this;
	}

	SMVector2D &SMVector2D::operator ++ (int)
	{
		x++;
		y++;

		return *this;
	}

	SMVector2D &SMVector2D::operator -- ()
	{
		--x;
		--y;

		return *this;
	}

	SMVector2D &SMVector2D::operator -- (int)
	{
		x--;
		y--;

		return *this;
	}

	SMVector2D &SMVector2D::operator += (const SMVector2D &value)
	{
		x += value.x;
		y += value.y;

		return *this;
	}

	SMVector2D &SMVector2D::operator += (const float size)
	{
		x += size;
		y += size;

		return *this;
	}

	SMVector2D &SMVector2D::operator -= (const SMVector2D &value)
	{
		x -= value.x;
		y -= value.y;

		return *this;
	}

	SMVector2D &SMVector2D::operator -= (const float size)
	{
		x -= size;
		y -= size;

		return *this;
	}

	SMVector2D &SMVector2D::operator *= (const SMVector2D &value)
	{
		x *= value.x;
		y *= value.y;

		return *this;
	}

	SMVector2D &SMVector2D::operator *= (const float size)
	{
		x *= size;
		y *= size;

		return *this;
	}

	SMVector2D &SMVector2D::operator /= (const SMVector2D &value)
	{
		x /= value.x;
		y /= value.y;

		return *this;
	}

	SMVector2D &SMVector2D::operator /= (const float size)
	{
		x /= size;
		y /= size;

		return *this;
	}

	bool SMVector2D::operator < (const SMVector2D &value) const
	{
		if(x < value.x && y < value.y) return true;

		return false;
	}

	bool SMVector2D::operator > (const SMVector2D &value) const
	{
		if(x > value.x && y > value.y) return true;

		return false;
	}

	void SMVector2D::Zero()
	{
		x = 0.0f;
		y = 0.0f;
	}

	void SMVector2D::Rotate(float angle)
	{
		angle = -SMMath::ConvertDegreeToRadian(angle);

		float x1 = (x * cosf(angle)) - (y * sinf(angle));
		float y1 = (y * cosf(angle)) + (x * sinf(angle));

		x = x1;
		y = y1;
	}

	void SMVector2D::RotateCeil(float angle)
	{
		angle = -SMMath::ConvertDegreeToRadian(angle);

		float x1 = (x * cosf(angle)) - (y * sinf(angle));
		float y1 = (y * cosf(angle)) + (x * sinf(angle));

		x = ceilf(x1);
		y = ceilf(y1);
	}

    void SMVector2D::Rotate90DegreeForward()
	{
		float x1 = y;
		float y1 = -x;

		x = x1;
		y = y1;
	}

	void SMVector2D::Rotate90DegreeBackward()
	{
		float x1 = -y;
		float y1 = x;

		x = x1;
		y = y1;
	}
};};
