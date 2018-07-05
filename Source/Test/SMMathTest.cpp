#include "SMMathTest.h"

#include "..\\Math\\SMMath.h"
#include "..\\Math\\SMRandom.h"
#include "..\\Math\\SMRectangle.h"
#include "..\\Math\\SMVector2D.h"

#include "..\\Test\\SMTest.h"

using namespace SMEngine::Math;
using namespace SMEngine::Test;

namespace SMEngine { namespace Test
{
    void SMMathTest::SMMathMainTest()
    {
        SMTest::AssertOk(SMMath::Min(10, 23) == 10, "SMMath::Min");
        SMTest::AssertOk(SMMath::Max(10, 23) == 23, "SMMath::Max");
        SMTest::AssertOk(SMMath::Lerp(10, 20, 0.5) == 15, "SMMath::Lerp");
        SMTest::AssertOk(SMMath::Clamp(12, -10, 10) == 10 && SMMath::Clamp(-15, -10, 10) == -10, "SMMath::Clamp");
        SMTest::AssertOk(SMMath::Distance(10.5f, 12.5f) == 2, "SMMath::Distance");
    }

    void SMMathTest::SMMatrix4Test()
    {
        SMLogger::Instance().WriteOutput("TODO SMMathTest::SMMatrix4Test");
    }

    void SMMathTest::SMRandomTest()
    {
        SMRandom rand1, rand2;

        int rand10Counter = 0;
        int rand10 = rand1.CreateRandom(0, 10), rand11 = rand1.CreateRandom(0, 10), rand12 = rand1.CreateRandom(0, 10);
        int rand13 = rand2.CreateRandom(0, 10), rand14 = rand2.CreateRandom(0, 10), rand15 = rand2.CreateRandom(0, 10);
        if (rand10 == rand13) rand10Counter++;
        if (rand11 == rand14) rand10Counter++;
        if (rand12 == rand15) rand10Counter++;
        SMTest::AssertOk(rand10Counter < 3, "SMRandom::CreateRandom(int min, int max) - rand1, rand2");

        int rand20 = rand1.CreateRandom(0, 10), rand21 = rand1.CreateRandom(0, 10), rand22 = rand1.CreateRandom(0, 10);
        SMTest::AssertOk(!(rand20 == rand21 && rand20 == rand22 && rand21 == rand22), "SMRandom::CreateRandom(int min, int max) - rand1, rand1");

        SMVector2D rand30 = rand1.CreateRandom(SMVector2D(0, 10), SMVector2D(5, 10)), rand31 = rand1.CreateRandom(SMVector2D(0, 10), SMVector2D(5, 10)), rand32 = rand1.CreateRandom(SMVector2D(0, 10), SMVector2D(5, 10));
        SMTest::AssertOk(!(rand30 == rand31 && rand30 == rand32 && rand31 == rand32), "SMRandom::CreateRandom(SMVector2D min, SMVector2D max) - rand1, rand1");
    }

    void SMMathTest::SMRectangleTest()
    {
        SMRectangle rectangle(0, 0, 20, 30);
        SMRectangle rectangle2 = rectangle;
        SMRectangle rectangle3;
        rectangle3 = rectangle;

        SMTest::AssertOk(rectangle == rectangle2, "SMRectangle::copy constructor, SMRectangle::operator==");
        SMTest::AssertOk(rectangle == rectangle3, "SMRectangle::operator=, SMRectangle::operator==");
        SMTest::AssertOk(rectangle != SMRectangle(), "SMRectangle::operator!=");
        SMTest::AssertOk(rectangle.Left() == 0, "SMRectangle::Left()");
        SMTest::AssertOk(rectangle.Right() == 20, "SMRectangle::Right()");
        SMTest::AssertOk(rectangle.Top() == 0, "SMRectangle::Top()");
        SMTest::AssertOk(rectangle.Bottom() == 30, "SMRectangle::Bottom()");
        SMTest::AssertOk(rectangle.Contains(10, 29), "SMRectangle::Contains(int x, int y) equals");
        SMTest::AssertOk(!rectangle.Contains(20, 30), "SMRectangle::Contains(int x, int y) not equals");
        SMTest::AssertOk(rectangle.Contains(SMRectangle(0, 0, 5, 10)), "SMRectangle::Contains(const SMRectangle &value) equals");
        SMTest::AssertOk(!rectangle.Contains(SMRectangle(0, 0, 30, 40)), "SMRectangle::Contains(const SMRectangle &value) not equals");
        SMTest::AssertOk(rectangle.Intersects(SMRectangle(0, 0, 30, 40)), "SMRectangle::Intersects(const SMRectangle &value) equals");
        SMTest::AssertOk(!rectangle.Intersects(SMRectangle(20, 30, 10, 10)), "SMRectangle::Intersects(const SMRectangle &value) not equals");
    }

