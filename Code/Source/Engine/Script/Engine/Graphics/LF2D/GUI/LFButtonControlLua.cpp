/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFButtonControlLua.h"
#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\..\Graphics\LF2D\GUI\LFButtonControl.h"
#include "..\..\..\..\..\..\Core\Math\LFRectangle.h"
#include "..\..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::Graphics::LF2D::GUI;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFButtonControlConstructor(lua_State *luaState)
{
	int paramCount = 5;
	if (LFScriptSystem::Instance()->IsParamCountOk(paramCount))
	{
		//#1 font material
		LFFontMaterial fontMaterial = LoadLFFontMaterial(paramCount, 1);

		//#2 control material
		//#3 nonTouched atlas
		//#4 touched atlas
		LFControlMaterial controlMaterialNonTouched = LoadLFControlMaterialNAtlas(paramCount, 2, 3);
		LFControlMaterial controlMaterialTouched = LoadLFControlMaterialNAtlas(paramCount, 2, 4);

		//#5 label data
		LFLabelData labelData;
		labelData.labelName = LFScriptSystem::Instance()->GetMetatableParameterValue("name", paramCount, 5, LFLuaType::LT_STRING).string;
		labelData.posX = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posX", paramCount, 5, LFLuaType::LT_NUMBER).number;
		labelData.posY = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posY", paramCount, 5, LFLuaType::LT_NUMBER).number;
		labelData.text = LFString(LFScriptSystem::Instance()->GetMetatableParameterValue("text", paramCount, 5, LFLuaType::LT_STRING).string);

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFButtonControl>(AT, fontMaterial, controlMaterialNonTouched, controlMaterialTouched, labelData), sizeof(LFButtonControl *));
		LFScriptSystem::Instance()->CreateMetatable(LFButtonControlName);
	}

	return 1; //return user data
}

int LFButtonControlGetName(lua_State *luaState)
{
	return GetName(luaState, LFButtonControlName);
}

int LFButtonControlSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFButtonControlName);
}

int LFButtonControlSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFButtonControlName);
}

/**
@defgroup Graphics

@defgroup LFButtonControl
@ingroup Graphics

@page my_ButtonConstructor New
@ingroup LFButtonControl
Construct LFButtonControl object.<br>
[Lua API]
@code
LFButtonControl LFButtonControl.New(table fontMaterial, table controlMaterial, table controlMaterialAtlasNonTouched, table controlMaterialAtlasTouched, table labelData)
@endcode
@param[in] fontMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight, alphabet, alphabetSize }<br>
@param[in] controlMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight }<br>
@param[in] controlMaterialAtlasNonTouched <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] controlMaterialAtlasTouched <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] labelData <br>
{ name, posX, posY, text } <br>

@page my_ButtonGetName GetName
@ingroup LFButtonControl
Get LFButtonControl name.<br>
[Lua API]
@code
string LFButtonControl:GetName()
@endcode

@page my_ButtonSetIsAlive SetIsAlive
@ingroup LFButtonControl
Set object is alive or not.<br>
[Lua API]
@code
LFButtonControl:SetIsAlive(bool isAlive)
@endcode

@page my_ButtonSetIsVisible SetIsVisible
@ingroup LFButtonControl
Set object is visible or not.<br>
[Lua API]
@code
LFButtonControl:SetIsVisible(bool isVisible)
@endcode
*/
luaL_Reg LFButtonControlFunctions[] =
{
	{ "New", LFButtonControlConstructor },
	//{ "__gc", LFButtonControlDestructor },
	{ "GetName", LFButtonControlGetName },
	{ "SetIsAlive", LFButtonControlSetIsAlive },
	{ "SetIsVisible", LFButtonControlSetIsVisible },
	{ 0, 0 }
};

luaL_Reg *GetLFButtonControlFunctions()
{
	return LFButtonControlFunctions;
}
