/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameStatedata.h"
#include "..\LFCore\LFIO\LFLogger.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	LFGameStateData::LFGameStateData()
	{
		LFGameStateData::Reset();
	}

	void LFGameStateData::Reset()
	{
		data.id = 0;
		data.levelIndexPuzzle = 0;
		data.levelIndexArcade = 0;
		data.second = 0;
		data.lives = 0;
		data.scorePuzzle = 0;
		data.scoreArcade = 0;
		data.rank = 0;
	
		data.editorData.levelSizeX = 0;
		data.editorData.levelSizeY = 0;
		data.editorData.tilesId = 0;
		data.editorData.zoom = 0;
	}
	
	bool LFGameStateData::Load()
	{
		data = serializer.ReadStaticBinaryData(LFVFSPath::DataReadWrite, LFSystemData::LFGameStateDataName);
	
		if (data.id != LFSystemData::LFGameStateDataId)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Info, "Reset and save!");
			Reset();
			Save();
		}
	
		LFIoc<LFLogger>::Get().WriteOutput("Load GameState");
		return data.id == LFSystemData::LFGameStateDataId;
	}
	
	bool LFGameStateData::Load(const char *fileName)
	{
		data = serializer.ReadStaticBinaryData(LFVFSPath::No, fileName);
	
		if (data.id != LFSystemData::LFGameStateDataId)
		{
			LFString fileFullName(fileName);
			fileFullName += " wrong or incompatible! LFGameStateData::Load(const char *fileName)";
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Info, fileFullName);
		}
	
		LFIoc<LFLogger>::Get().WriteOutput("Load GameState");
		return data.id == LFSystemData::LFGameStateDataId;
	}
	
	void LFGameStateData::Save()
	{
		data.id = LFSystemData::LFGameStateDataId;
		serializer.WriteStaticBinaryData(LFVFSPath::DataReadWrite, LFSystemData::LFGameStateDataName, data);
		LFIoc<LFLogger>::Get().WriteOutput("Save GameState");
	}
	
	void LFGameStateData::Save(const char *fileName)
	{
		data.id = LFSystemData::LFGameStateDataId;
		serializer.WriteStaticBinaryData(LFVFSPath::No, fileName, data);
		LFIoc<LFLogger>::Get().WriteOutput("Save GameState");
	}
}}}
