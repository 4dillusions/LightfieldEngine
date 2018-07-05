/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFEvent.h"

namespace LFCore { namespace Common
{
	struct LFTime
	{
		int minute, second;

		LFTime() : minute(0), second(0)
		{ }

		LFTime(int minute, int second) : minute(minute), second(second)
		{ }

		void operator += (const LFTime &value);
		bool operator == (const LFTime &value) const;
	};

	class LFCORE_LIBRARY LFIWatchAlarmEventHandler
	{
	public:
		virtual ~LFIWatchAlarmEventHandler() { }
		virtual void OnAlarm() = 0;
	};

	class LFCORE_LIBRARY LFWatch
	{
	private:
		LFTime minTime, maxTime, changerTime;

		void ChangeTime(const LFTime &value);

	public:
		LFTime time;
		LFEvent<LFIWatchAlarmEventHandler> AlarmEvent;

		explicit LFWatch(const LFTime &time, const LFTime &min = LFTime(), const LFTime &max = LFTime());

		void Reset();
		LFWatch &operator ++ (int); //increase seconds
		LFWatch &operator -- (int); //decrease seconds
		bool Min() { return time == minTime; }
		bool Max() { return time == maxTime; }
	};
}}
