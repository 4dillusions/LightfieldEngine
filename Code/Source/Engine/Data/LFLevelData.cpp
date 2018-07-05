/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLevelData.h"
#include "..\..\Core\Common\LFMemoryManager.h"
#include "..\..\Core\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Data
{
	LFLevelData::LFLevelData()
	{
		Reset();
	}

	void LFLevelData::Reset()
	{
		data.id = 0;
		data.levelCount = 0;

		for (int x = 0; x < LFDataMaxLevelCount; x++)
			for (int y = 0; y < LFDataMaxLevelSize; y++)
				for (int z = 0; z < LFDataMaxLevelSize; z++)
					data.levelMatrix[x][y][z] = 0;

		data.editorData.levelSizeX = 0;
		data.editorData.levelSizeY = 0;
		data.editorData.tilesId = 0;
		data.editorData.zoom = 0;
	}

	bool LFLevelData::Load()
	{
		data = serializer.ReadBinaryData(LevelDataName, LFVFSManager::CP_DATA);
		
		if (data.id != LFLevelDataId)
		{
			LFString fileName;
			fileName += LevelDataName;
			fileName += " wrong or incompatible! LFLevelData::Load()";
			LFLogger::Instance().WriteOutput(LFLogger::MT_LOAD_ERROR, fileName);
		}

		LFLogger::Instance().WriteOutput("Load Levels");
		return (data.id == LFLevelDataId);
	}

	bool LFLevelData::Load(const char *fileName)
	{
		data = serializer.ReadBinaryData(fileName, LFVFSManager::CP_NO);
		
		if (data.id != LFLevelDataId)
		{
			LFString fileFullName;
			fileFullName += fileName;
			fileFullName += " wrong or incompatible! LFLevelData::Load(const char *fileName)";
			LFLogger::Instance().WriteOutput(LFLogger::MT_LOAD_ERROR, fileFullName);
		}

		LFLogger::Instance().WriteOutput("Load Levels");
		return (data.id == LFLevelDataId);
	}

	void LFLevelData::Save()
	{
		data.id = LFLevelDataId;
		serializer.WriteBinaryData(LevelDataName, data, LFVFSManager::CP_DATA);
		LFLogger::Instance().WriteOutput("Save Levels");
	}

	void LFLevelData::Save(const char *fileName)
	{
		data.id = LFLevelDataId;
		serializer.WriteBinaryData(fileName, data, LFVFSManager::CP_NO);
		LFLogger::Instance().WriteOutput("Save Levels");
	}
}}
