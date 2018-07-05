/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFMessageBoxControlLua.h"
#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\..\Graphics\LF2D\GUI\LFMessageBoxControl.h"
#include "..\..\..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::Graphics::LF2D::GUI;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFMessageBoxControlConstructor(lua_State *luaState)
{
	int paramCount = 6;
	if (LFScriptSystem::Instance()->IsParamCountOk(paramCount))
	{
		//#1 font material
		LFFontMaterial fontMaterial = LoadLFFontMaterial(paramCount, 1);

		//#2 control material
		//#3 messageBox atlas
		//#4 nonTouched atlas
		//#5 touched atlas
		LFControlMaterial messageBoxMaterial = LoadLFControlMaterialNAtlas(paramCount, 2, 3);
		LFControlMaterial controlMaterialNonTouched = LoadLFControlMaterialNAtlas(paramCount, 2, 4);
		LFControlMaterial controlMaterialTouched = LoadLFControlMaterialNAtlas(paramCount, 2, 5);

		//#6 messageBox data
		LFMessageBoxData messageBoxData;
		messageBoxData.messageBoxName = LFScriptSystem::Instance()->GetMetatableParameterValue("name", paramCount, 6, LFLuaType::LT_STRING).string;
		messageBoxData.messageLine1 = LFString(LFScriptSystem::Instance()->GetMetatableParameterValue("messageLine1", paramCount, 6, LFLuaType::LT_STRING).string);
		messageBoxData.messageLine2 = LFString(LFScriptSystem::Instance()->GetMetatableParameterValue("messageLine2", paramCount, 6, LFLuaType::LT_STRING).string);
		messageBoxData.messageLine3 = LFString(LFScriptSystem::Instance()->GetMetatableParameterValue("messageLine3", paramCount, 6, LFLuaType::LT_STRING).string);
		messageBoxData.messageType = LFString(LFScriptSystem::Instance()->GetMetatableParameterValue("messageType", paramCount, 6, LFLuaType::LT_STRING).string);

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFMessageBoxControl>(AT, fontMaterial, messageBoxMaterial, controlMaterialNonTouched, controlMaterialTouched, messageBoxData),
			sizeof(LFMessageBoxControl *));
		LFScriptSystem::Instance()->CreateMetatable(LFMessageBoxControlName);
	}

	return 1; //return user data
}

int LFMessageBoxControlGetName(lua_State *luaState)
{
	return GetName(luaState, LFMessageBoxControlName);
}

int LFMessageBoxControlSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFMessageBoxControlName);
}

int LFMessageBoxControlSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFMessageBoxControlName);
}

/**
@defgroup Graphics

@defgroup LFMessageBoxControl
@ingroup Graphics

@page my_MessageBoxConstructor New
@ingroup LFMessageBoxControl
Construct LFMessageBoxControl object.<br>
[Lua API]
@code
LFMessageBoxControl LFMessageBoxControl.New(table fontMaterial, table controlMaterial, table controlMaterialAtlasNonTouched, table controlMaterialAtlasTouched, table messageBoxData)
@endcode
@param[in] fontMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight, alphabet, alphabetSize }<br>
@param[in] controlMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight }<br>
@param[in] controlMaterialAtlasNonTouched <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] controlMaterialAtlasTouched <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] messageBoxData <br>
{ name, messageLine1, messageLine2, messageLine3, messageType:"info"|"question" } <br>

@page my_MessageBoxGetName GetName
@ingroup LFMessageBoxControl
Get LFMessageBoxControl name.<br>
[Lua API]
@code
string LFMessageBoxControl:GetName()
@endcode

@page my_MessageBoxSetIsAlive SetIsAlive
@ingroup LFMessageBoxControl
Set object is alive or not.<br>
[Lua API]
@code
LFMessageBoxControl:SetIsAlive(bool isAlive)
@endcode

@page my_MessageBoxSetIsVisible SetIsVisible
@ingroup LFMessageBoxControl
Set object is visible or not.<br>
[Lua API]
@code
LFMessageBoxControl:SetIsVisible(bool isVisible)
@endcode
*/
luaL_Reg LFMessageBoxControlFunctions[] =
{
	{ "New", LFMessageBoxControlConstructor },
	//{ "__gc", LFMessageBoxControlDestructor },
	{ "GetName", LFMessageBoxControlGetName },
	{ "SetIsAlive", LFMessageBoxControlSetIsAlive },
	{ "SetIsVisible", LFMessageBoxControlSetIsVisible },
	{ 0, 0 }
};

luaL_Reg *GetLFMessageBoxControlFunctions()
{
	return LFMessageBoxControlFunctions;
}
