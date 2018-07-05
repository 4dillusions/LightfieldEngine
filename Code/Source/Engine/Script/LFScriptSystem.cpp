/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFScriptSystem.h"
#include "LuaHeaders.h"
#include "..\..\Core\Common\LFMemoryManager.h"
#include "..\..\Core\Common\LFVFSManager.h"
#include "..\..\Core\\IO\LFLogger.h"
#include "..\..\Core\\IO\LFFile.h"
#include "..\Common\LFExtensions.h"
#include "Core\Common\LFTimerLua.h"
#include "Core\IO\LFLoggerLua.h"
#include "Engine\GameEngine\LFGameLua.h"
#include "Engine\GameEngine\LFSceneGraphLua.h"
#include "Engine\GameEngine\LFScreenLua.h"
#include "Engine\GameEngine\LFLayerLua.h"
#include "Engine\Graphics\LF2D\LFSpriteLua.h"
#include "Engine\Graphics\LF2D\GUI\LFLabelControlLua.h"
#include "Engine\Graphics\LF2D\GUI\LFNumberLabelControlLua.h"
#include "Engine\Graphics\LF2D\GUI\LFLabelFPSControlLua.h"
#include "Engine\Graphics\LF2D\GUI\LFLevelLabelControlLua.h"
#include "Engine\Graphics\LF2D\GUI\LFTimeLabelControlLua.h"
#include "Engine\Graphics\LF2D\GUI\LFButtonControlLua.h"
#include "Engine\Graphics\LF2D\GUI\LFCheckButtonControlLua.h"
#include "Engine\Graphics\LF2D\GUI\LFSliderControlLua.h"
#include "Engine\Graphics\LF2D\GUI\LFMessageBoxControlLua.h"
#include "Engine\Input\LFInputLua.h"
#include "Engine\Audio\LFAudioLua.h"
#include "System\LFScriptSystemLua.h"

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Script
{
	LFScriptSystem *LFScriptSystem::instance = nullptr;

	LFScriptSystem::LFScriptSystem()
	{
		luaState = luaL_newstate();
		RegisterAllWrappers();
		
		luaL_requiref(luaState, "_G", luaopen_base, 1); //#1
		//luaL_requiref(luaState, LUA_LOADLIBNAME, luaopen_package, 1);
		//luaL_requiref(luaState, LUA_COLIBNAME, luaopen_coroutine, 1);
		//luaL_requiref(luaState, LUA_TABLIBNAME, luaopen_table, 1);
		//luaL_requiref(luaState, LUA_IOLIBNAME, luaopen_io, 1);
		//luaL_requiref(luaState, LUA_OSLIBNAME, luaopen_os, 1);
		luaL_requiref(luaState, LUA_STRLIBNAME, luaopen_string, 1); //#2
		//luaL_requiref(luaState, LUA_BITLIBNAME, luaopen_bit32, 1);
		luaL_requiref(luaState, LUA_MATHLIBNAME, luaopen_math, 1); //#3
		//luaL_requiref(luaState, LUA_DBLIBNAME, luaopen_debug, 1);
		lua_pop(luaState, 3);
	}

	LFScriptSystem::~LFScriptSystem()
	{
		lua_close(luaState);	
	}

	void LFScriptSystem::CreateInstance()
	{
		if (instance == nullptr)
		{
			LFLogger::Instance().WriteOutput("Create ScriptEngine");
			instance = LFNew<LFScriptSystem>(AT);
		}
	}

	void LFScriptSystem::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			LFLogger::Instance().WriteOutput("Release ScriptEngine");
			LFDelete(instance);
		}
	}

	void LFScriptSystem::RegisterAllWrappers()
	{
		//Common
		RegisterMetatable(LFTimerName, GetLFTimerFunctions(), true);

		//IO
		RegisterMetatable(LFLoggerName, GetLFLoggerFunctions(), true);

		//GameEngine
		RegisterMetatable(LFGameName, GetLFGameFunctions(), true);
		RegisterMetatable(LFLayerName, GetLFLayerFunctions(), false);
		RegisterMetatable(LFSceneGraphName, GetLFSceneGraphFunctions(), true);
		RegisterMetatable(LFScreenName, GetLFScreenFunctions(), false);

		//Graphics
		RegisterMetatable(LFLabelControlName, GetLFLabelControlFunctions(), false);
		RegisterMetatable(LFNumberLabelControlName, GetLFNumberLabelControlFunctions(), false);
		RegisterMetatable(LFLabelFPSControlName, GetLFLabelFPSControlFunctions(), false);
		RegisterMetatable(LFLevelLabelControlName, GetLFLevelLabelControlFunctions(), false);
		RegisterMetatable(LFTimeLabelControlName, GetLFTimeLabelControlFunctions(), false);
		RegisterMetatable(LFButtonControlName, GetLFButtonControlFunctions(), false);
		RegisterMetatable(LFCheckButtonControlName, GetLFCheckButtonControlFunctions(), false);
		RegisterMetatable(LFSliderControlName, GetLFSliderControlFunctions(), false);
		RegisterMetatable(LFMessageBoxControlName, GetLFMessageBoxControlFunctions(), false);
		RegisterMetatable(LFSpriteName, GetLFSpriteFunctions(), false);

		//Input
		RegisterMetatable(LFInputName, GetLFInputFunctions(), true);

		//Audio
		RegisterMetatable(LFAudioName, GetLFAudioFunctions(), true);

		//Script
		RegisterMetatable(LFScriptName, GetLFScriptFunctions(), true);
	}

	bool LFScriptSystem::LoadScript(const char *fileName, bool isAddRootPathFromVFS, bool isRun)
	{
		LFString fileNameAndPathText;
		LFString fileNameAndPathBytecode;

		if (!isAddRootPathFromVFS)
			fileNameAndPathText += LFVFSManager::Instance()->Path(LFVFSManager::CP_SCRIPT);

		fileNameAndPathText += fileName;
		fileNameAndPathBytecode += fileNameAndPathText;
		fileNameAndPathText += LFLuaTextExtension;
		fileNameAndPathBytecode += LFLuaBytecodeExtension;

		if (LFFile::Instance().IsFileExist(fileNameAndPathText.ToChar(), false))
		{
			if (isRun ? luaL_dofile(luaState, fileNameAndPathText.ToChar()) : luaL_loadfile(luaState, fileNameAndPathText.ToChar()))
			{
				LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, lua_tostring(luaState, -1));
				return false;
			}
		}
		else if (LFFile::Instance().IsFileExist(fileNameAndPathBytecode.ToChar(), true))
		{
			if (isRun ? luaL_dofile(luaState, fileNameAndPathBytecode.ToChar()) : luaL_loadfile(luaState, fileNameAndPathBytecode.ToChar()))
			{
				LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, lua_tostring(luaState, -1));
				return false;
			}
		}
		else
		{
			LFString errorMessage;
			errorMessage += "Can't open '";
			errorMessage += fileName;
			errorMessage += "' LFScriptSystem::LoadScript";
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, errorMessage);

			return false;
		}

		LFString message;
		message += "LoadScript: ";
		message += fileName;
		LFLogger::Instance().WriteOutput(message);

		return true;
	}

	void LFScriptSystem::Execute()
	{
		lua_pcall(luaState, 0, LUA_MULTRET, 0);
	}

	void LFScriptSystem::RegisterFunction(const char *funcName, int (*func)(lua_State *))
	{
		lua_register(luaState, funcName, func);
	}

	void LFScriptSystem::PushString(const char *string)
	{
		lua_pushstring(luaState, string);
	}

	void LFScriptSystem::PushNumber(double number)
	{
		lua_pushnumber(luaState, number);
	}

	void LFScriptSystem::PushBoolean(bool boolean)
	{
		lua_pushboolean(luaState, boolean);
	}

	void LFScriptSystem::PushUserData(void *userData)
	{
		lua_pushlightuserdata(luaState, userData);
	}

	void LFScriptSystem::PushNil()
	{
		lua_pushnil(luaState);
	}

	void LFScriptSystem::CreateUserData(void *userData, unsigned int size)
	{
		void **data = (void **)lua_newuserdata(luaState, size);
		*data = userData;
	}

	void *LFScriptSystem::GetUserDataParameter(const char *metatableName, int paramIndex)
	{
		void *result = lua_touserdata(luaState, paramIndex);

		if (result != nullptr)
		{
			if (lua_getmetatable(luaState, paramIndex))
			{
				lua_getfield(luaState, LUA_REGISTRYINDEX, metatableName);

				if (lua_rawequal(luaState, -1, -2))
				{
					lua_pop(luaState, 2);
					return *(void **)result;
				}
				else
      				lua_pop(luaState, 1);
			}
			else
      			lua_pop(luaState, 1);
		}

		return nullptr;
	}

	LFLuaType LFScriptSystem::GetMetatableParameterValue(const char *metatableValueName, int paramCount, int paramIndex, LFLuaType::LFLuaTypeEnum luaType)
	{
		LFLuaType result;
		
		lua_getfield(luaState, paramIndex - (paramCount + 1), metatableValueName);
		switch(luaType)
		{
			case LFLuaType::LT_NUMBER: result.number = lua_tonumber(luaState, -1); break;
			case LFLuaType::LT_BOOLEAN: result.boolean = (bool)lua_toboolean(luaState, -1); break;
			case LFLuaType::LT_STRING: result.string = (char *)lua_tostring(luaState, -1); break;
			case LFLuaType::LT_OBJECT: result.object = lua_touserdata(luaState, -1); break;
		}
		lua_pop(luaState, 1); //remove value

		return result;
	}

	void LFScriptSystem::CreateMetatable(const char *metatableName)
	{
		luaL_getmetatable(luaState, metatableName);
		lua_setmetatable(luaState, -2);
	}

	void LFScriptSystem::RegisterMetatable(const char *metatableName, luaL_Reg *functions, bool isSingleton)
	{
		luaL_newmetatable(luaState, metatableName);
		luaL_setfuncs(luaState, functions, 0);
		lua_pushvalue(luaState, -1);
		lua_setfield(luaState, -1, "__index");

		if (isSingleton)
			CreateMetatable(metatableName);
		
		lua_setglobal(luaState, metatableName);
	}

	double LFScriptSystem::GetNumberGlobal(const char *numberName)
	{
		double result;

		lua_getglobal(luaState, numberName);
		result = lua_tonumber(luaState, 1);
		lua_pop(luaState, 1);

		return result;
	}

	char *LFScriptSystem::GetStringGlobal(const char *stringName)
	{
		char *result;

		lua_getglobal(luaState, stringName);
		result = (char *)lua_tostring(luaState, 1);
		lua_pop(luaState, 1);

		return result;
	}

	bool LFScriptSystem::GetBooleanGlobal(const char *booleanName)
	{
		bool result;

		lua_getglobal(luaState, booleanName);
		result = (bool)lua_toboolean(luaState, 1);
		lua_pop(luaState, 1);

		return result;
	}

	double LFScriptSystem::GetNumberParameter(int paramIndex)
	{
		return luaL_checknumber(luaState, paramIndex);
	}

	LFString LFScriptSystem::GetStringParameter(int paramIndex)
	{
		return LFString((char *)luaL_checkstring(luaState, paramIndex));
	}

	bool LFScriptSystem::GetBooleanParameter(int paramIndex)
	{
		lua_Number result = lua_toboolean(luaState, paramIndex);
		if(result == 0 && !lua_isboolean(luaState, paramIndex)) 
			luaL_error(luaState, "%d argument is not a boolean type", paramIndex);  

		return (bool)result;
	}

	int LFScriptSystem::GetParamCount()
	{
		return lua_gettop(luaState);  //Number of arguments
	}

	bool LFScriptSystem::IsParamCountOk(int paramCount)
	{
		int count = lua_gettop(luaState);  //Number of arguments
    
		if (count != paramCount)
		{
			luaL_error(luaState, "Got %d arguments expected", count); 
			return false;
		}

		return true;
	}

	void LFScriptSystem::PushLuaType(LFLuaType luaType)
	{
		switch(luaType.luaTypeEnum)
		{
			case LFLuaType::LT_NUMBER: lua_pushnumber(luaState, luaType.number); break;
			case LFLuaType::LT_BOOLEAN: lua_pushboolean(luaState, luaType.boolean); break;
			case LFLuaType::LT_STRING: lua_pushstring(luaState, luaType.string); break;
			
			case LFLuaType::LT_OBJECT: 
				CreateUserData(luaType.object, luaType.objectTypeSize);
				CreateMetatable(luaType.objectName);
				break;
		}
	}

	void LFScriptSystem::CallFunction(LFLuaType metatableObject, const char *functionName)
	{
		PushLuaType(metatableObject);
		luaL_getmetafield(luaState, 1, functionName);
		lua_call(luaState, 0, 0);
		
		lua_pop(luaState, 1);
	}

	void LFScriptSystem::CallFunction(LFLuaType metatableObject, const char *functionName, LFLuaType param1)
	{
		PushLuaType(metatableObject);
		luaL_getmetafield(luaState, 1, functionName);

		lua_pushnil(luaState); //#1 self
		PushLuaType(param1); //#2 param1
		lua_call(luaState, 2, 0);

		lua_pop(luaState, 1);
	}

	void LFScriptSystem::CallFunction(const char *metatableSingletonName, const char *functionName)
	{
		luaL_getmetatable(luaState, metatableSingletonName);
		luaL_getmetafield(luaState, 1, functionName);
		
		lua_call(luaState, 0, 0);
		
		lua_pop(luaState, 1);
	}

	void LFScriptSystem::CallFunction(const char *metatableSingletonName, const char *functionName, LFLuaType param1)
	{
		luaL_getmetatable(luaState, metatableSingletonName);
		luaL_getmetafield(luaState, 1, functionName);

		lua_pushnil(luaState); //#1 self
		PushLuaType(param1); //#2 param1
		lua_call(luaState, 2, 0);

		lua_pop(luaState, 1);
	}

	void LFScriptSystem::CallFunction(const char *metatableSingletonName, const char *functionName, LFLuaType param1, LFLuaType param2)
	{
		luaL_getmetatable(luaState, metatableSingletonName);
		luaL_getmetafield(luaState, 1, functionName);

		lua_pushnil(luaState); //#1 self
		PushLuaType(param1); //#2 param1
		PushLuaType(param2); //#3 param2
		lua_call(luaState, 3, 0);

		lua_pop(luaState, 1);
	}

	void LFScriptSystem::CallFunction(const char *metatableSingletonName, const char *functionName, LFLuaType param1, LFLuaType param2, LFLuaType param3)
	{
		luaL_getmetatable(luaState, metatableSingletonName);
		luaL_getmetafield(luaState, 1, functionName);

		lua_pushnil(luaState); //#1 self
		PushLuaType(param1); //#2 param1
		PushLuaType(param2); //#3 param2
		PushLuaType(param3); //#4 param3
		lua_call(luaState, 4, 0);

		lua_pop(luaState, 1);
	}
}}
