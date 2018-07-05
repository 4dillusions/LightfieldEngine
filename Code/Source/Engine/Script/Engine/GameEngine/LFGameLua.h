/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

struct lua_State;
struct luaL_Reg;

#define LFGameName "LFGame"

#define LFGameOnInitName "OnInitGame"
#define LFGameOnTerminateName "OnTerminateGame"
#define LFGameExitGameName "Exit"
#define LFGameSaveOptionsData "SaveOptionsData"
#define LFGameSaveGameStateData "SaveGameStateData"
#define LFGameGetGameStateLevelIndex "GetGameStateLevelIndex"
#define LFGameSetGameStateLevelIndex "SetGameStateLevelIndex"
#define LFGameGetGameStateSecond "GetGameStateSecond"
#define LFGameSetGameStateSecond "SetGameStateSecond"
#define LFGameGetGameStateLives "GetGameStateLives"
#define LFGameSetGameStateLives "SetGameStateLives"
#define LFGameGetGameStateLevelMatrixValue "GetGameStateLevelMatrixValue"
#define LFGameSetGameStateLevelMatrixValue "SetGameStateLevelMatrixValue"
#define LFSetGameStateEditorLevelSizeX "SetGameStateEditorLevelSizeX"
#define LFSetGameStateEditorLevelSizeY "SetGameStateEditorLevelSizeY"
#define LFSetGameStateEditorTilesId "SetGameStateEditorTilesId"
#define LFSetGameStateEditorZoom "SetGameStateEditorZoom"
#define LFGameGetLevelCount "GetLevelCount"
#define LFGameSetLevelCount "SetLevelCount"
#define LFGameGetLevelMatrixValue "GetLevelMatrixValue"
#define LFGameSetLevelMatrixValue "SetLevelMatrixValue"
#define LFGetEditorLevelSizeX "GetEditorLevelSizeX"
#define LFGetEditorLevelSizeY "GetEditorLevelSizeY"
#define LFGetEditorTilesId "GetEditorTilesId"
#define LFGetEditorZoom "GetEditorZoom"

luaL_Reg *GetLFGameFunctions();