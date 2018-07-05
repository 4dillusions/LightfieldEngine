/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFRandom.h"
#include "LFVector2D.h"

#include <ctime>
#include <stdlib.h>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	LFRandom::LFRandom()
	{
		srand(static_cast<unsigned int>(time(nullptr)));
	}

	float LFRandom::CreateRandom(float min, float max)
	{
		static LFRandom random;

		return static_cast<float>((rand() % (static_cast<int>(++max) - static_cast<int>(min))) + static_cast<int>(min));
	}

	int LFRandom::CreateRandom(int min, int max)
	{
		return CreateRandom(static_cast<float>(min), static_cast<float>(max));
	}

	LFVector2D LFRandom::CreateRandom(const LFVector2D &min, const LFVector2D &max)
	{
		return LFVector2D(CreateRandom(min.x, max.x), CreateRandom(min.y, max.y));
	}
}}}}
