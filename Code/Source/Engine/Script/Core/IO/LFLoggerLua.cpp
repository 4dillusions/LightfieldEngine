/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLoggerLua.h"
#include "..\..\LuaHeaders.h"
#include "..\..\LFScriptSystem.h"
#include "..\..\..\..\Core\\IO\LFLogger.h"

using namespace LFEngine::Script;
using namespace LFCore::IO;

int LFLoggerWriteOutput(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		LFLogger::Instance().WriteOutput(LFScriptSystem::Instance()->GetStringParameter(2).ToChar()); //#2
	}

	return 0; //no return value
}

/**
@defgroup IO

@defgroup LFLogger
@ingroup IO

@page my_WriteOutput WriteOutput
@ingroup LFLogger
Logging to console and Log.txt<br>
[Lua API]
@code
LFLogger:WriteOutput(string log)
@endcode
*/
luaL_Reg LFLoggerFunctions[] =
{
	//{ "New", Constructor }, 
	//{ "__gc", Destructor }, 
	{ "WriteOutput", LFLoggerWriteOutput },
	{ 0, 0 }
};

luaL_Reg *GetLFLoggerFunctions()
{
	return LFLoggerFunctions;
}