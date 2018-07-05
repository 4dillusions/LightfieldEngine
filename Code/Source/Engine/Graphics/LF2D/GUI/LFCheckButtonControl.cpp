/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFCheckButtonControl.h"
#include "LFSpriteFont.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\..\Core\\Math\LFVector2D.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFCheckButtonControlLua.h"
#include "..\..\..\Script\LFLuaType.h"
#include "..\..\..\Script\LFScriptSystem.h"

using namespace LFCore::Common;
using namespace LFEngine::Input;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Script;
using namespace LFCore::Math;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFCheckButtonControl::LFCheckButtonControl(const LFControlMaterial &unCheckedControlMaterial, LFControlMaterial &checkedControlMaterial,
		const LFControlMaterial &unCheckedTouchedControlMaterial, LFControlMaterial &checkedTouchedControlMaterial,
		const LFLabelData &labelData, bool isChecked) :
		LFControl(LFString(labelData.labelName), 
		LFRectangle(LFVector2D(labelData.posX, labelData.posY), LFVector2D(unCheckedControlMaterial.textureWidth * unCheckedControlMaterial.atlasPosSize.width, unCheckedControlMaterial.textureHeight * unCheckedControlMaterial.atlasPosSize.height)),
		false),
		unCheckedControlMaterial(unCheckedControlMaterial), checkedControlMaterial(checkedControlMaterial),
		unCheckedTouchedControlMaterial(unCheckedTouchedControlMaterial), checkedTouchedControlMaterial(checkedTouchedControlMaterial),
		labelData(labelData),
		isChecked(isChecked)
	{
		controlType = LFLuaType().SetObject(this, LFCheckButtonControlName, sizeof(LFCheckButtonControl));
	}

	LFCheckButtonControl::~LFCheckButtonControl()
	{ }

	void LFCheckButtonControl::IsChecked(bool isChecked)
	{ 
		this->isChecked = isChecked; 
		SetSpriteItems(true, false, isChecked);
	}

	void LFCheckButtonControl::AttachChildren(LFLayer *layer)
	{		
		LFString unCheckedNonTuchedName;
		unCheckedNonTuchedName += name;
		unCheckedNonTuchedName += "unCheckedNonTouched";
		AttachSpriteChildren(unCheckedNonTuchedName.ToChar(), layer, LFString(unCheckedControlMaterial.textureName), LFRectangle(labelData.posX, labelData.posY, unCheckedControlMaterial.textureWidth, unCheckedControlMaterial.textureHeight),
			LFRectangle(unCheckedControlMaterial.atlasPosSize.position, LFVector2D(unCheckedControlMaterial.atlasWidth, unCheckedControlMaterial.atlasHeight)),
			LFVector2D(unCheckedControlMaterial.atlasPosSize.width, unCheckedControlMaterial.atlasPosSize.height), LFControl::SIS_NONTOUCHED_UNCHECKED);

		LFString checkedNonTouchedName;
		checkedNonTouchedName += name;
		checkedNonTouchedName += "checkedNonTouched";
		AttachSpriteChildren(checkedNonTouchedName.ToChar(), layer, LFString(checkedControlMaterial.textureName), LFRectangle(labelData.posX, labelData.posY, checkedControlMaterial.textureWidth, checkedControlMaterial.textureHeight),
			LFRectangle(checkedControlMaterial.atlasPosSize.position, LFVector2D(checkedControlMaterial.atlasWidth, checkedControlMaterial.atlasHeight)),
			LFVector2D(checkedControlMaterial.atlasPosSize.width, checkedControlMaterial.atlasPosSize.height), LFControl::SIS_NONTOUCHED);

		LFString uncheckedTouchedName;
		uncheckedTouchedName += name;
		uncheckedTouchedName += "uncheckedTouched";
		AttachSpriteChildren(uncheckedTouchedName.ToChar(), layer, LFString(unCheckedTouchedControlMaterial.textureName), LFRectangle(labelData.posX, labelData.posY, unCheckedTouchedControlMaterial.textureWidth, unCheckedTouchedControlMaterial.textureHeight),
			LFRectangle(unCheckedTouchedControlMaterial.atlasPosSize.position, LFVector2D(unCheckedTouchedControlMaterial.atlasWidth, unCheckedTouchedControlMaterial.atlasHeight)),
			LFVector2D(unCheckedTouchedControlMaterial.atlasPosSize.width, unCheckedTouchedControlMaterial.atlasPosSize.height), LFControl::SIS_TOUCHED_UNCHECKED);

		LFString checkedTouchedName;
		checkedTouchedName += name;
		checkedTouchedName += "checkedTouched";
		AttachSpriteChildren(checkedTouchedName.ToChar(), layer, LFString(checkedTouchedControlMaterial.textureName), LFRectangle(labelData.posX, labelData.posY, checkedTouchedControlMaterial.textureWidth, checkedTouchedControlMaterial.textureHeight),
			LFRectangle(checkedTouchedControlMaterial.atlasPosSize.position, LFVector2D(checkedTouchedControlMaterial.atlasWidth, checkedTouchedControlMaterial.atlasHeight)),
			LFVector2D(checkedTouchedControlMaterial.atlasPosSize.width, checkedTouchedControlMaterial.atlasPosSize.height), LFControl::SIS_TOUCHED);

		SetRelativeScale(posSize); //for touch scale
		SetSpriteItems(true, false, isChecked);
	}

	void LFCheckButtonControl::OnControlPress(const LFPointerEventArgs &args)
	{ 
		SetSpriteItems(false, true, isChecked);
	}

	void LFCheckButtonControl::OnControlRelease(const LFPointerEventArgs &args)
	{ 
		SetSpriteItems(true, false, isChecked);
	}

	void LFCheckButtonControl::OnControlPressed(const LFPointerEventArgs &args)
	{  
		isChecked = !isChecked;
		SetSpriteItems(true, false, isChecked);
		LFScriptSystem::Instance()->CallFunction(controlType, LFCheckButtonControlOnCheckChangedName, controlType);
	}

	void LFCheckButtonControl::IsVisible(bool isVisible)
	{
		LFGameCompositComponent::SetIsVisible(isVisible);

		if (isVisible)
			SetSpriteItems(true, false, isChecked);
	}
}}}}
