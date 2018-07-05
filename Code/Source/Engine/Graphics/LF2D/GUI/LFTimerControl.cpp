/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTimerControl.h"

using namespace LFCore::Common;
using namespace LFCore::Math;
using namespace LFEngine::GameEngine;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFTimerControl::LFTimerControl(const LFString &name, double interval)
		: LFControl(name, LFRectangle(), false, false), time(0), interval(interval * 1000.0), isActive(false), TickEvent(&LFITickEventHandler<LFTimerControl *>::Tick)
	{ }

	LFTimerControl::LFTimerControl(const LFTimerControl &value)
		: LFControl(name, LFRectangle(), false), TickEvent(&LFITickEventHandler<LFTimerControl *>::Tick)
	{
		*this = value;
	}

	LFTimerControl::~LFTimerControl()
	{ }

	void LFTimerControl::Update(double deltaTime)
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
}}}}
