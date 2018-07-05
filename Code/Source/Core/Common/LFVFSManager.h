/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"
#include "..\Collections\LFDictionary.h"

namespace LFCore { namespace Common
{
	/*
	VFS: Virtual File System
	*/
	class LFCORE_LIBRARY LFVFSManager
	{
	public:
		enum VFSPath { CP_NO, CP_IMAGE, CP_SOUND, CP_LEVEL, CP_SCRIPT, CP_DATA, CP_DATA_SAVE };

	private:
		static LFVFSManager *instance;

		LFCore::Collections::LFDictionary<VFSPath, const char *> vfsPathList;

	public:
		LFVFSManager();

		static LFVFSManager *Instance();
		static void CreateInstance();
		static void ReleaseInstance();

		void AddPath(const VFSPath &pathEnum, const char *path);
		const char *Path(const VFSPath &pathEnum);
	};
}}
