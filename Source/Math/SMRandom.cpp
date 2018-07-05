#include "SMRandom.h"
#include <ctime>
#include <stdlib.h>

namespace SMEngine { namespace Math
{
	SMRandom::SMRandom()
	{
		srand((unsigned int)(time(0)));
	}

	int SMRandom::CreateRandom(int min, int max)
	{
		++max;

		return ((rand() % (max - min)) + min);
	}

	float SMRandom::CreateRandom(float min, float max)
	{
		++max;

		return (float)((rand() % ((int)max - (int)min)) + (int)min);
	}

	SMVector2D SMRandom::CreateRandom(SMVector2D min, SMVector2D max)
	{
		return SMVector2D(CreateRandom(min.x, max.x), CreateRandom(min.y, max.y));
	}
};};
