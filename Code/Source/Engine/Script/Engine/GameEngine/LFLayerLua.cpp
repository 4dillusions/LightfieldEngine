/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLayerLua.h"
#include "..\..\Engine\Graphics\LF2D\LFSpriteLua.h"
#include "..\..\..\Script\LuaHeaders.h"
#include "..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\GameEngine\LFLayer.h"
#include "..\..\..\GameEngine\LF2DObject.h"
#include "..\..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\..\Engine\Script\Core\Common\LFGameCompositComponentLua.h"
#include "..\..\..\..\Engine\Script\Core\Common\LFGameComponentLua.h"
#include "..\..\..\Graphics\LF2D\LFSprite.h"
#include "..\..\Engine\Graphics\LF2D\GUI\LFLabelControlLua.h"
#include "..\..\Engine\Graphics\LF2D\GUI\LFNumberLabelControlLua.h"
#include "..\..\Engine\Graphics\LF2D\GUI\LFLabelFPSControlLua.h"
#include "..\..\Engine\Graphics\LF2D\GUI\LFLevelLabelControlLua.h"
#include "..\..\Engine\Graphics\LF2D\GUI\LFTimeLabelControlLua.h"
#include "..\..\Engine\Graphics\LF2D\GUI\LFButtonControlLua.h"
#include "..\..\Engine\Graphics\LF2D\GUI\LFCheckButtonControlLua.h"
#include "..\..\Engine\Graphics\LF2D\GUI\LFSliderControlLua.h"
#include "..\..\Engine\Graphics\LF2D\GUI\LFMessageBoxControlLua.h"
#include "..\..\..\Graphics\LF2D\GUI\LFLabelControl.h"
#include "..\..\..\Graphics\LF2D\GUI\LFNumberLabelControl.h"
#include "..\..\..\Graphics\LF2D\GUI\LFLabelFPSControl.h"
#include "..\..\..\Graphics\LF2D\GUI\LFLevelLabelControl.h"
#include "..\..\..\Graphics\LF2D\GUI\LFTimeLabelControl.h"
#include "..\..\..\Graphics\LF2D\GUI\LFButtonControl.h"
#include "..\..\..\Graphics\LF2D\GUI\LFCheckButtonControl.h"
#include "..\..\..\Graphics\LF2D\GUI\LFSliderControl.h"
#include "..\..\..\Graphics\LF2D\GUI\LFMessageBoxControl.h"

using namespace LFEngine::Script;
using namespace LFEngine::GameEngine;
using namespace LFCore::Common;
using namespace LFEngine::Graphics::LF2D;
using namespace LFEngine::Graphics::LF2D::GUI;

int LFLayerConstructor(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		LFString name = LFScriptSystem::Instance()->GetStringParameter(1); //#1
	
		LFScriptSystem::Instance()->CreateUserData(LFNew<LFLayer>(AT, name), sizeof(LFLayer *));
		LFScriptSystem::Instance()->CreateMetatable(LFLayerName);
	}

	return 1; //return user data
}

int LFLayerGetName(lua_State *luaState)
{
	return GetName(luaState, LFLayerName);
}

