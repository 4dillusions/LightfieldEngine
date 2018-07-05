/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFInputSystem.h"
#include "..\LFCore\LFPatterns\LFIoc.h"
#include "..\LFCore\LFIO\LFLogger.h"
#include "..\LFGameEngine\LFIGame.h"

using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFGameEngine;

namespace LF3Engine { namespace LFEngine { namespace LFInput
{
	char *const LFInputSystem::SoundUp = "SoundUp";
	char *const LFInputSystem::SoundDown = "SoundDown";
	char *const LFInputSystem::Back = "Back";

	HardwareButtonEventArgs LFInputSystem::hardwareButtonEventArgs;
	PointerPressReleaseEventArgs LFInputSystem::pointerPressReleaseEventArgs;
	PointerMoveEventArgs LFInputSystem::pointerMoveEventArgs;

	LFInputSystem *LFInputSystem::input = nullptr;
	LFIGame *LFInputSystem::game = nullptr;

	LFInputSystem::LFInputSystem()
    {
		LFIoc<LFLogger>::Get().WriteOutput("Create InputSystem");
	}

	LFInputSystem::~LFInputSystem()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Release InputSystem");
	}
}}}
