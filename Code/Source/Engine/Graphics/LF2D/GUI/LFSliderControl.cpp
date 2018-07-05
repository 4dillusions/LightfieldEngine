/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSliderControl.h"
#include "LFSpriteFont.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\..\Core\\Math\LFVector2D.h"
#include "..\..\..\..\Core\\Math\LFMath.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFSliderControlLua.h"
#include "..\..\..\Script\LFLuaType.h"
#include "..\..\..\Script\LFScriptSystem.h"

using namespace LFCore::Common;
using namespace LFEngine::Input;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Script;
using namespace LFCore::Math;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFSliderControl::LFSliderControl(const LFControlMaterial &potmeterMaterial, LFControlMaterial &potmeterTouchedControlMaterial,
		const LFLabelData &labelData, int width, int value) :
		LFControl(LFString(labelData.labelName), 
		LFRectangle(LFVector2D(labelData.posX, labelData.posY), LFVector2D(width, potmeterMaterial.textureHeight * potmeterMaterial.atlasPosSize.height)),
		false, true),
		potmeterMaterial(potmeterMaterial), potmeterTouchedControlMaterial(potmeterTouchedControlMaterial),
		labelData(labelData),
		value(value)
	{
		controlType = LFLuaType().SetObject(this, LFSliderControlName, sizeof(LFSliderControl));
	}

	LFSliderControl::~LFSliderControl()
	{ }

	void LFSliderControl::SetPotmeterFromValue(int value)
	{
		int val = (int)LFMath::Clamp(value, 1, 100);
		float offset = (posSize.width * (val / 100.0f)) - potmeterHalfSize / 2;
		potmeterPositionX = (int)LFMath::Clamp(posSize.position.x + offset, posSize.position.x, (posSize.position.x + posSize.width) - potmeterHalfSize);
		SetSpriteChildrenPosition(LFVector2D(potmeterPositionX, posSize.position.y));
	}

	void LFSliderControl::SetPotmeterFromPointer(int posX)
	{
		potmeterPositionX = (int)LFMath::Clamp(posX - potmeterHalfSize / 2, posSize.position.x, (posSize.position.x + posSize.width) - potmeterHalfSize);
		SetSpriteChildrenPosition(LFVector2D(potmeterPositionX, posSize.position.y));
	}

	void LFSliderControl::SetValueFromPotmeter(int posX)
	{
		value = (int)LFMath::Clamp(((potmeterPositionX - posSize.position.x) / (posSize.width - potmeterHalfSize)) * 100, 1, 100);
	}

	void LFSliderControl::Value(int value)
	{ 
		this->value = (int)LFMath::Clamp(value, 1, 100);
		SetPotmeterFromValue(this->value);
	}

	void LFSliderControl::AttachChildren(LFLayer *layer)
	{		
		LFString potmeterName;
		potmeterName += name;
		potmeterName += "potmeter";
		AttachSpriteChildren(potmeterName.ToChar(), layer, LFString(potmeterMaterial.textureName), LFRectangle(labelData.posX, labelData.posY, potmeterMaterial.textureWidth, potmeterMaterial.textureHeight),
			LFRectangle(potmeterMaterial.atlasPosSize.position, LFVector2D(potmeterMaterial.atlasWidth, potmeterMaterial.atlasHeight)),
			LFVector2D(potmeterMaterial.atlasPosSize.width, potmeterMaterial.atlasPosSize.height), LFControl::SIS_NONTOUCHED);

		potmeterHalfSize = nonTouchedSpriteItems.GetFirst()->PosSize().width / 2;

		LFString potmeterTouchedName;
		potmeterTouchedName += name;
		potmeterTouchedName += "potmeterTouched";
		AttachSpriteChildren(potmeterTouchedName.ToChar(), layer, LFString(potmeterTouchedControlMaterial.textureName), LFRectangle(labelData.posX, labelData.posY, potmeterTouchedControlMaterial.textureWidth, potmeterTouchedControlMaterial.textureHeight),
			LFRectangle(potmeterTouchedControlMaterial.atlasPosSize.position, LFVector2D(potmeterTouchedControlMaterial.atlasWidth, potmeterTouchedControlMaterial.atlasHeight)),
			LFVector2D(potmeterTouchedControlMaterial.atlasPosSize.width, potmeterTouchedControlMaterial.atlasPosSize.height), LFControl::SIS_TOUCHED);

		SetRelativeScale(posSize); //for touch scale
		SetSpriteItems(true, false);
		SetPotmeterFromValue(value);
	}

	void LFSliderControl::OnControlPress(const LFPointerEventArgs &args)
	{ 
		SetSpriteItems(false, true);
		SetPotmeterFromPointer(args.x);
	}

	void LFSliderControl::OnControlRelease(const LFPointerEventArgs &args)
	{ 
		SetSpriteItems(true, false);
		SetValueFromPotmeter(args.x);
		LFScriptSystem::Instance()->CallFunction(controlType, LFSliderControlOnValueChangedName, controlType);
	}

	void LFSliderControl::OnControlPressed(const LFPointerEventArgs &args)
	{  }

	void LFSliderControl::OnMouseMove(const LFEngine::Input::LFPointerMoveEventArgs &args)
	{
		SetPotmeterFromPointer(args.x);
	}

	void LFSliderControl::IsVisible(bool isVisible)
	{
		LFGameCompositComponent::SetIsVisible(isVisible);

		if (isVisible)
			SetSpriteItems(true, false);
	}
}}}}
