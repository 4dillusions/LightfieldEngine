/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCommon\LFVFSPath.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFIO 
{
	class LFFile final
	{
		LFFile() = delete;
		LFFile(const LFFile&) = delete;
		LFFile(LFFile &&) = delete;
		LFFile &operator=(const LFFile &) = delete;
		LFFile &operator=(LFFile &&) = delete;

	public:
        static bool IsFileExist(LFCommon::LFVFSPath path, const char *fileName);
        static bool Delete(LFCommon::LFVFSPath path, const char *fileName);
	};
}}}}
