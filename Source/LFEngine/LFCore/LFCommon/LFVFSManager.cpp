/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVFSManager.h"
#include "..\LFIO\LFLogger.h"
#include "..\LFPatterns\LFIoc.h"

#ifdef WINCLASSIC
#include "..\..\LFCore\LFCommon\LFSystemData.h"
#include "..\..\LFData\LFAppData.h"

using namespace LF3Engine::LFEngine::LFData;
#endif

#ifdef TIZEN
#include <app_common.h>
#endif

using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	LFVFSManager::LFVFSManager()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Create VFS Manager");

		#ifdef WINCLASSIC
			auto pathAndName = LFString(LFSystemData::GetAppData().argv[0]);
			auto splits = pathAndName.Split('\\');
			auto splitName = splits[splits.GetLength() - 1];
			auto programName = splits[splits.GetLength() - 1].Split('.')[0];
			
			vfsPathList.Add(LFVFSPath::No, LFString());
			vfsPathList.Add(LFVFSPath::Sound, programName + LFString("/Home/Media/Sound/"));
			vfsPathList.Add(LFVFSPath::Image, programName + LFString("/Home/Media/Image/"));
			vfsPathList.Add(LFVFSPath::DataRead, programName + LFString("/Home/Data/"));
			vfsPathList.Add(LFVFSPath::ShaderEffect, programName + LFString("/Home/Media/ShaderEffect/"));
			vfsPathList.Add(LFVFSPath::DataReadWrite, programName + LFString("/Home/Data/"));
		#endif

		#ifdef TIZEN
			auto path = LFString(app_get_shared_resource_path());

			vfsPathList.Add(LFVFSPath::No, LFString());
			vfsPathList.Add(LFVFSPath::Sound, path + "Home/Media/Sound/");
			vfsPathList.Add(LFVFSPath::Image, path + "Home/Media/Image/");
			vfsPathList.Add(LFVFSPath::DataRead, path + "Home/Data/");
			vfsPathList.Add(LFVFSPath::ShaderEffect, path + "Home/Media/ShaderEffect/");
			vfsPathList.Add(LFVFSPath::DataReadWrite, LFString(app_get_data_path()));
		#endif
	}

	LFVFSManager::~LFVFSManager()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Release VFS Manager");
	}

	const char *LFVFSManager::GetPath(const LFVFSPath &pathEnum)
	{
		return vfsPathList.GetItem(pathEnum).ToChar();
	}
}}}}
