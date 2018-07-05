/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTime.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	LFTime::LFTime(int minute, int second) : minute(minute), second(second)
	{ }

	void LFTime::operator += (const LFTime &value)
	{
		minute += value.minute;
		second += value.second;
	}

	bool LFTime::operator == (const LFTime &value) const
	{
		return (minute == value.minute && second == value.second);
	}
}}}}