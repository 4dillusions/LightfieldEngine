/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore\LFCommon\LFGameCompositeComponent.h"

namespace LF3Engine { namespace LFEngine { namespace LFScene
{
	class LFScreen;

	class LFSceneGraph final : public LFCore::LFCommon::LFGameCompositeComponent
	{
		LFScreen *activeScreen;
		
	public:
		LFSceneGraph();
		~LFSceneGraph();

		bool GetIsActiveScreen(const LFCore::LFCommon::LFString &name) const;
		LFScreen const *GetActiveScreen() const;
		void SetActiveScreen(LFScreen *screen);
		void SetActiveScreen(const LFCore::LFCommon::LFString &name);

		LFScreen *FindScreen(const LFCore::LFCommon::LFString &name);

		//LFGameCompositeComponent functions
		void Add(LFGameComponent *screen) override;
		void Remove(LFGameComponent *screen) override;

		//LFGameComponent functions
		void Update(double deltaTime) override;
	};
}}}
