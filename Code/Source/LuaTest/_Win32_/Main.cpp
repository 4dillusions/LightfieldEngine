/*
Copyright (c) 2013-2015 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include <iostream>
using namespace std;

extern "C" 
{
	#include "..\..\Depencies\Lua\Source\lua.h";
	#include "..\..\Depencies\Lua\Source\lualib.h"
	#include "..\..\Depencies\Lua\Source\lauxlib.h"
}

int CreateMainWindow(lua_State *L)
{
	int argc = lua_gettop(L);

	cout << "window name: " << luaL_checkstring(L, 1, 0) << endl;
	cout << "variable 1: " << luaL_checknumber(L, 2) << endl;
	cout << "variable 2: " << luaL_checknumber(L, 3) << endl;

	return 0;
}

int Add(lua_State *L)
{
	int argc = lua_gettop(L);

	float a = luaL_checknumber(L, 1);
	float b = luaL_checknumber(L, 2);

	lua_pushnumber(L, a + b); // return value
	return 1; // number of return values
}

int TrueOrFalse(lua_State *L)
{
	int argc = lua_gettop(L);
	if (argc == 3)
	{
		bool x = lua_toboolean(L, 1);
		bool y = lua_toboolean(L, 2);
		const char *string = luaL_checkstring(L, 3);

		cout << "TrueOrFalse: " << "x:" << (x ? "true" : "false") << " y:" << (y ? "true" : "false") << " string:" << string << endl;
	}

	return 0; //no return value
}

class Foo
{
public:
	int x;
	Foo() : x(10) { cout << "Foo()" << endl; }
};

class Foo2 : public Foo
{
public:
	int y;
	Foo2() : y(20) { cout << "Foo2()" << endl; }
};

int FooConstructor(lua_State * l) //create object (if it isn't a singleton)
{
	Foo **udata = (Foo **)lua_newuserdata(l, sizeof(Foo *));
	*udata = new Foo();

    luaL_getmetatable(l, "Foo");
    lua_setmetatable(l, -2);
 
    return 1;
}

int Foo2Constructor(lua_State * l) //create object (if it isn't a singleton)
{
	 Foo2 **udata = (Foo2 **)lua_newuserdata(l, sizeof(Foo2 *));
	*udata = new Foo2();

    luaL_getmetatable(l, "Foo2");
    lua_setmetatable(l, -2);
 
    return 1;
}

double GetTableDoubleParameterValue(lua_State *L, const char *tableValueName, int index)
{
	lua_getfield(L, index - 4, tableValueName);
	double result =  lua_tonumber(L, -1);
	lua_pop(L, 1); //remove value

	return result;
}

const char *GetTableStringParameterValue(lua_State *L, const char *tableValueName, int index)
{
	lua_getfield(L, index - 4, tableValueName);
	const char *result =  lua_tostring(L, -1);
	lua_pop(L, 1); //remove value

	return result;
}

int PrintTableParam(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if (argc == 3)
	{
		//#1 //self
		
		//#2 table parameter values
		double r = GetTableDoubleParameterValue(L, "r", 2);
		double g = GetTableDoubleParameterValue(L, "g", 2);
		double b = GetTableDoubleParameterValue(L, "b", 2);
		const char *textureName = GetTableStringParameterValue(L, "textureName", 2);

		//#3 table parameter values
		const char *materialName = GetTableStringParameterValue(L, "materialName", 3);
		double width = GetTableDoubleParameterValue(L, "width", 3);
		double height = GetTableDoubleParameterValue(L, "height", 3);

		cout << "table parameter values 1: " << "r:" << r << " g:" << g << " b:" << b << " texture name:" << textureName << endl;
		cout << "table parameter values 2: " << "materialName:" << materialName << " width:" << width << " height:" << height << endl;
	}

	return 0;
}

void *GetUserData(lua_State *state, int index, const char *tableParamName)
{
	void *result = lua_touserdata(state, index);

	if (result != nullptr)
	{
		if (lua_getmetatable(state, index))
		{
			lua_getfield(state, LUA_REGISTRYINDEX, tableParamName);

			if (lua_rawequal(state, -1, -2))
			{
				lua_pop(state, 2);
				return result;
			}
			else
      			lua_pop(state, 1);
		}
		else
      		lua_pop(state, 1);
	}

	return nullptr;
}

int PrintOOP(lua_State *L)
{
	int argc = lua_gettop(L);
	
	if (argc == 2)
	{
		//#1 //self
		
		//#2
		Foo *foo = nullptr;
		if (void *data = GetUserData(L, 2, "Foo"))
		{
			Foo *foo = *(Foo **)data;
			cout << "foo x:" << foo->x << endl;
		}
		else if (void *data = GetUserData(L, 2, "Foo2"))
		{
			Foo2 *foo = *(Foo2 **)data;
			cout << "foo2 x:" << foo->x << " y:" << foo->y << endl; 
		}
	}

	return 0;
}

luaL_Reg FooRegs[] =
{
    { "New", FooConstructor }, //create object (if it isn't a singleton)
    { 0, 0 }
};

luaL_Reg Foo2Regs[] =
{
    { "New", Foo2Constructor }, //create object (if it isn't a singleton)
    { 0, 0 }
};

luaL_Reg HelperRegs[] =
{
	{ "PrintTableParam", PrintTableParam },
    { "PrintOOP", PrintOOP },
    { 0, 0 }
};

void GlobalTest()
{
	cout << "GlobalTest------------" << endl;

	bool isOk = true;
	lua_State *lua = luaL_newstate();
	
	lua_register(lua, "CreateMainWindow", CreateMainWindow);
	lua_register(lua, "Add", Add);
	lua_register(lua, "TrueOrFalse", TrueOrFalse);
	
	if (luaL_dofile(lua, "Home/Script/Test/TestFunction.lua"))
	{
		cout << "Lua script error: " << lua_tostring(lua, -1) << endl;
		isOk = false;
	}

	int call = lua_pcall(lua, 0, LUA_MULTRET, 0); // execute Lua program

	lua_getglobal(lua, "x");
	float x = (float)lua_tonumber(lua, 1);
	lua_pop(lua, 1);
	cout << "X a + b: " << x << endl;

	lua_getglobal(lua, "y");
	float y = (float)lua_tonumber(lua, 1);
	lua_pop(lua, 1);
	cout << "Y a + b: " << y << endl;

	lua_close(lua);
}

//register tabletábla with functions
void CreateMetatable(lua_State *lua, const char *name, luaL_Reg *functions, bool isSingleton, const char* baseName = "")
{
	luaL_newmetatable(lua, name);
    luaL_setfuncs(lua, functions, 0);
    lua_pushvalue(lua, -1);
	
	lua_setfield(lua, -1, "__index");	

	if (isSingleton)
	{
		lua_setglobal(lua, name);	
	}
	else
	{
		luaL_getmetatable(lua, name);
		lua_setmetatable(lua, -2); //metatable.__index = metatable
		lua_setglobal(lua, name);
	}
}

void MetatableTest()
{
	cout << "MetatableTest------------" << endl;

	bool isOk = true;
	lua_State *lua = luaL_newstate();

	CreateMetatable(lua, "Foo", FooRegs, false);
	CreateMetatable(lua, "Foo2", Foo2Regs, false, "Foo");
	CreateMetatable(lua, "Helper", HelperRegs, true);

	if (luaL_dofile(lua, "Home/Script/Test/TestMetatable.lua"))
	{
		cout << "Lua script error: " << lua_tostring(lua, -1) << endl;
		isOk = false;
	}

	int call = lua_pcall(lua, 0, LUA_MULTRET, 0); // execute Lua program
	lua_close(lua);
}

void main()
{
	GlobalTest();
	MetatableTest();

	cout << "ready" << endl;
	system("pause");
}

#endif