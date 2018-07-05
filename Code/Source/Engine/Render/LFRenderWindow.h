/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"
#include "..\..\Core\\Math\LFColor.h"
#include "..\..\Core\\Common\LFTimer.h"
#include "..\..\Core\\Common\LFEventArgs.h"
#include "..\GameEngine\LFGameEngine.h"

namespace LFEngine { namespace GameEngine
{
	class LFSceneGraph;
}}

namespace LFEngine { namespace Render
{
	class LFRender;

	class LFENGINE_LIBRARY LFRenderWindow :
		public GameEngine::LFIPauseResumeEventHandler
	{ 
	protected:
		static LFRenderWindow *instance;

		LFRender *render;
		LFCore::Common::LFTimer deltaTimer;
		LFCore::Math::LFColor backgroundColor;
		LFEngine::GameEngine::LFSceneGraph *sceneGraph;
		GameEngine::LFAppInitTerminateEventArgs appInitTerminateEventArgs;
		bool isRendering, isPaused;

	public:
		LFRenderWindow();
		virtual ~LFRenderWindow();

		static LFRenderWindow *Instance() { return instance; }

		LFCore::Common::LFEventArgs<GameEngine::LFIAppInitTerminateEventHandler, GameEngine::LFAppInitTerminateEventArgs> AppInitTerminateEvent;
		
		void InitSceneGraph();
		void WriteScreenData();
		virtual void InitWindow() = 0;
		virtual void Update() = 0;
		virtual void Foreground();
		virtual void Background();
		virtual void AppInit();
		virtual void AppTerminate();
		virtual void CloseWindow() = 0;

		virtual void OnPauseResumeChanged(const GameEngine::LFPauseResumeEventArgs &args) = 0;
	};
}}
