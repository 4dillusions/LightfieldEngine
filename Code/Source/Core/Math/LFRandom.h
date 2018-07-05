/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"

namespace LFCore { namespace Math
{
	class LFVector2D;

	class LFCORE_LIBRARY LFRandom
	{
    private:
        float CreateRandom(float min, float max);

	public:
		LFRandom();

		int CreateRandom(int min, int max);
		LFVector2D CreateRandom(const LFVector2D &minX, const LFVector2D &minY);
	};
}}
