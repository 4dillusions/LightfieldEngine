/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL

#include "LFRenderWindowWin32.h"
#include "..\..\LFData\LFAppData.h"
#include "..\..\LFCore\LFCommon\LFSystemData.h"
#include "..\..\..\LFEngine\LFScene\LFSceneGraph.h"
#include "..\..\..\LFEngine\LFRender\LFIRenderSystem.h"
#include "..\..\..\ThirdParty\_Win32_\GLFW\glfw3.h"
#include "..\..\..\ThirdParty\_Win32_\GLFW\glfw3native.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	LFRenderWindowWin32 *LFRenderWindowWin32::renderWindowWin32 = nullptr;

	GLFWwindow *LFRenderWindowWin32::GetWindow() const
	{
		return window;
	}

	HWND LFRenderWindowWin32::GetHwnd() const
	{
		return glfwGetWin32Window(window);
	}

	LFRenderWindowWin32::LFRenderWindowWin32()
	{
		renderWindowWin32 = this;
	}

	void LFRenderWindowWin32::InitWindow()
	{
		int windowWidth = LFSystemData::GetWindowWidth();
		int windowHeight = LFSystemData::GetWindowHeight();
		int screenWidth = LFSystemData::GetScreenWidth();
		int screenHeight = LFSystemData::GetScreenHeight();

		if (!glfwInit())
			CloseWindow();

		window = glfwCreateWindow(windowWidth, windowHeight, LFSystemData::GetAppData().logTag, nullptr, nullptr);
		if (!window)
			CloseWindow();

		glfwSetWindowPos(window, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2);
		glfwMakeContextCurrent(window);

		glfwSetWindowFocusCallback(window, OnWindowFocus);
		glfwSetWindowCloseCallback(window, OnWindowClose);

		SetWindowLong(GetHwnd(), GWL_STYLE, GetWindowLong(GetHwnd(), GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME); //set window maximize box style hide and disable resize
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

	void LFRenderWindowWin32::OnAppPauseResume(const LFGameEngine::AppPauseResumeEventArgs &appPauseResumeEventArgs)
	{
        if (appPauseResumeEventArgs.appRunState == LFGameEngine::AppPauseResumeEventArgs::AppRunState::Resume)
            isPaused = false;

        if (appPauseResumeEventArgs.appRunState == LFGameEngine::AppPauseResumeEventArgs::AppRunState::Pause)
            isPaused = true;
    }

	void LFRenderWindowWin32::OnWindowFocus(GLFWwindow *window, int focused)
	{
		if (focused == GL_TRUE)
			renderWindowWin32->Foreground();
		else
			renderWindowWin32->Background();
	}

	void LFRenderWindowWin32::OnWindowClose(GLFWwindow *window)
	{
		renderWindowWin32->CloseWindow();
	}
}}}

#endif
