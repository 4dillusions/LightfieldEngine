/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFWatch.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	LFWatch::LFWatch(const LFTime &time, const LFTime &minTime, const LFTime &maxTime) : time(time), minTime(minTime), maxTime(maxTime)
	{
		changerTime = LFTime();
	}

	void LFWatch::SetAlarmEvent(const std::function<void()> &alarmEvent)
	{
		this->alarmEvent = alarmEvent;
	}

	const LFTime &LFWatch::GetTime() const
	{
		return time;
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
			if (alarmEvent != nullptr)
				alarmEvent();
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

	bool LFWatch::IsMin() const
	{
		return time == minTime;
	}

	bool LFWatch::IsMax() const
	{
		return time == maxTime;
	}
}}}}