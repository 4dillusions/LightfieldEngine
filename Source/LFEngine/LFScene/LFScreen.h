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

namespace LF3Engine { namespace LFEngine { namespace LFScene
{
	class LFLayer;
	
	class LFScreen final : public LFCore::LFCommon::LFGameCompositeComponent
	{
	public:
		explicit LFScreen(const LFCore::LFCommon::LFString &name);
		~LFScreen();

		bool GetIsActive() const;
		void SetActive();
		LFLayer *FindLayer(const LFCore::LFCommon::LFString &name);
		void AddBackground(const LFCore::LFCommon::LFString &controlName, const LFCore::LFCommon::LFString &imageName);
		void AddGUIObject(const LFCore::LFCommon::LFString &layerName, LFGUI::LFControl *control);

		//LFGameCompositeComponent functions
		void Add(LFGameComponent *layer) override;
		void Remove(LFGameComponent *layer) override;
	};
}}}
