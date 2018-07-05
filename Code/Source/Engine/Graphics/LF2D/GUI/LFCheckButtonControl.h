/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLabelControl.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	class LFENGINE_LIBRARY LFCheckButtonControl : public LFEngine::GameEngine::LFControl
	{
	private:
		bool isChecked;

	protected:
		LFEngine::GameEngine::LFControlMaterial unCheckedControlMaterial, checkedControlMaterial, unCheckedTouchedControlMaterial, checkedTouchedControlMaterial;
		LFLabelData labelData;

	public:
		LFCheckButtonControl(const LFEngine::GameEngine::LFControlMaterial &unCheckedControlMaterial, GameEngine::LFControlMaterial &checkedControlMaterial,
			const LFEngine::GameEngine::LFControlMaterial &unCheckedTouchedControlMaterial, GameEngine::LFControlMaterial &checkedTouchedControlMaterial,
			const LFLabelData &labelData, bool isChecked);
		virtual ~LFCheckButtonControl();

		bool IsChecked() { return isChecked; }
		void IsChecked(bool isChecked);

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
