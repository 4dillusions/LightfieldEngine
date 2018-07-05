/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFDateTime.h"
#include <ctime>

namespace LFCore { namespace Common
{
	LFDateTime LFDateTime::instance;

	LFDateTime::LFDateTime()
    { }

	LFDateTime::~LFDateTime()
    { }

	LFString LFDateTime::GetCurrentTime()
    {
		LFString result;

		time_t currentTime;
		struct tm *localTime;

		time(&currentTime);
		localTime = localtime(&currentTime);

		result += localTime->tm_hour;
		result += ":";
		result += localTime->tm_min;
		result += ":";
		result += localTime->tm_sec;

		return result;
    }

	LFString LFDateTime::GetCurrentDate()
	{
		LFString result;

		time_t currentTime;
		struct tm *localTime;

		time(&currentTime);
		localTime = localtime(&currentTime);

		result += localTime->tm_mday;
		result += ".";
		result += localTime->tm_mon + 1;
		result += ".";
		result += localTime->tm_year + 1900;

		return result;
	}
}}
