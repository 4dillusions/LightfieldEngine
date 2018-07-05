/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLabelControl.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	class LFENGINE_LIBRARY LFSliderControl : public LFEngine::GameEngine::LFControl
	{
	private:
		int value; //1-100 percent
		int potmeterHalfSize;
		int potmeterPositionX;

		void SetPotmeterFromValue(int value);
		void SetPotmeterFromPointer(int posX);
		void SetValueFromPotmeter(int posX);

	protected:
		LFEngine::GameEngine::LFControlMaterial potmeterMaterial, potmeterTouchedControlMaterial;
		LFLabelData labelData;

	public:
		LFSliderControl(const LFEngine::GameEngine::LFControlMaterial &potmeterMaterial, GameEngine::LFControlMaterial &potmeterTouchedControlMaterial,
			const LFLabelData &labelData, int width, int value);
		virtual ~LFSliderControl();

		int Value() { return value; }
		void Value(int value);

		//LFControl
		virtual void AttachChildren(LFEngine::GameEngine::LFLayer *layer);

		virtual void OnControlPress(const LFEngine::Input::LFPointerEventArgs &args);
		virtual void OnControlRelease(const LFEngine::Input::LFPointerEventArgs &args);
		virtual void OnControlPressed(const LFEngine::Input::LFPointerEventArgs &args);
		virtual void OnMouseMove(const LFEngine::Input::LFPointerMoveEventArgs &args);

		//LFGameCompositComponent
		virtual void IsVisible(bool isVisible);
	};
}}}}
