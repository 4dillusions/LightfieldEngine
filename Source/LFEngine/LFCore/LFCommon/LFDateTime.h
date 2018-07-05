/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFString.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	class LFDateTime final
	{
		LFDateTime() = delete;
		LFDateTime(const LFDateTime&) = delete;
		LFDateTime(LFDateTime &&) = delete;
		LFDateTime &operator=(const LFDateTime &) = delete;
		LFDateTime &operator=(LFDateTime &&) = delete;
		~LFDateTime() = delete;

	public:
		static LFString GetTimeStamp(); //for logging
		static LFString GetSqlTimeStamp(); //for MySQL (fractional-second time datatypes supported in MySQL 5.6.4 or later)
		static LFString GetSQLTimeStampNumbers(); //for MySQL (under the version 5.6.4)
	};
}}}}