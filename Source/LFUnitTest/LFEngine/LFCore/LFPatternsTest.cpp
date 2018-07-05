/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFPatternsTest.h"
#include "..\..\LFTest.h"
#include "..\..\LFTestObjectA.h"
#include "..\..\LFTestObjectB.h"
#include "..\..\..\LFEngine\LFCore\LFCore.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFMemoryManager.h"
#include "..\..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFUnitTest;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore
{
	void LFPatternsTest::LFIocTest()
	{
		//static Ioc test
		LFIoc<LFTestObjectA>::Get().SetId(12);
		LFTest::AssertOk(LFIoc<LFTestObjectA>::Get().GetId() == 12, INFO);
		LFIoc<LFTestObjectA>::Get().SetId(20);
		LFTest::AssertOk(LFIoc<LFTestObjectA>::Get().GetId() == 20, INFO);

		//dynamic Ioc test
		int memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();
		LFTest::AssertOk(LFIoc<LFITestObject *>::IsExist() == false, INFO);

		LFIoc<LFITestObject *>::Register<LFTestObjectA>();
		LFIoc<LFITestObject *>::Create();
		LFTest::AssertOk(LFIoc<LFITestObject *>::Get()->GetId() == 0, INFO);
		LFTest::AssertOk(LFIoc<LFITestObject *>::Get()->GetTypeCode() == 'A', INFO);

		LFIoc<LFITestObject *>::Get()->SetId(20);
		LFIoc<LFITestObject *>::Register<LFTestObjectB>(); //no operation if instance not nullptr
		LFIoc<LFITestObject *>::Create(); //no operation if instance not nullptr
		LFTest::AssertOk(LFIoc<LFITestObject *>::Get()->GetId() == 20, INFO);
		LFTest::AssertOk(LFIoc<LFITestObject *>::Get()->GetTypeCode() == 'A', INFO);

		LFIoc<LFITestObject *>::Release();
		LFTest::AssertOk(LFIoc<LFITestObject *>::IsExist() == false, INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		LFIoc<LFITestObject *>::Register<LFTestObjectB>();
		LFIoc<LFITestObject *>::Create();
		LFTest::AssertOk(LFIoc<LFITestObject *>::Get()->GetTypeCode() == 'B', INFO);

		LFIoc<LFITestObject *>::Release();
		LFIoc<LFITestObject *>::Register<LFTestObjectA>([]()
			{
				auto result = LFMemoryManager::New<LFTestObjectB>(INFO);
				result->SetId(44);

				return result;
			});
		LFIoc<LFITestObject *>::Create();
		LFTest::AssertOk(LFIoc<LFITestObject *>::Get()->GetTypeCode() == 'B', INFO);
		LFTest::AssertOk(LFIoc<LFITestObject *>::Get()->GetId() == 44, INFO);

		LFIoc<LFITestObject *>::Release();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);
	}

	void LFPatternsTest::RunAllTests()
	{
		LFIocTest();
	}
}}}}