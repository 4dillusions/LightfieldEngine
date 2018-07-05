/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFOptionsData.h"
#include "LFDataConstants.h"
#include "..\..\Core\Common\LFMemoryManager.h"
#include "..\..\Core\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Data
{
	LFOptionsData::LFOptionsData()
	{
		Reset();
	}

	void LFOptionsData::Reset()
	{
		data.id = LFOptionsDataId;
		data.isMusicOn = true;
		data.isSFXOn = true;
		data.volumeMusic = 80;
		data.volumeSFX = 100;
	}

	bool LFOptionsData::Load()
	{
		data = serializer.ReadBinaryData(OptionsDataName, LFVFSManager::CP_DATA_SAVE);
		
		if (data.id != LFOptionsDataId)
		{
			LFLogger::Instance().WriteOutput(LFLogger::MT_OK, "Reset and save!");
			Reset();
			Save();
		}

		LFLogger::Instance().WriteOutput("Load Options");
		return (data.id == LFOptionsDataId);
	}

	bool LFOptionsData::Load(const char *fileName)
	{
		data = serializer.ReadBinaryData(fileName, LFVFSManager::CP_NO);

		if (data.id != LFOptionsDataId)
		{
			LFString fileFullName;
			fileFullName += fileName;
			fileFullName += " wrong or incompatible! LFOptionsData::Load(const char *fileName)";
			LFLogger::Instance().WriteOutput(LFLogger::MT_LOAD_ERROR, fileFullName);
		}
		
		LFLogger::Instance().WriteOutput("Load Options");
		return (data.id == LFOptionsDataId);
	}

	void LFOptionsData::Save()
	{
		data.id = LFOptionsDataId;
		serializer.WriteBinaryData(OptionsDataName, data, LFVFSManager::CP_DATA_SAVE);
		LFLogger::Instance().WriteOutput("Save Options");
	}

	void LFOptionsData::Save(const char *fileName)
	{
		data.id = LFOptionsDataId;
		serializer.WriteBinaryData(fileName, data, LFVFSManager::CP_NO);
		LFLogger::Instance().WriteOutput("Save Options");
	}
}}
