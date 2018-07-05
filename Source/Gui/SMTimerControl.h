#pragma once

#include "SMControl.h"

namespace SMEngine { namespace Gui
{
	/*
	TimerControl:
	Automatikusan frissíthetõ timer komponens Tick eseménnyel.
	*/
	class SMTimerControl : public SMControl
	{
	private:
		double time, interval;
		SMObserverEventArgs<SMTimerControl *> timerArgs;
		bool isActive;

	public:
		SMTimerControl(const SMString &name, double interval = 0);
		SMTimerControl(const SMTimerControl &value);
		virtual ~SMTimerControl();

		SMEventArgs<SMITickEventHandler<SMTimerControl *>, SMObserverEventArgs<SMTimerControl *> > TickEvent;

		double Interval() { return interval; }
		void Interval(double interval) { this->interval = interval > 0 ? interval : 0; }
		void Start() { isActive = true; };
		void Stop() { isActive = false; };
	
		override void Update(double deltaTime);
	};
};};
