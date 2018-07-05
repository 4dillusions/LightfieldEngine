/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFInput
{
	struct HardwareButtonEventArgs;
	struct PointerPressReleaseEventArgs;
	struct PointerMoveEventArgs;
}}}

namespace LF3Engine { namespace LFEngine { namespace LFGameEngine
{
	/**
	@brief
	Game interface supports main game events
	*/
	class LFIGame
	{
		LFIGame(const LFIGame&) = delete;
		LFIGame(LFIGame &&) = delete;
		LFIGame &operator=(const LFIGame &) = delete;
		LFIGame &operator=(LFIGame &&) = delete;

	public:
		LFIGame() = default;
		virtual ~LFIGame() = default;

		virtual void OnInitGame() = 0;
		virtual void OnLoadedGame() = 0;
		virtual void OnTerminateGame() = 0;
		virtual void OnButtonPressRelease(const LFInput::HardwareButtonEventArgs &args) = 0;
		virtual void OnPointerPressRelease(const LFInput::PointerPressReleaseEventArgs &args) = 0;
		virtual void OnPointerMove(const LFInput::PointerMoveEventArgs &args) = 0;
	};
}}}
