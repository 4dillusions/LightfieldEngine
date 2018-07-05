/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFControl.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFSpriteControl : public LFControl
	{
	public:
		LFSpriteControl(const LFCore::LFCommon::LFString &name, const LFCore::LFMath::LFRectangle &posVertexSize, const LFCore::LFMath::LFVector2D &posAtlas, bool isBasicShader = false, const LFCore::LFMath::LFColor &color = LFCore::LFMath::LFColor(LFCore::LFMath::LFColor::White));
		virtual ~LFSpriteControl() = default;
	};
}}} 
