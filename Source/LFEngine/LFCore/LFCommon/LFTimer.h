/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include <time.h>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	class LFTimer final
	{
		clock_t lastTime = 0, currentTime = 0, deltaTime = 0;

		LFTimer(const LFTimer&) = delete;
		LFTimer(LFTimer &&) = delete;
		LFTimer &operator=(const LFTimer &) = delete;
		LFTimer &operator=(LFTimer &&) = delete;

	#ifdef TIZEN
		timespec nixTime;
	#endif

	public:
		LFTimer();

		static double GetActualTime();

		void Reset();
		double DeltaTime();
	};
}}}}