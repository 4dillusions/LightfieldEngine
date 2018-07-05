/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#pragma once

#include "..\LFRenderWindow.h"
#include <windows.h>

struct GLFWwindow;

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	/**
		@brief
		Render window for rendering OpenGL on Win32
		Render window for rendering Direct3D on Win32
	*/
    class LFRenderWindowWin32 final : public LFRenderWindow
	{
		GLFWwindow *window = nullptr;
		static LFRenderWindowWin32 *renderWindowWin32;

	public:
		GLFWwindow *GetWindow() const;
		HWND GetHwnd() const;

        LFRenderWindowWin32(const LFRenderWindowWin32 &) = delete;
		LFRenderWindowWin32(LFRenderWindowWin32 &&) = delete;
		LFRenderWindowWin32 &operator=(const LFRenderWindowWin32 &) = delete;
        LFRenderWindowWin32 &operator=(LFRenderWindowWin32 &&) = delete;

		LFRenderWindowWin32();
        ~LFRenderWindowWin32() = default;

		//LFRenderWindow functions
		void InitWindow() override;
		void Update() override;
		void Foreground() override;
		void Background() override;
		void AppInit() override;
		void AppTerminate() override;
		void CloseWindow() override;

		void OnAppPauseResume(const LFGameEngine::AppPauseResumeEventArgs &appPauseResumeEventArgs) override;

		//GLFW functions
		static void OnWindowFocus(GLFWwindow *window, int focused);
		static void OnWindowClose(GLFWwindow *window);
	};
}}}

#endif
