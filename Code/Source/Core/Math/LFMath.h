/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"

namespace LFCore { namespace Math
{
	class LFCORE_LIBRARY LFMath
	{
	public:
        static const float Pi;
        static const float E;
        static const float Log10E;
        static const float Log2E;
        static const float PiOver2;
        static const float PiOver4;
        static const float TwoPi;

		template<typename T> static T Min(T value1, T value2) { return (value1 < value2) ? value1 : value2; }
		template<typename T> static T Max(T value1, T value2) { return (value1 > value2) ? value1 : value2; }
		template<typename T> static T Max3(T value1, T value2, T value3) { return (value1 > value2) ? ((value1 > value3) ? value1 : value3) : (( value2 > value3) ? value2 : value3); }
		template<typename T> static T Min3(T value1, T value2, T value3) { return (value1 < value2) ? ((value1 < value3) ? value1 : value3) : (( value2 < value3) ? value2 : value3); }
		template<typename T> static T Abs(T value) { return (value < 0) ? -value : value; }

		static float ConvertDegreeToRadian(float degree);
		static float ConvertRadianToDegree(float radian);
		static float Lerp(float value1, float value2, float amount);
		static float Clamp(float value, float min, float max);
		static float Distance(float value1, float value2);
		static float Log(int x, float value);
		static float Pow(int x, float value);
		static bool IsPowerOfTwo(int value);
	};
}}
