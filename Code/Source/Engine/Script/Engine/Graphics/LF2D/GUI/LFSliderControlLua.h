/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

struct lua_State;
struct luaL_Reg;

#define LFSliderControlName "LFSliderControl"
#define LFSliderControlOnValueChangedName "OnValueChanged"

luaL_Reg *GetLFSliderControlFunctions();
