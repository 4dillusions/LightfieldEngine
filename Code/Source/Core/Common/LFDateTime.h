/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFString.h"

namespace LFCore { namespace Common
{
	class LFCORE_LIBRARY LFDateTime
	{
    private:
		LFDateTime();
		~LFDateTime();
	    
		static LFDateTime instance;

	public:
		static LFDateTime &Instance() { return instance; }

		LFString GetCurrentTime();
		LFString GetCurrentDate();
	};
}}
