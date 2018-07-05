/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFMatrix3.h"
#include "LFVector3D.h"

#include <cmath>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	LFMatrix3::LFMatrix3(
		float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;

		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;

		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
	}

	LFMatrix3 &LFMatrix3::operator = (const LFMatrix3 &value)
	{
		m[0][0] = value.m[0][0];
		m[0][1] = value.m[0][1];
		m[0][2] = value.m[0][2];
		
		m[1][0] = value.m[1][0];
		m[1][1] = value.m[1][1];
		m[1][2] = value.m[1][2];
		
		m[2][0] = value.m[2][0];
		m[2][1] = value.m[2][1];
		m[2][2] = value.m[2][2];

		return *this;
	}

	float LFMatrix3::operator() (int indexX, int indexY) const
	{
		return m[indexX][indexY];
	}

	float &LFMatrix3::operator() (int indexX, int indexY)
	{
		return m[indexX][indexY];
	}

	LFMatrix3 LFMatrix3::operator * (const LFMatrix3 &value) const
	{
		LFMatrix3 result;

		result.m[0][0] = m[0][0] * value.m[0][0] + m[0][1] * value.m[1][0] + m[0][2] * value.m[2][0];
		result.m[0][1] = m[0][0] * value.m[0][1] + m[0][1] * value.m[1][1] + m[0][2] * value.m[2][1];
		result.m[0][2] = m[0][0] * value.m[0][2] + m[0][1] * value.m[1][2] + m[0][2] * value.m[2][2];

		result.m[1][0] = m[1][0] * value.m[0][0] + m[1][1] * value.m[1][0] + m[1][2] * value.m[2][0];
		result.m[1][1] = m[1][0] * value.m[0][1] + m[1][1] * value.m[1][1] + m[1][2] * value.m[2][1];
		result.m[1][2] = m[1][0] * value.m[0][2] + m[1][1] * value.m[1][2] + m[1][2] * value.m[2][2];

		result.m[2][0] = m[2][0] * value.m[0][0] + m[2][1] * value.m[1][0] + m[2][2] * value.m[2][0];
		result.m[2][1] = m[2][0] * value.m[0][1] + m[2][1] * value.m[1][1] + m[2][2] * value.m[2][1];
		result.m[2][2] = m[2][0] * value.m[0][2] + m[2][1] * value.m[1][2] + m[2][2] * value.m[2][2];

		return result;
	}

	LFMatrix3 LFMatrix3::operator + (const LFMatrix3 &value) const
	{
		LFMatrix3 result;

		result.m[0][0] = m[0][0] + value.m[0][0];
		result.m[0][1] = m[0][1] + value.m[0][1];
		result.m[0][2] = m[0][2] + value.m[0][2];

		result.m[1][0] = m[1][0] + value.m[1][0];
		result.m[1][1] = m[1][1] + value.m[1][1];
		result.m[1][2] = m[1][2] + value.m[1][2];

		result.m[2][0] = m[2][0] + value.m[2][0];
		result.m[2][1] = m[2][1] + value.m[2][1];
		result.m[2][2] = m[2][2] + value.m[2][2];

		return result;
	}

	LFMatrix3 LFMatrix3::operator - (const LFMatrix3 &value) const
	{
		LFMatrix3 result;

		result.m[0][0] = m[0][0] - value.m[0][0];
		result.m[0][1] = m[0][1] - value.m[0][1];
		result.m[0][2] = m[0][2] - value.m[0][2];

		result.m[1][0] = m[1][0] - value.m[1][0];
		result.m[1][1] = m[1][1] - value.m[1][1];
		result.m[1][2] = m[1][2] - value.m[1][2];

		result.m[2][0] = m[2][0] - value.m[2][0];
		result.m[2][1] = m[2][1] - value.m[2][1];
		result.m[2][2] = m[2][2] - value.m[2][2];
		
		return result;
	}

	bool LFMatrix3::operator == (const LFMatrix3 &value) const
	{
		if (m[0][0] != value.m[0][0] || m[0][1] != value.m[0][1] || m[0][2] != value.m[0][2] ||
			m[1][0] != value.m[1][0] || m[1][1] != value.m[1][1] || m[1][2] != value.m[1][2] ||
			m[2][0] != value.m[2][0] || m[2][1] != value.m[2][1] || m[2][2] != value.m[2][2])
			return false;

		return true;
	}

	bool LFMatrix3::operator != (const LFMatrix3 &value) const
	{
		if (m[0][0] != value.m[0][0] || m[0][1] != value.m[0][1] || m[0][2] != value.m[0][2] ||
			m[1][0] != value.m[1][0] || m[1][1] != value.m[1][1] || m[1][2] != value.m[1][2] ||
			m[2][0] != value.m[2][0] || m[2][1] != value.m[2][1] || m[2][2] != value.m[2][2])
			return true;

		return false;
	}

	LFVector3D LFMatrix3::operator * (const LFVector3D &vector) const
	{
		LFVector3D result;
		
		result.x = m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z;
		result.y = m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z;
		result.z = m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z;

		return result;
	}

	LFMatrix3 LFMatrix3::operator * (float scalar) const
	{
		LFMatrix3 result;

		result.m[0][0] = scalar * m[0][0];
		result.m[0][1] = scalar * m[0][1];
		result.m[0][2] = scalar * m[0][2];

		result.m[1][0] = scalar * m[1][0];
		result.m[1][1] = scalar * m[1][1];
		result.m[1][2] = scalar * m[1][2];

		result.m[2][0] = scalar * m[2][0];
		result.m[2][1] = scalar * m[2][1];
		result.m[2][2] = scalar * m[2][2];
		
		return result;
	}

	bool LFMatrix3::Inverse(LFMatrix3 &inverse, float tolerance) const
	{
		inverse.m[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
		inverse.m[0][1] = m[0][2] * m[2][1] - m[0][1] * m[2][2];
		inverse.m[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
		inverse.m[1][0] = m[1][2] * m[2][0] - m[1][0] * m[2][2];
		inverse.m[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
		inverse.m[1][2] = m[0][2] * m[1][0] - m[0][0] * m[1][2];
		inverse.m[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];
		inverse.m[2][1] = m[0][1] * m[2][0] - m[0][0] * m[2][1];
		inverse.m[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];

		float det =
			m[0][0] * inverse.m[0][0] +
			m[0][1] * inverse.m[1][0] +
			m[0][2] * inverse.m[2][0];

		if (fabs(det) <= tolerance)
			return false;

		float invDet = 1.0 / det;
		
		inverse.m[0][0] *= invDet;
		inverse.m[0][1] *= invDet;
		inverse.m[0][2] *= invDet;

		inverse.m[1][0] *= invDet;
		inverse.m[1][1] *= invDet;
		inverse.m[1][2] *= invDet;

		inverse.m[2][0] *= invDet;
		inverse.m[2][1] *= invDet;
		inverse.m[2][2] *= invDet;

		return true;
	}

	LFMatrix3 LFMatrix3::Inverse(float tolerance) const
	{
		LFMatrix3 result;
		result.Zero();
		Inverse(result, tolerance);
		
		return result;
	}

	LFMatrix3 LFMatrix3::Transpose() const
	{
		LFMatrix3 result;

		result.m[0][0] = m[0][0];
		result.m[0][1] = m[1][0];
		result.m[0][2] = m[2][0];

		result.m[1][0] = m[0][1];
		result.m[1][1] = m[1][1];
		result.m[1][2] = m[2][1];

		result.m[2][0] = m[0][2];
		result.m[2][1] = m[1][2];
		result.m[2][2] = m[2][2];

		return result;
	}

	float LFMatrix3::Determinant() const
	{
		float factor = m[1][1] * m[2][2] - m[1][2] * m[2][1];
		float factor1 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
		float factor2 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

		float result =
			m[0][0] * factor +
			m[0][1] * factor1 +
			m[0][2] * factor2;

		return result;
	}

	void LFMatrix3::Orthonormalize()
	{
		float invLength = 1.0 / sqrt(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);

		m[0][0] *= invLength;
		m[1][0] *= invLength;
		m[2][0] *= invLength;

		float dot = m[0][0] * m[0][1] + m[1][0] * m[1][1] + m[2][0] * m[2][1];

		m[0][1] -= dot * m[0][0];
		m[1][1] -= dot * m[1][0];
		m[2][1] -= dot * m[2][0];

		invLength = 1.0 / sqrt(m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1]);

		m[0][1] *= invLength;
		m[1][1] *= invLength;
		m[2][1] *= invLength;

		float dot1 = m[0][1] * m[0][2] + m[1][1] * m[1][2] + m[2][1] * m[2][2];
		dot = m[0][0] * m[0][2] + m[1][0] * m[1][2] + m[2][0] * m[2][2];

		m[0][2] -= dot * m[0][0] + dot1 * m[0][1];
		m[1][2] -= dot * m[1][0] + dot1 * m[1][1];
		m[2][2] -= dot * m[2][0] + dot1 * m[2][1];

		invLength = 1.0 / sqrt(m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2]);

		m[0][2] *= invLength;
		m[1][2] *= invLength;
		m[2][2] *= invLength;
	}

	void LFMatrix3::Zero()
	{
		m[0][0] = 0; m[0][1] = 0; m[0][2] = 0;
		m[1][0] = 0; m[1][1] = 0; m[1][2] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 0;
	}

	void LFMatrix3::Identity()
	{
		m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
		m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
	}
}}}}
