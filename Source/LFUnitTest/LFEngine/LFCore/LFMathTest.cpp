/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFMathTest.h"
#include "..\..\LFTest.h"
#include "..\..\..\LFEngine\LFCore\LFCore.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFMath.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFCircle.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFRandom.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFRectangle.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFVector3D.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFVector4D.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFMatrix3.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFMatrix4.h"

#include <cmath>

using namespace LF3Engine::LFUnitTest;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore
{
	void LFMathTest::LFMathMainTest()
	{
		LFTest::AssertOk(LFMath::Min(10, 23) == 10, INFO);
		LFTest::AssertOk(LFMath::Max(10, 23) == 23, INFO);
		LFTest::AssertOk(LFMath::Lerp(10, 20, 0.5) == 15, INFO);
		LFTest::AssertOk(LFMath::Abs(-3.12) == 3.12 && LFMath::Abs(3.12) == 3.12, INFO);
		LFTest::AssertOk(LFMath::Clamp(12, -10, 10) == 10 && LFMath::Clamp(-15, -10, 10) == -10, INFO);
		LFTest::AssertOk(LFMath::Distance(10.5f, 12.5f) == 2, INFO);
		LFTest::AssertOk(LFMath::Log(3, 9) == 2, INFO);
		LFTest::AssertOk(LFMath::Log(10, 1000) == 3, INFO);
		LFTest::AssertOk(LFMath::Pow(3, 2) == 9, INFO);
		LFTest::AssertOk(LFMath::Pow(10, 3) == 1000, INFO);
		LFTest::AssertOk(LFMath::IsPowerOfTwo(1024), INFO);
		LFTest::AssertOk(!LFMath::IsPowerOfTwo(127), INFO);
	}

	void LFMathTest::Vector2DTest()
	{
		LFVector2D vec(20, 30);
		LFVector2D vec2 = vec;
		LFVector2D vec3;
		vec3 = vec;

		LFVector2D vec4 = static_cast<LFVector2D>(12);
		LFVector2D vec7(20, 30);

		LFTest::AssertOk(vec == vec2, INFO);
		LFTest::AssertOk(vec == vec3, INFO);
		LFTest::AssertOk(vec4.x == 12 && vec4.y == 12, INFO);
		LFTest::AssertOk(vec != LFVector2D(), INFO);

		LFTest::AssertOk((LFVector2D(1, 2) + LFVector2D(3, 4)) == LFVector2D(4, 6), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) + 10) == LFVector2D(11, 12), INFO);
		LFTest::AssertOk((LFVector2D(3, 4) - LFVector2D(1, 2)) == LFVector2D(2, 2), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) - 1) == LFVector2D(0, 1), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) * LFVector2D(3, 4)) == LFVector2D(3, 8), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) * 10) == LFVector2D(10, 20), INFO);
		LFTest::AssertOk((LFVector2D(30, 20) / LFVector2D(15, 5)) == LFVector2D(2, 4), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) / 10) == LFVector2D(0.1f, 0.2f), INFO);

		LFTest::AssertOk(-LFVector2D(1, 2) == LFVector2D(-1, -2), INFO);

		LFTest::AssertOk(LFVector2D(21, 31) == ++vec7, INFO);
		LFTest::AssertOk(LFVector2D(22, 32) == vec7++, INFO);
		LFTest::AssertOk(LFVector2D(21, 31) == --vec7, INFO);
		LFTest::AssertOk(LFVector2D(20, 30) == --vec7, INFO);

		LFTest::AssertOk((LFVector2D(1, 2) += LFVector2D(3, 4)) == LFVector2D(4, 6), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) += 10) == LFVector2D(11, 12), INFO);
		LFTest::AssertOk((LFVector2D(3, 4) -= LFVector2D(1, 2)) == LFVector2D(2, 2), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) -= 1) == LFVector2D(0, 1), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) *= LFVector2D(3, 4)) == LFVector2D(3, 8), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) *= 10) == LFVector2D(10, 20), INFO);
		LFTest::AssertOk((LFVector2D(30, 20) /= LFVector2D(15, 5)) == LFVector2D(2, 4), INFO);
		LFTest::AssertOk((LFVector2D(1, 2) /= 10) == LFVector2D(0.1f, 0.2f), INFO);

		LFTest::AssertOk(LFVector2D(1, 2) < LFVector2D(2, 3), INFO);
		LFTest::AssertOk(LFVector2D(2, 3) > LFVector2D(1, 2), INFO);

		vec.Zero();

		LFVector2D vec5(1, 1), vec6(1, 1);
		vec5.Rotate90DegreeForward();
		vec6.Rotate90DegreeBackward();

		LFTest::AssertOk(vec == LFVector2D() && vec == LFVector2D(0, 0), INFO);
		LFTest::AssertOk(vec5 == LFVector2D(1, -1), INFO);
		LFTest::AssertOk(vec6 == LFVector2D(-1, 1), INFO);

		LFTest::AssertOk(LFVector2D(0, 8).Length() == 8, INFO);
		LFTest::AssertOk(LFVector2D(-6, 8).Length() == 10, INFO);
		LFTest::AssertOk(LFVector2D(5, 12).Length() == 13, INFO);
		LFTest::AssertOk(LFVector2D(-3, 0.5f).Distance(LFVector2D(5, 6.5)) == 10, INFO);
		LFTest::AssertOk(LFVector2D(-6, 8).DotProduct(LFVector2D(5, 12)) == 66, INFO);
		LFTest::AssertOk(LFVector2D(3, 1).CrossProduct(LFVector2D(4, 8)) == 20, INFO);
		LFTest::AssertOk(LFVector2D(3, 4).Normalise() == 5, INFO);
		
		vec = LFVector2D(3, 1);
		vec.Normalizing();
		LFTest::AssertOk(ceilf(vec.Length()) == 1, INFO);

		LFTest::AssertOk(LFVector2D(-6, -6).MidPoint(LFVector2D(10, 2)) == LFVector2D(2, -2), INFO);
	}

	void LFMathTest::CircleTest()
	{
		LFCircle circle(0, 0, 20);
		LFCircle circle2 = circle;
		LFCircle circle3;
		circle3 = circle;

		LFTest::AssertOk(circle == circle2, INFO);
		LFTest::AssertOk(circle == circle3, INFO);
		LFTest::AssertOk(circle != LFCircle(), INFO);
		LFTest::AssertOk(circle.Contains(0, 19), INFO);
		LFTest::AssertOk(!circle.Contains(20, 30), INFO);
		LFTest::AssertOk(circle.Contains(LFCircle(0, 0, 5)), INFO);
		LFTest::AssertOk(!circle.Contains(LFCircle(0, 40, 10)), INFO);
		LFTest::AssertOk(circle.Intersects(LFCircle(0, 0, 30)), INFO);
		LFTest::AssertOk(!circle.Intersects(LFCircle(20, 30, 10)), INFO);
	}

	void LFMathTest::RandomTest()
	{
		int rand10Counter = 0;
		int rand10 = LFRandom::CreateRandom(0, 10), rand11 = LFRandom::CreateRandom(0, 10), rand12 = LFRandom::CreateRandom(0, 10);
		int rand13 = LFRandom::CreateRandom(0, 10), rand14 = LFRandom::CreateRandom(0, 10), rand15 = LFRandom::CreateRandom(0, 10);
		if (rand10 == rand13) rand10Counter++;
		if (rand11 == rand14) rand10Counter++;
		if (rand12 == rand15) rand10Counter++;
		LFTest::AssertOk(rand10Counter < 3, INFO);

		int rand20 = LFRandom::CreateRandom(0, 10), rand21 = LFRandom::CreateRandom(0, 10), rand22 = LFRandom::CreateRandom(0, 10);
		LFTest::AssertOk(!(rand20 == rand21 && rand20 == rand22 && rand21 == rand22), INFO);

		LFVector2D rand30 = LFRandom::CreateRandom(LFVector2D(0, 100), LFVector2D(50, 100)), rand31 = LFRandom::CreateRandom(LFVector2D(0, 100), LFVector2D(50, 100)), rand32 = LFRandom::CreateRandom(LFVector2D(0, 100), LFVector2D(50, 100));
		LFTest::AssertOk(!(rand30 == rand31 && rand30 == rand32 && rand31 == rand32), INFO);
	}

	void LFMathTest::RectangleTest()
	{
		LFRectangle rectangle(0, 0, 20, 30);
		LFRectangle rectangle2 = rectangle;
		LFRectangle rectangle3;
		rectangle3 = rectangle;
		LFRectangle rectangle4(100, 100, 100, 100);

		LFTest::AssertOk(rectangle == rectangle2, INFO);
		LFTest::AssertOk(rectangle == rectangle3, INFO);
		LFTest::AssertOk(rectangle != LFRectangle(), INFO);
		LFTest::AssertOk(rectangle.GetLeft() == 0, INFO);
		LFTest::AssertOk(rectangle.GetRight() == 20, INFO);
		LFTest::AssertOk(rectangle.GetTop() == 0, INFO);
		LFTest::AssertOk(rectangle.GetBottom() == 30, INFO);
		LFTest::AssertOk(rectangle.Contains(10, 29), INFO);
		LFTest::AssertOk(!rectangle.Contains(20, 30), INFO);
		LFTest::AssertOk(rectangle.Contains(LFRectangle(0, 0, 5, 10)), INFO);
		LFTest::AssertOk(!rectangle.Contains(LFRectangle(0, 0, 30, 40)), INFO);
		LFTest::AssertOk(rectangle.Intersects(LFRectangle(0, 0, 30, 40)), INFO);
		LFTest::AssertOk(!rectangle.Intersects(LFRectangle(20, 30, 10, 10)), INFO);
		
		LFTest::AssertOk(rectangle4.Contains(134, 137), INFO);
		LFTest::AssertOk(!rectangle4.Contains(20, 30), INFO);
		LFTest::AssertOk(rectangle4.Contains(LFRectangle(120, 140, 5, 10)), INFO);
		LFTest::AssertOk(!rectangle4.Contains(LFRectangle(0, 0, 300, 400)), INFO);
		LFTest::AssertOk(rectangle4.Intersects(LFRectangle(0, 0, 300, 400)), INFO);
		LFTest::AssertOk(!rectangle4.Intersects(LFRectangle(202, 203, 10, 10)), INFO);
	}

	void LFMathTest::Vector3DTest()
	{
		LFVector3D vec(20, 30, 40);
		LFVector3D vec2 = vec;
		LFVector3D vec3;
		vec3 = vec;

		LFVector3D vec4 = static_cast<LFVector3D>(12);
		LFVector3D vec7(20, 30, 40);

		LFTest::AssertOk(vec == vec2, INFO);
		LFTest::AssertOk(vec == vec3, INFO);
		LFTest::AssertOk(vec4.x == 12 && vec4.y == 12, INFO);
		LFTest::AssertOk(vec != LFVector3D(), INFO);
		
		LFTest::AssertOk((LFVector3D(1, 2, 3) + LFVector3D(3, 4, 5)) == LFVector3D(4, 6, 8), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 3) + 10) == LFVector3D(11, 12, 13), INFO);
		LFTest::AssertOk((LFVector3D(3, 4, 5) - LFVector3D(1, 2, 3)) == LFVector3D(2, 2, 2), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 3) - 1) == LFVector3D(0, 1, 2), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 3) * LFVector3D(3, 4, 5)) == LFVector3D(3, 8, 15), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 3) * 10) == LFVector3D(10, 20, 30), INFO);
		LFTest::AssertOk((LFVector3D(30, 20, 60) / LFVector3D(15, 5, 10)) == LFVector3D(2, 4, 6), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 314) / 10) == LFVector3D(0.1f, 0.2f, 31.4f), INFO);
		
		LFTest::AssertOk(-LFVector3D(1, 2, 3) == LFVector3D(-1, -2, -3), INFO);
		
		LFTest::AssertOk(LFVector3D(21, 31, 41) == ++vec7, INFO);
		LFTest::AssertOk(LFVector3D(22, 32, 42) == vec7++, INFO);
		LFTest::AssertOk(LFVector3D(21, 31, 41) == --vec7, INFO);
		LFTest::AssertOk(LFVector3D(20, 30, 40) == --vec7, INFO);
		
		LFTest::AssertOk((LFVector3D(1, 2, 3) += LFVector3D(3, 4, 5)) == LFVector3D(4, 6, 8), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 3) += 10) == LFVector3D(11, 12, 13), INFO);
		LFTest::AssertOk((LFVector3D(3, 4, 5) -= LFVector3D(1, 2, 3)) == LFVector3D(2, 2, 2), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 3) -= 1) == LFVector3D(0, 1, 2), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 3) *= LFVector3D(3, 4, 5)) == LFVector3D(3, 8, 15), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 3) *= 10) == LFVector3D(10, 20, 30), INFO);
		LFTest::AssertOk((LFVector3D(30, 20, 60) /= LFVector3D(15, 5, 10)) == LFVector3D(2, 4, 6), INFO);
		LFTest::AssertOk((LFVector3D(1, 2, 314) /= 10) == LFVector3D(0.1f, 0.2f, 31.4f), INFO);
		
		LFTest::AssertOk(LFVector3D(1, 2, 3) < LFVector3D(2, 3, 4), INFO);
		LFTest::AssertOk(LFVector3D(2, 3, 4) > LFVector3D(1, 2, 3), INFO);
		
		vec.Zero();
		LFTest::AssertOk(vec == LFVector3D() && vec == LFVector3D(0, 0, 0), INFO);

		LFTest::AssertOk(LFVector3D(2, 1, 2).Length() == 3, INFO);
		LFTest::AssertOk(LFVector3D(2, 1, 2).Distance(LFVector3D(4, 2, 4)) == 3, INFO);
		LFTest::AssertOk(LFVector3D(1, 2, 3).DotProduct(LFVector3D(6, 7, 8)) == 44, INFO);
		LFTest::AssertOk(LFVector3D(2, 3, 4).CrossProduct(LFVector3D(5, 6, 7)) == LFVector3D(-3, 6, -3), INFO);
		LFTest::AssertOk(LFVector3D(2, 1, 2).Normalise() == LFVector3D(2, 1, 2).Length(), INFO);
		
		vec = LFVector3D(3, 1, 2);
		vec.Normalizing();
		LFTest::AssertOk(ceilf(vec.Length()) == 1, INFO);

		LFTest::AssertOk(LFVector3D(2, 4, 6).MidPoint(LFVector3D(1, 7, 9)) == LFVector3D(1.5f, 5.5f, 7.5f), INFO);
	}

	void LFMathTest::Vector4DTest()
	{
		LFVector4D vec(20, 30, 40, 50);
		LFVector4D vec2 = vec;
		LFVector4D vec3;
		vec3 = vec;

		LFVector4D vec4 = static_cast<LFVector4D>(12);
		LFVector4D vec7(20, 30, 40, 50);

		LFTest::AssertOk(vec == vec2, INFO);
		LFTest::AssertOk(vec == vec3, INFO);
		LFTest::AssertOk(vec4.x == 12 && vec4.y == 12, INFO);
		LFTest::AssertOk(vec != LFVector4D(), INFO);

		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) + LFVector4D(3, 4, 5, 6)) == LFVector4D(4, 6, 8, 10), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) + 10) == LFVector4D(11, 12, 13, 14), INFO);
		LFTest::AssertOk((LFVector4D(3, 4, 5, 6) - LFVector4D(1, 2, 3, 4)) == LFVector4D(2, 2, 2, 2), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) - 1) == LFVector4D(0, 1, 2, 3), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) * LFVector4D(3, 4, 5, 6)) == LFVector4D(3, 8, 15, 24), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) * 10) == LFVector4D(10, 20, 30, 40), INFO);
		LFTest::AssertOk((LFVector4D(30, 20, 60, 100) / LFVector4D(15, 5, 10, 20)) == LFVector4D(2, 4, 6, 5), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 314, 234) / 10) == LFVector4D(0.1f, 0.2f, 31.4f, 23.4f), INFO);

		LFTest::AssertOk(-LFVector4D(1, 2, 3, 4) == LFVector4D(-1, -2, -3, -4), INFO);

		LFTest::AssertOk(LFVector4D(21, 31, 41, 51) == ++vec7, INFO);
		LFTest::AssertOk(LFVector4D(22, 32, 42, 52) == vec7++, INFO);
		LFTest::AssertOk(LFVector4D(21, 31, 41, 51) == --vec7, INFO);
		LFTest::AssertOk(LFVector4D(20, 30, 40, 50) == --vec7, INFO);

		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) += LFVector4D(3, 4, 5, 6)) == LFVector4D(4, 6, 8, 10), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) += 10) == LFVector4D(11, 12, 13, 14), INFO);
		LFTest::AssertOk((LFVector4D(3, 4, 5, 6) -= LFVector4D(1, 2, 3, 4)) == LFVector4D(2, 2, 2, 2), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) -= 1) == LFVector4D(0, 1, 2, 3), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) *= LFVector4D(3, 4, 5, 6)) == LFVector4D(3, 8, 15, 24), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 3, 4) *= 10) == LFVector4D(10, 20, 30, 40), INFO);
		LFTest::AssertOk((LFVector4D(30, 20, 60, 100) /= LFVector4D(15, 5, 10, 20)) == LFVector4D(2, 4, 6, 5), INFO);
		LFTest::AssertOk((LFVector4D(1, 2, 314, 234) /= 10) == LFVector4D(0.1f, 0.2f, 31.4f, 23.4f), INFO);

		LFTest::AssertOk(LFVector4D(1, 2, 3, 4) < LFVector4D(2, 3, 4, 5), INFO);
		LFTest::AssertOk(LFVector4D(2, 3, 4, 5) > LFVector4D(1, 2, 3, 4), INFO);

		vec.Zero();
		LFTest::AssertOk(vec == LFVector4D() && vec == LFVector4D(0, 0, 0, 0), INFO);

		LFTest::AssertOk(LFVector4D(1, 2, 3, 4).DotProduct(LFVector4D(6, 7, 8, 9)) == 80, INFO);
	}

	void LFMathTest::Matrix3DTest()
	{
		LFMatrix3 mat
		(1.0f, 2.0f, 3.0f, 
			4.0f, 5.0f, 6.0f, 
			7.0f, 8.0f, 9.0f);

		LFMatrix3 mat2 = mat;
		LFMatrix3 mat3 = mat;

		LFTest::AssertOk(mat == mat2, INFO);
		LFTest::AssertOk(mat == mat3, INFO);
		LFTest::AssertOk(mat != LFMatrix3(), INFO);

		LFTest::AssertOk((mat + mat2) == LFMatrix3
		(2.0f, 4.0f, 6.0f, 
			8.0f, 10.0f, 12.0f, 
			14.0f, 16.0f, 18.0f), INFO);

		auto mat4 = mat3;
		mat4.Zero();
		LFTest::AssertOk((mat - mat2) == mat4, INFO);

		LFTest::AssertOk((mat * mat2) == LFMatrix3
		(30.0f, 36.0f, 42.0f, 
			66.0f, 81.0f, 96.0f, 
			102.0f, 126.0f, 150.0f), INFO);

		mat4.Identity();
		LFTest::AssertOk(mat4 == LFMatrix3
		(1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f), INFO);

		LFTest::AssertOk(LFMatrix3(mat) * LFVector3D(1, 2, 3) == LFVector3D(14, 32, 50), INFO);

		LFTest::AssertOk((mat * 10) == LFMatrix3
		(10.0f, 20.0f, 30.0f,
			40.0f, 50.0f, 60.0f,
			70.0f, 80.0f, 90.0f), INFO);

		LFMatrix3 mat5 = mat;
		LFTest::AssertOk(LFMatrix3(mat5).Inverse(mat5) == false, INFO);
		LFMatrix3 mat6
		(1.0f, 3.0f, 3.0f,
			1.0f, 4.0f, 3.0f,
			1.0f, 3.0f, 4.0f);
		LFTest::AssertOk(mat6.Inverse(mat6) == true, INFO);

		LFMatrix3 mat7
		(1.0f, 3.0f, 3.0f,
			1.0f, 4.0f, 3.0f,
			1.0f, 3.0f, 4.0f);
		LFTest::AssertOk(mat7.Inverse() == LFMatrix3
		(7.0f, -3.0f, -3.0f,
			-1.0f, 1.0f, 0.0f,
			-1.0f, 0.0f, 1.0f), INFO);
		
		mat4 = mat;
		LFTest::AssertOk(mat4.Transpose() == LFMatrix3
		(1.0f, 4.0f, 7.0f,
			2.0f, 5.0f, 8.0f,
			3.0f, 6.0f, 9.0f), INFO);

		LFTest::AssertOk(LFMatrix3
		(-5.0f, 0.0f, -1.0f,
			1.0f, 2.0f, -1.0f,
			-3.0f, 4.0f, 1.0f).Determinant() == -40.0f, INFO);

		LFMatrix3 mat8(-5.0f, 3.0f, -1.0f,
				1.0f, 5.0f, -1.0f,
				-3.0f, 4.0f, 10.0f);
		mat8.Orthonormalize();
		auto mat9 = mat8.Inverse();
		auto mat10 = mat8 * mat9;
		LFTest::AssertOk(1.0f == floorf(mat10(0, 0)) && 1.0f == floorf(mat10(1, 1)) && 1.0f == floorf(mat10(2, 2)), INFO); //A * inverse(A) = Identity, if A -> Orthogonal
	}

	void LFMathTest::Matrix4DTest()
	{
		LFMatrix4 mat
		(1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f, 7.0f);

		LFMatrix4 mat2 = mat;
		LFMatrix4 mat3 = mat;

		LFTest::AssertOk(mat == mat2, INFO);
		LFTest::AssertOk(mat == mat3, INFO);
		LFTest::AssertOk(mat != LFMatrix4(), INFO);

		LFTest::AssertOk((mat + mat2) == LFMatrix4
		(2.0f, 4.0f, 6.0f, 8.0f,
			10.0f, 12.0f, 14.0f, 16.0f,
			18.0f, 2.0f, 4.0f, 6.0f,
			8.0f, 10.0f, 12.0f, 14.0f), INFO);

		LFTest::AssertOk((mat - mat2) == LFMatrix4(), INFO);

		LFTest::AssertOk((mat * mat2) == LFMatrix4
		(54.0f, 37.0f, 47.0f, 57.0f,
			130.0f, 93.0f, 119.0f, 145.0f,
			44.0f, 41.0f, 56.0f, 71.0f,
			111.0f, 79.0f, 101.0f, 123.0f), INFO);

		LFTest::AssertOk(LFMatrix4(1.0f, 0.0f, 0.0f, 10.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f) * LFVector3D(0.0f, 0.0f, -1.0f) == LFVector3D(10.0f, 0.0f, -1.0f), INFO);

		LFTest::AssertOk(LFMatrix4(1.0f, 0.0f, 0.0f, 10.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f) * LFVector4D(0.0f, 0.0f, -1.0f, 0.0f) == LFVector4D(0.0f, 0.0f, -1.0f, 0.0f), INFO);
		LFTest::AssertOk(LFMatrix4(1.0f, 0.0f, 0.0f, 10.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f) * LFVector4D(10.0f, 10.0f, 10.0f, 1.0f) == LFVector4D(20.0f, 10.0f, 10.0f, 1.0f), INFO);
		
		LFTest::AssertOk((mat * 10) == LFMatrix4
		(10.0f, 20.0f, 30.0f, 40.0f,
			50.0f, 60.0f, 70.0f, 80.0f,
			90.0f, 10.0f, 20.0f, 30.0f,
			40.0f, 50.0f, 60.0f, 70.0f), INFO);

		LFMatrix4 matT2D;
		matT2D.SetTranslation(LFVector2D(2, 2));
		LFTest::AssertOk(LFVector2D(2, 2) == matT2D.GetTranslation2D(), INFO);
		matT2D.MakeTranslation(LFVector2D(2, 2));
		LFTest::AssertOk(matT2D == LFMatrix4::GetTranslation(LFVector2D(2, 2)), INFO);

		LFMatrix4 matT3D;
		matT3D.SetTranslation(LFVector3D(2, 2, 2));
		LFTest::AssertOk(LFVector3D(2, 2, 2) == matT3D.GetTranslation3D(), INFO);
		matT3D.MakeTranslation(LFVector3D(2, 2, 2));
		LFTest::AssertOk(matT3D == LFMatrix4::GetTranslation(LFVector3D(2, 2, 2)), INFO);

		LFMatrix4 matR, matR2;
		matR.Identity();
		matR.SetRotationYaw(90.0f); //Y
		matR2.m[0][0] = cosf(90.0f);
		matR2.m[0][2] = -sinf(90.0f);
		matR2.m[2][0] = sinf(90.0f);
		matR2.m[2][2] = cosf(90.0f);
		LFTest::AssertOk(matR.m[0][0] == matR2.m[0][0]  && matR.m[0][2] == matR2.m[0][2] &&
				matR.m[2][0] == matR2.m[2][0] && matR.m[2][2] == matR2.m[2][2], INFO);
		matR.SetRotationPitch(90.0f); //X
		matR2.m[1][1] = cosf(90.0f);
		matR2.m[1][2] = sinf(90.0f);
		matR2.m[2][1] = -sinf(90.0f);
		matR2.m[2][2] = cosf(90.0f);
		LFTest::AssertOk(matR.m[1][1] == matR2.m[1][1] && matR.m[1][2] == matR2.m[1][2] &&
				matR.m[2][1] == matR2.m[2][1] && matR.m[2][2] == matR2.m[2][2], INFO);
		matR.SetRotationRoll(90.0f); //Z
		matR2.m[0][0] = cosf(90.0f);
		matR2.m[0][1] = sinf(90.0f);
		matR2.m[1][0] = -sinf(90.0f);
		matR2.m[1][1] = cosf(90.0f);
		LFTest::AssertOk(matR.m[0][0] == matR2.m[0][0] && matR.m[0][1] == matR2.m[0][1] &&
				matR.m[1][0] == matR2.m[1][0] && matR.m[1][1] == matR2.m[1][1], INFO);
		
		LFMatrix4 mat4;
		mat4.Identity();
		LFTest::AssertOk(mat4.IsHasScale() == false, INFO);
		mat4.SetScale(LFVector3D(2, 2, 2));
		LFTest::AssertOk(mat4 == LFMatrix4(2.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 2.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f), INFO);
		LFTest::AssertOk(mat4.IsHasScale() == true, INFO);
		LFTest::AssertOk(mat4 == LFMatrix4().GetScale(LFVector3D(2, 2, 2)), INFO);
		
		mat4.Identity();
		LFTest::AssertOk(mat4.IsAffine() == true, INFO);

		LFMatrix4 matAff(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f);
		LFMatrix4 matAff2;
		matAff2.Identity();
		LFTest::AssertOk(matAff.Concatenate(matAff.Inverse()) == matAff2, INFO);

		LFTest::AssertOk(LFMatrix4(1.0f, 1.0f, 1.0f, 1.0f,
			2.0f, 2.0f, 2.0f, 2.0f,
			3.0f, 3.0f, 3.0f, 3.0f,
			4.0f, 4.0f, 4.0f, 4.0f).TransformAffine(LFVector3D(1, 1, 1)) == LFVector3D(4, 8, 12), INFO);
		
		LFTest::AssertOk(LFMatrix4(1.0f, 1.0f, 1.0f, 1.0f,
			2.0f, 2.0f, 2.0f, 2.0f,
			3.0f, 3.0f, 3.0f, 3.0f,
			4.0f, 4.0f, 4.0f, 4.0f).TransformAffine(LFVector4D(1, 1, 1, 1)) == LFVector4D(4, 8, 12, 1), INFO);
		
		LFMatrix4 mat5(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 1.0f, 20.0f,
			1.0f, 0.0f, 0.0f, 1.0f);
		LFMatrix4 mat6;
		mat6.Identity();
		LFTest::AssertOk(mat5.Concatenate(mat5.Inverse()) == mat6, INFO);

		LFTest::AssertOk(mat5.ConcatenateAffine(mat5.InverseAffine()) == mat6, INFO);
		
		LFTest::AssertOk(LFMatrix4(1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								0.0f, 1.0f, 1.0f, 0.0f, 
								1.0f, 0.0f, 0.0f, 1.0f).Inverse() ==
			LFMatrix4(1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, -1.0f, 1.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					-1.0f, 0.0f, 0.0f, 1.0f), INFO);
		
		LFTest::AssertOk(LFMatrix4(mat).Transpose() ==
			LFMatrix4(1.0f, 5.0f, 9.0f, 4.0f,
				2.0f, 6.0f, 1.0f, 5.0f,
				3.0f, 7.0f, 2.0f, 6.0f,
				4.0f, 8.0f, 3.0f, 7.0f), INFO);

		LFTest::AssertOk(LFMatrix4(3.0f, 0.0f, 2.0f, -1.0f,
			1.0f, 2.0f, 0.0f, -2.0f,
			4.0f, 0.0f, 6.0f, -3.0f,
			5.0f, 0.0f, 2.0f, 0.0f).Determinant() == 20.0f, INFO);
	}
	
	void LFMathTest::RunAllTests()
	{
		LFMathMainTest();
		Vector2DTest();
		CircleTest();
		RandomTest();
		RectangleTest();
		Vector3DTest();
		Vector4DTest();
		Matrix3DTest();
		Matrix4DTest();
	}
}}}}
