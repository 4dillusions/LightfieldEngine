/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

struct lua_State;

int GetName(lua_State *luaState, const char *objectName);
int GetIsAlive(lua_State *luaState, const char *objectName);
int GetIsVisible(lua_State *luaState, const char *objectName);
int SetIsAlive(lua_State *luaState, const char *objectName);
int SetIsVisible(lua_State *luaState, const char *objectName);