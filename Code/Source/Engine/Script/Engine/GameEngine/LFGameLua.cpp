/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameLua.h"
#include "..\..\..\Script\LuaHeaders.h"
#include "..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\GameEngine\LFGameEngine.h"
#include "..\..\..\Data\LFGameStateData.h"
#include "..\..\..\Data\LFLevelData.h"

using namespace LFEngine::Script;
using namespace LFEngine::GameEngine;

int OnInitGame(lua_State *luaState)
{
	return 0; //no return value
}

int OnTerminateGame(lua_State *luaState)
{
	return 0; //no return value
}

int Exit(lua_State *luaState)
{
	LFGameEngine::Instance()->Exit();

	return 0; //no return value
}

int SaveOptionsData(lua_State *luaState)
{
	LFGameEngine::Instance()->SaveOptionsData();

	return 0; //no return value
}

int SaveGameStateData(lua_State *luaState)
{
	LFGameEngine::Instance()->SaveGameStateData();

	return 0; //no return value
}

int GetGameStateLevelIndex(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		//self //#1
		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->GameStateData()->data.levelIndex);
	}

	return 1; //return levelIndex
}

int SetGameStateLevelIndex(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		double levelIndex = LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		LFGameEngine::Instance()->GameStateData()->data.levelIndex = levelIndex;
	}

	return 0; //no return value
}

int GetGameStateSecond(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		//self //#1
		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->GameStateData()->data.second);
	}

	return 1; //return second
}

int SetGameStateSecond(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		double second = LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		LFGameEngine::Instance()->GameStateData()->data.second = second;
	}

	return 0; //no return value
}

int GetGameStateLives(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		//self //#1
		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->GameStateData()->data.lives);
	}

	return 1; //return lives
}

int SetGameStateLives(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		double lives = LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		LFGameEngine::Instance()->GameStateData()->data.lives = lives;
	}

	return 0; //no return value
}

int GetGameStateLevelMatrixValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(3))
	{
		//self //#1
		double x = LFScriptSystem::Instance()->GetNumberParameter(2); //#2
		double y = LFScriptSystem::Instance()->GetNumberParameter(3); //#3

		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->GameStateData()->data.levelMatrix[(int)x][(int)y]);
	}

	return 1; //return levelMatrix value
}

int SetGameStateLevelMatrixValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(4))
	{
		//self //#1
		double x = LFScriptSystem::Instance()->GetNumberParameter(2); //#2
		double y = LFScriptSystem::Instance()->GetNumberParameter(3); //#3
		double value = LFScriptSystem::Instance()->GetNumberParameter(4); //#4

		LFGameEngine::Instance()->GameStateData()->data.levelMatrix[(int)x][(int)y] = value;
	}

	return 0; //no return value
}

int SetGameStateEditorLevelSizeX(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		double levelSizeX = LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		LFGameEngine::Instance()->GameStateData()->data.editorData.levelSizeX = levelSizeX;
	}

	return 0; //no return value
}

int SetGameStateEditorLevelSizeY(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		double levelSizeY = LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		LFGameEngine::Instance()->GameStateData()->data.editorData.levelSizeY = levelSizeY;
	}

	return 0; //no return value
}

int SetGameStateEditorTilesId(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		double tilesId = LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		LFGameEngine::Instance()->GameStateData()->data.editorData.tilesId = tilesId;
	}

	return 0; //no return value
}

int SetGameStateEditorZoom(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		double zoom = LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		LFGameEngine::Instance()->GameStateData()->data.editorData.zoom = zoom;
	}

	return 0; //no return value
}

int GetLevelCount(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		//self //#1
		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->LevelData()->data.levelCount);
	}

	return 1; //return levelCount
}

int SetLevelCount(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		double levelCount = LFScriptSystem::Instance()->GetNumberParameter(2); //#2

		LFGameEngine::Instance()->LevelData()->data.levelCount = levelCount;
	}

	return 0; //no return value
}

int GetLevelMatrixValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(4))
	{
		//self //#1
		double x = LFScriptSystem::Instance()->GetNumberParameter(2); //#2
		double y = LFScriptSystem::Instance()->GetNumberParameter(3); //#3
		double z = LFScriptSystem::Instance()->GetNumberParameter(4); //#4

		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->LevelData()->data.levelMatrix[(int)x][(int)y][(int)z]);
	}

	return 1; //return levelMatrix value
}

int SetLevelMatrixValue(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(5))
	{
		//self //#1
		double x = LFScriptSystem::Instance()->GetNumberParameter(2); //#2
		double y = LFScriptSystem::Instance()->GetNumberParameter(3); //#3
		double z = LFScriptSystem::Instance()->GetNumberParameter(4); //#4
		double value = LFScriptSystem::Instance()->GetNumberParameter(5); //#5

		LFGameEngine::Instance()->LevelData()->data.levelMatrix[(int)x][(int)y][(int)z] = value;
	}

	return 0; //no return value
}

