#include "SMLogger.h"
#include "..\\Core\\SMCore.h"
#include "..\\Engine\\SMSystemInfo.h"

using namespace SMEngine::Engine;

namespace SMEngine { namespace IO
{
    SMLogger SMLogger::instance;

    SMLogger::SMLogger()
    {
    	SMString text;
    	text.Append("Start log ");
    	text.Append(SMSystemInfo::Instance().DateTime());

    	SMLogger::Instance().WriteOutput(text);
    }

    SMLogger::~SMLogger()
    {
    	SMString text;
    	text.Append("End log ");
    	text.Append(SMSystemInfo::Instance().DateTime());

    	SMLogger::Instance().WriteOutput(text);
    }

	void SMLogger::WriteOutput(const char *log)
	{
		#ifdef _DEBUG

		AppLog("%s", log);

		#endif
	}

	void WriteOutput(const SMParams<const char *> &log)
	{
		#ifdef _DEBUG

		SMString text;
		for (int i = 0; i < log.Lenght(); ++i)
			text.Append(log[i]);

		AppLog("%ls", text.ToBadaChar());

		#endif
	}

	void SMLogger::WriteOutput(const SMString &log)
	{
		#ifdef _DEBUG

		AppLog("%ls", SMString(log).ToBadaChar());

		#endif
	}
};};
