#include "SMMatrix4.h"

namespace SMEngine { namespace Math
{
	SMMatrix4::SMMatrix4()
	{
		Zero();
	}

	/*
	float NCGMatrix4::operator() (int indexX, int indexY) const
	{
		return m[indexX][indexY];
	}

	float &NCGMatrix4::operator() (int indexX, int indexY)
	{
		return m[indexX][indexY];
	}
	*/

	SMMatrix4 SMMatrix4::operator * (const SMMatrix4 &value) const
	{
		SMMatrix4 result;

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

	SMMatrix4 SMMatrix4::operator + (const SMMatrix4 &value) const
	{
		SMMatrix4 result;

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

	SMMatrix4 SMMatrix4::operator - (const SMMatrix4 &value) const
	{
		SMMatrix4 result;

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

	bool SMMatrix4::operator == (const SMMatrix4 &value) const
	{
		if(m[0][0] != value.m[0][0] || m[0][1] != value.m[0][1] || m[0][2] != value.m[0][2] || m[0][3] != value.m[0][3] ||
		    m[1][0] != value.m[1][0] || m[1][1] != value.m[1][1] || m[1][2] != value.m[1][2] || m[1][3] != value.m[1][3] ||
			m[2][0] != value.m[2][0] || m[2][1] != value.m[2][1] || m[2][2] != value.m[2][2] || m[2][3] != value.m[2][3] ||
			m[3][0] != value.m[3][0] || m[3][1] != value.m[3][1] || m[3][2] != value.m[3][2] || m[3][3] != value.m[3][3])
				return false;

		return true;
	}

	bool SMMatrix4::operator != (const SMMatrix4 &value) const
	{
		if(m[0][0] != value.m[0][0] || m[0][1] != value.m[0][1] || m[0][2] != value.m[0][2] || m[0][3] != value.m[0][3] ||
		    m[1][0] != value.m[1][0] || m[1][1] != value.m[1][1] || m[1][2] != value.m[1][2] || m[1][3] != value.m[1][3] ||
			m[2][0] != value.m[2][0] || m[2][1] != value.m[2][1] || m[2][2] != value.m[2][2] || m[2][3] != value.m[2][3] ||
			m[3][0] != value.m[3][0] || m[3][1] != value.m[3][1] || m[3][2] != value.m[3][2] || m[3][3] != value.m[3][3])
				return true;

		return false;
	}

	void SMMatrix4::Zero()
	{
		m[0][0] = 0; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
		m[1][0] = 0; m[1][1] = 0; m[1][2] = 0; m[1][3] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 0; m[2][3] = 0;
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 0;
	}

	void SMMatrix4::Identity()
	{
		m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
		m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
		m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	}
};};
