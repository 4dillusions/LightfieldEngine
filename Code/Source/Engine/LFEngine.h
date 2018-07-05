/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\..\Common.h"

#ifdef WIN32
	#ifdef LFENGINE_EXPORTS
		#define LFENGINE_LIBRARY __declspec(dllexport)
	#else
		#define LFENGINE_LIBRARY __declspec(dllimport)
	#endif
#else
	#define LFENGINE_LIBRARY /**/
#endif
