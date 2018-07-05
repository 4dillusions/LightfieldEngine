/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFVFSPath.h"
#include "LFString.h"
#include "..\LFCollections\LFDictionary.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	/**
		@brief
		VFS: Virtual File System
	*/
	class LFVFSManager final
	{
		LFCollections::LFDictionary<LFVFSPath, LFString> vfsPathList;

		LFVFSManager(const LFVFSManager&) = delete;
		LFVFSManager(LFVFSManager &&) = delete;
		LFVFSManager &operator=(const LFVFSManager &) = delete;
		LFVFSManager &operator=(LFVFSManager &&) = delete;

	public:
		LFVFSManager();
		~LFVFSManager();

		const char *GetPath(const LFVFSPath &pathEnum);
	};
}}}}
