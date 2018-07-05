/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFControl.h"
#include "..\LFCore\LFCommon\LFEvent.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFTimerControl final : public LFControl
	{
		double time, interval; //msec
		bool isActive;

	public:
		LFTimerControl(const LFCore::LFCommon::LFString &name, double interval);
		~LFTimerControl() = default;

		LFCore::LFCommon::LFEvent<LFTimerControl> TickEvent;

		double Interval() const; //second
		void Interval(double interval); //second
		void Start();
		void Stop();

		//LFGameComponent
		void Update(double deltaTime) override;
	};
}}}
