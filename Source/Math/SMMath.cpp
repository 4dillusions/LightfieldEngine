#include "SMMath.h"
#include <cmath>
#include <stdlib.h>

namespace SMEngine { namespace Math
{
	const float SMMath::Pi = 3.141593f;
    const float SMMath::E = 2.718282f;
    const float SMMath::Log10E = 0.4342945f;
    const float SMMath::Log2E = 1.442695f;
    const float SMMath::PiOver2 = 1.570796f;
    const float SMMath::PiOver4 = 0.7853982f;
    const float SMMath::TwoPi = 6.283185f;

    float SMMath::Min(float value1, float value2)
    {
        if (value1 < value2)
            return value1;

        return value2;
    }

    float SMMath::Max(float value1, float value2)
    {
        if (value1 > value2)
            return value1;

        return value2;
    }

	float SMMath::ConvertDegreeToRadian(float degree)
	{
		return (degree * 0.01745329f);
	}

	float SMMath::ConvertRadianToDegree(float radian)
	{
		return (radian * 57.29578f);
	}

	float SMMath::Lerp(float value1, float value2, float amount)
    {
        return (value1 + ((value2 - value1) * amount));
    }

    float SMMath::Clamp(float value, float min, float max)
    {
        value = (value > max) ? max : value;
        value = (value < min) ? min : value;

        return value;
    }

    float SMMath::Distance(float value1, float value2)
    {
        return abs((value1 - value2));
    }
};};
