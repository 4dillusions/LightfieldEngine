/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore
{
	/**
		@brief
		analyzer macro for UnitTest and MemoryManager
	*/
	#define LFSTRINGIFY(x) #x
	#define LFTOSTRING(x) LFSTRINGIFY(x)
	#define INFO __FILE__ ": " LFTOSTRING(__LINE__)
}}}
