/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFInputSystem.h"
#include "..\..\Core\\IO\LFLogger.h"

using namespace LFCore::IO;

namespace LFEngine { namespace Input
{
	LFInputSystem *LFInputSystem::instance = nullptr;

	LFInputSystem::LFInputSystem() : 
		PointerPressReleaseEvent(&LFIPointerPressReleaseEventHandler::OnPointerPressRelease), 
		PointerMoveEvent(&LFIPointerMoveEventHandler::OnPointerMove)
	{ 
		LFLogger::Instance().WriteOutput("Create InputSystem");
	}

	LFInputSystem::~LFInputSystem()
	{ 
		LFLogger::Instance().WriteOutput("Release InputSystem");
	}
}}
