/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\Common\LFGameCompositComponent.h"

namespace LFEngine { namespace GameEngine
{
	class LFScreen;

	class LFENGINE_LIBRARY LFSceneGraph : public LFCore::Common::LFGameCompositComponent
	{
	private:
		LFScreen *activeScreen;
		static LFSceneGraph *instance;

	public:
		LFSceneGraph();
		virtual ~LFSceneGraph();

		static void CreateInstance();
		static void ReleaseInstance();
		static LFSceneGraph *Instance() { return instance; }

		bool IsActiveScreen(const LFCore::Common::LFString &name);
		LFScreen const *ActiveScreen() const { return activeScreen; }
		void ActiveScreen(LFScreen *screen) { activeScreen = screen; }
		void ActiveScreen(const LFCore::Common::LFString &name);

		LFScreen *FindScreen(const LFCore::Common::LFString &name);

		//LFGameCompositComponent
		void Add(LFGameComponent *lFScreen);
		void Remove(LFGameComponent *lFScreen);

		//LFGameComponent
		virtual void Update(double deltaTime);
	};
}}
