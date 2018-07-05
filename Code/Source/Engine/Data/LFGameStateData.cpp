/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameStateData.h"
#include "..\..\Core\Common\LFMemoryManager.h"
#include "..\..\Core\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Data
{
	LFGameStateData::LFGameStateData()
	{
		Reset();
	}

	void LFGameStateData::Reset()
	{
		data.id = 0;
		data.levelIndex = 0;
		data.second = 0;
		data.lives = 0;

		for (int x = 0; x < LFDataMaxLevelSize; x++)
			for (int y = 0; y < LFDataMaxLevelSize; y++)
				data.levelMatrix[x][y] = 0;

		data.editorData.levelSizeX = 0;
		data.editorData.levelSizeY = 0;
		data.editorData.tilesId = 0;
		data.editorData.zoom = 0;
	}

	bool LFGameStateData::Load()
	{
		data = serializer.ReadBinaryData(GameStateDataName, LFVFSManager::CP_DATA_SAVE);
		
		if (data.id != LFGameStateDataId)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_OK, "Reset and save!");
			Reset();
			Save();
		}

		LFLogger::Instance().WriteOutput("Load GameState");
		return (data.id == LFGameStateDataId);
	}

	bool LFGameStateData::Load(const char *fileName)
	{
		data = serializer.ReadBinaryData(fileName, LFVFSManager::CP_NO);
		
		if (data.id != LFGameStateDataId)
		{
			LFString fileFullName;
			fileFullName += fileName;
			fileFullName += " wrong or incompatible! LFGameStateData::Load(const char *fileName)";
			LFLogger::Instance().WriteOutput(LFLogger::MT_LOAD_ERROR, fileFullName);
		}

		LFLogger::Instance().WriteOutput("Load GameState");
		return (data.id == LFGameStateDataId);
	}

	void LFGameStateData::Save()
	{
		data.id = LFGameStateDataId;
		serializer.WriteBinaryData(GameStateDataName, data, LFVFSManager::CP_DATA_SAVE);
		LFLogger::Instance().WriteOutput("Save GameState");
	}

	void LFGameStateData::Save(const char *fileName)
	{
		data.id = LFGameStateDataId;
		serializer.WriteBinaryData(fileName, data, LFVFSManager::CP_NO);
		LFLogger::Instance().WriteOutput("Save GameState");
	}
}}