    void SMMathTest::SMVector2DTest()
    {
        SMVector2D vec(20, 30);
        SMVector2D vec2 = vec;
        SMVector2D vec3;
        vec3 = vec;

        SMVector2D vec4 = (SMVector2D)12; //implicit cast only

        SMTest::AssertOk(vec == vec2, "SMVector2D::copy constructor, SMVector2D::operator==");
        SMTest::AssertOk(vec == vec3, "SMVector2D::operator=, SMVector2D::operator==");
        SMTest::AssertOk(vec != SMVector2D(), "SMVector2D::operator!=");

        SMTest::AssertOk((SMVector2D(1, 2) + SMVector2D(3, 4)) == SMVector2D(4, 6), "operator + (const SMVector2D &value)");
        SMTest::AssertOk((SMVector2D(1, 2) + 10) == SMVector2D(11, 12), "operator + (const float size)");
        SMTest::AssertOk((SMVector2D(3, 4) - SMVector2D(1, 2)) == SMVector2D(2, 2), "operator - (const SMVector2D &value)");
        SMTest::AssertOk((SMVector2D(1, 2) - 1) == SMVector2D(0, 1), "operator - (const float size)");
        SMTest::AssertOk((SMVector2D(1, 2) * SMVector2D(3, 4)) == SMVector2D(3, 8), "operator * (const SMVector2D &value)");
        SMTest::AssertOk((SMVector2D(1, 2) * 10) == SMVector2D(10, 20), "operator * (const float size)");
        SMTest::AssertOk((SMVector2D(30, 20) / SMVector2D(15, 5)) == SMVector2D(2, 4), "operator / (const SMVector2D &value)");
        SMTest::AssertOk((SMVector2D(1, 2) / 10) == SMVector2D(0.1f, 0.2f), "operator / (const float size)");

        SMTest::AssertOk(-SMVector2D(1, 2) == SMVector2D(-1, -2), "operator - ()");

        SMTest::AssertOk((SMVector2D(1, 2) += SMVector2D(3, 4)) == SMVector2D(4, 6), "operator += (const SMVector2D &value)");
        SMTest::AssertOk((SMVector2D(1, 2) += 10) == SMVector2D(11, 12), "operator += (const float size)");
        SMTest::AssertOk((SMVector2D(3, 4) -= SMVector2D(1, 2)) == SMVector2D(2, 2), "operator -= (const SMVector2D &value)");
        SMTest::AssertOk((SMVector2D(1, 2) -= 1) == SMVector2D(0, 1), "operator -= (const float size)");
        SMTest::AssertOk((SMVector2D(1, 2) *= SMVector2D(3, 4)) == SMVector2D(3, 8), "operator *= (const SMVector2D &value)");
        SMTest::AssertOk((SMVector2D(1, 2) *= 10) == SMVector2D(10, 20), "operator *= (const float size)");
        SMTest::AssertOk((SMVector2D(30, 20) /= SMVector2D(15, 5)) == SMVector2D(2, 4), "operator /= (const SMVector2D &value)");
        SMTest::AssertOk((SMVector2D(1, 2) /= 10) == SMVector2D(0.1f, 0.2f), "operator /= (const float size)");

        SMTest::AssertOk(SMVector2D(1, 2) < SMVector2D(2, 3), "operator < (const SMVector2D &value)");
        SMTest::AssertOk(SMVector2D(2, 3) > SMVector2D(1, 2), "operator > (const SMVector2D &value)");

        vec.Zero();

        SMVector2D vec5(1, 1), vec6(1, 1);
        vec5.Rotate90DegreeForward();
        vec6.Rotate90DegreeBackward();

        SMTest::AssertOk(vec == SMVector2D(), "SMVector2D::Zero()");
        SMTest::AssertOk(vec5 == SMVector2D(1, -1), "Rotate90DegreeForward()");
        SMTest::AssertOk(vec6 == SMVector2D(-1, 1), "Rotate90DegreeBackward()");
    }
};};
