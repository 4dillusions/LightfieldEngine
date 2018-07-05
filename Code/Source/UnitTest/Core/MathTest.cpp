/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "MathTest.h"
#include "..\Test.h"
#include "..\..\Core\\Math\LFCircle.h"
#include "..\..\Core\\Math\LFMath.h"
#include "..\..\Core\\Math\LFMatrix4.h"
#include "..\..\Core\\Math\LFRandom.h"
#include "..\..\Core\\Math\LFRectangle.h"
#include "..\..\Core\\Math\LFVector2D.h"
#include "..\..\Core\\Math\LFVector3D.h"

using namespace LFCore::Common;
using namespace LFCore::Math;

namespace UnitTest
{
	void MathTest::CircleTest()
	{
		LFCircle circle(0, 0, 20);
        LFCircle circle2 = circle;
        LFCircle circle3;
        circle3 = circle;

        Test::AssertOk(circle == circle2, "LFCore::Math::LFCircle::copy constructor, LFCore::Math::LFCircle::operator==");
        Test::AssertOk(circle == circle3, "LFCore::Math::LFCircle::operator=, LFCore::Math::LFCircle::operator==");
        Test::AssertOk(circle != LFCircle(), "LFCore::Math::LFCircle::operator!=");
        Test::AssertOk(circle.Contains(0, 19), "LFCore::Math::LFCircle::Contains(int x, int y) equals");
        Test::AssertOk(!circle.Contains(20, 30), "LFCore::Math::LFCircle::Contains(int x, int y) not equals");
        Test::AssertOk(circle.Contains(LFCircle(0, 0, 5)), "LFCore::Math::LFCircle::Contains(const LFCircle &value) equals");
        Test::AssertOk(!circle.Contains(LFCircle(0, 40, 10)), "LFCore::Math::LFCircle::Contains(const LFCircle &value) not equals");
        Test::AssertOk(circle.Intersects(LFCircle(0, 0, 30)), "LFCore::Math::LFCircle::Intersects(const LFCircle &value) equals");
        Test::AssertOk(!circle.Intersects(LFCircle(20, 30, 10)), "LFCore::Math::LFCircle::Intersects(const LFCircle &value) not equals");
	}

	void MathTest::MathMainTest()
    {
        Test::AssertOk(LFMath::Min(10, 23) == 10, "LFCore::Math::LFMath::Min");
        Test::AssertOk(LFMath::Max(10, 23) == 23, "LFCore::Math::LFMath::Max");
        Test::AssertOk(LFMath::Lerp(10, 20, 0.5) == 15, "LFCore::Math::LFMath::Lerp");
        Test::AssertOk(LFMath::Abs(-3.12) == 3.12 && LFMath::Abs(3.12) == 3.12, "LFCore::Math::LFMath::Abs");
        Test::AssertOk(LFMath::Clamp(12, -10, 10) == 10 && LFMath::Clamp(-15, -10, 10) == -10, "LFCore::Math::LFMath::Clamp");
        Test::AssertOk(LFMath::Distance(10.5f, 12.5f) == 2, "LFCore::Math::LFMath::Distance");
		Test::AssertOk(LFMath::Log(3, 9) == 2, "LFCore::Math::Log(3, 9) == 2");
		Test::AssertOk(LFMath::Log(10, 1000) == 3, "LFCore::Math::Log(10, 1000) == 3");
		Test::AssertOk(LFMath::Pow(3, 2) == 9, "LFCore::Math::Pow(3, 2) == 9");
		Test::AssertOk(LFMath::Pow(10, 3) == 1000, "LFCore::Math::Pow(10, 3) == 1000");
		Test::AssertOk(LFMath::IsPowerOfTwo(1024), "LFCore::Math::IsPowerOfTwo true");
		Test::AssertOk(!LFMath::IsPowerOfTwo(127), "LFCore::Math::IsPowerOfTwo false");
    }

