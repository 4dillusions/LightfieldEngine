/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFButtonControl.h"
#include "LFSpriteFont.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\..\Core\\Math\LFVector2D.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFButtonControlLua.h"
#include "..\..\..\Script\LFLuaType.h"

using namespace LFCore::Common;
using namespace LFEngine::Input;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Script;
using namespace LFCore::Math;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFButtonControl::LFButtonControl(const LFFontMaterial &fontMaterial, const LFControlMaterial &nonTouchedControlMaterial,
		LFControlMaterial &touchedControlMaterial, const LFLabelData &labelData, float labelPosY) :
		LFControl(LFString(labelData.labelName), 
		LFRectangle(LFVector2D(labelData.posX, labelData.posY), LFVector2D(nonTouchedControlMaterial.textureWidth * nonTouchedControlMaterial.atlasPosSize.width, nonTouchedControlMaterial.textureHeight * nonTouchedControlMaterial.atlasPosSize.height)),
		false),
		fontMaterial(fontMaterial), nonTouchedControlMaterial(nonTouchedControlMaterial), touchedControlMaterial(touchedControlMaterial), labelData(labelData), labelPosY(labelPosY)
	{
		controlType = LFLuaType().SetObject(this, LFButtonControlName, sizeof(LFButtonControl));
		posSize.height *= labelPosY;
	}

	LFButtonControl::~LFButtonControl()
	{ }

	void LFButtonControl::AttachLabelChild(LFLayer *layer)
	{
		LFString labelName(labelData.labelName);
		labelName += "Label";
		labelData.labelName = labelName.ToChar();

		labelData.posX += posSize.width / 2 - (labelData.text.Length() * fontMaterial.textureWidth) / 2 + ((labelData.text.Length() - labelData.text.LengthNoSpace()) * fontMaterial.textureWidth) / 4;
		labelData.posY += (fontMaterial.textureHeight / 4) * labelPosY;
		LFLabelControl *label = LFNew<LFLabelControl>(AT, fontMaterial, labelData);
		this->label = label;

		label->AttachChildren(layer);
		componentList.Add(label); //for hierarchy
		layer->Add(label); //for render/update
	}

	void LFButtonControl::AttachChildren(LFLayer *layer)
	{
		LFString tuchedName;
		tuchedName += name;
		tuchedName += "touched";
		AttachSpriteChildren(tuchedName.ToChar(), layer, LFString(touchedControlMaterial.textureName), LFRectangle(labelData.posX, labelData.posY, touchedControlMaterial.textureWidth, touchedControlMaterial.textureHeight),
			LFRectangle(touchedControlMaterial.atlasPosSize.position, LFVector2D(touchedControlMaterial.atlasWidth, touchedControlMaterial.atlasHeight)),
			LFVector2D(touchedControlMaterial.atlasPosSize.width, touchedControlMaterial.atlasPosSize.height), LFControl::SIS_TOUCHED);

		LFString nonTuchedName;
		nonTuchedName += name;
		nonTuchedName += "nonTouched";
		AttachSpriteChildren(nonTuchedName.ToChar(), layer, LFString(nonTouchedControlMaterial.textureName), LFRectangle(labelData.posX, labelData.posY, nonTouchedControlMaterial.textureWidth, nonTouchedControlMaterial.textureHeight),
			LFRectangle(nonTouchedControlMaterial.atlasPosSize.position, LFVector2D(nonTouchedControlMaterial.atlasWidth, nonTouchedControlMaterial.atlasHeight)),
			LFVector2D(nonTouchedControlMaterial.atlasPosSize.width, nonTouchedControlMaterial.atlasPosSize.height), LFControl::SIS_NONTOUCHED);

		AttachLabelChild(layer);

		SetRelativeScale(posSize); //for touch scale
	}

	void LFButtonControl::OnControlPress(const LFPointerEventArgs &args)
	{ 
		SetSpriteItems(false, true);
	}

	void LFButtonControl::OnControlRelease(const LFPointerEventArgs &args)
	{ 
		SetSpriteItems(true, false);
	}

	void LFButtonControl::OnControlPressed(const LFPointerEventArgs &args)
	{  }

	void LFButtonControl::IsVisible(bool isVisible)
	{
		LFGameCompositComponent::SetIsVisible(isVisible);

		if (isVisible)
			SetSpriteItems(true, false);
	}
}}}}
