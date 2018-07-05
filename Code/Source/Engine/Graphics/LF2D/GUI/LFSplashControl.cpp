/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSplashControl.h"
#include "LFSpriteFont.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\GameEngine\LFScreen.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFLabelControlLua.h"
#include "..\..\..\Script\LFLuaType.h"
#include "..\..\..\..\Engine\Common\LFSystemInfo.h"
#include "..\..\..\..\Core\Math\LFRectangle.h"
#include "..\..\..\..\Core\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::Math;
using namespace LFCore::IO;
using namespace LFEngine::Input;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Script;
using namespace LFEngine::Common;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFSplashControl::LFSplashControl() :
		LFControl(LFString(LFSplashControlName), LFRectangle(), false, false)
	{ 
		//controlType = LFLuaType().SetObject(this, LFSplashControlName, sizeof(LFSplashControl));
	}

	LFSplashControl::~LFSplashControl()
	{ }

	void LFSplashControl::AttachChildren(LFLayer *layer)
	{
		LFString timerName;
		timerName += name;
		timerName += "Timer";
		timerControl = LFNew<LFTimerControl>(AT, timerName, LFSystemInfo::SplashScreenSeconds());
		componentList.Add(timerControl); //for hierarchy
		layer->Add(timerControl); //for render/update
		timerControl->TickEvent += this;

		LFString spriteGeneratedName;
		spriteGeneratedName += LFSplashControlName;
		spriteGeneratedName += "Sprite";

		LFSprite *sprite = LFNew<LFSprite>(AT, spriteGeneratedName, LFString(LFSystemInfo::SplashScreenTexture()), 
			LFRectangle(0, 0, LFSystemInfo::DefaultWindowWidth(), LFSystemInfo::DefaultWindowHeight()), LFRectangle());
		componentList.Add(sprite); //for hierarchy
		layer->Add(sprite); //for render/update

		timerControl->Start();
		LFLogger::Instance().WriteOutput("Start splash screen");
	}

	void LFSplashControl::Tick(const LFObserverEventArgs<LFTimerControl *> &args)
	{
		timerControl->Stop();
		timerControl->TickEvent -= this;

		//scene graph change first screen because of invalid active screen
		layer->Screen()->SetIsAlive(false);

		LFLogger::Instance().WriteOutput("End splash screen");
	}
}}}}
