/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLuaType.h"
#include "..\..\Core\Common\LFString.h"

struct lua_State;
struct luaL_Reg;

namespace LFEngine { namespace Script
{
	class LFENGINE_LIBRARY LFScriptSystem
	{ 
	private:
		static LFScriptSystem *instance;
		lua_State *luaState;

		void RegisterAllWrappers();
		void PushLuaType(LFLuaType luaType);

	public:
		LFScriptSystem();
		~LFScriptSystem();

        static LFScriptSystem *Instance() { return instance; }
		static void CreateInstance();
		static void ReleaseInstance();

		bool LoadScript(const char *fileName, bool isAddRootPathFromVFS = false, bool isRun = true);
		void Execute();

		void RegisterFunction(const char *funcName, int (*func)(lua_State *));
		void PushString(const char *string);
		void PushNumber(double number);
		void PushBoolean(bool boolean);
		void PushUserData(void *userData);
		void PushNil();

		void CreateUserData(void *userData, unsigned int size);
		void CreateMetatable(const char *metatableName);
		void RegisterMetatable(const char *metatableName, luaL_Reg *functions, bool isSingleton);

		double GetNumberGlobal(const char *numberName);
		char *GetStringGlobal(const char *stringName);
		bool GetBooleanGlobal(const char *booleanName);

		double GetNumberParameter(int paramIndex);
		LFCore::Common::LFString GetStringParameter(int paramIndex);
		bool GetBooleanParameter(int paramIndex);
		void *GetUserDataParameter(const char *metatableName, int paramIndex);
		LFLuaType GetMetatableParameterValue(const char *metatableValueName, int paramCount, int paramIndex, LFLuaType::LFLuaTypeEnum luaType);

		int GetParamCount();
		bool IsParamCountOk(int paramCount);
		
		void CallFunction(LFLuaType metatableObject, const char *functionName);
		void CallFunction(LFLuaType metatableObject, const char *functionName, LFLuaType param1);

		void CallFunction(const char *metatableSingletonName, const char *functionName);
		void CallFunction(const char *metatableSingletonName, const char *functionName, LFLuaType param1);
		void CallFunction(const char *metatableSingletonName, const char *functionName, LFLuaType param1, LFLuaType param2);
		void CallFunction(const char *metatableSingletonName, const char *functionName, LFLuaType param1, LFLuaType param2, LFLuaType param3);
	};
}}
