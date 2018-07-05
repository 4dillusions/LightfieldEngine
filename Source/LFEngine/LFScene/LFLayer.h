/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore\LFCommon\LFGameCompositeComponent.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFControl;
}}}

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	class LFShaderEffect;
}}}

namespace LF3Engine { namespace LFEngine { namespace LFScene
{
	class LFScreen;

	class LFLayer final : public LFCore::LFCommon::LFGameCompositeComponent
	{
		LFScreen *screen;
		LFRender::LFShaderEffect *shader = nullptr; //one shader per layer

	public:
		explicit LFLayer(const LFCore::LFCommon::LFString &name);
		~LFLayer();

		LFScreen *GetScreen() const;
		void SetScreen(LFScreen *screen);

		LFGUI::LFControl *FindControl(const LFCore::LFCommon::LFString &name);

		//LFGameCompositeComponent functions
		void Add(LFGameComponent *control) override;
		void Remove(LFGameComponent *control) override;
		void Update(double deltaTime) override;
	};
}}}
