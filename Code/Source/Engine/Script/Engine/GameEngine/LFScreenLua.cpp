/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFScreenLua.h"
#include "LFLayerLua.h"
#include "..\..\..\Script\LuaHeaders.h"
#include "..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\GameEngine\LFScreen.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"
#include "..\..\..\..\Engine\Script\Core\Common\LFGameCompositComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;

int LFScreenConstructor(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFString name = LFScriptSystem::Instance()->GetStringParameter(1); //#1
	
		LFScriptSystem::Instance()->CreateUserData(LFNew<LFScreen>(AT, name), sizeof(LFScreen *));
		LFScriptSystem::Instance()->CreateMetatable(LFScreenName);
	}

	return 1; //return user data
}

int LFScreenFindLayer(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFScreen *self = (LFScreen *)LFScriptSystem::Instance()->GetUserDataParameter(LFScreenName, 1); //#1
		LFString name = LFScriptSystem::Instance()->GetStringParameter(2); //#2

		LFLayer *layer = self->FindLayer(name);

		if (layer == nullptr)
		{
			LFScriptSystem::Instance()->PushNil();
			return 1; //return nil value
		}

		LFScriptSystem::Instance()->CreateUserData(layer, sizeof(LFLayer *));
		LFScriptSystem::Instance()->CreateMetatable(LFLayerName);
	}

	return 1; //return user data
}

int LFScreenAddLayer(lua_State *luaState)
{
	return Add(luaState, LFScreenName, LFLayerName);
}

int LFScreenGetIsActive(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFScreen *self = (LFScreen *)LFScriptSystem::Instance()->GetUserDataParameter(LFScreenName, 1); //#1
		LFScriptSystem::Instance()->PushBoolean(self->IsActive());
	}

	return 1; //return IsActive
}

int LFScreenSetActive(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFScreen *self = (LFScreen *)LFScriptSystem::Instance()->GetUserDataParameter(LFScreenName, 1); //#1
		self->SetActive();
	}

	return 0; //no return value
}

int LFScreenGetName(lua_State *luaState)
{
	return GetName(luaState, LFScreenName);
}

int LFScreenWriteLayerNames(lua_State *luaState)
{
	return WriteOutputComponentNames(luaState, LFScreenName);
}

int LFScreenGetIsAlive(lua_State *luaState)
{
	return GetIsAlive(luaState, LFScreenName);
}

int LFScreenSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFScreenName);
}

int LFScreenGetIsVisible(lua_State *luaState)
{
	return GetIsVisible(luaState, LFScreenName);
}

int LFScreenSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFScreenName);
}

/**
@defgroup GameEngine

@defgroup LFScreen
@ingroup GameEngine

@page my_ScreenConstructor New
@ingroup LFScreen
Construct LFScreen object.<br>
[Lua API]
@code
LFScreen LFScreen.New(string name)
@endcode

@page my_ScreenFindLayer FindLayer
@ingroup LFScreen
Get LFLayer in LFScreen.<br>
[Lua API]
@code
LFLayer LFScreen:FindLayer(string name)
@endcode

@page my_ScreenAddLayer AddLayer
@ingroup LFScreen
Add LFLayer to LFScreen.<br>
[Lua API]
@code
LFScreen:AddLayer(LFLayer layer)
@endcode

@page my_ScreenGetIsActive GetIsActive
@ingroup LFScreen
Get screen is the main screen or not.<br>
[Lua API]
@code
LFScreen:GetIsActive()
@endcode

@page my_ScreenSetActive SetActive
@ingroup LFScreen
This screen will be the main screen.<br>
[Lua API]
@code
LFScreen:SetActive()
@endcode

@page my_ScreenGetName GetName
@ingroup LFScreen
Get LFScreen name.<br>
[Lua API]
@code
string LFScreen:GetName()
@endcode

@page my_ScreenWriteComponentNames WriteComponentNames
@ingroup LFScreen
Write component names in LFScreen.<br>
[Lua API]
@code
LFScreen:WriteComponentNames()
@endcode

@page my_ScreenGetIsAlive GetIsAlive
@ingroup LFScreen
Get object is alive or not.<br>
[Lua API]
@code
bool LFScreen:GetIsAlive()
@endcode

@page my_ScreenSetIsAlive SetIsAlive
@ingroup LFScreen
Set object is alive or not.<br>
[Lua API]
@code
LFScreen:SetIsAlive(bool isAlive)
@endcode

@page my_ScreenGetIsVisible GetIsVisible
@ingroup LFScreen
Get object is visible or not.<br>
[Lua API]
@code
bool LFScreen:GetIsVisible()
@endcode

@page my_ScreenSetIsVisible SetIsVisible
@ingroup LFScreen
Set object is visible or not.<br>
[Lua API]
@code
LFScreen:SetIsVisible(bool isVisible)
@endcode
*/
luaL_Reg LFScreenFunctions[] =
{
	{ "New", LFScreenConstructor }, 
	//{ "__gc", LFScreenDestructor }, 
	{ "FindLayer", LFScreenFindLayer },
	{ "AddLayer", LFScreenAddLayer },
	{ "GetIsActive", LFScreenGetIsActive },
	{ "SetActive", LFScreenSetActive }, 
	{ "GetName", LFScreenGetName }, 
	{ "WriteLayerNames", LFScreenWriteLayerNames },
	{ "GetIsAlive", LFScreenGetIsAlive },
	{ "SetIsAlive", LFScreenSetIsAlive }, 
	{ "GetIsVisible", LFScreenGetIsVisible },
	{ "SetIsVisible", LFScreenSetIsVisible }, 
	{ 0, 0 }
};

luaL_Reg *GetLFScreenFunctions()
{
	return LFScreenFunctions;
}
