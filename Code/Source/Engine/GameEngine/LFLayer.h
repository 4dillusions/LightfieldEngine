/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Common\LFGameCompositComponent.h"

namespace LFEngine { namespace Graphics { namespace LF2D
{
	class LFSprite;
}}}

namespace LFEngine { namespace GameEngine
{
	class LF2DObject;
	class LFControl;
	class LFScreen;

	class LFENGINE_LIBRARY LFLayer : public LFCore::Common::LFGameCompositComponent
	{
	private:
		LFScreen *screen;

		void AddSprite(LFEngine::Graphics::LF2D::LFSprite *sprite);
		void AddControl(LFControl *control);

	public:
		LFLayer(const LFCore::Common::LFString &name);
		virtual ~LFLayer();

		LFScreen *Screen() const { return screen; }
		void Screen(LFScreen *screen) { this->screen = screen; }

		LF2DObject *Find2DObject(const LFCore::Common::LFString &name);

		//LFGameCompositComponent
		void Add(LFGameComponent *lF2DObject);
		void Remove(LFGameComponent *lF2DObject);

		//LFGameComponent
		virtual void SetIsVisible(bool isVisible);
	};
}}
