/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTimeLabelControl.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\Script\LFLuaType.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFTimeLabelControlLua.h"
#include "..\..\..\Script\LFScriptSystem.h"

using namespace LFCore::Common;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Script;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFTimeLabelControl::LFTimeLabelControl(const LFFontMaterial &fontMaterial, const LFControlMaterial &controlMaterial, const LFLabelData &labelData, const LFTimeLabelData &timeLabelData) :
		LFLevelLabelControl(fontMaterial, controlMaterial, labelData),
		timeLabelData(timeLabelData), timerControl(nullptr)
	{
		controlType = LFLuaType().SetObject(this, LFTimeLabelControlName, sizeof(LFTimeLabelControl));
	}

	LFTimeLabelControl::~LFTimeLabelControl()
	{ }

	int LFTimeLabelControl::Time()
	{
		return Value();
	}

	void LFTimeLabelControl::Time(int second)
	{
		Value(second);
	}

	void LFTimeLabelControl::Reset()
	{
		Stop();

		if (timeLabelData.isIncrement)
			Value(timeLabelData.minTime);
		else
			Value(timeLabelData.maxTime);
	}

	void LFTimeLabelControl::Start()
	{
		if (timerControl != nullptr && (timeLabelData.isIncrement ? Value() < timeLabelData.maxTime : Value() > timeLabelData.minTime))
			timerControl->Start();
	}

	void LFTimeLabelControl::Stop()
	{
		if (timerControl != nullptr)
			timerControl->Stop();
	}

	void LFTimeLabelControl::CallTimeOutLuaEvent()
	{
		LFScriptSystem::Instance()->CallFunction(controlType, LFTimeLabelOnTimeOutName, controlType);
	}

	void LFTimeLabelControl::AttachChildren(LFLayer *layer)
	{
		LFString timerName;
		timerName += name;
		timerName += "Timer";
		timerControl = LFNew<LFTimerControl>(AT, timerName, timeLabelData.interval);
		componentList.Add(timerControl); //for hierarchy
		layer->Add(timerControl); //for render/update
		timerControl->TickEvent += this;

		LFLevelLabelControl::AttachChildren(layer);

		Reset();
	}

	void LFTimeLabelControl::Tick(const LFObserverEventArgs<LFTimerControl *> &args)
	{
		if (timeLabelData.isIncrement)
		{
			Value(Value() + 1);

			if (Value() == timeLabelData.maxTime)
			{
				timerControl->Stop();
				CallTimeOutLuaEvent();
			}
		}
		else
		{
			Value(Value() - 1);

			if (Value() == timeLabelData.minTime)
			{
				timerControl->Stop();
				CallTimeOutLuaEvent();
			}
		}
	}
}}}}
