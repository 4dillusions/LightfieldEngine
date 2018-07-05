/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#pragma once

#include "..\LFInputSystem.h"

struct GLFWwindow;

namespace LF3Engine { namespace LFEngine { namespace LFInput
{
	class LFInputSystemWin32 final : public LFInputSystem
	{
		LFInputSystemWin32(const LFInputSystemWin32&) = delete;
		LFInputSystemWin32(LFInputSystemWin32 &&) = delete;
		LFInputSystemWin32 &operator=(const LFInputSystemWin32 &) = delete;
		LFInputSystemWin32 &operator=(LFInputSystemWin32 &&) = delete;

	public:
		LFInputSystemWin32();
		~LFInputSystemWin32() = default;

		//GLFW functions
		static void OnKeyPressRelease(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void OnMousePressRelease(GLFWwindow *window, int button, int action, int modifier);
		static void OnMouseMove(GLFWwindow *window, double posX, double posY);
	};
}}}

#endif
