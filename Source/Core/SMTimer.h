#pragma once

namespace SMEngine { namespace Core
{
	/*
	C-s idõzítõ: delta time-ot ad vissza a renderelt elemeknek.
	A DeltaTime visszaadja az eltelt idõt két lekérdezés között.

	Ezredmásodperceket ad vissza pl 3 mp-es pause:

	SMTimer timer;
	...
	double time = 0;
    for(; ;)
    {
        time += timer.DeltaTime();

        if (time > 3000)
            break;
    }
	*/
	class SMTimer
	{
	private:
		#ifdef BADA_PLATFORM
		#define CLOCK_TYPE long long
		#else
		#define CLOCK_TYPE double
		#endif

		CLOCK_TYPE lastTime, currentTime, deltaTime;

	public:
		SMTimer();

		void Reset();
		double DeltaTime();
	};
};};
