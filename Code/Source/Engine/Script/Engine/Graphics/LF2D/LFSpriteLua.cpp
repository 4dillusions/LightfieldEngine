/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSpriteLua.h"
#include "..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\Graphics\LF2D\LFSprite.h"
#include "..\..\..\..\..\Core\Math\LFRectangle.h"
#include "..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::Graphics::LF2D;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFSpriteConstructor(lua_State *luaState)
{
	int paramCount = 3;
	if (LFScriptSystem::Instance()->IsParamCountOk(paramCount))
	{
		//#1 material
		const char *textureName = LFScriptSystem::Instance()->GetMetatableParameterValue("textureName", paramCount, 1, LFLuaType::LT_STRING).string;
		double textureWidth = LFScriptSystem::Instance()->GetMetatableParameterValue("textureWidth", paramCount, 1, LFLuaType::LT_NUMBER).number;
		double textureHeight = LFScriptSystem::Instance()->GetMetatableParameterValue("textureHeight", paramCount, 1, LFLuaType::LT_NUMBER).number;
		double atlasWidth = LFScriptSystem::Instance()->GetMetatableParameterValue("atlasWidth", paramCount, 1, LFLuaType::LT_NUMBER).number;
		double atlasHeight = LFScriptSystem::Instance()->GetMetatableParameterValue("atlasHeight", paramCount, 1, LFLuaType::LT_NUMBER).number;

		//#2 atlas quads data
		double atlasPosX = LFScriptSystem::Instance()->GetMetatableParameterValue("posX", paramCount, 2, LFLuaType::LT_NUMBER).number;
		double atlasPosY = LFScriptSystem::Instance()->GetMetatableParameterValue("posY", paramCount, 2, LFLuaType::LT_NUMBER).number;

		//#3 sprite data
		const char *name = LFScriptSystem::Instance()->GetMetatableParameterValue("name", paramCount, 3, LFLuaType::LT_STRING).string;
		double posX = LFScriptSystem::Instance()->GetMetatableParameterValue("posX", paramCount, 3, LFLuaType::LT_NUMBER).number;
		double posY = LFScriptSystem::Instance()->GetMetatableParameterValue("posY", paramCount, 3, LFLuaType::LT_NUMBER).number;

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFSprite>(AT, LFString(name), LFString(textureName), LFRectangle(posX, posY, textureWidth, textureHeight), 
			LFRectangle(atlasPosX, atlasPosY, atlasWidth, atlasHeight)), sizeof(LFSprite *));
		LFScriptSystem::Instance()->CreateMetatable(LFSpriteName);
	}

	return 1; //return user data
}

int LFSpriteGetName(lua_State *luaState)
{
	return GetName(luaState, LFSpriteName);
}

int LFSpriteSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFSpriteName);
}

int LFSpriteSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFSpriteName);
}

/**
@defgroup Graphics

@defgroup LFSprite
@ingroup Graphics

@page my_SpriteConstructor New
@ingroup LFSprite
Construct LFSprite object.<br>
[Lua API]
@code
LFSprite LFSprite.New(table material, table atlasQuadsData, table spriteData)
@endcode
@param[in] material <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight }<br>
@param[in] atlasQuadsData <br>
{ posX, posY } <br>
@param[in] spriteData <br>
{ name, posX, posY } <br>

@page my_SpriteGetName GetName
@ingroup LFSprite
Get LFSprite name.<br>
[Lua API]
@code
string LFSprite:GetName()
@endcode

@page my_SpriteSetIsAlive SetIsAlive
@ingroup LFSprite
Set object is alive or not.<br>
[Lua API]
@code
LFSprite:SetIsAlive(bool isAlive)
@endcode

@page my_SpriteSetIsVisible SetIsVisible
@ingroup LFSprite
Set object is visible or not.<br>
[Lua API]
@code
LFSprite:SetIsVisible(bool isVisible)
@endcode
*/
luaL_Reg LFSpriteFunctions[] =
{
	{ "New", LFSpriteConstructor }, 
	//{ "__gc", LFScreenDestructor }, 
	{ "GetName", LFSpriteGetName },
	{ "SetIsAlive", LFSpriteSetIsAlive }, 
	{ "SetIsVisible", LFSpriteSetIsVisible }, 
	{ 0, 0 }
};

luaL_Reg *GetLFSpriteFunctions()
{
	return LFSpriteFunctions;
}
