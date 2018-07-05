/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include <functional>
#include "LFLogMessageType.h"
#include "LFLogOutputType.h"

#ifdef WINCLASSIC
    #include <fstream>
#endif

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
    class LFString;
}}}}

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFIO
{
    class LFLogger final
    {
        bool outputTypes[static_cast<unsigned int>(LFLogOutputType::Count)];
        std::function<void (const LFCommon::LFString &log)> logTrigger = nullptr;

        #ifdef WINCLASSIC
            std::wofstream wof;
        #endif

        #ifdef TIZEN
            char *logTag = nullptr;
        #endif

		LFCommon::LFString *buffer = nullptr;

		int warnings = 0, errors = 0;

        LFLogger(const LFLogger&) = delete;
        LFLogger(LFLogger &&) = delete;
        LFLogger &operator=(const LFLogger &) = delete;
        LFLogger &operator=(LFLogger &&) = delete;

    public:
		const char *const LogFileName = "Log.txt";

        const char *const InfoTag = "[Info]";
        const char *const WarningTag = "[Warning]";
        const char *const ErrorTag = "[Error]";

        LFLogger();
        ~LFLogger();

		/** @brief Avoid buffer leak before detecting */
		void ReleaseBuffer();

        void SetOutputTypeFlag(LFLogOutputType outputType, bool isEnable);

		/** @brief Log trigger helps show logs another environment for example in editor */
        void SetLogTrigger(const std::function<void (const LFCommon::LFString &log)> &logTrigger);

		LFCommon::LFString const *GetBuffer() const;

	    LFCommon::LFString GetWarnings() const;
		LFCommon::LFString GetErrors() const;

        void WriteOutput(const LFCommon::LFString &log);
        void WriteOutput(LFLogMessageType messageType, const LFCommon::LFString &log);
        void WriteOutput(LFLogMessageType messageType, const char *log);
        void WriteOutput(const char *log);
    };
}}}}
