#pragma once

#include "..\\IO\\SMLogger.h"

using namespace SMEngine::IO;

namespace SMEngine { namespace Test
{
	class SMTest
	{
    private:
        static int errorCounter;

    public:
        static void AssertOk(bool isOk, const char *description);
        void WriteStatistics();

        void SMIOSystemTest();
        void SMMathSystemTest();
        void SMCoreSystemTest();
        void SMInputSystemTest();
        void SMAudioSystemTest();
        void SMEngineSystemTest();
        void SMGraphicsSystemTest();
	};
};};
