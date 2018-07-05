#include "SMWatch.h"

namespace SMEngine { namespace Core
{
	void SMTime::operator += (const SMTime &value)
	{
		minute += value.minute;
		second += value.second;
	}

	bool SMTime::operator == (const SMTime &value) const
	{
		return (minute == value.minute && second == value.second);
	}

	SMWatch::SMWatch(const SMTime &time, const SMTime &min, const SMTime &max) : time(time), min(min), max(max),
			AlarmEvent(&SMIWatchAlarmEventHandler::Alarm)
	{
		changer = SMTime();
	}

	void SMWatch::Reset()
	{
		time = SMTime();
		changer = SMTime();
	}

	void SMWatch::ChangeTime(const SMTime &value)
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

		if (time == min || time == max)
			AlarmEvent();
	}

	SMWatch &SMWatch::operator ++ (int)
	{
		changer.second = 1;
		ChangeTime(changer);

		return *this;
	}

	SMWatch &SMWatch::operator -- (int)
	{
		changer.second = -1;
		ChangeTime(changer);

		return *this;
	}
};};
