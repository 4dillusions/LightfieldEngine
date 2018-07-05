/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLabelControl.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	class LFENGINE_LIBRARY LFButtonControl : public LFEngine::GameEngine::LFControl
	{
	private:
		LFLabelControl *label;
		void AttachLabelChild(LFEngine::GameEngine::LFLayer *layer);

	protected:
		LFEngine::GameEngine::LFFontMaterial fontMaterial;
		LFEngine::GameEngine::LFControlMaterial nonTouchedControlMaterial, touchedControlMaterial;
		LFLabelData labelData;
		float labelPosY; //label center y position of 100% or 50% size button 1.0 = 100%

	public:
		LFButtonControl(const LFEngine::GameEngine::LFFontMaterial &fontMaterial, const LFEngine::GameEngine::LFControlMaterial &nonTouchedControlMaterial,
			GameEngine::LFControlMaterial &touchedControlMaterial, const LFLabelData &labelData, float labelPosY = 1.0f);
		virtual ~LFButtonControl();

		//LFControl
		virtual void AttachChildren(LFEngine::GameEngine::LFLayer *layer);

		virtual void OnControlPress(const LFEngine::Input::LFPointerEventArgs &args);
		virtual void OnControlRelease(const LFEngine::Input::LFPointerEventArgs &args);
		virtual void OnControlPressed(const LFEngine::Input::LFPointerEventArgs &args);
		virtual void OnMouseMove(const LFEngine::Input::LFPointerMoveEventArgs &args) { }

		//LFGameCompositComponent
		virtual void IsVisible(bool isVisible);
	};
}}}}
