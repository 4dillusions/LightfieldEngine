/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFRenderWindow.h"
#include "LFRender.h"
#include "..\Common\LFSystemInfo.h"
#include "..\..\Core\\IO\LFLogger.h"
#include "..\GameEngine\LFSceneGraph.h"
#include "..\GameEngine\LFGameEngine.h"
#include "_Win32_\LFRenderWindowWin32.h"

using namespace LFCore::Common;
using namespace LFCore::IO;
using namespace LFCore::Math;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Common;

namespace LFEngine { namespace Render
{
	LFRenderWindow *LFRenderWindow::instance = nullptr;

	LFRenderWindow::LFRenderWindow() : 
		backgroundColor(LFColor(51, 51, 51)),
		AppInitTerminateEvent(&LFIAppInitTerminateEventHandler::OnInitTerminateChanged),
		isRendering(true), isPaused(false)
	{ 
		LFLogger::Instance().WriteOutput("Create RenderWindow");
		render = LFRender::Instance();
	}

	LFRenderWindow::~LFRenderWindow()
	{ 
		LFLogger::Instance().WriteOutput("Release RenderWindow");
	}

	void LFRenderWindow::InitSceneGraph()
	{
		sceneGraph = LFSceneGraph::Instance();
	}

	void LFRenderWindow::WriteScreenData()
	{
		LFString log;

		log += "Screen size: ";
		log += LFSystemInfo::ScreenWidth();
		log += " ";
		log += LFSystemInfo::ScreenHeight();
		log += " ";
		log += "Window size: ";
		log += LFSystemInfo::WindowWidth();
		log += " ";
		log += LFSystemInfo::WindowHeight();

		LFLogger::Instance().WriteOutput(log);
	}

	void LFRenderWindow::Foreground()
	{
		LFLogger::Instance().WriteOutput("RenderWindow foreground");
		LFGameEngine::Instance()->Resume();
		deltaTimer.Reset();
	}

	void LFRenderWindow::Background()
	{
		LFLogger::Instance().WriteOutput("RenderWindow background");
		LFGameEngine::Instance()->Pause();
	}

	void LFRenderWindow::AppInit()
	{
		WriteScreenData();

		LFLogger::Instance().WriteOutput("Initialize application");

		appInitTerminateEventArgs.applicationState = LFAppInitTerminateEventArgs::INITIALIZING;
		AppInitTerminateEvent(appInitTerminateEventArgs);
	}

	void LFRenderWindow::AppTerminate()
	{
		LFLogger::Instance().WriteOutput("Terminate application");

		appInitTerminateEventArgs.applicationState = LFAppInitTerminateEventArgs::TERMINATE;
		AppInitTerminateEvent(appInitTerminateEventArgs);
	}
}}
