/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFOptionsData.h"
#include "..\LFCore\LFPatterns\LFIoc.h"
#include "..\LFCore\LFIO\LFLogger.h"
#include "..\LFCore\LFCommon\LFDateTime.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	LFOptionsData::LFOptionsData()
	{
		LFOptionsData::Reset();
	}

	void LFOptionsData::Reset()
	{
		data.id = LFSystemData::LFOptionsDataId;
		data.isMusicOn = true;
		data.isSFXOn = true;
		data.volumeMusic = 0.8f;
		data.volumeSFX = 1.0;
		LFString::CopyToArray("Player", data.playerName);
		LFString::CopyToArray(const_cast<char *>(LFDateTime::GetSQLTimeStampNumbers().ToChar()), data.phoneId);
	}

	bool LFOptionsData::Load()
	{
		data = serializer.ReadStaticBinaryData(LFVFSPath::DataReadWrite, LFSystemData::LFOptionsDataName);
		
		if (data.id != LFSystemData::LFOptionsDataId)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Info, "Reset and save!");
			Reset();
			Save();
		}

		LFIoc<LFLogger>::Get().WriteOutput("Load Options");
		return data.id == LFSystemData::LFOptionsDataId;
	}

	bool LFOptionsData::Load(const char *fileName)
	{
		data = serializer.ReadStaticBinaryData(LFVFSPath::No, fileName);

		if (data.id != LFSystemData::LFOptionsDataId)
		{
			LFString fileFullName(fileName);
			fileFullName += " wrong or incompatible! LFOptionsData::Load(const char *fileName)";
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, fileFullName);
		}
		
		LFIoc<LFLogger>::Get().WriteOutput("Load Options");
		return data.id == LFSystemData::LFOptionsDataId;
	}

	void LFOptionsData::Save()
	{
		data.id = LFSystemData::LFOptionsDataId;
		serializer.WriteStaticBinaryData(LFVFSPath::DataReadWrite, LFSystemData::LFOptionsDataName, data);
		LFIoc<LFLogger>::Get().WriteOutput("Save Options");
	}

	void LFOptionsData::Save(const char *fileName)
	{
		data.id = LFSystemData::LFOptionsDataId;
		serializer.WriteStaticBinaryData(LFVFSPath::No, fileName, data);
		LFIoc<LFLogger>::Get().WriteOutput("Save Options");
	}
}}}
