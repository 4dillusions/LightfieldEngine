/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTimer.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	LFTimer::LFTimer()
	{
		Reset();
	}

	double LFTimer::GetActualTime()
	{
		static double result;

	#ifdef TIZEN
		static timespec nixTimeLocal;
		clock_gettime(CLOCK_REALTIME, &nixTimeLocal);
		result = ((nixTimeLocal.tv_sec * 1000) + (nixTimeLocal.tv_nsec / 1000000));
	#else
		result = clock();
	#endif

		return result;
	}

	void LFTimer::Reset()
	{
	#ifdef TIZEN
		clock_gettime(CLOCK_REALTIME, &nixTime);
		lastTime = ((nixTime.tv_sec * 1000) + (nixTime.tv_nsec / 1000000));
	#else
		lastTime = clock();
	#endif

		currentTime = 0;
		deltaTime = 0;
	}

	double LFTimer::DeltaTime()
	{
	#ifdef TIZEN
		clock_gettime(CLOCK_REALTIME, &nixTime);
		currentTime = ((nixTime.tv_sec * 1000) + (nixTime.tv_nsec / 1000000));
	#else
		currentTime = clock();
	#endif

		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		return deltaTime;
	}
}}}}
