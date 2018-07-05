/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFDateTime.h"
#include <ctime>
#include <chrono>

using namespace std::chrono;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	LFString LFDateTime::GetTimeStamp()
	{
		time_t currentTime;
		struct tm *localTime;

		time(&currentTime);
		localTime = localtime(&currentTime);

		//xample: [08.09.2014 17:51:04]
		return LFString('[') + localTime->tm_mday + "." + (localTime->tm_mon + 1) + "." + (localTime->tm_year + 1900) + " " + localTime->tm_hour + ":" + localTime->tm_min + ":" + localTime->tm_sec + "] ";
	}

	LFString LFDateTime::GetSqlTimeStamp()
	{
		time_t currentTime;
		struct tm *localTime;

		time(&currentTime);
		localTime = localtime(&currentTime);

		int milliseconds = duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count() % 1000;

		//xample: '2014-09-08 17:51:04.777'
		return LFString(localTime->tm_year + 1900) + "-" + (localTime->tm_mon + 1) + "-" + localTime->tm_mday + " " + 
			localTime->tm_hour + ":" + localTime->tm_min + ":" + localTime->tm_sec + "." + milliseconds;
	}

	LFString LFDateTime::GetSQLTimeStampNumbers()
	{
		LFString result(GetSqlTimeStamp());
		result.Replace('-', ' ');
		result.Replace(':', ' ');
		result.Replace('.', ' ');
		result.Trim();

		//xample: '20140908175104777'
		return result;
	}
}}}}
