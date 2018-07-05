/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSpriteControl.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFData;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFSpriteControl::LFSpriteControl(const LFString &name, const LFRectangle &posVertexSize, const LFVector2D &posAtlas, bool isBasicShader, const LFColor &color)
		: LFControl(name, LFString(LFSystemData::LFAtlasName), posVertexSize,
			LFRectangle(posAtlas.x, posAtlas.y, LFSystemData::LFDataAtlasWidth, LFSystemData::LFDataAtlasHeight), color, isBasicShader)
	{ }
}}} 
