/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFTest.h"
#include "..\LFEngine\LFCore\LFIO\LFLogger.h"
#include "..\LFEngine\LFCore\LFPatterns\LFIoc.h"
#include "..\LFEngine\LFCore\LFCommon\LFMemoryManager.h"
#include "..\LFEngine\LFRender\LFRenderWindow.h"

using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFRender;

namespace LF3Engine { namespace LFUnitTest
{
	class LFUnitTestMain final
	{
		LFUnitTestMain() = delete;
		LFUnitTestMain(const LFUnitTestMain&) = delete;
		LFUnitTestMain(LFUnitTestMain &&) = delete;
		LFUnitTestMain &operator=(const LFUnitTestMain &) = delete;
		LFUnitTestMain &operator=(LFUnitTestMain &&) = delete;
		~LFUnitTestMain() = delete;

	public:
		static void Run()
		{
			//LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToOutput, true);
			//LFIoc<LFLogger>::Get().WriteOutput(LFSystemData::GetSystemInfo());

			LFTest::RunAllTests();
			LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToOutput, true);
			LFTest::WriteStatistics();

			LFMemoryManager::WriteStatistics(true);
		}
	};
}}
