/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "LFInputSystemGlfw.h"
#include "..\..\..\..\Source\Depencies\Glfw\SDK\include\GLFW\glfw3.h"
#include "..\..\Script\LFScriptSystem.h"
#include "..\..\Script\Engine\Input\LFInputLua.h"
#include "..\..\..\Core\Common\LFMemoryManager.h"

using namespace LFCore::Common;
using namespace LFEngine::Script;

namespace LFEngine { namespace Input
{
	LFPointerEventArgs mouseArgsGlobal;
	LFPointerMoveEventArgs mouseMoveArgsGlobal;
	LFButtonEventArgs keyArgsGlobal;
	double xPos, yPos;

	void OnMousePressReleaseGlobal(GLFWwindow *window, int button, int action, int modifier) 
	{
		char *btnStr;
		if (button == GLFW_MOUSE_BUTTON_1)
		{
			btnStr = TCLeft;
			mouseArgsGlobal.touch = LFPointerEventArgs::TC_LEFT;
		}
		else
		{
			btnStr = TCRight;
			mouseArgsGlobal.touch = LFPointerEventArgs::TC_RIGHT;
		}

		glfwGetCursorPos(window, &xPos, &yPos);
		mouseArgsGlobal.x = (int)xPos;
		mouseArgsGlobal.y = (int)yPos;

		if (action == GLFW_PRESS)
		{
			LFScriptSystem::Instance()->CallFunction(LFInputName, LFInputOnPointerPressedName, LFLuaType().SetString(btnStr), LFLuaType().SetNumber(mouseArgsGlobal.x), LFLuaType().SetNumber(mouseArgsGlobal.y));
			mouseArgsGlobal.isPressed = true;
		}

		if (action == GLFW_RELEASE)
		{
			LFScriptSystem::Instance()->CallFunction(LFInputName, LFInputOnPointerReleasedName, LFLuaType().SetString(btnStr), LFLuaType().SetNumber(mouseArgsGlobal.x), LFLuaType().SetNumber(mouseArgsGlobal.y));
			mouseArgsGlobal.isPressed = false;
		}

		if (LFInputSystem::Instance() != nullptr)
			LFInputSystem::Instance()->PointerPressReleaseEvent(mouseArgsGlobal);
	}

	void OnKeyPressReleaseGlobal(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		switch(key)
		{
			case GLFW_KEY_ESCAPE: keyArgsGlobal.button = LFButtonEventArgs::BT_BACK; break; //esc
			case GLFW_KEY_KP_ADD: keyArgsGlobal.button = LFButtonEventArgs::BT_SOUND_UP; break; //numpad +
			case GLFW_KEY_KP_SUBTRACT: keyArgsGlobal.button = LFButtonEventArgs::BT_SOUND_DOWN; break; //numpad -
			default: return;
		}

		char *keyStr;
		switch(key)
		{
			case GLFW_KEY_KP_ADD: keyStr = BTSoundUp; break;
			case GLFW_KEY_KP_SUBTRACT: keyStr = BTSoundDown; break;
			case GLFW_KEY_ESCAPE: keyStr = BTBack; break;
			default: return;
		}

		if (action == GLFW_PRESS)
			LFScriptSystem::Instance()->CallFunction(LFInputName, LFInputOnButtonPressedName, LFLuaType().SetString(keyStr));

		if (action == GLFW_RELEASE)
			LFScriptSystem::Instance()->CallFunction(LFInputName, LFInputOnButtonReleasedName, LFLuaType().SetString(keyStr));
	}

	void OnMouseMoveGlobal(GLFWwindow *window, double posX, double posY)
	{
		if (mouseArgsGlobal.isPressed && mouseArgsGlobal.touch == LFPointerEventArgs::TC_LEFT)
		{
			mouseMoveArgsGlobal.x = (int)posX;
			mouseMoveArgsGlobal.y = (int)posY;

			LFInputSystem::Instance()->PointerMoveEvent(mouseMoveArgsGlobal);
		}
	}

	LFInputSystemGlfw::LFInputSystemGlfw(GLFWwindow *window)
	{
		glfwSetMouseButtonCallback(window, OnMousePressReleaseGlobal);
		glfwSetKeyCallback(window, OnKeyPressReleaseGlobal);
		glfwSetCursorPosCallback(window, OnMouseMoveGlobal);
	}

	void LFInputSystemGlfw::CreateInstance(GLFWwindow *window)
	{
		if (instance == nullptr)
			instance = LFNew<LFInputSystemGlfw>(AT, window);
	}

	void LFInputSystemGlfw::ReleaseInstance()
	{
		if (instance != nullptr)
			LFDelete(instance);
	}
}}

#endif
