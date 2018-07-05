#pragma once

#include "..\\Core\\SMGameCompositComponent.h"
#include "SMScreen.h"

using namespace SMEngine::Core;

namespace  SMEngine { namespace Engine
{
	class SMSceneGraph : public SMGameCompositComponent
	{
	private:
		SMScreen *mainScreen;
		static SMSceneGraph *instance;

		SMSceneGraph();
		override ~SMSceneGraph();

	public:
		static void CreateInstance();
		static void ReleaseInstance();
		static SMSceneGraph *Instance() { return instance; }

		SMScreen const *MainScreen() const { return mainScreen; }
		void MainScreen(SMScreen *screen) { mainScreen = screen; }
		void MainScreen(const SMString &name);

		override void Add(SMGameComponent *gameComponent); //Screen-eket lehet hozzáadni
		override void Update(double deltaTime); //csak a mainScreen-t frissíti
	};
};};