	void MathTest::Matrix4Test()
    {
        LFMatrix4 mat
			(1.0f, 2.0f, 3.0f, 4.0f,
			5.0f, 6.0f, 7.0f, 8.0f,
			9.0f, 1.0f, 2.0f, 3.0f,
			4.0f, 5.0f, 6.0f, 7.0f);

		LFMatrix4 mat2 = mat;
        LFMatrix4 mat3;
        mat3 = mat;

		Test::AssertOk(mat == mat2, "LFCore::Math::LFMatrix4::copy constructor, LFMatrix4::operator==");
        Test::AssertOk(mat == mat3, "LFCore::Math::LFMatrix4::operator=, LFMatrix4::operator==");
        Test::AssertOk(mat != LFMatrix4(), "LFCore::Math::LFMatrix4::operator!=");

		Test::AssertOk((mat + mat2) == LFMatrix4
			(2.0f, 4.0f, 6.0f, 8.0f,
			10.0f, 12.0f, 14.0f, 16.0f,
			18.0f, 2.0f, 4.0f, 6.0f,
			8.0f, 10.0f, 12.0f, 14.0f), "LFCore::Math::LFMatrix4::operator + (const LFMatrix4 &value)");

		Test::AssertOk((mat - mat2) == LFMatrix4(), "LFCore::Math::LFMatrix4::operator - (const LFMatrix4 &value)");

		Test::AssertOk((mat * mat2) == LFMatrix4
			(54.0f, 37.0f, 47.0f, 57.0f,
			130.0f, 93.0f, 119.0f, 145.0f,
			44.0f, 41.0f, 56.0f, 71.0f,
			111.0f, 79.0f, 101.0f, 123.0f), "LFCore::Math::LFMatrix4::operator * (const LFMatrix4 &value)");

		mat.Identity();
		mat.Translation(LFVector2D(10, 20));
		Test::AssertOk(mat == LFMatrix4
			(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			10.0f, 20.0f, 0.0f, 1.0f), "LFCore::Math::LFMatrix4::Translation(const LFVector2D &vector)");
    }

    void MathTest::RandomTest()
    {
        LFRandom rand1, rand2;

        int rand10Counter = 0;
        int rand10 = rand1.CreateRandom(0, 10), rand11 = rand1.CreateRandom(0, 10), rand12 = rand1.CreateRandom(0, 10);
        int rand13 = rand2.CreateRandom(0, 10), rand14 = rand2.CreateRandom(0, 10), rand15 = rand2.CreateRandom(0, 10);
        if (rand10 == rand13) rand10Counter++;
        if (rand11 == rand14) rand10Counter++;
        if (rand12 == rand15) rand10Counter++;
        Test::AssertOk(rand10Counter < 3, "LFCore::Math::LFRandom::CreateRandom(int min, int max) - rand1, rand2");

        int rand20 = rand1.CreateRandom(0, 10), rand21 = rand1.CreateRandom(0, 10), rand22 = rand1.CreateRandom(0, 10);
        Test::AssertOk(!(rand20 == rand21 && rand20 == rand22 && rand21 == rand22), "LFCore::Math::LFRandom::CreateRandom(int min, int max) - rand1, rand1");

        LFVector2D rand30 = rand1.CreateRandom(LFVector2D(0, 10), LFVector2D(5, 10)), rand31 = rand1.CreateRandom(LFVector2D(0, 10), LFVector2D(5, 10)), rand32 = rand1.CreateRandom(LFVector2D(0, 10), LFVector2D(5, 10));
        Test::AssertOk(!(rand30 == rand31 && rand30 == rand32 && rand31 == rand32), "LFCore::Math::SMRandom::CreateRandom(LFVector2D min, LFVector2D max) - rand1, rand1");
    }

