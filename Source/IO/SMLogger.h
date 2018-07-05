#pragma once

#include "..\\Core\\SMString.h"
#include "..\\Core\\SMParams.h"

using namespace SMEngine::Core;

namespace SMEngine { namespace IO
{
	/*
    Outputra, vagy game logfile-ba logol.
    Singleton objektum

    Használat:
    SMString text;
    text.Append(errorCounter);
    SMLogger::Instance().WriteOutput(text);
	*/
	class SMLogger
	{
    private:
	    SMLogger();
	    ~SMLogger();
	    static SMLogger instance;

	public:
        static SMLogger &Instance() { return instance; }

		void WriteOutput(const char *log);
		void WriteOutput(const SMParams<const char *> &log);
		void WriteOutput(const SMString &log);
	};
};};
