/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFScriptSystemLua.h"
#include "..\LuaHeaders.h"
#include "..\LFScriptSystem.h"

using namespace LFEngine::Script;

int LFScriptLoadScript(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		LFScriptSystem::Instance()->LoadScript(LFScriptSystem::Instance()->GetStringParameter(2).ToChar()); //#2
	}

	return 0; //no return value
}

/**
@defgroup Script

@defgroup LFScript
@ingroup Script

@page my_LoadScript LoadScript
@ingroup LFScript
Load .lua or .lby script file<br>
[Lua API]
@code
LFScript:LoadScript(string sriptPathAndName)
@endcode
*/
luaL_Reg LFScriptFunctions[] =
{
	//{ "New", Constructor }, 
	//{ "__gc", Destructor }, 
	{ "LoadScript", LFScriptLoadScript },
	{ 0, 0 }
};

luaL_Reg *GetLFScriptFunctions()
{
	return LFScriptFunctions;
}