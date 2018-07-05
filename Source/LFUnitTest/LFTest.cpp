/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFTest.h"
#include "..\LFEngine\LFCore\LFPatterns\LFIoc.h"
#include "..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\LFEngine\LFCore\LFCommon\LFString.h"
#include "LFEngine\LFCore\LFCommonTest.h"
#include "LFEngine\LFCore\LFPatternsTest.h"
#include "LFEngine\LFCore\LFMathTest.h"
#include "LFEngine\LFCore\LFIOTest.h"
#include "LFEngine\LFCore\LFCollectionsTest.h"
#include "LFEngine\LFData\LFDataTest.h"
#include "LFEngine\LFNetwork\LFNetworkTest.h"

using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFUnitTest::LFEngine::LFCore;
using namespace LF3Engine::LFUnitTest::LFEngine::LFData;
using namespace LF3Engine::LFUnitTest::LFEngine::LFNetwork;

namespace LF3Engine { namespace LFUnitTest
{
	int LFTest::errorCounter = 0;
	int LFTest::tests = 0;
	int LFTest::passedTests = 0;
	std::list<const char *> LFTest::errorList;

	void LFTest::AssertOk(bool isOk, const char *at)
	{
		tests++;

		if (isOk)
			passedTests++;
		else
		{
			errorCounter++;
			errorList.push_back(at);
		}
	}

	void LFTest::WriteStatistics()
	{
		LFIoc<LFLogger>::Get().WriteOutput("UnitTest");
		LFIoc<LFLogger>::Get().WriteOutput(LFString("Passed: ") + tests + '/' + passedTests);
		LFIoc<LFLogger>::Get().WriteOutput("Unit test Errors:");

		if (errorCounter > 0)
			for (auto i : errorList)
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, i);
		else
			LFIoc<LFLogger>::Get().WriteOutput("0 error");
	}

	void LFTest::CoreSystemTests()
	{
		LFCommonTest::RunAllTests();
		LFPatternsTest::RunAllTests();
		LFMathTest::RunAllTests();
		LFIOTest::RunAllTests();
		LFCollectionsTest::RunAllTests();
	}

	void LFTest::DataSystemTests()
	{
		LFDataTest::RunAllTests();
	}

	void LFTest::NetworkSystemTests()
	{
		LFNetworkTest::RunAllTests();
	}

	void LFTest::RunAllTests()
	{
		CoreSystemTests();
		DataSystemTests();
		//NetworkSystemTests();
	}
}}
