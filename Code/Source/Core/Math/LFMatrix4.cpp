/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFMatrix4.h"
#include "LFVector2D.h"

namespace LFCore { namespace Math
{
	LFMatrix4::LFMatrix4()
	{
		Zero();
	}

	LFMatrix4::LFMatrix4(
		float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33)
    {
            m[0][0] = m00;
            m[0][1] = m01;
            m[0][2] = m02;
            m[0][3] = m03;
            m[1][0] = m10;
            m[1][1] = m11;
            m[1][2] = m12;
            m[1][3] = m13;
            m[2][0] = m20;
            m[2][1] = m21;
            m[2][2] = m22;
            m[2][3] = m23;
            m[3][0] = m30;
            m[3][1] = m31;
            m[3][2] = m32;
            m[3][3] = m33;
    }

	LFMatrix4 &LFMatrix4::operator = (const LFMatrix4 &value)
	{
		m[0][0] = value.m[0][0];
        m[0][1] = value.m[0][1];
        m[0][2] = value.m[0][2];
        m[0][3] = value.m[0][3];
        m[1][0] = value.m[1][0];
        m[1][1] = value.m[1][1];
        m[1][2] = value.m[1][2];
        m[1][3] = value.m[1][3];
        m[2][0] = value.m[2][0];
        m[2][1] = value.m[2][1];
        m[2][2] = value.m[2][2];
        m[2][3] = value.m[2][3];
        m[3][0] = value.m[3][0];
        m[3][1] = value.m[3][1];
        m[3][2] = value.m[3][2];
        m[3][3] = value.m[3][3];

		return *this;
	}

	float LFMatrix4::operator() (int indexX, int indexY) const
	{
		return m[indexX][indexY];
	}

	float &LFMatrix4::operator() (int indexX, int indexY)
	{
		return m[indexX][indexY];
	}

	LFMatrix4 LFMatrix4::operator * (const LFMatrix4 &value) const
	{
		LFMatrix4 result;

		result.m[0][0] = m[0][0] * value.m[0][0] + m[0][1] * value.m[1][0] + m[0][2] * value.m[2][0] + m[0][3] * value.m[3][0];
		result.m[0][1] = m[0][0] * value.m[0][1] + m[0][1] * value.m[1][1] + m[0][2] * value.m[2][1] + m[0][3] * value.m[3][1];
		result.m[0][2] = m[0][0] * value.m[0][2] + m[0][1] * value.m[1][2] + m[0][2] * value.m[2][2] + m[0][3] * value.m[3][2];
		result.m[0][3] = m[0][0] * value.m[0][3] + m[0][1] * value.m[1][3] + m[0][2] * value.m[2][3] + m[0][3] * value.m[3][3];

		result.m[1][0] = m[1][0] * value.m[0][0] + m[1][1] * value.m[1][0] + m[1][2] * value.m[2][0] + m[1][3] * value.m[3][0];
		result.m[1][1] = m[1][0] * value.m[0][1] + m[1][1] * value.m[1][1] + m[1][2] * value.m[2][1] + m[1][3] * value.m[3][1];
		result.m[1][2] = m[1][0] * value.m[0][2] + m[1][1] * value.m[1][2] + m[1][2] * value.m[2][2] + m[1][3] * value.m[3][2];
		result.m[1][3] = m[1][0] * value.m[0][3] + m[1][1] * value.m[1][3] + m[1][2] * value.m[2][3] + m[1][3] * value.m[3][3];

		result.m[2][0] = m[2][0] * value.m[0][0] + m[2][1] * value.m[1][0] + m[2][2] * value.m[2][0] + m[2][3] * value.m[3][0];
		result.m[2][1] = m[2][0] * value.m[0][1] + m[2][1] * value.m[1][1] + m[2][2] * value.m[2][1] + m[2][3] * value.m[3][1];
		result.m[2][2] = m[2][0] * value.m[0][2] + m[2][1] * value.m[1][2] + m[2][2] * value.m[2][2] + m[2][3] * value.m[3][2];
		result.m[2][3] = m[2][0] * value.m[0][3] + m[2][1] * value.m[1][3] + m[2][2] * value.m[2][3] + m[2][3] * value.m[3][3];

		result.m[3][0] = m[3][0] * value.m[0][0] + m[3][1] * value.m[1][0] + m[3][2] * value.m[2][0] + m[3][3] * value.m[3][0];
		result.m[3][1] = m[3][0] * value.m[0][1] + m[3][1] * value.m[1][1] + m[3][2] * value.m[2][1] + m[3][3] * value.m[3][1];
		result.m[3][2] = m[3][0] * value.m[0][2] + m[3][1] * value.m[1][2] + m[3][2] * value.m[2][2] + m[3][3] * value.m[3][2];
		result.m[3][3] = m[3][0] * value.m[0][3] + m[3][1] * value.m[1][3] + m[3][2] * value.m[2][3] + m[3][3] * value.m[3][3];

		return result;
	}