    void MathTest::RectangleTest()
    {
        LFRectangle rectangle(0, 0, 20, 30);
        LFRectangle rectangle2 = rectangle;
        LFRectangle rectangle3;
        rectangle3 = rectangle;
		LFRectangle rectangle4(100, 100, 100, 100);

        Test::AssertOk(rectangle == rectangle2, "LFCore::Math::LFRectangle::copy constructor, LFRectangle::operator==");
        Test::AssertOk(rectangle == rectangle3, "LFCore::Math::LFRectangle::operator=, LFRectangle::operator==");
        Test::AssertOk(rectangle != LFRectangle(), "LFCore::Math::LFRectangle::operator!=");
        Test::AssertOk(rectangle.Left() == 0, "LFCore::Math::LFRectangle::Left()");
        Test::AssertOk(rectangle.Right() == 20, "LFCore::Math::LFRectangle::Right()");
        Test::AssertOk(rectangle.Top() == 0, "LFCore::Math::LFRectangle::Top()");
        Test::AssertOk(rectangle.Bottom() == 30, "LFCore::Math::LFRectangle::Bottom()");
        Test::AssertOk(rectangle.Contains(10, 29), "LFCore::Math::LFRectangle::Contains(int x, int y) equals");
        Test::AssertOk(!rectangle.Contains(20, 30), "LFCore::Math::LFRectangle::Contains(int x, int y) not equals");
        Test::AssertOk(rectangle.Contains(LFRectangle(0, 0, 5, 10)), "LFCore::Math::LFRectangle::Contains(const LFRectangle &value) equals");
        Test::AssertOk(!rectangle.Contains(LFRectangle(0, 0, 30, 40)), "LFCore::Math::LFRectangle::Contains(const LFRectangle &value) not equals");
        Test::AssertOk(rectangle.Intersects(LFRectangle(0, 0, 30, 40)), "LFCore::Math::LFRectangle::Intersects(const LFRectangle &value) equals");
        Test::AssertOk(!rectangle.Intersects(LFRectangle(20, 30, 10, 10)), "LFCore::Math::LFRectangle::Intersects(const LFRectangle &value) not equals");

		Test::AssertOk(rectangle4.Contains(134, 137), "LFCore::Math::LFRectangle::Contains(int x, int y) equals 2");
		Test::AssertOk(!rectangle4.Contains(20, 30), "LFCore::Math::LFRectangle::Contains(int x, int y) not equals 2");
		Test::AssertOk(rectangle4.Contains(LFRectangle(120, 140, 5, 10)), "LFCore::Math::LFRectangle::Contains(const LFRectangle &value) equals 2");
		Test::AssertOk(!rectangle4.Contains(LFRectangle(0, 0, 300, 400)), "LFCore::Math::LFRectangle::Contains(const LFRectangle &value) not equals 2");
		Test::AssertOk(rectangle4.Intersects(LFRectangle(0, 0, 300, 400)), "LFCore::Math::LFRectangle::Intersects(const LFRectangle &value) equals 2");
		Test::AssertOk(!rectangle4.Intersects(LFRectangle(202, 203, 10, 10)), "LFCore::Math::LFRectangle::Intersects(const LFRectangle &value) not equals 2");
    }

