/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\..\Common.h"

#ifdef WIN32
	#ifdef LFCORE_EXPORTS
		#define LFCORE_LIBRARY __declspec(dllexport)
	#else
		#define LFCORE_LIBRARY __declspec(dllimport)
	#endif
#else
	#define LFCORE_LIBRARY /**/
#endif
