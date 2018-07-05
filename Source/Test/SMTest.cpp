#include "SMTest.h"

#include "SMIOTest.h"
#include "SMMathTest.h"
#include "SMCoreTest.h"
#include "SMInputTest.h"
#include "SMAudioTest.h"
#include "SMEngineTest.h"
#include "SMGraphicsTest.h"

namespace SMEngine { namespace Test
{
    int SMTest::errorCounter = 0;

    void SMTest::AssertOk(bool isOk, const char *description)
    {
        SMString text;

        if (isOk)
        {
            text.Append("OK ");
            text.Append(description);
            SMLogger::Instance().WriteOutput(text);
        }
        else
        {
            errorCounter++;

            text.Append("!!ERROR!! ");
            text.Append(description);
            SMLogger::Instance().WriteOutput(text);
        }
    }

    void SMTest::WriteStatistics()
    {
        SMLogger::Instance().WriteOutput("Total errors:");

        SMString text;
        text.Append(errorCounter);
        SMLogger::Instance().WriteOutput(text);
    }

    void SMTest::SMIOSystemTest()
    {
        SMIOTest test;

        test.SMLoggerTest();
        test.SMSerializerTest();
    }

    void SMTest::SMMathSystemTest()
    {
        SMMathTest test;

        test.SMMathMainTest();
        test.SMMatrix4Test();
        test.SMRandomTest();
        test.SMRectangleTest();
        test.SMVector2DTest();
    }

    void SMTest::SMCoreSystemTest()
    {
    	SMCoreTest test;

    	test.SMStringTest();
        test.SMSmartPtrTest();
        test.SMArrayTest();
        test.SMArray2DTest();
        test.SMTupleTest();
        test.SMParamsTest();
        test.SMTimerTest();
        test.SMListTest();
        test.SMDictionaryTest();
        test.SMEventTest();
        test.SMEventArgsTest();
        test.SMGameComponentTest();
    }

    void SMTest::SMInputSystemTest()
    {
        SMInputTest test;

        test.SMTouchTest();
    }

    void SMTest::SMAudioSystemTest()
    {
        SMAudioTest test;

        test.SMPlayMusicTest();
    }

    void SMTest::SMEngineSystemTest()
    {
        SMEngineTest test;

        test.SMInfoTest();
    }

    void SMTest::SMGraphicsSystemTest()
    {
		SMGraphicsTest test;

		test.SMVbTest();
		test.SMTextureTest();
    }
};};
