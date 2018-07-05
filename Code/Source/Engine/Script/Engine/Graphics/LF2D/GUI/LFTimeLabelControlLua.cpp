/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTimeLabelControlLua.h"
#include "MaterialLoaderLua.h"
#include "..\..\..\..\..\Script\LuaHeaders.h"
#include "..\..\..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\..\..\..\Core\Common\LFString.h"
#include "..\..\..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\..\Graphics\LF2D\GUI\LFTimeLabelControl.h"
#include "..\..\..\..\..\..\Core\Math\LFRectangle.h"
#include "..\..\..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::Graphics::LF2D::GUI;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFCore::Math;

int LFTimeLabelControlConstructor(lua_State *luaState)
{
	int paramCount = 5;
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
		labelData.digits = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("digits", paramCount, 4, LFLuaType::LT_NUMBER).number;
		labelData.text = LFString().AppendStr(0, labelData.digits);

		//#5 timeLabel data
		LFTimeLabelData timeLabelData;
		timeLabelData.minTime = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("minTime", paramCount, 5, LFLuaType::LT_NUMBER).number;
		timeLabelData.maxTime = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("maxTime", paramCount, 5, LFLuaType::LT_NUMBER).number;
		timeLabelData.interval = (int)LFScriptSystem::Instance()->GetMetatableParameterValue("interval", paramCount, 5, LFLuaType::LT_NUMBER).number;
		timeLabelData.isIncrement = LFScriptSystem::Instance()->GetMetatableParameterValue("isIncrement", paramCount, 5, LFLuaType::LT_BOOLEAN).boolean;

		LFScriptSystem::Instance()->CreateUserData(LFNew<LFTimeLabelControl>(AT, fontMaterial, controlMaterial, labelData, timeLabelData), sizeof(LFTimeLabelControl *));
		LFScriptSystem::Instance()->CreateMetatable(LFTimeLabelControlName);
	}

	return 1; //return user data
}

int LFTimeLabelControlGetName(lua_State *luaState)
{
	return GetName(luaState, LFTimeLabelControlName);
}

int LFTimeLabelControlSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFTimeLabelControlName);
}

int LFTimeLabelControlSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFTimeLabelControlName);
}

int LFTimeLabelControlGetTime(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFTimeLabelControl *self = (LFTimeLabelControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFTimeLabelControlName, 1); //#1
		LFScriptSystem::Instance()->PushNumber(self->Time());
	}

	return 1; //return Value
}

int LFTimeLabelControlSetTime(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFTimeLabelControl *self = (LFTimeLabelControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFTimeLabelControlName, 1); //#1
		int second = (int)LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		self->Time(second);
	}

	return 0; //no return value
}

int LFTimeLabelControlReset(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFTimeLabelControl *self = (LFTimeLabelControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFTimeLabelControlName, 1); //#1
		self->Reset();
	}

	return 0; //no return value
}

int LFTimeLabelControlStart(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFTimeLabelControl *self = (LFTimeLabelControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFTimeLabelControlName, 1); //#1
		self->Start();
	}

	return 0; //no return value
}

int LFTimeLabelControlStop(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFTimeLabelControl *self = (LFTimeLabelControl *)LFScriptSystem::Instance()->GetUserDataParameter(LFTimeLabelControlName, 1); //#1
		self->Stop();
	}

	return 0; //no return value
}

int LFTimeLabelControlOnTimeOut(lua_State *luaState)
{
	return 0; //no return value
}

/**
@defgroup Graphics

@defgroup LFTimeLabelControl
@ingroup Graphics

@page my_TimeLabelConstructor New
@ingroup LFTimeLabelControl
Construct LFTimeLabelControl object.<br>
[Lua API]
@code
LFTimeLabelControl LFTimeLabelControl.New(table fontMaterial, table controlMaterial, table controlMaterialAtlas, table labelData, table timeLabelData)
@endcode
@param[in] fontMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight, alphabet, alphabetSize }<br>
@param[in] controlMaterial <br>
{ textureName, textureWidth, textureHeight, atlasWidth, atlasHeight }<br>
@param[in] controlMaterialAtlas <br>
{ posX, posY, sizeX, sizeY }<br>
@param[in] labelData <br>
{ labelName, posX, posY, value, digits } <br>
@param[in] timeLabelData <br>
{ minTime (sec), maxTime (sec), interval (sec), isIncrement } <br>

@page my_TimeLabelGetName GetName
@ingroup LFTimeLabelControl
Get LFTimeLabelControl name.<br>
[Lua API]
@code
string LFTimeLabelControl:GetName()
@endcode

@page my_TimeLabelSetIsAlive SetIsAlive
@ingroup LFTimeLabelControl
Set object is alive or not.<br>
[Lua API]
@code
LFTimeLabelControl:SetIsAlive(bool isAlive)
@endcode

@page my_TimeLabelSetIsVisible SetIsVisible
@ingroup LFTimeLabelControl
Set object is visible or not.<br>
[Lua API]
@code
LFTimeLabelControl:SetIsVisible(bool isVisible)
@endcode

@page my_TimeLabelGetTime GetTime
@ingroup LFTimeLabelControl
Get time (second).<br>
[Lua API]
@code
number LFTimeLabelControl:GetTime()
@endcode

@page my_TimeLabelSetTime SetTime
@ingroup LFTimeLabelControl
Set time (second).<br>
[Lua API]
@code
LFTimeLabelControl:SetTime(number second)
@endcode

@page my_TimeLabelReset Reset
@ingroup LFTimeLabelControl
Reset min or max time value, and stop timing.<br>
[Lua API]
@code
LFTimeLabelControl:Reset()
@endcode

@page my_TimeLabelStart Start
@ingroup LFTimeLabelControl
Start timing increment or decrement.<br>
[Lua API]
@code
LFTimeLabelControl:Start()
@endcode

@page my_TimeLabelStop Stop
@ingroup LFTimeLabelControl
Pause timing.<br>
[Lua API]
@code
LFTimeLabelControl:Stop()
@endcode

@page my_TimeLabelOnTimeOut OnTimeOut
@ingroup LFTimeLabelControl
Time out event.<br>
[Lua API]<br>
@code
function LFTimeLabelControl:OnTimeOut(LFTimeLabelControl sender)
@endcode
*/
luaL_Reg LFTimeLabelControlFunctions[] =
{
	{ "New", LFTimeLabelControlConstructor },
	//{ "__gc", LFTimeLabelControlDestructor },
	{ "GetName", LFTimeLabelControlGetName },
	{ "SetIsAlive", LFTimeLabelControlSetIsAlive },
	{ "SetIsVisible", LFTimeLabelControlSetIsVisible },
	{ "GetTime", LFTimeLabelControlGetTime },
	{ "SetTime", LFTimeLabelControlSetTime },
	{ "Reset", LFTimeLabelControlReset },
	{ "Start", LFTimeLabelControlStart },
	{ "Stop", LFTimeLabelControlStop },
	{ LFTimeLabelOnTimeOutName, LFTimeLabelControlOnTimeOut },
	{ 0, 0 }
};

luaL_Reg *GetLFTimeLabelControlFunctions()
{
	return LFTimeLabelControlFunctions;
}
