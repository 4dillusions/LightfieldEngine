/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFImageControl.h"
#include "../LFCore/LFCommon/LFSystemData.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFImageControl::LFImageControl(const LFString &name, const LFString &textureName) 
		: LFControl(name, textureName, LFRectangle(0, 0, LFSystemData::LFDefaultWindowWidth, LFSystemData::LFDefaultWindowHeight), 
			LFRectangle(0, 0, 1, 1), LFColor(LFColor::White), true)
	{ }
}}}
