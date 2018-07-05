/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTimer.h"

namespace LFCore { namespace Common
{
	LFTimer::LFTimer() : lastTime(0), currentTime(0), deltaTime(0)
	{
		Reset();
	}

	double LFTimer::GetActualTime()
	{
		static double result = 0;

		#ifdef TIZEN
		static timespec nixTimeLocal;
		clock_gettime(CLOCK_REALTIME, &nixTimeLocal);
		result = ((nixTimeLocal.tv_sec * 1000) + (nixTimeLocal.tv_nsec / 1000000));
		#endif

		#ifdef WIN32
		result = clock();
		#endif

		return result;
	}

	void LFTimer::Reset()
	{
		#ifdef TIZEN
		clock_gettime(CLOCK_REALTIME, &nixTime);
		lastTime = ((nixTime.tv_sec * 1000) + (nixTime.tv_nsec / 1000000));
		#endif

		#ifdef WIN32
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
		#endif

		#ifdef WIN32
		currentTime = clock();
		#endif

		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		return deltaTime;
	}
}}
