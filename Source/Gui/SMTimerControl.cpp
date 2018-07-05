#include "SMTimerControl.h"

namespace SMEngine { namespace Gui
{
	SMTimerControl::SMTimerControl(const SMString &name, double interval)
		: SMControl(name), time(0), interval(interval), isActive(false), TickEvent(&SMITickEventHandler<SMTimerControl *>::Tick)
	{
		isUpdatable = true;
	}

	SMTimerControl::SMTimerControl(const SMTimerControl &value)
		: SMControl(name), TickEvent(&SMITickEventHandler<SMTimerControl *>::Tick)
	{
		*this = value;
	}

	SMTimerControl::~SMTimerControl()
	{ }

	void SMTimerControl::Update(double deltaTime)
	{
		if (isActive)
		{
			if (time > interval)
			{
				time = 0;

				timerArgs.subject = this;
				TickEvent(timerArgs);
			}
			else
				time += deltaTime;
		}
	}
};};
