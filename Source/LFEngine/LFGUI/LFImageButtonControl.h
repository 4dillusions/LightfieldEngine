/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFTouchableControl.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFImageButtonControl final : public LFTouchableControl
	{
	public:
		LFImageButtonControl(const LFCore::LFCommon::LFString &name, const LFCore::LFMath::LFRectangle &posTileSize, const LFCore::LFMath::LFVector2D &posAtlasTile);
		~LFImageButtonControl() = default;
	};
}}}
