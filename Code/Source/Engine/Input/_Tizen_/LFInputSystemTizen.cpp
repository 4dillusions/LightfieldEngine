/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#include "LFInputSystemTizen.h"
#include "..\..\Script\LFScriptSystem.h"
#include "..\..\Script\Engine\Input\LFInputLua.h"
#include "..\..\..\..\LFCore\src\Common\LFMemoryManager.h"

using namespace LFCore::Common;
using namespace LFEngine::Script;
using namespace LFEngine::Input;

LFPointerEventArgs mouseArgsGlobal;
LFPointerMoveEventArgs mouseMoveArgsGlobal;

void mouse_down_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	static Evas_Event_Mouse_Down *downInfo = 0;
	downInfo = (Evas_Event_Mouse_Down *)event_info;

	if (downInfo->button == 1) //left button
	{
		mouseArgsGlobal.x = downInfo->output.x;
		mouseArgsGlobal.y = downInfo->output.y;
		mouseArgsGlobal.touch = LFPointerEventArgs::TC_LEFT;
		mouseArgsGlobal.isPressed = true;

		LFScriptSystem::Instance()->CallFunction(LFInputName, LFInputOnPointerPressedName, LFLuaType().SetString(TCLeft), LFLuaType().SetNumber(mouseArgsGlobal.x), LFLuaType().SetNumber(mouseArgsGlobal.y));

		if (LFInputSystem::Instance() != nullptr)
			LFInputSystem::Instance()->PointerPressReleaseEvent(mouseArgsGlobal);
	}
}

void mouse_up_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	static Evas_Event_Mouse_Up *upInfo = 0;
	upInfo = (Evas_Event_Mouse_Up *)event_info;

	if (upInfo->button == 1) //left button
	{
		mouseArgsGlobal.x = upInfo->output.x;
		mouseArgsGlobal.y = upInfo->output.y;
		mouseArgsGlobal.touch = LFPointerEventArgs::TC_LEFT;
		mouseArgsGlobal.isPressed = false;

		LFScriptSystem::Instance()->CallFunction(LFInputName, LFInputOnPointerReleasedName, LFLuaType().SetString(TCLeft), LFLuaType().SetNumber(mouseArgsGlobal.x), LFLuaType().SetNumber(mouseArgsGlobal.y));

		if (LFInputSystem::Instance() != nullptr)
			LFInputSystem::Instance()->PointerPressReleaseEvent(mouseArgsGlobal);
	}
}

void win_back_cb(void *data, Evas_Object *obj, void *event_info) //back hardware button
{
	LFScriptSystem::Instance()->CallFunction(LFInputName, LFInputOnButtonReleasedName, LFLuaType().SetString(BTBack));
}

void mouse_move_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	static Evas_Event_Mouse_Move *moveInfo = 0;
	moveInfo = (Evas_Event_Mouse_Move *)event_info;

	if (mouseArgsGlobal.isPressed && mouseArgsGlobal.touch == LFPointerEventArgs::TC_LEFT)
	{
		mouseMoveArgsGlobal.x = moveInfo->cur.output.x;
		mouseMoveArgsGlobal.y = moveInfo->cur.output.y;

		LFInputSystem::Instance()->PointerMoveEvent(mouseMoveArgsGlobal);
	}
}

namespace LFEngine { namespace Input
{
	LFInputSystemTizen::LFInputSystemTizen()
	{ }

	LFInputSystemTizen::~LFInputSystemTizen()
	{ }

	void LFInputSystemTizen::CreateInstance()
	{
		if (instance == nullptr)
			instance = LFNew<LFInputSystemTizen>(AT);
	}

	void LFInputSystemTizen::ReleaseInstance()
	{
		if (instance != nullptr)
			LFDelete(instance);
	}
}}

#endif
