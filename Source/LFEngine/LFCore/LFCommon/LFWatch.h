/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFTime.h"
#include <functional>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	class LFWatch final
	{
		LFTime time, minTime, maxTime, changerTime;
		std::function<void()> alarmEvent = nullptr;

		LFWatch(const LFWatch&) = delete;
		LFWatch(LFWatch &&) = delete;
		LFWatch &operator=(const LFWatch &) = delete;
		LFWatch &operator=(LFWatch &&) = delete;

		void ChangeTime(const LFTime &value);

	public:
		explicit LFWatch(const LFTime &time, const LFTime &min = LFTime(), const LFTime &max = LFTime());

		void SetAlarmEvent(const std::function<void()> &alarmEvent);
		const LFTime &GetTime() const;

		void Reset();
		/** @brief increase seconds */
		LFWatch &operator ++ (int);

		/** @brief decrease seconds */
		LFWatch &operator -- (int);

		bool IsMin() const;
		bool IsMax() const;
	};
}}}}