    void MathTest::Vector2DTest()
    {
        LFVector2D vec(20, 30);
        LFVector2D vec2 = vec;
        LFVector2D vec3;
        vec3 = vec;

        LFVector2D vec4 = (LFVector2D)12; //implicit cast only
		LFVector2D vec7(20, 30);

        Test::AssertOk(vec == vec2, "LFCore::Math::LFVector2D::copy constructor, LFVector2D::operator==");
        Test::AssertOk(vec == vec3, "LFCore::Math::LFVector2D::operator=, LFVector2D::operator==");
        Test::AssertOk(vec4.x == 12 && vec4.y == 12, "LFCore::Math::LFVector2D::explicit LFVector2D(const float scale)");
        Test::AssertOk(vec != LFVector2D(), "LFCore::Math::LFVector2D::operator!=");

        Test::AssertOk((LFVector2D(1, 2) + LFVector2D(3, 4)) == LFVector2D(4, 6), "LFCore::Math::LFVector2D::operator + (const LFVector2D &value)");
        Test::AssertOk((LFVector2D(1, 2) + 10) == LFVector2D(11, 12), "LFCore::Math::LFVector2D::operator + (const float size)");
        Test::AssertOk((LFVector2D(3, 4) - LFVector2D(1, 2)) == LFVector2D(2, 2), "LFCore::Math::LFVector2D::operator - (const LFVector2D &value)");
        Test::AssertOk((LFVector2D(1, 2) - 1) == LFVector2D(0, 1), "LFCore::Math::LFVector2D::operator - (const float size)");
        Test::AssertOk((LFVector2D(1, 2) * LFVector2D(3, 4)) == LFVector2D(3, 8), "LFCore::Math::LFVector2D::operator * (const LFVector2D &value)");
        Test::AssertOk((LFVector2D(1, 2) * 10) == LFVector2D(10, 20), "LFCore::Math::LFVector2D::operator * (const float size)");
        Test::AssertOk((LFVector2D(30, 20) / LFVector2D(15, 5)) == LFVector2D(2, 4), "LFCore::Math::LFVector2D::operator / (const LFVector2D &value)");
        Test::AssertOk((LFVector2D(1, 2) / 10) == LFVector2D(0.1f, 0.2f), "LFCore::Math::LFVector2D::operator / (const float size)");

        Test::AssertOk(-LFVector2D(1, 2) == LFVector2D(-1, -2), "LFCore::Math::LFVector2D::operator - ()");

		Test::AssertOk(LFVector2D(21, 31) == ++vec7, "LFCore::Math::LFVector2D &operator ++ ()");
		Test::AssertOk(LFVector2D(22, 32) == vec7++, "LFCore::Math::LFVector2D &operator ++ (int)");
		Test::AssertOk(LFVector2D(21, 31) == --vec7, "LFCore::Math::LFVector2D &operator -- ()");
		Test::AssertOk(LFVector2D(20, 30) == --vec7, "LFCore::Math::LFVector2D &operator -- (int)");
		
        Test::AssertOk((LFVector2D(1, 2) += LFVector2D(3, 4)) == LFVector2D(4, 6), "LFCore::Math::LFVector2D::operator += (const LFVector2D &value)");
        Test::AssertOk((LFVector2D(1, 2) += 10) == LFVector2D(11, 12), "LFCore::Math::LFVector2D::operator += (const float size)");
        Test::AssertOk((LFVector2D(3, 4) -= LFVector2D(1, 2)) == LFVector2D(2, 2), "LFCore::Math::LFVector2D::operator -= (const LFVector2D &value)");
        Test::AssertOk((LFVector2D(1, 2) -= 1) == LFVector2D(0, 1), "LFCore::Math::LFVector2D::operator -= (const float size)");
        Test::AssertOk((LFVector2D(1, 2) *= LFVector2D(3, 4)) == LFVector2D(3, 8), "LFCore::Math::LFVector2D::operator *= (const LFVector2D &value)");
        Test::AssertOk((LFVector2D(1, 2) *= 10) == LFVector2D(10, 20), "LFCore::Math::LFVector2D::operator *= (const float size)");
        Test::AssertOk((LFVector2D(30, 20) /= LFVector2D(15, 5)) == LFVector2D(2, 4), "LFCore::Math::LFVector2D::operator /= (const LFVector2D &value)");
        Test::AssertOk((LFVector2D(1, 2) /= 10) == LFVector2D(0.1f, 0.2f), "LFCore::Math::LFVector2D::operator /= (const float size)");

        Test::AssertOk(LFVector2D(1, 2) < LFVector2D(2, 3), "LFCore::Math::LFVector2D::operator < (const LFVector2D &value)");
        Test::AssertOk(LFVector2D(2, 3) > LFVector2D(1, 2), "LFCore::Math::LFVector2D::operator > (const LFVector2D &value)");

        vec.Zero();

        LFVector2D vec5(1, 1), vec6(1, 1);
        vec5.Rotate90DegreeForward();
        vec6.Rotate90DegreeBackward();

        Test::AssertOk(vec == LFVector2D() && vec == LFVector2D(0, 0), "LFCore::Math::LFVector2D::Zero()");
        Test::AssertOk(vec5 == LFVector2D(1, -1), "Rotate90DegreeForward()");
        Test::AssertOk(vec6 == LFVector2D(-1, 1), "Rotate90DegreeBackward()");
    }