int GetEditorLevelSizeX(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		//self //#1
		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->LevelData()->data.editorData.levelSizeX);
	}

	return 1; //return levelSizeX
}

int GetEditorLevelSizeY(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		//self //#1
		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->LevelData()->data.editorData.levelSizeY);
	}

	return 1; //return levelSizeY
}

int GetEditorTilesId(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		//self //#1
		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->LevelData()->data.editorData.tilesId);
	}

	return 1; //return tilesId
}

int GetEditorZoom(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(1))
	{
		//self //#1
		LFScriptSystem::Instance()->PushNumber(LFGameEngine::Instance()->LevelData()->data.editorData.zoom);
	}

	return 1; //return zoom
}

/**
@defgroup GameEngine

@defgroup LFGame
@ingroup GameEngine

@page my_GameOnInitGame OnInitGame
@ingroup LFGame
Initialization event.<br>
[Lua API]
@code
function LFGame:OnInitGame()
@endcode

@page my_GameOnTerminateGame OnTerminateGame
@ingroup LFGame
ShutDown event.<br>
[Lua API]
@code
function LFGame:OnTerminateGame()
@endcode

@page my_GameExit Exit
@ingroup LFGame
Shut down.<br>
[Lua API]
@code
LFGame:Exit()
@endcode

@page my_GameSaveOptionsData SaveOptionsData
@ingroup LFGame
Save options.<br>
[Lua API]
@code
LFGame:SaveOptionsData()
@endcode

@page my_GameSaveGameStateData SaveGameStateData
@ingroup LFGame
Save game actual state.<br>
[Lua API]
@code
LFGame:SaveGameStateData()
@endcode

@page my_GameGetGameStateLevelIndex GetGameStateLevelIndex
@ingroup LFGame
Get level index in game state.<br>
[Lua API]
@code
number LFGame:GetGameStateLevelIndex()
@endcode

@page my_GameSetGameStateLevelIndex SetGameStateLevelIndex
@ingroup LFGame
Set level index in game state.<br>
[Lua API]
@code
LFGame:SetGameStateLevelIndex(number levelIndex)
@endcode
@param[in] levelIndex <br>
Set index 1 to 100

@page my_GameGetGameStateSecond GetGameStateSecond
@ingroup LFGame
Get second in game state.<br>
[Lua API]
@code
number LFGame:GetGameStateSecond()
@endcode

@page my_GameSetGameStateSecond SetGameStateSecond
@ingroup LFGame
Set LF: second  / Snake: eggs in game state.<br>
[Lua API]
@code
LFGame:SetGameStateSecond(number second)
@endcode
@param[in] second <br>
Set second 1 to 999

@page my_GameGetGameStateLives GetGameStateLives
@ingroup LFGame
Get lives in game state.<br>
[Lua API]
@code
number LFGame:GetGameStateLives()
@endcode

@page my_GameSetGameStateLives SetGameStateLives
@ingroup LFGame
Set lives in game state.<br>
[Lua API]
@code
LFGame:SetGameStateLives(number lives)
@endcode
@param[in] lives <br>
Set second 1 to 999

@page my_GameGetGameStateLevelMatrixValue GetGameStateLevelMatrixValue
@ingroup LFGame
Get levelMatrix value in game state.<br>
[Lua API]
@code
number LFGame:GetGameStateLevelMatrixValue(number x, number y)
@endcode
@param[in] x <br>
dimension x of levelMatrix[x][y]
@param[in] y <br>
dimension y of levelMatrix[x][y]

@page my_GameSetGameStateLevelMatrixValue SetGameStateLevelMatrixValue
@ingroup LFGame
Set levelMatrix value in game state.<br>
[Lua API]
@code
LFGame:SetGameStateLevelMatrixValue(number x, number y, number value)
@endcode
@param[in] x <br>
dimension x of levelMatrix[x][y]
@param[in] y <br>
dimension y of levelMatrix[x][y]
@param[in] value <br>
set value of levelMatrix[x][y] = value

@page my_SetGameStateEditorLevelSizeX SetGameStateEditorLevelSizeX
@ingroup LFGame
Set levelSizeX value for editor in game state.<br>
[Lua API]
@code
LFGame:SetGameStateEditorLevelSizeX(number levelSizeX)
@endcode

@page my_SetGameStateEditorLevelSizeY SetGameStateEditorLevelSizeY
@ingroup LFGame
Set levelSizeY value for editor in game state.<br>
[Lua API]
@code
LFGame:SetGameStateEditorLevelSizeY(number levelSizeY)
@endcode

@page my_SetGameStateEditorTilesId SetGameStateEditorTilesId
@ingroup LFGame
Set tilesId value for editor in game state.<br>
[Lua API]
@code
LFGame:SetGameStateEditorTilesId(number tilesId)
@endcode

@page my_SetGameStateEditorZoom SetGameStateEditorZoom
@ingroup LFGame
Set zoom value for editor in game state.<br>
[Lua API]
@code
LFGame:SetGameStateEditorZoom(number zoom)
@endcode

@page my_GameGetLevelCount GetLevelCount
@ingroup LFGame
Get level count in Level data.<br>
[Lua API]
@code
number LFGame:GetLevelCount()
@endcode

@page my_GameSetLevelCount SetLevelCount
@ingroup LFGame
Set level count in Level data.<br>
[Lua API]
@code
LFGame:SetLevelCount(number levelCount)
@endcode
@param[in] levelCount <br>
Set count 1 to 100

@page my_GameGetLevelMatrixValue GetLevelMatrixValue
@ingroup LFGame
Get levelMatrix value in Level data.<br>
[Lua API]
@code
number LFGame:GetLevelMatrixValue(number x, number y, number z)
@endcode
@param[in] x <br>
dimension x of levelMatrix[x][y][z]
@param[in] y <br>
dimension y of levelMatrix[x][y][z]
@param[in] z <br>
dimension z of levelMatrix[x][y][z]

@page my_GameSetLevelMatrixValue SetLevelMatrixValue
@ingroup LFGame
Set levelMatrix value in Level data.<br>
[Lua API]
@code
LFGame:SetLevelMatrixValue(number x, number y, number z, number value)
@endcode
@param[in] x <br>
dimension x of levelMatrix[x][y][z]
@param[in] y <br>
dimension y of levelMatrix[x][y][z]
@param[in] z <br>
dimension z of levelMatrix[x][y][z]
@param[in] value <br>
set value of levelMatrix[x][y][z] = value

@page my_GameGetEditorLevelSizeX GetEditorLevelSizeX
@ingroup LFGame
Get levelSizeX for editor in Level data.<br>
[Lua API]
@code
number LFGame:GetEditorLevelSizeX()
@endcode

@page my_GameGetEditorLevelSizeY GetEditorLevelSizeY
@ingroup LFGame
Get levelSizeY for editor in Level data.<br>
[Lua API]
@code
number LFGame:GetEditorLevelSizeY()
@endcode

@page my_GameGetEditorTilesId GetEditorTilesId
@ingroup LFGame
Get tilesId for editor in Level data.<br>
[Lua API]
@code
number LFGame:GetEditorTilesId()
@endcode

@page my_GameGetEditorZoom GetEditorZoom
@ingroup LFGame
Get zoom for editor in Level data.<br>
[Lua API]
@code
number LFGame:GetEditorZoom()
@endcode
*/
luaL_Reg LFGameFunctions[] =
{
	//{ "New", Constructor }, 
	//{ "__gc", Destructor }, 
	{ LFGameOnInitName, OnInitGame },
	{ LFGameOnTerminateName, OnTerminateGame },
	{ LFGameExitGameName, Exit },
	{ LFGameSaveOptionsData, SaveOptionsData },
	{ LFGameSaveGameStateData, SaveGameStateData },
	{ LFGameGetGameStateLevelIndex, GetGameStateLevelIndex },
	{ LFGameSetGameStateLevelIndex, SetGameStateLevelIndex },
	{ LFGameGetGameStateSecond, GetGameStateSecond },
	{ LFGameSetGameStateSecond, SetGameStateSecond },
	{ LFGameGetGameStateLives, GetGameStateLives },
	{ LFGameSetGameStateLives, SetGameStateLives },
	{ LFGameGetGameStateLevelMatrixValue, GetGameStateLevelMatrixValue },
	{ LFGameSetGameStateLevelMatrixValue, SetGameStateLevelMatrixValue },
	{ LFSetGameStateEditorLevelSizeX, SetGameStateEditorLevelSizeX },
	{ LFSetGameStateEditorLevelSizeY, SetGameStateEditorLevelSizeY },
	{ LFSetGameStateEditorTilesId, SetGameStateEditorTilesId },
	{ LFSetGameStateEditorZoom, SetGameStateEditorZoom },
	{ LFGameGetLevelCount, GetLevelCount },
	{ LFGameSetLevelCount, SetLevelCount },
	{ LFGameGetLevelMatrixValue, GetLevelMatrixValue },
	{ LFGameSetLevelMatrixValue, SetLevelMatrixValue },
	{ LFGetEditorLevelSizeX, GetEditorLevelSizeX },
	{ LFGetEditorLevelSizeY, GetEditorLevelSizeY },
	{ LFGetEditorTilesId, GetEditorTilesId },
	{ LFGetEditorZoom, GetEditorZoom },
	{ 0, 0 }
};

luaL_Reg *GetLFGameFunctions()
{
	return LFGameFunctions;
}
