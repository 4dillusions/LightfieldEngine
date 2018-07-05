#pragma once

namespace SMEngine { namespace Math
{
    /*
    Burkol� oszt�ly matematikai m�veletekhez,

    Haszn�lat:
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
		static float Lerp(float value1, float value2, float amount); //az amount 0 �s 1 k�zti �rt�k lehet
		static float Clamp(float value, float min, float max); //a value �rt�ket min �s max k�z� k�nyszer�ti
		static float Distance(float value1, float value2); //int dist = SMMath::Distance(10.5f, 12.5f); //2
	};
};};