	void MathTest::Vector3DTest()
	{
		LFVector3D vec(20, 30, 40);
        LFVector3D vec2 = vec;
        LFVector3D vec3;
        vec3 = vec;

        LFVector3D vec4 = (LFVector3D)12; //implicit cast only
		LFVector3D vec7(20, 30, 40);

        Test::AssertOk(vec == vec2, "LFCore::Math::LFVector3D::copy constructor, LFVector3D::operator==");
        Test::AssertOk(vec == vec3, "LFCore::Math::LFVector3D::operator=, LFVector3D::operator==");
        Test::AssertOk(vec4.x == 12 && vec4.y == 12, "LFCore::Math::LFVector3D::explicit LFVector3D(const float scale)");
        Test::AssertOk(vec != LFVector3D(), "LFCore::Math::LFVector3D::operator!=");

        Test::AssertOk((LFVector3D(1, 2, 3) + LFVector3D(3, 4, 5)) == LFVector3D(4, 6, 8), "LFCore::Math::LFVector3D::operator + (const LFVector3D &value)");
        Test::AssertOk((LFVector3D(1, 2, 3) + 10) == LFVector3D(11, 12, 13), "LFCore::Math::LFVector3D::operator + (const float size)");
        Test::AssertOk((LFVector3D(3, 4, 5) - LFVector3D(1, 2, 3)) == LFVector3D(2, 2, 2), "LFCore::Math::LFVector3D::operator - (const LFVector3D &value)");
        Test::AssertOk((LFVector3D(1, 2, 3) - 1) == LFVector3D(0, 1, 2), "LFCore::Math::LFVector3D::operator - (const float size)");
        Test::AssertOk((LFVector3D(1, 2, 3) * LFVector3D(3, 4, 5)) == LFVector3D(3, 8, 15), "LFCore::Math::LFVector3D::operator * (const LFVector3D &value)");
        Test::AssertOk((LFVector3D(1, 2, 3) * 10) == LFVector3D(10, 20, 30), "LFCore::Math::LFVector3D::operator * (const float size)");
        Test::AssertOk((LFVector3D(30, 20, 60) / LFVector3D(15, 5, 10)) == LFVector3D(2, 4, 6), "LFCore::Math::LFVector3D::operator / (const LFVector3D &value)");
        Test::AssertOk((LFVector3D(1, 2, 314) / 10) == LFVector3D(0.1f, 0.2f, 31.4f), "LFCore::Math::LFVector3D::operator / (const float size)");

        Test::AssertOk(-LFVector3D(1, 2, 3) == LFVector3D(-1, -2, -3), "LFCore::Math::LFVector3D::operator - ()");

		Test::AssertOk(LFVector3D(21, 31, 41) == ++vec7, "LFCore::Math::LFVector3D &operator ++ ()");
		Test::AssertOk(LFVector3D(22, 32, 42) == vec7++, "LFCore::Math::LFVector3D &operator ++ (int)");
		Test::AssertOk(LFVector3D(21, 31, 41) == --vec7, "LFCore::Math::LFVector3D &operator -- ()");
		Test::AssertOk(LFVector3D(20, 30, 40) == --vec7, "LFCore::Math::LFVector3D &operator -- (int)");
		
        Test::AssertOk((LFVector3D(1, 2, 3) += LFVector3D(3, 4, 5)) == LFVector3D(4, 6, 8), "LFCore::Math::LFVector3D::operator += (const LFVector3D &value)");
        Test::AssertOk((LFVector3D(1, 2, 3) += 10) == LFVector3D(11, 12, 13), "LFCore::Math::LFVector3D::operator += (const float size)");
        Test::AssertOk((LFVector3D(3, 4, 5) -= LFVector3D(1, 2, 3)) == LFVector3D(2, 2, 2), "LFCore::Math::LFVector3D::operator -= (const LFVector3D &value)");
        Test::AssertOk((LFVector3D(1, 2, 3) -= 1) == LFVector3D(0, 1, 2), "LFCore::Math::LFVector3D::operator -= (const float size)");
        Test::AssertOk((LFVector3D(1, 2, 3) *= LFVector3D(3, 4, 5)) == LFVector3D(3, 8, 15), "LFCore::Math::LFVector3D::operator *= (const LFVector3D &value)");
        Test::AssertOk((LFVector3D(1, 2, 3) *= 10) == LFVector3D(10, 20, 30), "LFCore::Math::LFVector3D::operator *= (const float size)");
        Test::AssertOk((LFVector3D(30, 20, 60) /= LFVector3D(15, 5, 10)) == LFVector3D(2, 4, 6), "LFCore::Math::LFVector3D::operator /= (const LFVector3D &value)");
        Test::AssertOk((LFVector3D(1, 2, 314) /= 10) == LFVector3D(0.1f, 0.2f, 31.4f), "LFCore::Math::LFVector3D::operator /= (const float size)");

        Test::AssertOk(LFVector3D(1, 2, 3) < LFVector3D(2, 3, 4), "LFCore::Math::LFVector3D::operator < (const LFVector3D &value)");
        Test::AssertOk(LFVector3D(2, 3, 4) > LFVector3D(1, 2, 3), "LFCore::Math::LFVector3D::operator > (const LFVector3D &value)");

        vec.Zero();
        Test::AssertOk(vec == LFVector3D() && vec == LFVector3D(0, 0, 0), "LFCore::Math::LFVector3D::Zero()");
	}
};
