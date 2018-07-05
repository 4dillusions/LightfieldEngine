/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFFile.h"
#include <stdio.h>

namespace LFCore { namespace IO
{
	LFFile LFFile::instance;

	LFFile::LFFile()
    { }

	LFFile::~LFFile()
	{ }

	bool LFFile::IsFileExist(const char *fileNameAndPath, bool isBinary)
    {
		bool result = false;
		
		if (isBinary)
			result = (fopen(fileNameAndPath, "rb") != 0);
		else
			result = (fopen(fileNameAndPath, "r") != 0);

		return result;
    }
}}
