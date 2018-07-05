/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFWatch.h"

namespace LFCore { namespace Common
{
	void LFTime::operator += (const LFTime &value)
	{
		minute += value.minute;
		second += value.second;
	}

	bool LFTime::operator == (const LFTime &value) const
	{
		return (minute == value.minute && second == value.second);
	}

	LFWatch::LFWatch(const LFTime &time, const LFTime &minTime, const LFTime &maxTime) : minTime(minTime), maxTime(maxTime), time(time),
			AlarmEvent(&LFIWatchAlarmEventHandler::OnAlarm)
	{
		changerTime = LFTime();
	}

	void LFWatch::Reset()
	{
		time = LFTime();
		changerTime = LFTime();
	}

	void LFWatch::ChangeTime(const LFTime &value)
	{
		time += value;

		if (time.second > 59)
		{
			time.second = 0;
			time.minute++;
		}
		else if (time.second < 0)
		{
			time.second = 59;
			time.minute--;
		}

		if (time == minTime || time == maxTime)
			AlarmEvent();
	}

	LFWatch &LFWatch::operator ++ (int)
	{
		changerTime.second = 1;
		ChangeTime(changerTime);

		return *this;
	}

	LFWatch &LFWatch::operator -- (int)
	{
		changerTime.second = -1;
		ChangeTime(changerTime);

		return *this;
	}
}}
