/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

struct lua_State;

int GetComponetsLength(lua_State *luaState, const char *objectName);
int WriteOutputComponentNames(lua_State *luaState, const char *objectName);
int Add(lua_State *luaState, const char *objectName, const char *addObjectName);
int Remove(lua_State *luaState, const char *objectName, const char *removeObjectName); //After render only