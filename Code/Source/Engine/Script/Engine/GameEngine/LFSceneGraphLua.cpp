/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSceneGraphLua.h"
#include "LFScreenLua.h"
#include "..\..\..\Script\LuaHeaders.h"
#include "..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\GameEngine\LFSceneGraph.h"
#include "..\..\..\GameEngine\LFScreen.h"
#include "..\..\..\..\Core\Common\LFString.h"

using namespace LFEngine::Script;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;

int LFSceneGraphFindScreen(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		LFString name = LFScriptSystem::Instance()->GetStringParameter(2); //#2

		LFScreen *screen = LFSceneGraph::Instance()->FindScreen(name);

		if (screen == nullptr)
		{
			LFScriptSystem::Instance()->PushNil();
			return 1; //return nil value
		}

		LFScriptSystem::Instance()->CreateUserData(screen, sizeof(LFScreen *));
		LFScriptSystem::Instance()->CreateMetatable(LFScreenName);
	}

	return 1; //return user data
}

int LFSceneGraphAddScreen(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		LFGameComponent *screen = (LFGameComponent *)LFScriptSystem::Instance()->GetUserDataParameter(LFScreenName, 2); //#2

		LFSceneGraph::Instance()->Add(screen);
	}

	return 0; //no return value
}

int LFSceneGraphWriteScreenNames(lua_State *luaState)
{
	//self //#1
	LFSceneGraph::Instance()->WriteOutputComponentNames();

	return 0; //no return value
}

/**
@defgroup GameEngine

@defgroup LFSceneGraph
@ingroup GameEngine

@page my_SceneGraphFindScreen FindScreen
@ingroup LFSceneGraph
Get LFScreen in LFSceneGraph.<br>
[Lua API]
@code
LFScreen LFSceneGraph:FindScreen(string name)
@endcode

@page my_SceneGraphAddScreen AddScreen
@ingroup LFSceneGraph
Add LFScreen to LFSceneGraph.<br>
[Lua API]
@code
LFSceneGraph:AddScreen(LFScreen screen)
@endcode

@page my_SceneGraphWriteComponentNames WriteComponentNames
@ingroup LFSceneGraph
Write component names in LFSceneGraph.<br>
[Lua API]
@code
LFSceneGraph:WriteComponentNames()
@endcode
*/
luaL_Reg LFSceneGraphFunctions[] =
{
	//{ "New", LFSceneGraphConstructor }, 
	//{ "__gc", LFSceneGraphDestructor }, 
	{ "FindScreen", LFSceneGraphFindScreen },
	{ "AddScreen", LFSceneGraphAddScreen },
	{ "WriteScreenNames", LFSceneGraphWriteScreenNames },
	{ 0, 0 }
};

luaL_Reg *GetLFSceneGraphFunctions()
{
	return LFSceneGraphFunctions;
}
