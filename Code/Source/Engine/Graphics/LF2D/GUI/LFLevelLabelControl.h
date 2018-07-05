/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLabelControl.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	class LFNumberLabelControl;

	class LFENGINE_LIBRARY LFLevelLabelControl : public LFEngine::GameEngine::LFControl
	{
	private:
		LFNumberLabelControl *numberLabel;

		void AttachNumberLabelChild(LFEngine::GameEngine::LFLayer *layer);

	protected:
		LFEngine::GameEngine::LFFontMaterial fontMaterial;
		LFEngine::GameEngine::LFControlMaterial controlMaterial;
		LFLabelData labelData;

	public:
		LFLevelLabelControl(const LFEngine::GameEngine::LFFontMaterial &fontMaterial, const LFEngine::GameEngine::LFControlMaterial &controlMaterial, const LFLabelData &labelData);
		virtual ~LFLevelLabelControl();

		int Value();
		void Value(int value);

		//LFControl
		virtual void AttachChildren(LFEngine::GameEngine::LFLayer *layer);

		virtual void OnControlPress(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlRelease(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlPressed(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnMouseMove(const LFEngine::Input::LFPointerMoveEventArgs &args) { }
	};
}}}}
