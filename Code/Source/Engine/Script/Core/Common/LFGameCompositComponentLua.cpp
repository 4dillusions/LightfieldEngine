/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameCompositComponentLua.h"
#include "..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\Core\Common\LFGameCompositComponent.h"

using namespace LFEngine::Script;
using namespace LFCore::Common;

int GetComponetsLength(lua_State *luaState, const char *objectName)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFGameCompositComponent *self = (LFGameCompositComponent *)LFScriptSystem::Instance()->GetUserDataParameter(objectName, 1); //#1
		LFScriptSystem::Instance()->PushBoolean(self->GetComponetsLength());
	}

	return 1; //return ComponentsLenght
}

int WriteOutputComponentNames(lua_State *luaState, const char *objectName)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFGameCompositComponent *self = (LFGameCompositComponent *)LFScriptSystem::Instance()->GetUserDataParameter(objectName, 1); //#1
		self->WriteOutputComponentNames();
	}

	return 0; //no return value
}

int Add(lua_State *luaState, const char *objectName, const char *addObjectName)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFGameCompositComponent *self = (LFGameCompositComponent *)LFScriptSystem::Instance()->GetUserDataParameter(objectName, 1); //#1
		LFGameComponent *gameComponent = (LFGameComponent *)LFScriptSystem::Instance()->GetUserDataParameter(addObjectName, 2); //#2

		self->Add(gameComponent);
	}

	return 0; //no return value
}

int Remove(lua_State *luaState, const char *objectName, const char *removeObjectName) //After render only
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFGameCompositComponent *self = (LFGameCompositComponent *)LFScriptSystem::Instance()->GetUserDataParameter(objectName, 1); //#1
		LFGameComponent *gameComponent = (LFGameComponent *)LFScriptSystem::Instance()->GetUserDataParameter(removeObjectName, 2); //#2

		self->Remove(gameComponent);
	}

	return 0; //no return value
}