/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFButtonControl.h"
#include "LFSpriteControl.h"
#include "LFFontControl.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFData;
using namespace LF3Engine::LFEngine::LFInput;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFButtonControl::LFButtonControl(const LFString &name, int centerLenght, const LFString &text, const LFRectangle &posTileSize)
		: LFTouchableControl(name, posTileSize, LFVector2D(posTileSize.width * (centerLenght + 2), posTileSize.height)),
		centerLenght(centerLenght), text(text)
	{
		LFButtonControl::Add(LFMemoryManager::New<LFSpriteControl>(INFO, name + LFString("Left"), posTileSize, LFSystemData::ButtonLeft, true));
		
		for (int i = 0; i < centerLenght; i++)
			LFButtonControl::Add(LFMemoryManager::New<LFSpriteControl>(INFO, name + LFString("Center") + i, 
				LFRectangle(posTileSize.position.x + posTileSize.width + (posTileSize.width * i), posTileSize.position.y, posTileSize.width, posTileSize.height),
				LFSystemData::ButtonCenter, true));

		LFButtonControl::Add(LFMemoryManager::New<LFSpriteControl>(INFO, name + LFString("Right"), 
			LFRectangle(posTileSize.position.x + (posTileSize.width * (centerLenght + 1)), posTileSize.position.y, posTileSize.width, posTileSize.height),
			LFSystemData::ButtonRight, true));
		
		//its' tiles after button tiles are font charecters
		int width = posTileSize.width * (centerLenght + 2);
		int textWidth = text.GetTextLength() * posTileSize.width;
		int posX = posTileSize.position.x + (width - textWidth) / 2;

		//int posX = posTileSize.position.x + 50;
		for (int i = 0; i < text.GetTextLength(); i++)		
			LFButtonControl::Add(LFMemoryManager::New<LFFontControl>(INFO, name + LFString("Char") + i, text[i], 
				LFRectangle(posX + (posTileSize.width * i), posTileSize.position.y, posTileSize.width, posTileSize.height)));
	}

	void LFButtonControl::ChangeColor(bool isPressed)
	{
		int spriteCount = 0;
		for (componentList.First(); componentList.IsDone(); componentList.Next())
		{
			spriteCount++;
			if (spriteCount > (centerLenght + 2))
				break;

			if (LFSpriteControl *sprite = dynamic_cast<LFSpriteControl *>(componentList.Current()))
				sprite->SetColor(isPressed ? PressedColor : ReleasedColor);
		}
	}

	const LFString &LFButtonControl::GetText() const
	{
		return text;
	}
}}}
