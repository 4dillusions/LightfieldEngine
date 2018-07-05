/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	struct LFAppData
	{
		int argc, returnValue; 
		char **argv; 
		char *logTag;
		char *package;
	};
}}}
