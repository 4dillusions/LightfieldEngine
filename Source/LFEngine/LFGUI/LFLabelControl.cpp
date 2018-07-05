/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLabelControl.h"
#include "LFFontControl.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFData;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFLabelControl::LFLabelControl(const LFString &name, const LFString &text, const LFRectangle &posTileSize) :
		LFFontControl(name, text[0], posTileSize),
		text(text)
	{
		for (int i = 1; i < text.GetTextLength(); i++)
			LFLabelControl::Add(LFMemoryManager::New<LFFontControl>(INFO, name + i, text[i], 
				LFRectangle(posTileSize.position.x + (posTileSize.width * i), posTileSize.position.y, posTileSize.width, posTileSize.height)));
	}

	int LFLabelControl::GetTextLength() const
	{
		return text.GetTextLength();
	}

	void LFLabelControl::SetText(const LFString &text)
	{
		this->text = text;
		SetCharacter(text[0]);

		int i = 1;
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (LFFontControl *font = dynamic_cast<LFFontControl *>(componentList.Current()))
			{
				if (i < text.GetTextLength())
					font->SetCharacter(text[i++]);
				else
					font->SetCharacter(' ');
			}
	}

	const LFString &LFLabelControl::GetText() const
	{
		return text;
	}

	void LFLabelControl::SetColor(const LFColor &color)
	{
		LFControl::SetColor(color);

		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (LFControl *control = dynamic_cast<LFControl *>(componentList.Current()))
				control->SetColor(color);
	}
}}}