	LFMatrix4 LFMatrix4::operator + (const LFMatrix4 &value) const
	{
		LFMatrix4 result;

		result.m[0][0] = m[0][0] + value.m[0][0];
		result.m[0][1] = m[0][1] + value.m[0][1];
		result.m[0][2] = m[0][2] + value.m[0][2];
		result.m[0][3] = m[0][3] + value.m[0][3];

		result.m[1][0] = m[1][0] + value.m[1][0];
		result.m[1][1] = m[1][1] + value.m[1][1];
		result.m[1][2] = m[1][2] + value.m[1][2];
		result.m[1][3] = m[1][3] + value.m[1][3];

		result.m[2][0] = m[2][0] + value.m[2][0];
		result.m[2][1] = m[2][1] + value.m[2][1];
		result.m[2][2] = m[2][2] + value.m[2][2];
		result.m[2][3] = m[2][3] + value.m[2][3];

		result.m[3][0] = m[3][0] + value.m[3][0];
		result.m[3][1] = m[3][1] + value.m[3][1];
		result.m[3][2] = m[3][2] + value.m[3][2];
		result.m[3][3] = m[3][3] + value.m[3][3];

		return result;
	}

	LFMatrix4 LFMatrix4::operator - (const LFMatrix4 &value) const
	{
		LFMatrix4 result;

		result.m[0][0] = m[0][0] - value.m[0][0];
		result.m[0][1] = m[0][1] - value.m[0][1];
		result.m[0][2] = m[0][2] - value.m[0][2];
		result.m[0][3] = m[0][3] - value.m[0][3];

		result.m[1][0] = m[1][0] - value.m[1][0];
		result.m[1][1] = m[1][1] - value.m[1][1];
		result.m[1][2] = m[1][2] - value.m[1][2];
		result.m[1][3] = m[1][3] - value.m[1][3];

		result.m[2][0] = m[2][0] - value.m[2][0];
		result.m[2][1] = m[2][1] - value.m[2][1];
		result.m[2][2] = m[2][2] - value.m[2][2];
		result.m[2][3] = m[2][3] - value.m[2][3];

		result.m[3][0] = m[3][0] - value.m[3][0];
		result.m[3][1] = m[3][1] - value.m[3][1];
		result.m[3][2] = m[3][2] - value.m[3][2];
		result.m[3][3] = m[3][3] - value.m[3][3];

		return result;
	}

	bool LFMatrix4::operator == (const LFMatrix4 &value) const
	{
		if (m[0][0] != value.m[0][0] || m[0][1] != value.m[0][1] || m[0][2] != value.m[0][2] || m[0][3] != value.m[0][3] ||
		    m[1][0] != value.m[1][0] || m[1][1] != value.m[1][1] || m[1][2] != value.m[1][2] || m[1][3] != value.m[1][3] ||
			m[2][0] != value.m[2][0] || m[2][1] != value.m[2][1] || m[2][2] != value.m[2][2] || m[2][3] != value.m[2][3] ||
			m[3][0] != value.m[3][0] || m[3][1] != value.m[3][1] || m[3][2] != value.m[3][2] || m[3][3] != value.m[3][3])
				return false;

		return true;
	}

	bool LFMatrix4::operator != (const LFMatrix4 &value) const
	{
		if (m[0][0] != value.m[0][0] || m[0][1] != value.m[0][1] || m[0][2] != value.m[0][2] || m[0][3] != value.m[0][3] ||
		    m[1][0] != value.m[1][0] || m[1][1] != value.m[1][1] || m[1][2] != value.m[1][2] || m[1][3] != value.m[1][3] ||
			m[2][0] != value.m[2][0] || m[2][1] != value.m[2][1] || m[2][2] != value.m[2][2] || m[2][3] != value.m[2][3] ||
			m[3][0] != value.m[3][0] || m[3][1] != value.m[3][1] || m[3][2] != value.m[3][2] || m[3][3] != value.m[3][3])
				return true;

		return false;
	}

	void LFMatrix4::Zero()
	{
		m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
		m[1][0] = 0; m[1][1] = 0; m[1][2] = 0; m[1][3] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 0; m[2][3] = 0;
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 0;
	}

	void LFMatrix4::Identity()
	{
		m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
		m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	}

	void LFMatrix4::Translation(const LFVector2D &vector)
	{
		m[3][0] = vector.x;
        m[3][1] = vector.y;
	}
}}
