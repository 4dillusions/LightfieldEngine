/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFCheckButtonControlLua.h"
#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\..\Graphics\LF2D\GUI\LFCheckButtonControl.h"
#include "..\..\..\..\..\..\Core\Math\LFRectangle.h"
#include "..\..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::Graphics::LF2D::GUI;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFCheckButtonControlConstructor(lua_State *luaState)
{
	int paramCount = 6;
	if (LFScriptSystem::Instance()->IsParamCountOk(paramCount))
	{
		//#1 control material
		//#2 unChecked atlas
		//#3 checked atlas
		//#4 unCheckedTouched atlas
		//#5 checkedTouched atlas
		LFControlMaterial controlMaterialUnChecked = LoadLFControlMaterialNAtlas(paramCount, 1, 2);
		LFControlMaterial controlMaterialChecked = LoadLFControlMaterialNAtlas(paramCount, 1, 3);
		LFControlMaterial controlMaterialUnCheckedTouched = LoadLFControlMaterialNAtlas(paramCount, 1, 4);
		LFControlMaterial controlMaterialCheckedTouched = LoadLFControlMaterialNAtlas(paramCount, 1, 5);

		//#6 label data
		LFLabelData labelData;
		labelData.text = LFString(LFScriptSystem::Instance()->GetMetatableParameterValue("name", paramCount, 6, LFLuaType::LT_STRING).string);
		labelData.labelName = LFScriptSystem::Instance()->GetMetatableParameterValue("name", paramCount, 6, LFLuaType::LT_STRING).string;
		labelData.posX = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posX", paramCount, 6, LFLuaType::LT_NUMBER).number;
		labelData.posY = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posY", paramCount, 6, LFLuaType::LT_NUMBER).number;
		bool isChecked = LFScriptSystem::Instance()->GetMetatableParameterValue("isChecked", paramCount, 6, LFLuaType::LT_BOOLEAN).boolean;

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFCheckButtonControl>(AT, controlMaterialUnChecked, controlMaterialChecked, controlMaterialUnCheckedTouched, 
			controlMaterialCheckedTouched, labelData, isChecked), sizeof(LFCheckButtonControl *));
		LFScriptSystem::Instance()->CreateMetatable(LFCheckButtonControlName);
	}

	return 1; //return user data
}

int LFCheckButtonControlGetName(lua_State *luaState)
{
	return GetName(luaState, LFCheckButtonControlName);
}

int LFCheckButtonControlSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFCheckButtonControlName);
}

int LFCheckButtonControlSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFCheckButtonControlName);
}

int LFCheckButtonControlSetIsChecked(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFCheckButtonControl *self = (LFCheckButtonControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFCheckButtonControlName, 1); //#1
		bool isChecked = LFScriptSystem::Instance()->GetBooleanParameter(2); //#2

		self->IsChecked(isChecked);
	}

	return 0; //no return value
}

int LFCheckButtonControlGetIsChecked(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFCheckButtonControl *self = (LFCheckButtonControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFCheckButtonControlName, 1); //#1
		LFScriptSystem::Instance()->PushBoolean(self->IsChecked());
	}

	return 1; //return IsChecked
}

int LFCheckButtonControlOnCheckChanged(lua_State *luaState)
{
	return 0; //no return value
}

/**
@defgroup Graphics

@defgroup LFCheckButtonControl
@ingroup Graphics

@page my_CheckButtonConstructor New
@ingroup LFCheckButtonControl
Construct LFCheckButtonControl object.<br>
[Lua API]
@code
LFCheckButtonControl LFCheckButtonControl.New(table controlMaterial, table controlMaterialUnChecked, table controlMaterialChecked, table controlMaterialUnCheckedTouched, table controlMaterialCheckedTouched, table labelData)
@endcode
@param[in] controlMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight }<br>
@param[in] controlMaterialUnChecked <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] controlMaterialChecked <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] controlMaterialUnCheckedTouched <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] controlMaterialCheckedTouched <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] labelData <br>
{ name, posX, posY, isChecked } <br>

@page my_CheckButtonGetName GetName
@ingroup LFCheckButtonControl
Get LFCheckButtonControl name.<br>
[Lua API]
@code
string LFCheckButtonControl:GetName()
@endcode

@page my_CheckButtonSetIsAlive SetIsAlive
@ingroup LFCheckButtonControl
Set object is alive or not.<br>
[Lua API]
@code
LFCheckButtonControl:SetIsAlive(bool isAlive)
@endcode

@page my_CheckButtonSetIsVisible SetIsVisible
@ingroup LFCheckButtonControl
Set object is visible or not.<br>
[Lua API]
@code
LFCheckButtonControl:SetIsVisible(bool isVisible)
@endcode

@page my_CheckButtonSetIsChecked SetIsChecked
@ingroup LFCheckButtonControl
Set object is checked or not.<br>
[Lua API]
@code
LFCheckButtonControl:SetIsChecked(bool isChecked)
@endcode

@page my_CheckButtonGetIsChecked GetIsChecked
@ingroup LFCheckButtonControl
Get LFCheckButtonControl checked.<br>
[Lua API]
@code
bool LFCheckButtonControl:GetIsChecked()
@endcode

@page my_CheckButtonOnCheckChanged OnCheckChanged
@ingroup LFCheckButtonControl
Check changed event.<br>
[Lua API]<br>
@code
function LFCheckButtonControl:OnCheckChanged(LFCheckButtonControl sender)
@endcode
*/
luaL_Reg LFCheckButtonControlFunctions[] =
{
	{ "New", LFCheckButtonControlConstructor },
	//{ "__gc", LFCheckButtonControlDestructor },
	{ "GetName", LFCheckButtonControlGetName },
	{ "SetIsAlive", LFCheckButtonControlSetIsAlive },
	{ "SetIsVisible", LFCheckButtonControlSetIsVisible },
	{ "SetIsChecked", LFCheckButtonControlSetIsChecked },
	{ "GetIsChecked", LFCheckButtonControlGetIsChecked },
	{ LFCheckButtonControlOnCheckChangedName, LFCheckButtonControlOnCheckChanged },
	{ 0, 0 }
};

luaL_Reg *GetLFCheckButtonControlFunctions()
{
	return LFCheckButtonControlFunctions;
}
