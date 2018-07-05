/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLevelLabelControlLua.h"
#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\..\Graphics\LF2D\GUI\LFLevelLabelControl.h"
#include "..\..\..\..\..\..\Core\Math\LFRectangle.h"
#include "..\..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::Graphics::LF2D::GUI;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFLevelLabelControlConstructor(lua_State *luaState)
{
	int paramCount = 4;
	if (LFScriptSystem::Instance()->IsParamCountOk(paramCount))
	{
		//#1 font material
		LFFontMaterial fontMaterial = LoadLFFontMaterial(paramCount, 1);

		//#2 control material
		//#3 control material atlas
		LFControlMaterial controlMaterial = LoadLFControlMaterialNAtlas(paramCount, 2, 3);

		//#4 label data
		LFLabelData labelData;
		labelData.labelName = LFScriptSystem::Instance()->GetMetatableParameterValue("name", paramCount, 4, LFLuaType::LT_STRING).string;
		labelData.posX = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posX", paramCount, 4, LFLuaType::LT_NUMBER).number;
		labelData.posY = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posY", paramCount, 4, LFLuaType::LT_NUMBER).number;
		int value = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("value", paramCount, 4, LFLuaType::LT_NUMBER).number;
		labelData.digits = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("digits", paramCount, 4, LFLuaType::LT_NUMBER).number;

		labelData.text = LFString().AppendStr(value, labelData.digits);

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFLevelLabelControl>(AT, fontMaterial, controlMaterial, labelData), sizeof(LFLevelLabelControl *));
		LFScriptSystem::Instance()->CreateMetatable(LFLevelLabelControlName);
	}

	return 1; //return user data
}

int LFLevelLabelControlGetName(lua_State *luaState)
{
	return GetName(luaState, LFLevelLabelControlName);
}

int LFLevelLabelControlSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFLevelLabelControlName);
}

int LFLevelLabelControlSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFLevelLabelControlName);
}

int LFLevelLabelControlGetValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFLevelLabelControl *self = (LFLevelLabelControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFLevelLabelControlName, 1); //#1
		LFScriptSystem::Instance()->PushNumber(self->Value());
	}

	return 1; //return Value
}

int LFLevelLabelControlSetValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFLevelLabelControl *self = (LFLevelLabelControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFLevelLabelControlName, 1); //#1
		int value = (int)LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		self->Value(value);
	}

	return 0; //no return value
}

/**
@defgroup Graphics

@defgroup LFLevelLabelControl
@ingroup Graphics

@page my_LevelLabelConstructor New
@ingroup LFLevelLabelControl
Construct LFLevelLabelControl object.<br>
[Lua API]
@code
LFLevelLabelControl LFLevelLabelControl.New(table fontMaterial, table controlMaterial, table controlMaterialAtlas, table labelData)
@endcode
@param[in] fontMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight, alphabet, alphabetSize }<br>
@param[in] controlMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight }<br>
@param[in] controlMaterialAtlas <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] labelData <br>
{ labelName, posX, posY, value, digits } <br>

@page my_LevelLabelGetName GetName
@ingroup LFLevelLabelControl
Get LFLevelLabelControl name.<br>
[Lua API]
@code
string LFLevelLabelControl:GetName()
@endcode

@page my_LevelLabelSetIsAlive SetIsAlive
@ingroup LFLevelLabelControl
Set object is alive or not.<br>
[Lua API]
@code
LFLevelLabelControl:SetIsAlive(bool isAlive)
@endcode

@page my_LevelLabelSetIsVisible SetIsVisible
@ingroup LFLevelLabelControl
Set object is visible or not.<br>
[Lua API]
@code
LFLevelLabelControl:SetIsVisible(bool isVisible)
@endcode

@page my_LevelLabelGetValue GetValue
@ingroup LFLevelLabelControl
Get LFLevelLabelControl value.<br>
[Lua API]
@code
number LFLevelLabelControl:GetValue()
@endcode

@page my_LevelLabelSetValue SetValue
@ingroup LFLevelLabelControl
Set value number.<br>
[Lua API]
@code
LFLevelLabelControl:SetValue(number value)
@endcode
*/
luaL_Reg LFLevelLabelControlFunctions[] =
{
	{ "New", LFLevelLabelControlConstructor },
	//{ "__gc", LFLevelLabelControlDestructor },
	{ "GetName", LFLevelLabelControlGetName },
	{ "SetIsAlive", LFLevelLabelControlSetIsAlive },
	{ "SetIsVisible", LFLevelLabelControlSetIsVisible },
	{ "GetValue", LFLevelLabelControlGetValue },
	{ "SetValue", LFLevelLabelControlSetValue },
	{ 0, 0 }
};

luaL_Reg *GetLFLevelLabelControlFunctions()
{
	return LFLevelLabelControlFunctions;
}
