/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFInputLua.h"
#include "..\..\..\Script\LuaHeaders.h"
#include "..\..\..\Script\LFScriptSystem.h"

using namespace LFEngine::Script;

int LFInputOnPointerPressed(lua_State *luaState)
{
	return 0; //no return value
}

int LFInputOnPointerReleased(lua_State *luaState)
{
	return 0; //no return value
}

int LFInputOnButtonPressed(lua_State *luaState)
{
	return 0; //no return value
}

int LFInputOnButtonReleased(lua_State *luaState)
{
	return 0; //no return value
}

int LFInputOnControlPressed(lua_State *luaState)
{
	return 0; //no return value
}

/**
@defgroup Input

@defgroup LFInput
@ingroup Input

@page my_InputOnPointerPressed OnPointerPressed
@ingroup LFInput
Mouse or touch screen press event.<br>
[Lua API]<br>
@code
function LFInput:OnPointerPressed(string pointer, number posX, number posY)
@endcode
@param[out] pointer <br>
[PC] mouse: left click "TC_LEFT", right click "TC_RIGHT"<br>
[Mobile] touch screen: touch "TC_LEFT"

@page my_InputOnPointerReleased OnPointerReleased
@ingroup LFInput
Mouse or touch screen release event.<br>
[Lua API]<br>
@code
function LFInput:OnPointerReleased(string pointer, number posX, number posY)
@endcode
@param[out] pointer <br>
[PC] mouse: left click "TC_LEFT", right click "TC_RIGHT"<br>
[Mobile] touch screen: touch "TC_LEFT"

@page my_InputOnButtonPressed OnButtonPressed
@ingroup LFInput
Keyboard or hardware button press event.<br>
[Lua API]<br>
@code
function LFInput:OnButtonPressed(string button)
@endcode
@param[out] button <br>
[PC] keyboard: + "BT_SOUND_UP", - "BT_SOUND_DOWN", esc "BT_BACK"<br>
[Mobile] hardware button: Volume+ "BT_SOUND_UP", Volume- "BT_SOUND_DOWN", Back "BT_BACK"

@page my_InputOnButtonReleased OnButtonReleased
@ingroup LFInput
Keyboard or hardware button release event.<br>
[Lua API]<br>
@code
function LFInput:OnButtonReleased(string button)
@endcode
@param[out] button <br>
[PC] keyboard: + "BT_SOUND_UP", - "BT_SOUND_DOWN", esc "BT_BACK"<br>
[Mobile] hardware button: Volume+ "BT_SOUND_UP", Volume- "BT_SOUND_DOWN", Back "BT_BACK"

@page my_InputOnControlPressed OnControlPressed
@ingroup LFInput
Graphics object press event.<br>
[Lua API]<br>
@code
function LFInput:OnControlPressed(LFControl sender)
@endcode
*/
luaL_Reg LFInputFunctions[] =
{
	//{ "New", LFInputConstructor }, 
	//{ "__gc", LFInputDestructor }, 
	{ LFInputOnPointerPressedName, LFInputOnPointerPressed },
	{ LFInputOnPointerReleasedName, LFInputOnPointerReleased },
	{ LFInputOnButtonPressedName, LFInputOnButtonPressed },
	{ LFInputOnButtonReleasedName, LFInputOnButtonReleased },
	{ LFInputOnControlPressedName, LFInputOnControlPressed },
	{ 0, 0 }
};

luaL_Reg *GetLFInputFunctions()
{
	return LFInputFunctions;
}
