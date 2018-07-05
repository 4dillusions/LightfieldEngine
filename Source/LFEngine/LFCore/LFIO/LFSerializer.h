/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLogger.h"
#include "..\LFCommon\LFVFSManager.h"
#include "..\LFCommon\LFString.h"
#include "..\LFPatterns\LFIoc.h"

#include <fstream>

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFIO
{
	template <typename T> class LFSerializer final
	{
	public:
		void WriteStaticBinaryData(LFVFSPath path, const char *fileName, T &data)
		{
			LFString fileFullName;

			if (path != LFVFSPath::No)
				fileFullName += LFIoc<LFVFSManager *>::Get()->GetPath(path);

			fileFullName += fileName;

			std::ofstream outfile(fileFullName.ToChar(), std::ios::binary);
			outfile.write(reinterpret_cast<char *>(&data), sizeof(T));
			outfile.close();
		}

		T ReadStaticBinaryData(LFVFSPath path, const char *fileName)
		{
			T resultData = T();

			LFString fileFullName;

			if (path != LFVFSPath::No)
				fileFullName += LFIoc<LFVFSManager *>::Get()->GetPath(path);

			fileFullName += fileName;

			std::ifstream inFile(fileFullName.ToChar(), std::ios::binary);

			if (inFile)
			{
				inFile.read(reinterpret_cast<char *>(&resultData), sizeof(T));
				inFile.close();
			}
			else
			{
				fileFullName += LFString(" does not exist! ") + INFO;
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, fileFullName);
			}

			return resultData;
		}

		void WriteDynamicBinaryData(LFVFSPath path, const char *fileName, T *data, size_t size)
		{
			LFString fileFullName;

			if (path != LFVFSPath::No)
				fileFullName += LFIoc<LFVFSManager *>::Get()->GetPath(path);

			fileFullName += fileName;

			std::ofstream outfile(fileFullName.ToChar(), std::ios::binary);
			outfile.write(reinterpret_cast<char *>(data), size);
			outfile.close();
		}

		void ReadDynamicBinaryData(LFVFSPath path, const char *fileName, T *data, size_t size)
		{
			LFString fileFullName;

			if (path != LFVFSPath::No)
				fileFullName += LFIoc<LFVFSManager *>::Get()->GetPath(path);

			fileFullName += fileName;

			std::ifstream inFile(fileFullName.ToChar(), std::ios::binary);

			if (inFile)
			{
				inFile.read(reinterpret_cast<char *>(data), size);
				inFile.close();
			}
			else
			{
				fileFullName += LFString(" does not exist! ") + INFO;
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, fileFullName);
			}
		}
	};
}}}}
