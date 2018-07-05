/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFMath.h"
#include <cmath>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	const float LFMath::Pi = 3.141593f;
    const float LFMath::E = 2.718282f;
    const float LFMath::Log10E = 0.4342945f;
    const float LFMath::Log2E = 1.442695f;
    const float LFMath::PiOver2 = 1.570796f;
    const float LFMath::PiOver4 = 0.7853982f;
    const float LFMath::TwoPi = 6.283185f;

	float LFMath::ConvertDegreeToRadian(float degree)
	{
		return (degree * 0.01745329f);
	}

	float LFMath::ConvertRadianToDegree(float radian)
	{
		return (radian * 57.29578f);
	}

	float LFMath::Lerp(float value1, float value2, float amount)
    {
        return (value1 + ((value2 - value1) * amount));
    }

    float LFMath::Clamp(float value, float min, float max)
    {
        value = (value > max) ? max : value;
        value = (value < min) ? min : value;

        return value;
    }

    float LFMath::Distance(float value1, float value2)
    {
        return Abs((value1 - value2));
    }
	
	float LFMath::Log(int x, float value)
	{
		return static_cast<float>(log(value)) / static_cast<float>(log(x));
	}

	float LFMath::Pow(int x, float value)
	{
		return static_cast<float>(pow(x, value));
	}

	bool LFMath::IsPowerOfTwo(int value)
	{
		return (value & ( value - 1 )) == 0 && value > 0; //return !IsFloatNumber(Log(2, value));
	}
}}}}
