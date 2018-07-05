#pragma once

#include "SMVector2D.h"

namespace SMEngine { namespace Math
{
    /*
    V�letlen gener�tor: sz�m, Vektor2D

    Haszn�lat:
    SMRandom rand1;
    int x = rand1.CreateRandom(0, 10);
    SMVector2D vec = rand1.CreateRandom(SMVector2D(0, 10), SMVector2D(5, 10));
    */
	class SMRandom
	{
    private:
        float CreateRandom(float min, float max);

	public:
		SMRandom();

		int CreateRandom(int min, int max);
		SMVector2D CreateRandom(SMVector2D minX, SMVector2D minY);
	};
};};