int LFLayerAdd2dObject(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFLayer *self = (LFLayer *)LFScriptSystem::Instance()->GetUserDataParameter(LFLayerName, 1); //#1
		
		//#2
		void *object = nullptr;

		if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFSpriteName, 2))
		{
			object = obj;
		}
		else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFLabelControlName, 2))
		{
			object = obj;
			((LFLabelControl *)object)->AttachChildren(self);
		}
		else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFNumberLabelControlName, 2))
		{
			object = obj;
			((LFNumberLabelControl *)object)->AttachChildren(self);
		}
		else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFLabelFPSControlName, 2))
		{
			object = obj;
			((LFLabelFPSControl *)object)->AttachChildren(self);
		}
		else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFLevelLabelControlName, 2))
		{
			object = obj;
			((LFLevelLabelControl *)object)->AttachChildren(self);
		}
		else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFTimeLabelControlName, 2))
		{
			object = obj;
			((LFTimeLabelControl *)object)->AttachChildren(self);
		}
		else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFButtonControlName, 2))
		{
			object = obj;
			((LFButtonControl *)object)->AttachChildren(self);
		}
		else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFCheckButtonControlName, 2))
		{
			object = obj;
			((LFCheckButtonControl *)object)->AttachChildren(self);
		}
		else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFSliderControlName, 2))
		{
			object = obj;
			((LFSliderControl *)object)->AttachChildren(self);
		}
		else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter(LFMessageBoxControlName, 2))
		{
			object = obj;
			((LFMessageBoxControl *)object)->AttachChildren(self);
		}
		
		self->Add((LFGameComponent *)object);
	}

	return 0; //no return value
}

int LFLayerFind2dObject(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		LFLayer *self = (LFLayer *)LFScriptSystem::Instance()->GetUserDataParameter(LFLayerName, 1); //#1
		LFString name = LFScriptSystem::Instance()->GetStringParameter(2); //#2

		LF2DObject *object = self->Find2DObject(name);

		if (object == nullptr)
		{
			LFScriptSystem::Instance()->PushNil();
			return 1; //return nil value
		}

		if (dynamic_cast<LFSprite *>(object))
		{
			LFScriptSystem::Instance()->CreateUserData((LFSprite *)object, sizeof(LFSprite *));
			LFScriptSystem::Instance()->CreateMetatable(LFSpriteName);
		}
		else if (dynamic_cast<LFLabelFPSControl *>(object)) //inherited LFNumberLabelControl
		{
			LFScriptSystem::Instance()->CreateUserData((LFLabelFPSControl *)object, sizeof(LFLabelFPSControl *));
			LFScriptSystem::Instance()->CreateMetatable(LFLabelFPSControlName);
		}
		else if (dynamic_cast<LFNumberLabelControl *>(object)) //inherited LFLabelControl
		{
			LFScriptSystem::Instance()->CreateUserData((LFNumberLabelControl *)object, sizeof(LFNumberLabelControl *));
			LFScriptSystem::Instance()->CreateMetatable(LFNumberLabelControlName);
		}
		else if (dynamic_cast<LFTimeLabelControl *>(object)) //inherited LFLevelLabelControl
		{
			LFScriptSystem::Instance()->CreateUserData((LFTimeLabelControl *)object, sizeof(LFTimeLabelControl *));
			LFScriptSystem::Instance()->CreateMetatable(LFTimeLabelControlName);
		}
		else if (dynamic_cast<LFLevelLabelControl *>(object)) //inherited LFControl
		{
			LFScriptSystem::Instance()->CreateUserData((LFLevelLabelControl *)object, sizeof(LFLevelLabelControl *));
			LFScriptSystem::Instance()->CreateMetatable(LFLevelLabelControlName);
		}
		else if (dynamic_cast<LFLabelControl *>(object)) //inherited LFControl
		{
			LFScriptSystem::Instance()->CreateUserData((LFLabelControl *)object, sizeof(LFLabelControl *));
			LFScriptSystem::Instance()->CreateMetatable(LFLabelControlName);
		}
		else if (dynamic_cast<LFButtonControl *>(object)) //inherited LFControl
		{
			LFScriptSystem::Instance()->CreateUserData((LFButtonControl *)object, sizeof(LFButtonControl *));
			LFScriptSystem::Instance()->CreateMetatable(LFButtonControlName);
		}
		else if (dynamic_cast<LFCheckButtonControl *>(object)) //inherited LFControl
		{
			LFScriptSystem::Instance()->CreateUserData((LFCheckButtonControl *)object, sizeof(LFCheckButtonControl *));
			LFScriptSystem::Instance()->CreateMetatable(LFCheckButtonControlName);
		}
		else if (dynamic_cast<LFSliderControl *>(object)) //inherited LFControl
		{
			LFScriptSystem::Instance()->CreateUserData((LFSliderControl *)object, sizeof(LFSliderControl *));
			LFScriptSystem::Instance()->CreateMetatable(LFSliderControlName);
		}
		else if (dynamic_cast<LFMessageBoxControl *>(object)) //inherited LFControl
		{
			LFScriptSystem::Instance()->CreateUserData((LFMessageBoxControl *)object, sizeof(LFMessageBoxControl *));
			LFScriptSystem::Instance()->CreateMetatable(LFMessageBoxControlName);
		}
	}

	return 1; //return user data
}

