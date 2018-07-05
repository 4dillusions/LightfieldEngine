/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFNumberLabelControlLua.h"
#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\..\Graphics\LF2D\GUI\LFNumberLabelControl.h"
#include "..\..\..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::Graphics::LF2D::GUI;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFNumberLabelControlConstructor(lua_State *luaState)
{
	int paramCount = 2;
	if (LFScriptSystem::Instance()->IsParamCountOk(paramCount))
	{
		//#1 font material
		LFFontMaterial fontMaterial = LoadLFFontMaterial(paramCount, 1);

		//#2 label data
		LFLabelData labelData;
		labelData.labelName = LFScriptSystem::Instance()->GetMetatableParameterValue("name", paramCount, 2, LFLuaType::LT_STRING).string;
		labelData.posX = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posX", paramCount, 2, LFLuaType::LT_NUMBER).number;
		labelData.posY = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posY", paramCount, 2, LFLuaType::LT_NUMBER).number;
		int value = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("value", paramCount, 2, LFLuaType::LT_NUMBER).number;
		labelData.digits = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("digits", paramCount, 2, LFLuaType::LT_NUMBER).number;

		labelData.text = LFString().AppendStr(value, labelData.digits);

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFNumberLabelControl>(AT, fontMaterial, labelData), sizeof(LFNumberLabelControl *));
		LFScriptSystem::Instance()->CreateMetatable(LFNumberLabelControlName);
	}

	return 1; //return user data
}

int LFNumberLabelControlGetName(lua_State *luaState)
{
	return GetName(luaState, LFNumberLabelControlName);
}

int LFNumberLabelControlSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFNumberLabelControlName);
}

int LFNumberLabelControlSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFNumberLabelControlName);
}

int LFNumberLabelControlGetValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFNumberLabelControl *self = (LFNumberLabelControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFNumberLabelControlName, 1); //#1
		LFScriptSystem::Instance()->PushNumber(self->Value());
	}

	return 1; //return Value
}

int LFNumberLabelControlSetValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFNumberLabelControl *self = (LFNumberLabelControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFNumberLabelControlName, 1); //#1
		int value = (int)LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		self->Value(value);
	}

	return 0; //no return value
}

/**
@defgroup Graphics

@defgroup LFNumberLabelControl
@ingroup Graphics

@page my_NumberLabelConstructor New
@ingroup LFNumberLabelControl
Construct LFNumberLabelControl object.<br>
[Lua API]
@code
LFNumberLabelControl LFNumberLabelControl.New(table fontMaterial, table labelData)
@endcode
@param[in] fontMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight, alphabet, alphabetSize }<br>
@param[in] labelData <br>
{ name, posX, posY, value, digits } <br>

@page my_NumberLabelGetName GetName
@ingroup LFNumberLabelControl
Get LFNumberLabelControl name.<br>
[Lua API]
@code
string LFNumberLabelControl:GetName()
@endcode

@page my_NumberLabelSetIsAlive SetIsAlive
@ingroup LFNumberLabelControl
Set object is alive or not.<br>
[Lua API]
@code
LFNumberLabelControl:SetIsAlive(bool isAlive)
@endcode

@page my_NumberLabelSetIsVisible SetIsVisible
@ingroup LFNumberLabelControl
Set object is visible or not.<br>
[Lua API]
@code
LFNumberLabelControl:SetIsVisible(bool isVisible)
@endcode

@page my_NumberLabelGetValue GetValue
@ingroup LFNumberLabelControl
Get LFNumberLabelControl value.<br>
[Lua API]
@code
number LFNumberLabelControl:GetValue()
@endcode

@page my_NumberLabelSetValue SetValue
@ingroup LFNumberLabelControl
Set value number.<br>
[Lua API]
@code
LFNumberLabelControl:SetValue(number value)
@endcode
*/
luaL_Reg LFNumberLabelControlFunctions[] =
{
	{ "New", LFNumberLabelControlConstructor },
	//{ "__gc", LFNumberLabelControlDestructor },
	{ "GetName", LFNumberLabelControlGetName },
	{ "SetIsAlive", LFNumberLabelControlSetIsAlive },
	{ "SetIsVisible", LFNumberLabelControlSetIsVisible },
	{ "GetValue", LFNumberLabelControlGetValue },
	{ "SetValue", LFNumberLabelControlSetValue },
	{ 0, 0 }
};

luaL_Reg *GetLFNumberLabelControlFunctions()
{
	return LFNumberLabelControlFunctions;
}
