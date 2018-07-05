/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\Common\LFVFSManager.h"
#include "..\Common\LFString.h"
#include "LFLogger.h"

using namespace LFCore::Common;

#include <fstream>

namespace LFCore { namespace IO
{
	template <typename T> class LFSerializer
	{
	public:
		void WriteBinaryData(const char *fileName, T &data, LFVFSManager::VFSPath vfsPlace)
		{
			LFString fileFullName;

			if (vfsPlace != LFVFSManager::CP_NO)
				fileFullName += LFVFSManager::Instance()->Path(vfsPlace);

			fileFullName += fileName;

			std::ofstream outfile(fileFullName.ToChar(), std::ios::binary);
			outfile.write((char *)&data, sizeof(T));
		}

		T ReadBinaryData(const char *fileName, LFVFSManager::VFSPath vfsPlace)
		{
			T resultData = T();

			LFString fileFullName;

			if (vfsPlace != LFVFSManager::CP_NO)
				fileFullName += LFVFSManager::Instance()->Path(vfsPlace);

			fileFullName += fileName;

			std::ifstream inFile(fileFullName.ToChar(), std::ios::binary);

			if (inFile) 
				inFile.read((char *)&resultData, sizeof(T));
			else
			{
				fileFullName += " does not exist! LFSerializer::WriteBinaryData";
				LFLogger::Instance().WriteOutput(LFLogger::MT_LOAD_ERROR, fileFullName);
			}

			return resultData;
		}
	};
}}
