/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSprite.h"
#include "..\..\Render\LFRender.h"

using namespace LFCore::Common;
using namespace LFCore::Math;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Render;

namespace LFEngine { namespace Graphics { namespace LF2D
{
	LFSprite::LFSprite(const LFString &name, const LFString &textureName, LFRectangle &posVertexSize, LFRectangle &atlasPosSize) : 
		LF2DObject(name,  textureName, posVertexSize, atlasPosSize)
    {  }

	LFSprite::~LFSprite()
    { }
}}}
