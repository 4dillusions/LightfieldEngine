/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFTestFoo.h"

namespace LF3Engine { namespace LFUnitTest 
{
	class LFTestFoo2 final : public LFTestFoo
	{
	public:
		int y;
		
		LFTestFoo2(int x, int y) : LFTestFoo(x), y(y)
		{ }
	};
}}
