/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTouchableControl.h"
#include "..\LFScene\LFScreen.h"
#include "..\LFInput\LFInputSystem.h"
#include "..\LFCore\LFPatterns\LFIoc.h"
#include "..\LFCore\LFCommon\LFSystemData.h"
#include "LFSpriteControl.h"

using namespace LF3Engine::LFEngine::LFData;
using namespace LF3Engine::LFEngine::LFInput;
using namespace LF3Engine::LFEngine::LFScene;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFTouchableControl::LFTouchableControl(const LFString &name, const LFRectangle &posTileSize, const LFVector2D &touchSize)
		: LFControl(name, LFString(LFSystemData::LFAtlasName), posTileSize,
			LFRectangle(-1, -1, LFSystemData::LFDataAtlasWidth, LFSystemData::LFDataAtlasHeight), LFColor(LFColor::White), true)
	{
		this->posTouchSize = LFRectangle(posTileSize.position.x * LFSystemData::GetWindowWidthRelativeScale(),
			posTileSize.position.y * LFSystemData::GetWindowHeightRelativeScale(),
			touchSize.x * LFSystemData::GetWindowWidthRelativeScale(),
			touchSize.y * LFSystemData::GetWindowHeightRelativeScale());

		LFIoc<LFInputSystem *>::Get()->OnPointerPressRelease += [this](const PointerPressReleaseEventArgs &args)
		{
			if (this->screen->GetIsActive() && isVisible)
			{
				bool isContains = this->posTouchSize.Contains(args.x, args.y);

				if(args.isPressed)
				{
					if (isContains)
					{
						ChangeColor(true);
						lastTouchedControl = this;
					}
				}
				else
				{
					ChangeColor(false);

					if (isContains && lastTouchedControl == this)
						OnControlRelease(PointerReleaseEventArgs{ args.x, args.y });

					lastTouchedControl = nullptr;
				}
			}
		};
	}

	void LFTouchableControl::ChangeColor(bool isPressed)
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (LFSpriteControl *sprite = dynamic_cast<LFSpriteControl *>(componentList.Current()))
				sprite->SetColor(isPressed ? PressedColor : ReleasedColor);
	}
}}}
