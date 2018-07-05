/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTimerLua.h"
#include "..\..\LuaHeaders.h"
#include "..\..\LFScriptSystem.h"
#include "..\..\..\..\Core\Common\LFTimer.h"

using namespace LFEngine::Script;
using namespace LFCore::Common;

int LFTimerGetActualTime(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		//self //#1
		LFScriptSystem::Instance()->PushNumber(LFTimer::GetActualTime());
	}

	return 1; //return actualTime
}

/**
@defgroup Common

@defgroup LFTimer
@ingroup Common

@page my_GetActualTime GetActualTime
@ingroup LFTimer
Get actual time from OS<br>
[Lua API]
@code
number LFTimer:GetActualTime()
@endcode
*/
luaL_Reg LFTimerFunctions[] =
{
	//{ "New", Constructor }, 
	//{ "__gc", Destructor }, 
	{ "GetActualTime", LFTimerGetActualTime },
	{ 0, 0 }
};

luaL_Reg *GetLFTimerFunctions()
{
	return LFTimerFunctions;
}