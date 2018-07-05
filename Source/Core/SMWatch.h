#pragma once

#include "SMEvent.h"

namespace SMEngine { namespace Core
{
	struct SMTime
	{
		int minute, second;

		SMTime() : minute(0), second(0)
		{ }

		SMTime(int minute, int second) : minute(minute), second(second)
		{ }

		void operator += (const SMTime &value);
		bool operator == (const SMTime &value) const;
	};

	/*
	�ra t�pus: Perc �s m�sodperc alap� id�t t�rol �s l�ptet fel, vagy le m�sodpercenk�nt.
	*/
	class SMWatch
	{
	private:
		SMTime min, max, changer;

		void ChangeTime(const SMTime &value);

	public:
		SMTime time;

		SMWatch(const SMTime &time, const SMTime &min = SMTime(), const SMTime &max = SMTime());

		SMEvent<SMIWatchAlarmEventHandler> AlarmEvent;

		void Reset();
		SMWatch &operator ++ (int);
		SMWatch &operator -- (int);
		bool Min() { return time == min; }
		bool Max() { return time == max; }
	};
};};
