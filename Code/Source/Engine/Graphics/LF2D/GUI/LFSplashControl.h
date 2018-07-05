/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLabelControl.h"
#include "LFTimerControl.h"

#define LFSplashScreenName "SplashScreen"
#define LFSplashLayerName "LFSplashLayer"
#define LFSplashControlName "SplashControl"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	class LFENGINE_LIBRARY LFSplashControl : public LFEngine::GameEngine::LFControl, public LFITickEventHandler<LFTimerControl *>
	{
	private:
		LFTimerControl *timerControl;

	public:
		LFSplashControl();
		virtual ~LFSplashControl();

		//LFControl
		virtual void AttachChildren(LFEngine::GameEngine::LFLayer *layer);

		virtual void OnControlPress(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlRelease(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlPressed(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnMouseMove(const LFEngine::Input::LFPointerMoveEventArgs &args) { }

		//LFITickEventHandler
		virtual void Tick(const LFEngine::GameEngine::LFObserverEventArgs<LFTimerControl *> &args);
	};
}}}}
