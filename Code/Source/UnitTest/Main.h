/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#ifdef TIZEN
	#ifdef  LOG_TAG
	#undef  LOG_TAG
	#endif
	#define LOG_TAG "unittest"
#endif

#include "Test.h"
#include "..\..\Core\Common\LFMemoryManager.h"
#include "..\..\Core\Common\LFString.h"
#include "..\..\Core\IO\LFLogger.h"

void Run()
{
	#ifdef TIZEN
	LFCore::IO::LFLogger::Instance().LogTag((char *)LOG_TAG);
	#endif

	UnitTest::Test::CoreSystemTest();
	UnitTest::Test::ScriptSystemTest();

	UnitTest::Test::WriteStatistics();

	LFCore::Common::LFMemoryManager::Instance().CheckMemoryLeaks();

	LFCore::IO::LFLogger::Instance().WriteOutput("Ready");
}
