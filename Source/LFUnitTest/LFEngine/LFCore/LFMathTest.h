/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore 
{
	class LFMathTest final
	{
	public:
		LFMathTest() = delete;
		LFMathTest(const LFMathTest &) = delete;
		LFMathTest(LFMathTest &&) = delete;
		LFMathTest &operator=(const LFMathTest &) = delete;
		LFMathTest &operator=(LFMathTest &&) = delete;
		~LFMathTest() = delete;

		static void LFMathMainTest();
		static void Vector2DTest();
		static void CircleTest();
		static void RandomTest();
		static void RectangleTest();
		static void Vector3DTest();
		static void Vector4DTest();
		static void Matrix3DTest();
		static void Matrix4DTest();

		static void RunAllTests();
	};
}}}}
