/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "ScriptTest.h"
#include "..\Test.h"
#include "..\..\Core\Common\LFVFSManager.h"
#include "..\..\Engine\Script\LFScriptSystem.h"
#include "..\..\Engine\Script\LuaHeaders.h"
#include "..\..\Core\Common\LFString.h"
#include "..\..\Core\Common\LFMemoryManager.h"

#ifdef TIZEN
#include <app_common.h>
#endif

using namespace LFCore::Common;
using namespace LFEngine::Script;

namespace UnitTest
{
	ScriptTest *scriptTest;

	ScriptTest::ScriptTest()
	{
		LFVFSManager::CreateInstance();
		LFString path;

		#ifdef TIZEN
		path += app_get_shared_resource_path(); //path += app_get_resource_path();
		#endif

		path += "Home/Script/Test/";

		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_SCRIPT, path.ToNewChar());

		scriptTest = this;
	}

	ScriptTest::~ScriptTest()
	{
		LFVFSManager::ReleaseInstance();
	}

	void ScriptTest::LoadTest()
	{
		LFScriptSystem::CreateInstance();
		
		Test::AssertOk(LFScriptSystem::Instance()->LoadScript("WrongFile") == false, "LFScript::LFScriptSystem::LoadScript wrong file");
		Test::AssertOk(LFScriptSystem::Instance()->LoadScript("TestWrong") == false, "LFScript::LFScriptSystem::LoadScript wrong syntax");
		Test::AssertOk(LFScriptSystem::Instance()->LoadScript("Test"), "LFScript::LFScriptSystem::LoadScript");

		LFScriptSystem::ReleaseInstance();
	}

	void ScriptTest::LoadBytecodeTest()
	{
		LFScriptSystem::CreateInstance();

		Test::AssertOk(LFScriptSystem::Instance()->LoadScript("TestBytecode"), "LFScript::LFScriptSystem::LoadScript (bytecode)");

		LFScriptSystem::ReleaseInstance();
	}

	void ScriptTest::GetGlobalTest(bool isTextCode)
	{
		LFScriptSystem::CreateInstance();
		
		bool isLoadOk = false;

		if (isTextCode)
		{
			isLoadOk = LFScriptSystem::Instance()->LoadScript("Test");
			Test::AssertOk(isLoadOk, "LFScript::LFScriptSystem::LoadScript GetGlobalTest");
		}
		else
		{
			isLoadOk = LFScriptSystem::Instance()->LoadScript("TestBytecode");
			Test::AssertOk(isLoadOk, "LFScript::LFScriptSystem::LoadScript GetGlobalBytecodeTest");
		}

		if (isLoadOk)
		{
			Test::AssertOk(LFScriptSystem::Instance()->GetBooleanGlobal("boolVar") == true, "LFScript::LFScriptSystem::GetNumberValue boolean true");
			Test::AssertOk(LFScriptSystem::Instance()->GetBooleanGlobal("boolVar2") == false, "LFScript::LFScriptSystem::GetNumberValue boolean false");
			Test::AssertOk(LFScriptSystem::Instance()->GetNumberGlobal("num") == 800, "LFScript::LFScriptSystem::GetNumberValue integer");
			Test::AssertOk(LFScriptSystem::Instance()->GetNumberGlobal("doubleNum") == 1.238732, "LFScript::LFScriptSystem::GetNumberValue double");
			Test::AssertOk(LFScriptSystem::Instance()->GetNumberGlobal("doubleNum") == 1.238732, "LFScript::LFScriptSystem::GetNumberValue double");
			Test::AssertOk(LFString(LFScriptSystem::Instance()->GetStringGlobal("text")) == LFString("Hello Lua 5.1!"), "LFScript::LFScriptSystem::GetStringValue");
			Test::AssertOk(LFScriptSystem::Instance()->GetNumberGlobal("num") == 800, "LFScript::LFScriptSystem::GetNumberValue integer");
			Test::AssertOk(LFString(LFScriptSystem::Instance()->GetStringGlobal("text")) == LFString("Hello Lua 5.1!"), "LFScript::LFScriptSystem::GetStringValue");
		}

		LFScriptSystem::ReleaseInstance();
	}

	void ScriptTest::GetGlobalBytecodeTest()
	{
		GetGlobalTest(false);
	}

	LFString *windowName = nullptr;
	double var1 = 0, var2 = 0;
	int CreateMainWindow(lua_State *luaState)
	{
		if (LFScriptSystem::Instance()->IsParamCountOk(3))
		{
			if (windowName == nullptr)
			{
				var1 = 0, var2 = 0;
				windowName = LFNew<LFString>(AT);
			}

			*windowName += LFScriptSystem::Instance()->GetStringParameter(1);
			var1 += LFScriptSystem::Instance()->GetNumberParameter(2);
			var2 += LFScriptSystem::Instance()->GetNumberParameter(3);
		}

		return 0; //no return value
	}

	int Add(lua_State *luaState)
	{
		if (LFScriptSystem::Instance()->IsParamCountOk(2))
		{
			double a = LFScriptSystem::Instance()->GetNumberParameter(1);
			double b = LFScriptSystem::Instance()->GetNumberParameter(2);

			LFScriptSystem::Instance()->PushNumber(a + b);
		}

		return 1; //return number
	}

	bool isBooleanOk = false;
	int TrueOrFalse(lua_State *luaState)
	{
		if (LFScriptSystem::Instance()->IsParamCountOk(3))
		{
			bool x = LFScriptSystem::Instance()->GetBooleanParameter(1);
			bool y = LFScriptSystem::Instance()->GetBooleanParameter(2);
			LFString string = LFScriptSystem::Instance()->GetStringParameter(3);

			isBooleanOk = (x == true && y == false && string == LFString("string test"));
			LFScriptSystem::Instance()->PushBoolean(isBooleanOk);
		}

		return 1; //return boolean
	}

	void ScriptTest::CppFromLuaFunctionTest(bool isTextCode)
	{
		LFScriptSystem::CreateInstance();

		LFScriptSystem::Instance()->RegisterFunction("CreateMainWindow", CreateMainWindow);
		LFScriptSystem::Instance()->RegisterFunction("Add", Add);
		LFScriptSystem::Instance()->RegisterFunction("TrueOrFalse", TrueOrFalse);

		bool isLoadOk = false;

		if (isTextCode)
		{
			isLoadOk = LFScriptSystem::Instance()->LoadScript("TestFunction");
			Test::AssertOk(isLoadOk, "LFScript::LFScriptSystem::LoadScript CppFromLuaFunctionTest");
		}
		else
		{
			isLoadOk = LFScriptSystem::Instance()->LoadScript("TestFunctionBytecode");
			Test::AssertOk(isLoadOk, "LFScript::LFScriptSystem::LoadScript CppFromLuaFunctionBytecodeTest");
		}

		if (isLoadOk)
		{
			LFScriptSystem::Instance()->Execute();

			Test::AssertOk(*windowName == LFString("Window1Window2") && var1 == 400 && var2 == 600, "LFScript::LFScriptSystem CppFromLuaFunctionParameterTest number");
			Test::AssertOk(LFScriptSystem::Instance()->GetNumberGlobal("x") + LFScriptSystem::Instance()->GetNumberGlobal("y") == 10, 
				"LFScript::LFScriptSystem::GetNumberValue CppFromLuaReturnTest");
			Test::AssertOk(isBooleanOk, "LFScript::LFScriptSystem CppFromLuaFunctionParameterTest boolean");
		}

		LFDelete(windowName);

		LFScriptSystem::ReleaseInstance();
	}

	void ScriptTest::CppFromLuaFunctionBytecodeTest()
	{
		CppFromLuaFunctionTest(false);
	}

	class Foo
	{
	public:
		int x;
		Foo(int x) : x(x) { }
	};

	class Foo2 : public Foo
	{
	public:
		int y;
		Foo2(int x, int y) : Foo(x), y(y) { }
	};

	int FooConstructor(lua_State *luaState)
	{
		if(LFScriptSystem::Instance()->IsParamCountOk(1))
		{
			int x = LFScriptSystem::Instance()->GetNumberParameter(1); //#1
	
			LFScriptSystem::Instance()->CreateUserData(LFNew<Foo>(AT, x), sizeof(Foo *));
			LFScriptSystem::Instance()->CreateMetatable("Foo");
		}

		return 1; //return user data
	}

	int FooDestructor(lua_State *luaState)
	{
		Foo *foo = (Foo *)LFScriptSystem::Instance()->GetUserDataParameter("Foo", 1);
		LFDelete(foo);

		return 0;
	}

	luaL_Reg FooFunctions[] =
	{
		{ "New", FooConstructor },
		{ "__gc", FooDestructor }, 
		{ 0, 0 }
	};

	int Foo2Constructor(lua_State *luaState)
	{
		if(LFScriptSystem::Instance()->IsParamCountOk(2))
		{
			int x = LFScriptSystem::Instance()->GetNumberParameter(1); //#1
			int y = LFScriptSystem::Instance()->GetNumberParameter(2); //#2
	
			LFScriptSystem::Instance()->CreateUserData(LFNew<Foo2>(AT, x, y), sizeof(Foo2 *));
			LFScriptSystem::Instance()->CreateMetatable("Foo2");
		}

		return 1; //return user data
	}

	int Foo2Destructor(lua_State *luaState)
	{
		Foo2 *foo2 = (Foo2 *)LFScriptSystem::Instance()->GetUserDataParameter("Foo2", 1);
		LFDelete(foo2);

		return 0;
	}

	luaL_Reg Foo2Functions[] =
	{
		{ "New", Foo2Constructor }, 
		{ "__gc", Foo2Destructor }, 
		{ 0, 0 }
	};

	bool isTableParamOk = false;
	bool isTableParamStringOk = false;
	int PrintTableParam(lua_State *L)
	{
		if(LFScriptSystem::Instance()->IsParamCountOk(3))
		{
			//#1 //self
		
			//#2 table parameter values
			const char *textureName = LFScriptSystem::Instance()->GetMetatableParameterValue("textureName", 3, 2, LFLuaType::LT_STRING).string;
			double r = LFScriptSystem::Instance()->GetMetatableParameterValue("r", 3, 2, LFLuaType::LT_NUMBER).number;
			double g = LFScriptSystem::Instance()->GetMetatableParameterValue("g", 3, 2, LFLuaType::LT_NUMBER).number;
			double b = LFScriptSystem::Instance()->GetMetatableParameterValue("b", 3, 2, LFLuaType::LT_NUMBER).number;

			isTableParamOk = ((r + g + b) == 23,64);
			isTableParamStringOk = (LFString(textureName) == LFString("test.png"));

			//#3
			const char *materialName = LFScriptSystem::Instance()->GetMetatableParameterValue("materialName", 3, 3, LFLuaType::LT_STRING).string;
			double width = LFScriptSystem::Instance()->GetMetatableParameterValue("width", 3, 3, LFLuaType::LT_NUMBER).number;
			double height = LFScriptSystem::Instance()->GetMetatableParameterValue("height", 3, 3, LFLuaType::LT_NUMBER).number;

			isTableParamOk = (width + height) == 300;
			isTableParamStringOk = (LFString(materialName) == LFString("material1"));
		}

		return 0;
	}

	bool isFooOk = false;
	bool isFoo2Ok = false;
	int PrintOOP(lua_State *L)
	{
		if(LFScriptSystem::Instance()->IsParamCountOk(2))
		{
			//#1 //self

			//#2
			Foo *foo = nullptr;

			if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter("Foo", 2))
			{
				foo = (Foo *)obj;
				isFooOk = (foo->x == 10);
			}
			else if (void *obj = LFScriptSystem::Instance()->GetUserDataParameter("Foo2", 2))
			{
				foo = (Foo2 *)obj;
				isFoo2Ok = (foo->x == 1 && ((Foo2 *)foo)->y == 2);

				int c = ((Foo2 *)foo)->y;
				c = 0;
			}
		}

		return 0;
	}

	luaL_Reg HelperFunctions[] =
	{
		{ "PrintTableParam", PrintTableParam }, 
		{ "PrintOOP", PrintOOP }, 
		{ 0, 0 }
	};

	void ScriptTest::MetatableTest()
	{
		LFScriptSystem::CreateInstance();

		LFScriptSystem::Instance()->RegisterMetatable("Foo", FooFunctions, false);
		LFScriptSystem::Instance()->RegisterMetatable("Foo2", Foo2Functions, false);
		LFScriptSystem::Instance()->RegisterMetatable("Helper", HelperFunctions, true);

		bool isLoadOk = LFScriptSystem::Instance()->LoadScript("TestMetatable");
		Test::AssertOk(isLoadOk, "LFScript::LFScriptSystem::LoadScript TestMetatable");
		Test::AssertOk((isTableParamOk && isTableParamStringOk), "LFScript::LFScriptSystem::GetMetatableParameterValue TestMetatable as parameter");
		Test::AssertOk((isFooOk && isFoo2Ok), "LFScript::LFScriptSystem::GetUserDataParameter TestMetatable OOP");

		if (isLoadOk)
		{
			LFScriptSystem::Instance()->Execute();
			//Test::PushErrorCounts(LFScriptSystem::Instance()->GetNumberGlobal("errorCounter"));
		}

		LFScriptSystem::ReleaseInstance();
	}
};
