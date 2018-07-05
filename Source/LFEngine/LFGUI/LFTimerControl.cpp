/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTimerControl.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFTimerControl::LFTimerControl(const LFString &name, double interval) : 
		LFControl(name, LFString(), LFRectangle(), LFRectangle(), LFColor(), true),
			time(0), interval(interval * 1000.0), isActive(false)
	{ }

	double LFTimerControl::Interval() const
	{
		return interval / 1000.0;
	}

	void LFTimerControl::Interval(double interval)
	{
		this->interval = (interval * 1000.0) > 0 ? (interval * 1000.0) : 0;
	}

	void LFTimerControl::Start()
	{
		isActive = true;
	}

	void LFTimerControl::Stop()
	{
		isActive = false; 
		time = 0;
	}

	void LFTimerControl::Update(double deltaTime)
	{
		if (isActive)
		{
			if (time > interval)
			{
				time = 0;
				TickEvent(*this);
			}
			else
				time += deltaTime;
		}
	}
}}}
