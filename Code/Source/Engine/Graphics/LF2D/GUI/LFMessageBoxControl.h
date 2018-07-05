/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFButtonControl.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	class LFENGINE_LIBRARY LFMessageBoxData
	{
	public:
		const char *messageBoxName;
		LFCore::Common::LFString messageLine1, messageLine2, messageLine3, messageType;
	};

	class LFENGINE_LIBRARY LFMessageBoxControl : public LFEngine::GameEngine::LFControl
	{
	private:
		LFLabelControl *lblMessageLine1, *lblMessageLine2, *lblMessageLine3;
		LFButtonControl *btnYes, *btnOk, *btnNo;
		void AttachLabelChild(LFEngine::GameEngine::LFLayer *layer, const LFCore::Math::LFVector2D &mboxPos, int index, int maxLabelTextCount, int maxLabelSpaceCount);
		void AttachButtonChild(LFEngine::GameEngine::LFLayer *layer, const LFCore::Math::LFVector2D &mboxPos, int index);

	protected:
		LFEngine::GameEngine::LFFontMaterial fontMaterial;
		LFEngine::GameEngine::LFControlMaterial messageBoxMaterial, nonTouchedButtonMaterial, touchedButtonMaterial;
		LFMessageBoxData messageBoxData;

	public:
		LFMessageBoxControl(const LFEngine::GameEngine::LFFontMaterial &fontMaterial, const LFEngine::GameEngine::LFControlMaterial &messageBoxMaterial,
			const LFEngine::GameEngine::LFControlMaterial &nonTouchedButtonMaterial,
			GameEngine::LFControlMaterial &touchedButtonMaterial, const LFMessageBoxData &messageBoxData);
		virtual ~LFMessageBoxControl();

		//LFControl
		virtual void AttachChildren(LFEngine::GameEngine::LFLayer *layer);

		virtual void OnControlPress(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlRelease(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlPressed(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnMouseMove(const LFEngine::Input::LFPointerMoveEventArgs &args) { }

		//LFGameCompositComponent
		virtual void IsVisible(bool isVisible);
	};
}}}}
