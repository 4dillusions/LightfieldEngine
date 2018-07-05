/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFRenderWindow.h"
#include "..\..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"

using namespace std;
using namespace placeholders;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFGameEngine;
using namespace LF3Engine::LFEngine::LFScene;

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	LFRenderWindow::LFRenderWindow() : render(nullptr), sceneGraph(nullptr), isRendering(true), isPaused(false)
	{
		LFIoc<LFLogger>::Get().WriteOutput("Create RenderWindow");
        LF3GameEngine::Instance()->OnAppPauseResume += bind(&LFRenderWindow::OnAppPauseResume, this, _1);

		render = LFIoc<LFIRenderSystem *>::Get();
	}

	LFRenderWindow::~LFRenderWindow()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Release RenderWindow");
		LF3GameEngine::Instance()->OnAppPauseResume -= bind(&LFRenderWindow::OnAppPauseResume, this, _1);
	}

	void LFRenderWindow::InitSceneGraph()
	{
		sceneGraph = LFIoc<LFSceneGraph *>::Get();
	}

	void LFRenderWindow::Foreground()
	{
		LFIoc<LFLogger>::Get().WriteOutput("RenderWindow foreground");
		LF3GameEngine::Instance()->Resume();
		deltaTimer.Reset();
	}

	void LFRenderWindow::Background()
	{
		LFIoc<LFLogger>::Get().WriteOutput("RenderWindow background");
		LF3GameEngine::Instance()->Pause();
	}

	void LFRenderWindow::AppInit()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Initialize application");
		OnAppInitTerminate({ AppInitTerminateEventArgs::AppLifeState::Init });
	}

	void LFRenderWindow::AppTerminate()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Terminate application");
		OnAppInitTerminate({ AppInitTerminateEventArgs::AppLifeState::Terminate });
	}
}}}
