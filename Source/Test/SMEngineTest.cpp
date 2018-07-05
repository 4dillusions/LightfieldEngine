#include "SMEngineTest.h"
#include "..\\Test\\SMTest.h"
#include "..\\Engine\\SMSystemInfo.h"

using namespace SMEngine::Engine;

namespace SMEngine { namespace Test
{
    void SMEngineTest::SMInfoTest()
    {
    	SMLogger::Instance().WriteOutput("------------system info");

    	SMString allocText;
    	allocText.Append("screen: ");
    	allocText.Append(SMSystemInfo::Instance().ScreenWidth());
    	allocText.Append(" ");
    	allocText.Append(SMSystemInfo::Instance().ScreenHeight());
    	SMLogger::Instance().WriteOutput(allocText);

    	SMString avMemText;
    	avMemText.Append("available memory: ");
    	avMemText.Append(SMSystemInfo::Instance().AvailableMemory());
    	SMLogger::Instance().WriteOutput(avMemText);

    	SMString allocMemText;
    	allocMemText.Append("allocated memory: ");
    	allocMemText.Append(SMSystemInfo::Instance().AllocatedMemory());
    	SMLogger::Instance().WriteOutput(allocMemText);

    	SMString allocMaxMemText;
    	allocMaxMemText.Append("max allocated memory: ");
    	allocMaxMemText.Append(SMSystemInfo::Instance().AllocatedMemory());
    	SMLogger::Instance().WriteOutput(allocMaxMemText);

    	SMString avVideoMemText;
    	avVideoMemText.Append("available video memory: ");
    	avVideoMemText.Append(SMSystemInfo::Instance().AvailableVideoMemory());
    	SMLogger::Instance().WriteOutput(avVideoMemText);
    }
};};
