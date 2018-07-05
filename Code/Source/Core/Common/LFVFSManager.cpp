/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFVFSManager.h"
#include "LFMemoryManager.h"
#include "..\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFCore { namespace Common
{
	LFVFSManager *LFVFSManager::instance = nullptr;

	LFVFSManager::LFVFSManager() : vfsPathList(false)
	{ }

	void LFVFSManager::AddPath(const VFSPath &pathEnum, const char *path)
	{
		vfsPathList.Add(pathEnum, path);
	}

	const char *LFVFSManager::Path(const VFSPath &pathEnum)
	{
		return vfsPathList.FindItem(pathEnum);
	}

	LFVFSManager *LFVFSManager::Instance()
	{
		return instance;
	}

	void LFVFSManager::CreateInstance()
	{
		if (instance == nullptr)
		{
			LFLogger::Instance().WriteOutput("Create VFS Manager");
			instance = LFNew<LFVFSManager>(AT);
		}
	}

	void LFVFSManager::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			LFLogger::Instance().WriteOutput("Release VFS Manager");
			LFDelete(instance);
		}
	}
}}
