/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

struct lua_State;
struct luaL_Reg;

#define LFInputName "LFInput"

#define LFInputOnPointerPressedName "OnPointerPressed"
#define LFInputOnPointerReleasedName "OnPointerReleased"
#define LFInputOnButtonPressedName "OnButtonPressed"
#define LFInputOnButtonReleasedName "OnButtonReleased"
#define LFInputOnControlPressedName "OnControlPressed"

luaL_Reg *GetLFInputFunctions();