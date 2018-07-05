/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFControl.h"
#include "..\LFInput\LFInputSystem.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFTouchableControl : public LFControl
	{
		LFTouchableControl *lastTouchedControl = nullptr;

	protected:
		LFCore::LFMath::LFRectangle posTouchSize;
		const LFCore::LFMath::LFColor PressedColor = LFCore::LFMath::LFColor(LFCore::LFMath::LFColor::Gray);
		const LFCore::LFMath::LFColor ReleasedColor = LFCore::LFMath::LFColor(LFCore::LFMath::LFColor::White);

		virtual void ChangeColor(bool isPressed);

	public:
		LFTouchableControl(const LFCore::LFCommon::LFString &name, const LFCore::LFMath::LFRectangle &posTileSize, const LFCore::LFMath::LFVector2D &touchSize);
		virtual ~LFTouchableControl() = default;

		LFCore::LFCommon::LFEvent<LFInput::PointerReleaseEventArgs> OnControlRelease;
	};
}}}
