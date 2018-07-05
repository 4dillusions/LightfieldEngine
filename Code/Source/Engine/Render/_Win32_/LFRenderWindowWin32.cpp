/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL

#include "LFRenderWindowWin32.h"
#include "..\LFRenderWindow.h"
#include "..\LFRender.h"
#include "..\_Win32_\LFRenderWindowWin32.h"
#include "..\..\Common\LFSystemInfo.h"
#include "..\..\GameEngine\LFSceneGraph.h"
#include "..\..\Script\LFScriptSystem.h"
#include "..\..\..\Core\IO\LFLogger.h"
#include "..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\Source\Depencies\Glfw\SDK\include\GLFW\glfw3.h"
#include "..\..\..\..\Source\Depencies\Glfw\SDK\include\GLFW\glfw3native.h"

using namespace LFCore::Common;
using namespace LFCore::IO;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Common;
using namespace LFEngine::Script;

namespace LFEngine { namespace Render
{
	void OnWindowFocusGlobal(GLFWwindow *window, int focused)
	{
		if (focused == GL_TRUE)
		{
			/*LFLogger::Instance().WriteOutput("Reload scripts. (only on win32)");
			LFScriptSystem::Instance()->LoadScript("Main");*/
			LFRenderWindowWin32::Instance()->Foreground();
		}
		else
			LFRenderWindowWin32::Instance()->Background();
	}

	void OnWindowCloseGlobal(GLFWwindow *window)
	{
		LFRenderWindowWin32::Instance()->CloseWindow();
	}

	LFRenderWindowWin32::LFRenderWindowWin32()
	{ }

	LFRenderWindowWin32::~LFRenderWindowWin32()
	{ }

	void LFRenderWindowWin32::CreateInstance()
	{
		if (instance == nullptr)
			instance = LFNew<LFRenderWindowWin32>(AT);
	}

	void LFRenderWindowWin32::ReleaseInstance()
	{
		if (instance != nullptr)
			LFDelete(instance);
	}
		
	HWND LFRenderWindowWin32::Hwnd()
	{
		return glfwGetWin32Window(window);
	}

	void LFRenderWindowWin32::InitWindow()
	{
		int windowWidth = LFSystemInfo::WindowWidth();
		int windowHeight = LFSystemInfo::WindowHeight();
		int screenWidth = LFSystemInfo::ScreenWidth();
		int screenHeight = LFSystemInfo::ScreenHeight();

		if(!glfwInit())
			CloseWindow();

		window = glfwCreateWindow(windowWidth, windowHeight, LFSystemInfo::GameName().ToChar(), nullptr, nullptr);
		if (!window)
			CloseWindow();

		glfwSetWindowPos(window, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);
		glfwMakeContextCurrent(window);

		glfwSetWindowFocusCallback(window, OnWindowFocusGlobal);
		glfwSetWindowCloseCallback(window, OnWindowCloseGlobal);

		SetWindowLong(Hwnd(), GWL_STYLE, GetWindowLong(Hwnd(), GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME); //set window maximize box style hide and disable resize
	}
	
	void LFRenderWindowWin32::Update()
	{
		Foreground();

		while (!glfwWindowShouldClose(window) && isRendering)
		{
			if (isPaused == false)
			{
				render->BeginScene();
				sceneGraph->Update(deltaTimer.DeltaTime());
				render->EndScene();
			}
			else
				Sleep(1);

			glfwPollEvents();
		}
	}

	void LFRenderWindowWin32::Foreground()
	{
		LFRenderWindow::Foreground();
	}

	void LFRenderWindowWin32::Background()
	{
		LFRenderWindow::Background();
	}

	void LFRenderWindowWin32::AppInit()
	{
		InitWindow();

		render->Init();
		LFRenderWindow::AppInit();

		Update();
	}
	
	void LFRenderWindowWin32::AppTerminate()
	{
		LFRenderWindow::AppTerminate();
	}

	void LFRenderWindowWin32::CloseWindow()
	{
		AppTerminate();
		isRendering = false;
	}

	void LFRenderWindowWin32::OnPauseResumeChanged(const LFPauseResumeEventArgs &args)
	{
		if (args.gameEngineRunState == LFPauseResumeEventArgs::RESUME)
			isPaused = false;

		if (args.gameEngineRunState == LFPauseResumeEventArgs::PAUSE)
			isPaused = true;
	}
}}

#endif
