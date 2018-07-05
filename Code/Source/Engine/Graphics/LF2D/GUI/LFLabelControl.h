/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\..\..\GameEngine\LFControl.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI
{
	class LFENGINE_LIBRARY LFLabelData
	{
	public:
		const char *labelName;
		int posX;
		int posY;
		LFCore::Common::LFString text;
		
		int digits; //for number label
	};

	class LFENGINE_LIBRARY LFLabelControl : public LFEngine::GameEngine::LFControl
	{
	protected:
		LFEngine::GameEngine::LFFontMaterial fontMaterial;
		LFLabelData labelData;

	public:
		LFLabelControl(const LFEngine::GameEngine::LFFontMaterial &fontMaterial, const LFLabelData &labelData);
		virtual ~LFLabelControl();

		//LFControl
		virtual void AttachChildren(LFEngine::GameEngine::LFLayer *layer);

		virtual void OnControlPress(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlRelease(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnControlPressed(const LFEngine::Input::LFPointerEventArgs &args) { }
		virtual void OnMouseMove(const LFEngine::Input::LFPointerMoveEventArgs &args) { }
	};
}}}}
