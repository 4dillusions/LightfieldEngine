/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLabelControlLua.h"
#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\..\Graphics\LF2D\GUI\LFLabelControl.h"
#include "..\..\..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::GameEngine;
using namespace LFEngine::Graphics::LF2D::GUI;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFLabelControlConstructor(lua_State *luaState)
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
		labelData.text = LFString(LFScriptSystem::Instance()->GetMetatableParameterValue("text", paramCount, 2, LFLuaType::LT_STRING).string);

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFLabelControl>(AT, fontMaterial, labelData), sizeof(LFLabelControl *));
		LFScriptSystem::Instance()->CreateMetatable(LFLabelControlName);
	}

	return 1; //return user data
}

int LFLabelControlGetName(lua_State *luaState)
{
	return GetName(luaState, LFLabelControlName);
}

int LFLabelControlSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFLabelControlName);
}

int LFLabelControlSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFLabelControlName);
}

/**
@defgroup Graphics

@defgroup LFLabelControl
@ingroup Graphics

@page my_LabelConstructor New
@ingroup LFLabelControl
Construct LFLabelControl object.<br>
[Lua API]
@code
LFLabelControl LFLabelControl.New(table fontMaterial, table labelData)
@endcode
@param[in] fontMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight, alphabet, alphabetSize }<br>
@param[in] labelData <br>
{ name, posX, posY, text } <br>

@page my_LabelGetName GetName
@ingroup LFLabelControl
Get LFLabelControl name.<br>
[Lua API]
@code
string LFLabelControl:GetName()
@endcode

@page my_LabelSetIsAlive SetIsAlive
@ingroup LFLabelControl
Set object is alive or not.<br>
[Lua API]
@code
LFLabelControl:SetIsAlive(bool isAlive)
@endcode

@page my_LabelSetIsVisible SetIsVisible
@ingroup LFLabelControl
Set object is visible or not.<br>
[Lua API]
@code
LFLabelControl:SetIsVisible(bool isVisible)
@endcode
*/
luaL_Reg LFLabelControlFunctions[] =
{
	{ "New", LFLabelControlConstructor }, 
	//{ "__gc", LFLabelControlDestructor },
	{ "GetName", LFLabelControlGetName },
	{ "SetIsAlive", LFLabelControlSetIsAlive }, 
	{ "SetIsVisible", LFLabelControlSetIsVisible }, 
	{ 0, 0 }
};

luaL_Reg *GetLFLabelControlFunctions()
{
	return LFLabelControlFunctions;
}
