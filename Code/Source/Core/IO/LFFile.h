/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"

namespace LFCore { namespace IO
{
	class LFCORE_LIBRARY LFFile
	{
    private:
		LFFile();
		~LFFile();
	    
		static LFFile instance;
		
	public:
		static LFFile &Instance() { return instance; }

		bool IsFileExist(const char *fileNameAndPath, bool isBinary);
	};
}}
