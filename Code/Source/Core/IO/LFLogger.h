/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCore.h"

#ifdef WIN32
#include <string>
#include <fstream>
#include <iostream>
#endif

namespace LFCore { namespace Common
{
	class LFString;
}}

namespace LFCore { namespace IO
{
	class LFCORE_LIBRARY LFLogger
	{
    private:
	    LFLogger();
	    ~LFLogger();
	    
		static LFLogger instance;
		
		#ifdef WIN32
		std::wofstream wof;
		#endif

		#ifdef TIZEN
		char *logTag;
		#endif

	public:
		enum MessageType
		{
			MT_OK,
			MT_WARNING,
			MT_ERROR,
			MT_LEAK,
			MT_LOAD_ERROR,
		};

        static LFLogger &Instance() { return instance; }

		#ifdef TIZEN
        void LogTag(char *logTag);
		#endif		

		void WriteOutput(LFCore::Common::LFString &log);
		void WriteOutput(MessageType errorType, LFCore::Common::LFString &log);
		void WriteOutput(MessageType errorType, const char *log);
		void WriteOutput(const char *log);
	};
}}
