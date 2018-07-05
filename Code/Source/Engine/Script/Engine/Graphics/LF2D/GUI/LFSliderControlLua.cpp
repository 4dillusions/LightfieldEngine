/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFSliderControlLua.h"
#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\..\Graphics\LF2D\GUI\LFSliderControl.h"
#include "..\..\..\..\..\..\Core\\Math\LFRectangle.h"
#include "..\..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::Graphics::LF2D::GUI;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFSliderControlConstructor(lua_State *luaState)
{
	int paramCount = 4;
	if (LFScriptSystem::Instance()->IsParamCountOk(paramCount))
	{
		//#1 control material
		//#2 potmeter atlas
		//#3 potmeter touched atlas
		LFControlMaterial controlMaterialPotmeter = LoadLFControlMaterialNAtlas(paramCount, 1, 2);
		LFControlMaterial controlMaterialPotmeterTouched = LoadLFControlMaterialNAtlas(paramCount, 1, 3);

		//#4 label data
		LFLabelData labelData;
		labelData.text = LFString(LFScriptSystem::Instance()->GetMetatableParameterValue("name", paramCount, 4, LFLuaType::LT_STRING).string);
		labelData.labelName = LFScriptSystem::Instance()->GetMetatableParameterValue("name", paramCount, 4, LFLuaType::LT_STRING).string;
		labelData.posX = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posX", paramCount, 4, LFLuaType::LT_NUMBER).number;
		labelData.posY = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("posY", paramCount, 4, LFLuaType::LT_NUMBER).number;
		int width = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("width", paramCount, 4, LFLuaType::LT_NUMBER).number;
		int value = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("value", paramCount, 4, LFLuaType::LT_NUMBER).number;

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFSliderControl>(AT, controlMaterialPotmeter, controlMaterialPotmeterTouched,
			labelData, width, value), sizeof(LFSliderControl *));
		LFScriptSystem::Instance()->CreateMetatable(LFSliderControlName);
	}

	return 1; //return user data
}

int LFSliderControlGetName(lua_State *luaState)
{
	return GetName(luaState, LFSliderControlName);
}

int LFSliderControlSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFSliderControlName);
}

int LFSliderControlSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFSliderControlName);
}

int LFSliderControlSetValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFSliderControl *self = (LFSliderControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFSliderControlName, 1); //#1
		double value = LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		self->Value((int)value);
	}

	return 0; //no return value
}

int LFSliderControlGetValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFSliderControl *self = (LFSliderControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFSliderControlName, 1); //#1
		LFScriptSystem::Instance()->PushNumber(self->Value());
	}

	return 1; //return Value
}

int LFSliderControlOnValueChanged(lua_State *luaState)
{
	return 0; //no return value
}

/**
@defgroup Graphics

@defgroup LFSliderControl
@ingroup Graphics

@page my_SliderConstructor New
@ingroup LFSliderControl
Construct LFSliderControl object.<br>
[Lua API]
@code
LFSliderControl LFSliderControl.New(table controlMaterial, table controlMaterialPotmeter, table controlMaterialPotmeterTouched, table labelData)
@endcode
@param[in] controlMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight }<br>
@param[in] controlMaterialPotmeter <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] controlMaterialPotmeterTouched <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] labelData <br>
{ name, posX, posY, width, value } <br>

@page my_SliderGetName GetName
@ingroup LFSliderControl
Get LFSliderControl name.<br>
[Lua API]
@code
string LFSliderControl:GetName()
@endcode

@page my_SliderSetIsAlive SetIsAlive
@ingroup LFSliderControl
Set object is alive or not.<br>
[Lua API]
@code
LFSliderControl:SetIsAlive(bool isAlive)
@endcode

@page my_SliderSetIsVisible SetIsVisible
@ingroup LFSliderControl
Set object is visible or not.<br>
[Lua API]
@code
LFSliderControl:SetIsVisible(bool isVisible)
@endcode

@page my_SliderSetValue SetValue
@ingroup LFSliderControl
Set value 1 to 100 percent.<br>
[Lua API]
@code
LFSliderControl:SetValue(number Value)
@endcode

@page my_SliderGetValue GetValue
@ingroup LFSliderControl
Get value percent.<br>
[Lua API]
@code
number LFSliderControl:GetValue()
@endcode

@page my_SliderOnValueChanged OnValueChanged
@ingroup LFSliderControl
Check changed event.<br>
[Lua API]<br>
@code
function LFSliderControl:OnValueChanged(LFSliderControl sender)
@endcode
*/
luaL_Reg LFSliderControlFunctions[] =
{
	{ "New", LFSliderControlConstructor },
	//{ "__gc", LFSliderControlDestructor },
	{ "GetName", LFSliderControlGetName },
	{ "SetIsAlive", LFSliderControlSetIsAlive },
	{ "SetIsVisible", LFSliderControlSetIsVisible },
	{ "SetValue", LFSliderControlSetValue },
	{ "GetValue", LFSliderControlGetValue },
	{ LFSliderControlOnValueChangedName, LFSliderControlOnValueChanged },
	{ 0, 0 }
};

luaL_Reg *GetLFSliderControlFunctions()
{
	return LFSliderControlFunctions;
}