int LFLayerWriteComponentNames(lua_State *luaState)
{
	return WriteOutputComponentNames(luaState, LFLayerName);
}

int LFLayerGetIsAlive(lua_State *luaState)
{
	return GetIsAlive(luaState, LFLayerName);
}

int LFLayerSetIsAlive(lua_State *luaState)
{
	return SetIsAlive(luaState, LFLayerName);
}

int LFLayerGetIsVisible(lua_State *luaState)
{
	return GetIsVisible(luaState, LFLayerName);
}

int LFLayerSetIsVisible(lua_State *luaState)
{
	return SetIsVisible(luaState, LFLayerName);
}

/**
@defgroup GameEngine

@defgroup LFLayer
@ingroup GameEngine

@page my_LayerConstructor New
@ingroup LFLayer
Construct LFLayer object.<br>
[Lua API]
@code
LFLayer LFLayer.New(string name)
@endcode

@page my_LayerGetName GetName
@ingroup LFLayer
Get LFLayer name.<br>
[Lua API]
@code
string LFLayer:GetName()
@endcode

@page my_LayerFind2DObject Find2DObject
@ingroup LFLayer
Get LFSprite in LFLayer.<br>
[Lua API]
@code
LFSprite LFLayer:Find2DObject(string name)
@endcode

@page my_LayerAdd2DObject Add2DObject
@ingroup LFLayer
Add LFSprite to LFLayer.<br>
[Lua API]
@code
LFLayer:Add2DObject(LFSprite object2D)
@endcode

@page my_LayerWriteComponentNames WriteComponentNames
@ingroup LFLayer
Write component names in LFLayer.<br>
[Lua API]
@code
LFLayer:WriteComponentNames()
@endcode

@page my_LayerGetIsAlive GetIsAlive
@ingroup LFLayer
Get object is alive or not.<br>
[Lua API]
@code
bool LFLayer:GetIsAlive()
@endcode

@page my_LayerSetIsAlive SetIsAlive
@ingroup LFLayer
Set object is alive or not.<br>
[Lua API]
@code
LFLayer:SetIsAlive(bool isAlive)
@endcode

@page my_LayerGetIsVisible GetIsVisible
@ingroup LFLayer
Get object is visible or not.<br>
[Lua API]
@code
bool LFLayer:GetIsVisible()
@endcode

@page my_LayerSetIsVisible SetIsVisible
@ingroup LFLayer
Set object is visible or not.<br>
[Lua API]
@code
LFLayer:SetIsVisible(bool isVisible)
@endcode
*/
luaL_Reg LFLayerFunctions[] =
{
	{ "New", LFLayerConstructor }, 
	//{ "__gc", LFLayerDestructor }, 
	{ "GetName", LFLayerGetName }, 
	{ "Find2dObject", LFLayerFind2dObject },
	{ "Add2dObject", LFLayerAdd2dObject }, 
	{ "WriteComponentNames", LFLayerWriteComponentNames },
	{ "GetIsAlive", LFLayerGetIsAlive },
	{ "SetIsAlive", LFLayerSetIsAlive }, 
	{ "GetIsVisible", LFLayerGetIsVisible },
	{ "SetIsVisible", LFLayerSetIsVisible }, 
	{ 0, 0 }
};

luaL_Reg *GetLFLayerFunctions()
{
	return LFLayerFunctions;
}
