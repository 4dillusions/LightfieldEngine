/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFLogger.h"
#include "..\LFCommon\LFDateTime.h"
#include "..\LFCommon\LFString.h"

#ifdef TIZEN
	#include "..\..\LFCore\LFCommon\LFSystemData.h"
	#include "..\..\LFData\LFAppData.h"

	using namespace LF3Engine::LFEngine::LFData;
#endif

using namespace LF3Engine::LFEngine::LFCore::LFCommon;

#ifdef TIZEN
	#include <dlog.h>
#endif

#ifdef WINCLASSIC
	#include <iostream>
#endif

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFIO
{
	LFLogger::LFLogger() 
		#ifdef WINCLASSIC
			: wof(L"Log.txt")
		#endif
    {
		#ifdef TIZEN
		logTag = LFEngine::LFCore::LFCommon::LFSystemData::GetAppData().logTag;
		#endif

		buffer = LFMemoryManager::New<LFString>(INFO);

        for (unsigned int i = 0; i < static_cast<unsigned int>(LFLogOutputType::Count); i++)
			outputTypes[i] = false;
    }

    LFLogger::~LFLogger()
    {
		#ifdef WINCLASSIC
			wof.close();
		#endif
    }

	void LFLogger::ReleaseBuffer()
	{
		LFMemoryManager::Delete(buffer);
	}

	void LFLogger::SetOutputTypeFlag(LFLogOutputType outputType, bool isEnable)
	{
		outputTypes[static_cast<unsigned int>(outputType)] = isEnable;
	}

	void LFLogger::SetLogTrigger(const std::function<void (const LFString &log)> &logTrigger)
	{
		this->logTrigger = logTrigger;
	}

	LFString const *LFLogger::GetBuffer() const
	{
		return buffer;
	}

	LFString LFLogger::GetWarnings() const
	{
		return LFString(warnings);
	}

	LFString LFLogger::GetErrors() const
	{
		return LFString(errors);
	}

	void LFLogger::WriteOutput(const LFString &log)
    {
		WriteOutput(log.ToChar());
    }

	void LFLogger::WriteOutput(LFLogMessageType messageType, const LFString &log)
	{	
		WriteOutput(messageType, log.ToChar());
	}

	void LFLogger::WriteOutput(LFLogMessageType messageType, const char *log)
	{
		LFString text;

		switch (messageType)
		{
			case LFLogMessageType::Info: text += LFString(InfoTag) + " "; break;
			
			case LFLogMessageType::Warning: 
				text += LFString(WarningTag) + " ";
				warnings++;
				break;

			case LFLogMessageType::Error: 
				text += LFString(ErrorTag) + " "; 
				errors++;
				break;
		}

		text += log;

		WriteOutput(text);
	}

	void LFLogger::WriteOutput(const char *log)
	{
		LFString text = LFDateTime::GetTimeStamp() + log;

		if (outputTypes[static_cast<unsigned int>(LFLogOutputType::ToOutput)])
		{
			#ifdef WINCLASSIC
				std::cout << text.ToChar() << std::endl;
			#endif

			#ifdef TIZEN
				dlog_print(DLOG_VERBOSE, logTag, text.ToChar());
			#endif
		}

		if (outputTypes[static_cast<unsigned int>(LFLogOutputType::ToFile)])
		{
			#ifdef WINCLASSIC
				wof << text.ToChar() << std::endl;
			#endif
		}

		if (outputTypes[static_cast<unsigned int>(LFLogOutputType::ToLogTrigger)] && logTrigger != nullptr)
		{
			logTrigger(text);
		}

		if (outputTypes[static_cast<unsigned int>(LFLogOutputType::ToBuffer)])
		{
			if (buffer != nullptr)
				*buffer += text + '\n';
		}
	}
}}}}
