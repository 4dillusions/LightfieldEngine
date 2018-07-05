/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLevelLabelControl.h"
#include "LFTimerControl.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	class LFTimerControl;

	class LFENGINE_LIBRARY LFTimeLabelData
	{
	public:
		int minTime, maxTime, interval;
		bool isIncrement;
	};

	class LFENGINE_LIBRARY LFTimeLabelControl : public LFLevelLabelControl, public LFITickEventHandler<LFTimerControl *>
	{
	private:
		LFTimeLabelData timeLabelData;
		LFTimerControl *timerControl;

		LFEngine::GameEngine::LFObserverEventArgs<LFTimeLabelControl *> timerLabelArgs;

	public:
		LFTimeLabelControl(const LFEngine::GameEngine::LFFontMaterial &fontMaterial, const LFEngine::GameEngine::LFControlMaterial &controlMaterial, const LFLabelData &labelData,
			const LFTimeLabelData &timeLabelData);
		virtual ~LFTimeLabelControl();

		int Time();
		void Time(int second);

		void Reset();
		void Start();
		void Stop();

		void CallTimeOutLuaEvent();

		//LFLevelLabelControl
		virtual void AttachChildren(LFEngine::GameEngine::LFLayer *layer);

		//LFITickEventHandler
		virtual void Tick(const LFEngine::GameEngine::LFObserverEventArgs<LFTimerControl *> &args);
	};
}}}}
