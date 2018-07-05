#pragma once

namespace SMEngine { namespace Math
{
    /*
    Burkoló osztály matematikai mûveletekhez,

    Használat:
    float pi = SMMath::Pi;
    */
	class SMMath
	{
	public:
        static const float Pi;
        static const float E;
        static const float Log10E;
        static const float Log2E;
        static const float PiOver2;
        static const float PiOver4;
        static const float TwoPi;

        static float Min(float value1, float value2); //int min = SMMath::Min(10, 23); //10
        static float Max(float value1, float value2); //int max = SMMath::Max(10, 23); //23
		static float ConvertDegreeToRadian(float degree);
		static float ConvertRadianToDegree(float radian);
		static float Lerp(float value1, float value2, float amount); //az amount 0 és 1 közti érték lehet
		static float Clamp(float value, float min, float max); //a value értéket min és max közé kényszeríti
		static float Distance(float value1, float value2); //int dist = SMMath::Distance(10.5f, 12.5f); //2
	};
};};
