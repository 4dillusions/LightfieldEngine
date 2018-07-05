/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore\LFCommon\LFEvent.h"
#include "..\LFGameEngine\LF3GameEngine.h"
#include "..\LFCore\LFCommon\LFTimer.h"

namespace LF3Engine { namespace LFEngine { namespace LFScene
{
	class LFSceneGraph;
}}}

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	class LFIRenderSystem;

	/**
		@brief
		Render window for rendering OpenGL or Direct3D
	*/
	class LFRenderWindow
	{
	protected:
		LFIRenderSystem *render;
		LFCore::LFCommon::LFTimer deltaTimer;
		LFScene::LFSceneGraph *sceneGraph;
		bool isRendering, isPaused;

	public:
		LFCore::LFCommon::LFEvent<LFGameEngine::AppInitTerminateEventArgs> OnAppInitTerminate;

		LFRenderWindow(const LFRenderWindow &) = delete;
		LFRenderWindow(LFRenderWindow &&) = delete;
		LFRenderWindow &operator=(const LFRenderWindow &) = delete;
		LFRenderWindow &operator=(LFRenderWindow &&) = delete;

		LFRenderWindow();
		virtual ~LFRenderWindow();

		void InitSceneGraph();
		virtual void InitWindow() = 0;
		virtual void Update() = 0;
		virtual void Foreground();
		virtual void Background();
		virtual void AppInit();
		virtual void AppTerminate();
		virtual void CloseWindow() = 0;

        virtual void OnAppPauseResume(const LFGameEngine::AppPauseResumeEventArgs &appPauseResumeEventArgs) = 0;
	};
}}}
