/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLogger.h"
#include "..\Common\LFDateTime.h"

#ifdef TIZEN
#include <dlog.h>
#endif

using namespace LFCore::Common;

namespace LFCore { namespace IO
{
    LFLogger LFLogger::instance;

    LFLogger::LFLogger() 
		#ifdef WIN32
		: wof(L"Log.txt")
		#endif
    { 
		
	}

	#ifdef TIZEN
    void LFLogger::LogTag(char *logTag)
    {
    	this->logTag = logTag;
    }
	#endif

    LFLogger::~LFLogger()
    {
		#ifdef WIN32
		wof.close();
		#endif
    }

    void LFLogger::WriteOutput(LFString &log)
    {
		WriteOutput(log.ToChar());
    }

	void LFLogger::WriteOutput(MessageType messageType, LFString &log)
	{	
		WriteOutput(messageType, log.ToChar());
	}

	void LFLogger::WriteOutput(MessageType messageType, const char *log)
	{
		LFString text;

		switch(messageType)
		{
			case MT_OK: text += "[OK] "; break;
			case MT_WARNING: text += "[!!WARNING!!] "; break;
			case MT_ERROR: text += "[!!ERROR!!] "; break;
			case MT_LEAK: text += "[!!LEAK!!] "; break;
			
			case MT_LOAD_ERROR: text += "[!!LOAD ERROR!!] "; break;
		}

		text += log;

		WriteOutput(text);
	}

	void LFLogger::WriteOutput(const char *log)
	{
		LFString text; 
		text += LFDateTime::Instance().GetCurrentTime();
		text += " ";
		text += log;

		#if /*defined(DEBUG) &&*/ defined(TIZEN)
		dlog_print(DLOG_VERBOSE, logTag, text.ToChar());
	    #endif

		#ifdef WIN32
		wof << text.ToChar() << std::endl;

			//#ifdef DEBUG
			std::cout << text.ToChar() << std::endl;
			//#endif
		#endif
	}
}}
