/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLevelData.h"
#include "..\LFCore\LFIO\LFLogger.h"

using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	LFLevelData::LFLevelData()
	{
		LFLevelData::Reset();
	}

	void LFLevelData::Reset()
	{
		data.id = LFSystemData::LFLevelDataId;
		data.levelCount = 0;

		for (int x = 0; x < LFSystemData::LFDataMaxLevelCount; x++)
			for (int y = 0; y < LFSystemData::LFDataMaxLevelSize; y++)
				for (int z = 0; z < LFSystemData::LFDataMaxLevelSize; z++)
					data.levelMatrix[x][y][z] = 0;

		data.editorData.levelSizeX = 0;
		data.editorData.levelSizeY = 0;
		data.editorData.tilesId = 0;
		data.editorData.zoom = 0;
	}

	bool LFLevelData::Load(int fileIndex)
	{
		LFString fileName(LFSystemData::LFLevelDataName);
		if (fileIndex >= 0)
			fileName.Replace(LFString("."), LFString(fileIndex) + ".");

		data = serializer.ReadStaticBinaryData(LFVFSPath::DataRead, fileName.ToChar());

		if (data.id != LFSystemData::LFLevelDataId)
		{
			fileName += " wrong or incompatible! LFLevelData::Load()";
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, fileName);
		}

		LFIoc<LFLogger>::Get().WriteOutput("Load Levels");
		return data.id == LFSystemData::LFLevelDataId;
	}

	void LFLevelData::Save(int fileIndex)
	{
		data.id = LFSystemData::LFLevelDataId;

		LFString fileName(LFSystemData::LFLevelDataName);
		if (fileIndex >= 0)
			fileName.Replace(LFString("."), LFString(fileIndex) + ".");

		serializer.WriteStaticBinaryData(LFVFSPath::DataRead, fileName.ToChar(), data);
		LFIoc<LFLogger>::Get().WriteOutput("Save Levels");
	}

	bool LFLevelData::Load()
	{
		return Load(-1); //load without index
	}

	bool LFLevelData::Load(const char *fileName)
	{
		data = serializer.ReadStaticBinaryData(LFVFSPath::No, fileName);
		
		if (data.id != LFSystemData::LFLevelDataId)
		{
			LFString fileFullName(fileName);
			fileFullName += " wrong or incompatible! LFLevelData::Load(const char *fileName)";
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, fileFullName);
		}

		LFIoc<LFLogger>::Get().WriteOutput("Load Levels");
		return data.id == LFSystemData::LFLevelDataId;
	}

	void LFLevelData::Save()
	{
		Save(-1); //save without index
	}

	void LFLevelData::Save(const char *fileName)
	{
		data.id = LFSystemData::LFLevelDataId;
		serializer.WriteStaticBinaryData(LFVFSPath::No, fileName, data);
		LFIoc<LFLogger>::Get().WriteOutput("Save Levels");
	}
}}}
