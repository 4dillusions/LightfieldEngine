/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore\LFCommon\LFEvent.h"
#include "LFHardwareButtonTypes.h"

namespace LF3Engine { namespace LFEngine { namespace LFGameEngine
{
	class LFIGame;
}}}

namespace LF3Engine { namespace LFEngine { namespace LFInput
{
	struct HardwareButtonEventArgs { bool isPressed; LFHardwareButtonTypes button; };
	struct PointerPressReleaseEventArgs { bool isPressed; int x, y; };
	struct PointerReleaseEventArgs { int x, y; };
	struct PointerMoveEventArgs { int x, y; };

	/** 
		@brief 
		Input subsystem for PC and mobile devices <br>
			pointer: PC mouse / mobile touch screen <br>
			button: PC keyboard / mobile hardware buttons <br>
	*/
	class LFInputSystem
	{
		LFInputSystem(const LFInputSystem&) = delete;
		LFInputSystem(LFInputSystem &&) = delete;
		LFInputSystem &operator=(const LFInputSystem &) = delete;
		LFInputSystem &operator=(LFInputSystem &&) = delete;

	protected:
		static char *const SoundUp;
		static char *const SoundDown;
		static char *const Back;

		static HardwareButtonEventArgs hardwareButtonEventArgs;
		static PointerPressReleaseEventArgs pointerPressReleaseEventArgs;
		static PointerMoveEventArgs pointerMoveEventArgs;

		static LFInputSystem *input;
		static LFGameEngine::LFIGame *game;

	public:
		LFInputSystem();
		virtual ~LFInputSystem();

		LFCore::LFCommon::LFEvent<HardwareButtonEventArgs> OnHardwareButtonPressRelease;
		LFCore::LFCommon::LFEvent<PointerPressReleaseEventArgs> OnPointerPressRelease;
		LFCore::LFCommon::LFEvent<PointerMoveEventArgs> OnPointerMove;
	};
}}}
