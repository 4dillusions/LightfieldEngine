/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLevelLabelControl.h"
#include "LFNumberLabelControl.h"
#include "LFTimerControl.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFLevelLabelControlLua.h"
#include "..\..\..\Script\LFLuaType.h"

using namespace LFCore::Common;
using namespace LFEngine::Input;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Script;
using namespace LFCore::Math;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFLevelLabelControl::LFLevelLabelControl(const LFFontMaterial &fontMaterial, const LFControlMaterial &controlMaterial, const LFLabelData &labelData) :
		LFControl(LFString(labelData.labelName), LFRectangle(), false, false),
		fontMaterial(fontMaterial), controlMaterial(controlMaterial), labelData(labelData)
	{
		controlType = LFLuaType().SetObject(this, LFLevelLabelControlName, sizeof(LFLevelLabelControl));
	}

	LFLevelLabelControl::~LFLevelLabelControl()
	{ }

	int LFLevelLabelControl::Value()
	{ 
		return numberLabel->Value(); 
	}

	void LFLevelLabelControl::Value(int value)
	{ 
		numberLabel->Value(value); 
	}

	void LFLevelLabelControl::AttachNumberLabelChild(LFLayer *layer)
	{
		LFString numberLabelName(labelData.labelName);
		numberLabelName += "NumberLabel";
		labelData.labelName = numberLabelName.ToChar();

		labelData.posX += (controlMaterial.textureWidth - (labelData.digits * fontMaterial.textureWidth)) / 2;
		labelData.posY += (controlMaterial.textureHeight - fontMaterial.textureHeight + (fontMaterial.textureHeight / 4));
		
		LFNumberLabelControl *numberLabel = LFNew<LFNumberLabelControl>(AT, fontMaterial, labelData);
		
		this->numberLabel = numberLabel;

		numberLabel->AttachChildren(layer);
		componentList.Add(numberLabel); //for hierarchy
		layer->Add(numberLabel); //for render/update
	}

	void LFLevelLabelControl::AttachChildren(LFLayer *layer)
	{
		AttachSpriteChildren(name.ToChar(), layer, LFString(controlMaterial.textureName), LFRectangle(labelData.posX, labelData.posY, controlMaterial.textureWidth, controlMaterial.textureHeight),
			LFRectangle(controlMaterial.atlasPosSize.position, LFVector2D(controlMaterial.atlasWidth, controlMaterial.atlasHeight)), 
			LFVector2D(controlMaterial.atlasPosSize.width, controlMaterial.atlasPosSize.height));

		AttachNumberLabelChild(layer);
	}
}}}}
