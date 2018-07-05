#include "SMTimer.h"
#include <time.h>

#ifdef BADA_PLATFORM
#include <FSystem.h>
#endif

namespace SMEngine { namespace Core
{
	SMTimer::SMTimer()
	{
		Reset();
	}

	void SMTimer::Reset()
	{
		lastTime = currentTime = deltaTime = 0;
	}

	double SMTimer::DeltaTime()
	{
		#ifdef BADA_PLATFORM
		Osp::System::SystemTime::GetTicks(currentTime);
		#else
		currentTime = clock();
		#endif

		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		return deltaTime;
	}
};};
