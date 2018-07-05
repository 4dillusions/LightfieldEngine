/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFImageButtonControl.h"
#include "LFSpriteControl.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFData;
using namespace LF3Engine::LFEngine::LFInput;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFImageButtonControl::LFImageButtonControl(const LFString &name, const LFRectangle &posTileSize, const LFVector2D &posAtlasTile)
			: LFTouchableControl(name, posTileSize, LFVector2D(posTileSize.width, posTileSize.height))
	{
		LFImageButtonControl::Add(LFMemoryManager::New<LFSpriteControl>(INFO, name + LFString("Tile"), posTileSize, posAtlasTile, true));
	}
}}}
