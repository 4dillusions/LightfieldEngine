/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "Test.h"
#include "..\Core\Common\LFString.h"
#include "..\Core\IO\LFLogger.h"
#include "..\Core\Collections\LFList.h"
#include "Core\CommonTest.h"
#include "Core\CollectionsTest.h"
#include "Core\IOTest.h"
#include "Core\MathTest.h"
#include "Script\ScriptTest.h"

using namespace LFCore::Common;
using namespace LFCore::IO;
using namespace LFCore::Collections;

namespace UnitTest
{
    int Test::errorCounter = 0;
	LFList<const char *> errorList = LFList<const char *>();

	void Test::PushErrorCounts(int errorCounter)
	{
		Test::errorCounter += errorCounter;
	}

    void Test::AssertOk(bool isOk, const char *description)
    {
        if (isOk)
        {
			LFLogger::Instance().WriteOutput(LFLogger::MT_OK, description);
        }
        else
        {
            errorCounter++;
			errorList.Add(description);
        }
    }

	void Test::Write(LFString &description)
	{
		LFLogger::Instance().WriteOutput(description);
	}

    void Test::WriteStatistics()
    {
		LFString text;

		LFLogger::Instance().WriteOutput("");
		LFLogger::Instance().WriteOutput("UnitTest - Total errors:");

		if (errorCounter > 0)
		{
			for (errorList.First(); errorList.IsDone(); errorList.Next())
				LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, errorList.Current());
		}
		else
			LFCore::IO::LFLogger::Instance().WriteOutput("0 error");
    }
	
    void Test::CoreSystemTest()
    {
		CollectionsTest collectionsTest;
		collectionsTest.DictionaryTest();
		collectionsTest.ListTest();

		CommonTest commonTest;
		commonTest.VFSManagerTest();
		commonTest.EventTest();
		commonTest.EventArgsTest();
		commonTest.GameComponentTest();
		commonTest.GameCompositComponentTest();
		commonTest.MemoryTest();
		commonTest.StringTest();
		commonTest.TimerTest();
		commonTest.WatchTest();

		IOTest ioTest;
		ioTest.SerializerTest();

		MathTest mathTest;
		mathTest.CircleTest();
		mathTest.MathMainTest();
		mathTest.Matrix4Test();
		mathTest.RandomTest();
		mathTest.RectangleTest();
		mathTest.Vector2DTest();
		mathTest.Vector3DTest();
    }

	void Test::ScriptSystemTest()
	{
		ScriptTest scriptTest;
		scriptTest.LoadTest();
		scriptTest.LoadBytecodeTest();
		scriptTest.GetGlobalTest();
		scriptTest.GetGlobalBytecodeTest();
		scriptTest.CppFromLuaFunctionTest();
		scriptTest.CppFromLuaFunctionBytecodeTest();
		scriptTest.MetatableTest();
	}
};
