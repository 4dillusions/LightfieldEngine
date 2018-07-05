/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFMessageBoxControl.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\..\Core\Math\LFRectangle.h"
#include "..\..\..\..\Core\Math\LFVector2D.h"
#include "..\..\..\..\Core\Math\LFMath.h"
#include "..\..\..\..\Engine\Common\LFSystemInfo.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFMessageBoxControlLua.h"
#include "..\..\..\Script\LFLuaType.h"

using namespace LFCore::Common;
using namespace LFEngine::Common;
using namespace LFEngine::Input;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Script;
using namespace LFCore::Math;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	LFMessageBoxControl::LFMessageBoxControl(const LFFontMaterial &fontMaterial, const LFControlMaterial &messageBoxMaterial, 
		const LFControlMaterial &nonTouchedButtonMaterial, LFControlMaterial &touchedButtonMaterial, const LFMessageBoxData &messageBoxData) :
		LFControl(LFString(messageBoxData.messageBoxName),
			LFRectangle(0, 0, LFSystemInfo::DefaultWindowWidth(), LFSystemInfo::DefaultWindowHeight()),
			false),
		lblMessageLine1(nullptr), lblMessageLine2(nullptr), lblMessageLine3(nullptr), btnYes(nullptr), btnOk(nullptr), btnNo(nullptr),
		fontMaterial(fontMaterial), messageBoxMaterial(messageBoxMaterial), 
		nonTouchedButtonMaterial(nonTouchedButtonMaterial), touchedButtonMaterial(touchedButtonMaterial), messageBoxData(messageBoxData)
	{
		this->messageBoxMaterial.textureWidth *= 1.5;
		this->messageBoxMaterial.textureHeight *= 1.5;
		this->isPressable = false;
		controlType = LFLuaType().SetObject(this, LFMessageBoxControlName, sizeof(LFButtonControl));
	}

	LFMessageBoxControl::~LFMessageBoxControl()
	{ }

	void LFMessageBoxControl::AttachLabelChild(LFLayer *layer, const LFVector2D &mboxPos, int index, int maxLabelTextCount, int maxLabelSpaceCount)
	{
		LFString labelName(messageBoxData.messageBoxName);
		LFLabelData labelData;
		int posX = 20 + mboxPos.x + (fontMaterial.textureWidth * maxLabelTextCount / 2) + messageBoxMaterial.textureWidth / 2 - (fontMaterial.textureWidth * maxLabelSpaceCount / 4);
		int posY = 70 + mboxPos.y + (((index - 1) * fontMaterial.textureHeight / 2)) + LFSystemInfo::WindowHeightRelativeScale();

		switch (index)
		{
			case 1:
				labelName += "lblOne";
				labelData.labelName = labelName.ToChar();
				labelData.text = messageBoxData.messageLine1;
				break;

			case 2:
				labelName += "lblTwo";
				labelData.labelName = labelName.ToChar();
				labelData.text = messageBoxData.messageLine2;
				break;

			case 3:
				labelName += "lblThree";
				labelData.labelName = labelName.ToChar();
				labelData.text = messageBoxData.messageLine3;
				break;
		}
		
		labelData.posX = posX;
		labelData.posY = posY;
		LFLabelControl *label = LFNew<LFLabelControl>(AT, fontMaterial, labelData);

		switch (index)
		{
			case 1: lblMessageLine1 = label; break;
			case 2: lblMessageLine2 = label; break;
			case 3: lblMessageLine3 = label; break;
		}

		label->AttachChildren(layer);
		componentList.Add(label); //for hierarchy
		layer->Add(label); //for render/update
	}

	void LFMessageBoxControl::AttachButtonChild(LFLayer *layer, const LFVector2D &mboxPos, int index)
	{
		LFString buttonName(messageBoxData.messageBoxName);
		LFLabelData labelData;
		int posX = (185 + mboxPos.x + (95 * (index - 1))) + LFSystemInfo::WindowWidthRelativeScale();
		int posY = 335 + LFSystemInfo::WindowHeightRelativeScale();

		switch (index)
		{
		case 1:
			buttonName += "Yes";
			labelData.labelName = buttonName.ToChar();
			labelData.text = LFString("YES");
			break;

		case 2:
			buttonName += "Ok";
			labelData.labelName = buttonName.ToChar();
			labelData.text = LFString("OK");
			break;

		case 3:
			buttonName += "No";
			labelData.labelName = buttonName.ToChar();
			labelData.text = LFString("NO");
			break;
		}

		labelData.posX = posX;
		labelData.posY = posY;
		LFFontMaterial fontMat = fontMaterial;
		fontMat.textureWidth /= 1.2;
		//fontMat.textureHeight /= 1.2;
		LFButtonControl *button = LFNew<LFButtonControl>(AT, fontMat, nonTouchedButtonMaterial, touchedButtonMaterial, labelData);

		switch (index)
		{
			case 1: btnYes = button; break;
			case 2: btnOk = button; break;
			case 3: btnNo = button; break;
		}

		button->AttachChildren(layer);
		componentList.Add(button); //for hierarchy
		layer->Add(button); //for render/update
	}

	void LFMessageBoxControl::AttachChildren(LFLayer *layer)
	{
		LFVector2D mboxPos(LFSystemInfo::DefaultWindowWidth() / 2 - (messageBoxMaterial.textureWidth * messageBoxMaterial.atlasPosSize.width) / 2,
						   LFSystemInfo::DefaultWindowHeight() / 2 - (messageBoxMaterial.textureHeight * messageBoxMaterial.atlasPosSize.height) / 2);

		LFString mboxName;
		mboxName += name;
		mboxName += "mbox";
		AttachSpriteChildren(mboxName.ToChar(), layer, LFString(messageBoxMaterial.textureName), 
			LFRectangle(mboxPos.x, mboxPos.y, messageBoxMaterial.textureWidth, messageBoxMaterial.textureHeight),
			LFRectangle(messageBoxMaterial.atlasPosSize.position, LFVector2D(messageBoxMaterial.atlasWidth, messageBoxMaterial.atlasHeight)),
			LFVector2D(messageBoxMaterial.atlasPosSize.width, messageBoxMaterial.atlasPosSize.height), LFControl::SIS_NONTOUCHED);
		
		int maxLabelTextCount = LFMath::Max3(messageBoxData.messageLine1.Length(), messageBoxData.messageLine2.Length(), messageBoxData.messageLine3.Length());
		int maxLabelSpaceCount = LFMath::Max3(messageBoxData.messageLine1.LengthNoSpace(), messageBoxData.messageLine2.LengthNoSpace(), messageBoxData.messageLine3.LengthNoSpace());
		maxLabelSpaceCount = maxLabelTextCount - maxLabelSpaceCount;
		if (!messageBoxData.messageLine1.IsEmpty())
			AttachLabelChild(layer, mboxPos, 1, maxLabelTextCount, maxLabelSpaceCount); //line1

		if (!messageBoxData.messageLine2.IsEmpty())
			AttachLabelChild(layer, mboxPos, 2, maxLabelTextCount, maxLabelSpaceCount); //line2

		if (!messageBoxData.messageLine3.IsEmpty())
			AttachLabelChild(layer, mboxPos, 3, maxLabelTextCount, maxLabelSpaceCount); //line3

		if (messageBoxData.messageType == LFString("info"))
		{
			AttachButtonChild(layer, mboxPos, 2); //ok
		}

		if (messageBoxData.messageType == LFString("question"))
		{
			AttachButtonChild(layer, mboxPos, 1); //yes
			AttachButtonChild(layer, mboxPos, 3); //no
		}

		SetRelativeScale(posSize); //for touch scale
	}

	void LFMessageBoxControl::IsVisible(bool isVisible)
	{
		LFGameCompositComponent::SetIsVisible(isVisible);

		if (isVisible)
			SetSpriteItems(true, false);
	}
}}}}
