/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"
#include <time.h>

namespace LFCore { namespace Common
{
	class LFCORE_LIBRARY LFTimer
	{
	private:
		clock_t lastTime, currentTime, deltaTime;

		#ifdef TIZEN
		timespec nixTime;
		#endif

	public:
		LFTimer();

		static double GetActualTime();

		void Reset();
		double DeltaTime();
	};
}}
