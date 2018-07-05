/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	class LFVector2D;

	class LFRandom final
	{
		LFRandom();
		LFRandom(const LFRandom&) = delete;
		LFRandom(LFRandom &&) = delete;
		LFRandom &operator=(const LFRandom &) = delete;
		LFRandom &operator=(LFRandom &&) = delete;
		~LFRandom() = default;

		static float CreateRandom(float min, float max);

	public:
		static int CreateRandom(int min, int max);
		static LFVector2D CreateRandom(const LFVector2D &minX, const LFVector2D &minY);
	};
}}}}
