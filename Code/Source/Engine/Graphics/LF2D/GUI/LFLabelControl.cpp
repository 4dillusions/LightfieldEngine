/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLabelControl.h"
#include "LFSpriteFont.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFLabelControlLua.h"
#include "..\..\..\Script\LFLuaType.h"

using namespace LFCore::Common;
using namespace LFEngine::Input;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Script;
using namespace LFCore::Math;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFLabelControl::LFLabelControl(const LFFontMaterial &fontMaterial, const LFLabelData &labelData) : 
		LFControl(LFString(labelData.labelName), LFRectangle(), false, false),
		fontMaterial(fontMaterial), labelData(labelData)
	{ 
		controlType = LFLuaType().SetObject(this, LFLabelControlName, sizeof(LFLabelControl));
	}

	LFLabelControl::~LFLabelControl()
	{ }

	void LFLabelControl::AttachChildren(LFLayer *layer)
	{
		for (int i = 0, posX = labelData.posX; i < labelData.text.Length(); ++i, posX += fontMaterial.textureWidth)
		{
			FontData fontData;
			fontData.character = labelData.text[i];
			
			LFString spriteFontName;
			spriteFontName.Append(labelData.labelName);
			spriteFontName.Append(i);
			fontData.spriteFontName = spriteFontName.ToChar();

			LFSpriteFont *font = LFNew<LFSpriteFont>(AT, fontData, LFString(fontMaterial.textureName), 
				LFRectangle(posX -= fontData.character == ' ' ? fontMaterial.textureWidth / 2 : 0, labelData.posY, fontMaterial.textureWidth, fontMaterial.textureHeight),
				LFRectangle(fontMaterial.alphabetData[(int)fontData.character].x, fontMaterial.alphabetData[(int)fontData.character].y, fontMaterial.atlasWidth, fontMaterial.atlasHeight));

			componentList.Add(font); //for hierarchy
			layer->Add(font); //for render/update
		}
	}
}}}}
