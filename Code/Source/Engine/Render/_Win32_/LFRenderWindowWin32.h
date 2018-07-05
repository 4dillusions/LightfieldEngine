/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\LFRenderWindow.h"

struct GLFWwindow;

namespace LFEngine { namespace Render
{
	class LFENGINE_LIBRARY LFRenderWindowWin32 : public LFRenderWindow
	{ 
	private:
		GLFWwindow *window;

	public:
		LFRenderWindowWin32();
		virtual ~LFRenderWindowWin32();

		static void CreateInstance();
		static void ReleaseInstance();
		
		GLFWwindow *Window() { return window; }

		HWND Hwnd();

		virtual void InitWindow();
		virtual void Update();
		virtual void Foreground();
		virtual void Background();
		virtual void AppInit();
		virtual void AppTerminate();
		virtual void CloseWindow();

		virtual void OnPauseResumeChanged(const GameEngine::LFPauseResumeEventArgs &args);
	};
}}

#endif
