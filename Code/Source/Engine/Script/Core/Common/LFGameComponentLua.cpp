/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameComponentLua.h"
#include "..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\Core\Common\LFGameComponent.h"

using namespace LFEngine::Script;
using namespace LFCore::Common;

int GetName(lua_State *luaState, const char *objectName)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFGameComponent *self = (LFGameComponent *)LFScriptSystem::Instance()->GetUserDataParameter(objectName, 1); //#1
		LFScriptSystem::Instance()->PushString(self->GetName().ToChar());
	}

	return 1; //return Name
}

int GetIsAlive(lua_State *luaState, const char *objectName)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFGameComponent *self = (LFGameComponent *)LFScriptSystem::Instance()->GetUserDataParameter(objectName, 1); //#1
		LFScriptSystem::Instance()->PushBoolean(self->GetIsAlive());
	}

	return 1; //return IsAlive
}

int GetIsVisible(lua_State *luaState, const char *objectName)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFGameComponent *self = (LFGameComponent *)LFScriptSystem::Instance()->GetUserDataParameter(objectName, 1); //#1
		LFScriptSystem::Instance()->PushBoolean(self->GetIsVisible());
	}

	return 1; //return IsVisible
}

int SetIsAlive(lua_State *luaState, const char *objectName)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFGameComponent *self = (LFGameComponent *)LFScriptSystem::Instance()->GetUserDataParameter(objectName, 1); //#1
		bool isAlive = LFScriptSystem::Instance()->GetBooleanParameter(2); //#2

		self->SetIsAlive(isAlive);
	}

	return 0; //no return value
}

int SetIsVisible(lua_State *luaState, const char *objectName)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFGameComponent *self = (LFGameComponent *)LFScriptSystem::Instance()->GetUserDataParameter(objectName, 1); //#1
		bool isVisible = LFScriptSystem::Instance()->GetBooleanParameter(2); //#2

		self->SetIsVisible(isVisible);
	}

	return 0; //no return value
}