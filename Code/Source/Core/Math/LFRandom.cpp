/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFRandom.h"
#include "LFVector2D.h"

#include <ctime>
#include <stdlib.h>

namespace LFCore { namespace Math
{
	LFRandom::LFRandom()
	{
		srand((unsigned int)(time(0)));
	}

	int LFRandom::CreateRandom(int min, int max)
	{
		++max;

		return ((rand() % (max - min)) + min);
	}

	float LFRandom::CreateRandom(float min, float max)
	{
		++max;

		return (float)((rand() % ((int)max - (int)min)) + (int)min);
	}

	LFVector2D LFRandom::CreateRandom(const LFVector2D &min, const LFVector2D &max)
	{
		return LFVector2D(CreateRandom(min.x, max.x), CreateRandom(min.y, max.y));
	}
}}
