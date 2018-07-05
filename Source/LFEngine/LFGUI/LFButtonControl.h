/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFTouchableControl.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFButtonControl final : public LFTouchableControl
	{
		int centerLenght;
		LFCore::LFCommon::LFString text;

		void ChangeColor(bool isPressed) override;

	public:
		LFButtonControl(const LFCore::LFCommon::LFString &name, int centerLenght, const LFCore::LFCommon::LFString &text, const LFCore::LFMath::LFRectangle &posTileSize);
		~LFButtonControl() = default;

		const LFCore::LFCommon::LFString &GetText() const;
	};
}}}
