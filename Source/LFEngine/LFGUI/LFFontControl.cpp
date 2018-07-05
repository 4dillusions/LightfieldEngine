/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFFontControl.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFData;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFFontControl::LFFontControl(const LFString &name, char character, const LFRectangle &posSize)
		: LFControl(name, LFString(LFSystemData::LFAtlasName), posSize, LFRectangle(LFSystemData::GetLFAlphabetCoord(character).x,
			LFSystemData::GetLFAlphabetCoord(character).y, LFSystemData::LFDataAtlasWidth, LFSystemData::LFDataAtlasHeight), LFColor(LFColor::White), true)
	{ }

	void LFFontControl::SetCharacter(char character)
	{
		auto alphabetCoord = LFSystemData::GetLFAlphabetCoord(character);
		posAtlasSize.SetPosition(alphabetCoord.x, alphabetCoord.y);
		SetStartVertex();
	}
}}}
