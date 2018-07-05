/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\..\..\GameEngine\LFControl.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	template <typename T> class LFENGINE_LIBRARY LFITickEventHandler
	{
	public:
		virtual void Tick(const LFEngine::GameEngine::LFObserverEventArgs<T> &args) = 0;
	};

	class LFENGINE_LIBRARY LFTimerControl : public LFEngine::GameEngine::LFControl
	{
	private:
		double time, interval; //msec
		LFEngine::GameEngine::LFObserverEventArgs<LFTimerControl *> timerArgs;
		bool isActive;

	public:
		LFTimerControl(const LFCore::Common::LFString &name, double interval = 0);
		LFTimerControl(const LFTimerControl &value);
		virtual ~LFTimerControl();

		LFCore::Common::LFEventArgs<LFITickEventHandler<LFTimerControl *>, LFEngine::GameEngine::LFObserverEventArgs<LFTimerControl *> > TickEvent;

		double Interval() { return interval / 1000.0; } //second
		void Interval(double interval) { this->interval = (interval * 1000.0) > 0 ? (interval * 1000.0) : 0; } //second
		void Start() { isActive = true; };
		void Stop() { isActive = false; time = 0; };

		//LFGameCompositComponent
		virtual void Update(double deltaTime);

		//LFControl
		virtual void AttachChildren(LFEngine::GameEngine::LFLayer *layer) { }

		virtual void OnControlPress(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlRelease(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlPressed(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnMouseMove(const LFEngine::Input::LFPointerMoveEventArgs &args) { }
	};
}}}}
