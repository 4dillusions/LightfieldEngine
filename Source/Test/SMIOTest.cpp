#include "SMIOTest.h"
#include "SMTest.h"
#include "..\\IO\\SMLogger.h"
#include "..\\IO\\SMSerializer.h"

using namespace SMEngine::IO;

namespace SMEngine { namespace Test
{
    void SMIOTest::SMLoggerTest()
    {
        SMLogger::Instance().WriteOutput("OK SMIOTest::SMLoggerTest");
    }
	
    struct TestData { int x[5]; };

	void SMIOTest::SMSerializerTest()
    {
		TestData data;
		for(int i = 0; i < 5; ++i)
			data.x[i] = 1;

		data.x[0] = 22;

		SMSerializer<TestData> ser;
		ser.WriteBinaryData("testData.dat", data);

		TestData data2 = ser.ReadBinaryData("testData.dat");
		int dataArrayNum = 0;
		for(int i = 0; i < 5; ++i)
			dataArrayNum += data2.x[i];

		SMTest::AssertOk(dataArrayNum == 26, "SMIOTest::SMSerializerTest");
    }
};};
