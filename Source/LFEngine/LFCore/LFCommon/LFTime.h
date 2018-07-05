/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	struct LFTime final
	{
		int minute = 0, second = 0;

		LFTime() = default;
		LFTime(int minute, int second);

		void operator += (const LFTime &value);
		bool operator == (const LFTime &value) const;
	};
}}}}