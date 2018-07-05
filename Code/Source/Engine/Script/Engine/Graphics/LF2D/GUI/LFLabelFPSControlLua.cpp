/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLabelFPSControlLua.h"
#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\..\Graphics\LF2D\GUI\LFLabelFPSControl.h"
#include "..\..\..\..\..\..\Core\Math\LFRectangle.h"
#include "..\..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::Graphics::LF2D::GUI;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFLabelFPSControlConstructor(lua_State *luaState)
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
		
		labelData.digits = 4;
		labelData.text = LFString().AppendStr(0, labelData.digits);

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFLabelFPSControl>(AT, fontMaterial, labelData), sizeof(LFLabelFPSControl *));
		LFScriptSystem::Instance()->CreateMetatable(LFLabelFPSControlName);
	}

	return 1; //return user data
}

int LFLabelFPSControlGetName(lua_State *luaState)
{
	return GetName(luaState, LFLabelFPSControlName);
}

int LFLabelFPSControlSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFLabelFPSControlName);
}

int LFLabelFPSControlSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFLabelFPSControlName);
}

/**
@defgroup Graphics

@defgroup LFLabelFPSControl
@ingroup Graphics

@page my_LabelFPSConstructor New
@ingroup LFLabelFPSControl
Construct LFLabelFPSControl object.<br>
[Lua API]
@code
LFLabelFPSControl LFLabelFPSControl.New(table fontMaterial, table labelData)
@endcode
@param[in] fontMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight, alphabet, alphabetSize }<br>
@param[in] labelData <br>
{ name, posX, posY } <br>

@page my_LabelFPSGetName GetName
@ingroup LFLabelFPSControl
Get LFLabelFPSControl name.<br>
[Lua API]
@code
string LFLabelFPSControl:GetName()
@endcode

@page my_LabelFPSSetIsAlive SetIsAlive
@ingroup LFLabelFPSControl
Set object is alive or not.<br>
[Lua API]
@code
LFLabelFPSControl:SetIsAlive(bool isAlive)
@endcode

@page my_LabelFPSSetIsVisible SetIsVisible
@ingroup LFLabelFPSControl
Set object is visible or not.<br>
[Lua API]
@code
LFLabelFPSControl:SetIsVisible(bool isVisible)
@endcode
*/
luaL_Reg LFLabelFPSControlFunctions[] =
{
	{ "New", LFLabelFPSControlConstructor },
	//{ "__gc", LFLabelFPSControlDestructor },
	{ "GetName", LFLabelFPSControlGetName },
	{ "SetIsAlive", LFLabelFPSControlSetIsAlive },
	{ "SetIsVisible", LFLabelFPSControlSetIsVisible },
	{ 0, 0 }
};

luaL_Reg *GetLFLabelFPSControlFunctions()
{
	return LFLabelFPSControlFunctions;
}
