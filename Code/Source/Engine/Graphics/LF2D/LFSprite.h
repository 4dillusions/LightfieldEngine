/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\..\GameEngine\LF2DObject.h"

namespace LFEngine { namespace Graphics { namespace LF2D
{
	class LFENGINE_LIBRARY LFSprite : public LFEngine::GameEngine::LF2DObject
	{
	public:
		LFSprite(const LFCore::Common::LFString &name, const LFCore::Common::LFString &textureName, LFCore::Math::LFRectangle &posVertexSize, LFCore::Math::LFRectangle &atlasPosSize);
		virtual ~LFSprite();
	};
}}}
