/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFCheckBoxControl.h"
#include "LFSpriteControl.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFData;
using namespace LF3Engine::LFEngine::LFInput;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFCheckBoxControl::LFCheckBoxControl(const LFString &name, const LFRectangle &posTileSize, bool isChecked,
		const LFVector2D &posAtlasChecked, const LFVector2D &posAtlasUnchecked)
			: LFTouchableControl(name, posTileSize, LFVector2D(posTileSize.width, posTileSize.height)),
			isChecked(isChecked)
	{
		LFCheckBoxControl::Add(LFMemoryManager::New<LFSpriteControl>(INFO, name + LFString("Checked"), posTileSize, posAtlasChecked, true));
		LFCheckBoxControl::Add(LFMemoryManager::New<LFSpriteControl>(INFO, name + LFString("Unchecked"), posTileSize, posAtlasUnchecked, true));

		SetIsChecked(isChecked);

		OnControlRelease += [this](const PointerReleaseEventArgs &args) { SetIsChecked(!this->isChecked);  };
	}

	bool LFCheckBoxControl::GetIsChecked() const
	{
		return isChecked;
	}

	void LFCheckBoxControl::SetIsChecked(bool isChecked)
	{
		this->isChecked = isChecked;

		componentList.First();
		componentList.Next();
		componentList.Current()->SetIsVisible(!isChecked);
	}

	void LFCheckBoxControl::ChangeColor(bool isPressed)
	{
		LFTouchableControl::ChangeColor(isPressed);
	}

	void LFCheckBoxControl::SetIsVisible(bool isVisible)
	{
		LFControl::SetIsVisible(isVisible);
		
		if (isVisible)
			SetIsChecked(isChecked);
	}
}}}
