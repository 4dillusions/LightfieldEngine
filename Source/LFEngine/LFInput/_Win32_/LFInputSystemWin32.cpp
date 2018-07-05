/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#include "LFInputSystemWin32.h"
#include "..\..\LFCore\LFPatterns\LFIoc.h"
#include "..\..\LFRender\_Win32_\LFRenderWindowWin32.h"
#include "..\..\..\ThirdParty\_Win32_\GLFW\glfw3.h"
#include "..\..\LFGameEngine\LFIGame.h"

using namespace LF3Engine::LFEngine::LFGameEngine;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFRender;
using namespace LF3Engine::LFEngine::LFInput;

namespace LF3Engine { namespace LFEngine { namespace LFInput
{
	LFInputSystemWin32::LFInputSystemWin32()
	{
		input = this;
		game = LF3GameEngine::Instance()->GetGame();

		if (auto renderWindow = dynamic_cast<LFRenderWindowWin32 *>(LFIoc<LFRenderWindow *>::Get()))
		{
			auto window = renderWindow->GetWindow();

			glfwSetMouseButtonCallback(window, OnMousePressRelease);
			glfwSetKeyCallback(window, OnKeyPressRelease);
			glfwSetCursorPosCallback(window, OnMouseMove);
		}
	}

	void LFInputSystemWin32::OnKeyPressRelease(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE: hardwareButtonEventArgs.button = LFHardwareButtonTypes::Back; break; //esc
			case GLFW_KEY_KP_ADD: hardwareButtonEventArgs.button = LFHardwareButtonTypes::SoundUp; break; //numpad +
			case GLFW_KEY_KP_SUBTRACT: hardwareButtonEventArgs.button = LFHardwareButtonTypes::SoundDown; break; //numpad -
			default: return;
		}

		static char *keyStr;
		switch (key)
		{
			case GLFW_KEY_KP_ADD: keyStr = SoundUp; break;
			case GLFW_KEY_KP_SUBTRACT: keyStr = SoundDown; break;
			case GLFW_KEY_ESCAPE: keyStr = Back; break;
			default: return;
		}

		if (action == GLFW_PRESS)
			hardwareButtonEventArgs.isPressed = true;

		if (action == GLFW_RELEASE)
			hardwareButtonEventArgs.isPressed = false;

		game->OnButtonPressRelease(hardwareButtonEventArgs);
		input->OnHardwareButtonPressRelease(hardwareButtonEventArgs);
	}

	void LFInputSystemWin32::OnMousePressRelease(GLFWwindow *window, int button, int action, int modifier)
	{
		if (button == GLFW_MOUSE_BUTTON_1) //left mouse button
		{
			static double xPos, yPos;
			glfwGetCursorPos(window, &xPos, &yPos);
			pointerPressReleaseEventArgs.x = static_cast<int>(xPos);
			pointerPressReleaseEventArgs.y = static_cast<int>(yPos);

			if (action == GLFW_PRESS)
				pointerPressReleaseEventArgs.isPressed = true;

			if (action == GLFW_RELEASE)
				pointerPressReleaseEventArgs.isPressed = false;

			game->OnPointerPressRelease(pointerPressReleaseEventArgs);
			input->OnPointerPressRelease(pointerPressReleaseEventArgs);
		}
	}

	void LFInputSystemWin32::OnMouseMove(GLFWwindow *window, double posX, double posY)
	{
		if (pointerPressReleaseEventArgs.isPressed)
		{
			pointerMoveEventArgs.x = static_cast<int>(posX);
			pointerMoveEventArgs.y = static_cast<int>(posY);

			game->OnPointerMove(pointerMoveEventArgs);
			input->OnPointerMove(pointerMoveEventArgs);
		}
	}
}}}

#endif
