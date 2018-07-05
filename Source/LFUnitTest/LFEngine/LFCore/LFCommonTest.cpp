/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFCommonTest.h"
#include "..\..\LFTest.h"
#include "..\..\LFTestSprite.h"
#include "..\..\LFTestLayer.h"
#include "..\..\LFTestObjectB.h"
#include "..\..\..\LFEngine\LFCore\LFCore.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFTuple.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFMemoryManager.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFString.h"
#include "..\..\..\LFEngine\LFCore\LFPatterns\LFIoc.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFVFSManager.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFGameComponent.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFGameCompositeComponent.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFTimer.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFWatch.h"

using namespace LF3Engine::LFUnitTest;
using namespace LF3Engine::LFEngine::LFCore;
using namespace LFCommon;
using namespace LFPatterns;

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore
{
	void LFCommonTest::LFTupleTest()
	{
		const int v1 = 22;
		const float v2 = 3.14f;
		auto TupleTest1 = [v1, v2](LFTuple2<int, float> &t)
		{
			t.item1 = v1;
			t.item2 = v2;
		};

		const int v3 = 12;
		const int v4 = 34;
		auto TupleTest2 = [v3, v4]() { return LFTuple::Create(v3, v4); };

		LFTuple2<int, float> t1(1, 2);
		TupleTest1(t1);
		LFTest::AssertOk(t1.item1 == v1 && t1.item2 == v2, INFO);

		auto t2 = TupleTest2();
		LFTest::AssertOk(t2.item1 == v3 && t2.item2 == v4, INFO);
	}

	void LFCommonTest::LFMemoryManagerTest()
	{
		int memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();

		int *x = LFMemoryManager::New<int>(INFO, 0);
		int *y = LFMemoryManager::NewArray<int>(INFO, 10);

        LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 2, INFO);

		LFMemoryManager::Delete(x);
		LFMemoryManager::DeleteArray(y);

		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount && x == nullptr && y == nullptr, INFO);
	}

	void LFCommonTest::LFStringTest()
	{
		int memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();
		auto StringTestCtorOperators = []()
		{
			LFString text("test123");
			
			LFString text2("test");
			text2 += "123";

			LFString text3;
			text3 += "test";
			text3 += "123";

			LFString text4("test");
			text4 += 123;

			LFString text5;
			text5 += "test";
			text5 += 123;

			LFString text6(text5);

			LFTest::AssertOk(text == text2, INFO);
			LFTest::AssertOk(text == text3, INFO);
			LFTest::AssertOk(text == text4, INFO);
			LFTest::AssertOk(text == text5, INFO);
			LFTest::AssertOk(text == text6, INFO);

			text6 += 'K';
			text6 += 3.14f;

			LFTest::AssertOk(text6 == LFString("test123K3.140"), INFO);

			text6.Clear();
			text6 = static_cast<LFString>("test") + 123 + 'K' + 3.14f + " hoho";
			LFTest::AssertOk(text6 == LFString("test123K3.140 hoho"), INFO);

			text6 = 3.14f;
			LFTest::AssertOk(text6 == LFString("3.140"), INFO);
		};
		StringTestCtorOperators();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestReturn = []()
		{
			LFString result("hoho");

			return result;
		};
		LFTest::AssertOk(StringTestReturn() == LFString("hoho"), INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestTo = []()
		{
			LFString text;

			text = 148248853;
			LFTest::AssertOk(148248853 == text.ToInt(), INFO);

			text += "hoho";
			LFTest::AssertOk(0 == text.ToInt(), INFO);

			text = 3.1482488038f;
			LFTest::AssertOk(3.1482488038f == text.ToFloat(), INFO);
			LFTest::AssertOk(0 == text.ToInt(), INFO);
		};
		StringTestTo();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestGet = []()
		{
			LFTest::AssertOk(8 == LFString::GetNumberLength(12345678), INFO);

			const char *goodAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			const char *wrongAlphabet = "abcd}";
			const char *wrongAlphabet2 = "abcd0";

			bool isGoodAlphabet = true;
			for (int index = 0; goodAlphabet[index] != 0; index++)
			{
				if (!LFString::IsAbcLetter(goodAlphabet[index]))
				{
					isGoodAlphabet = false;
					break;
				}
			}
			LFTest::AssertOk(isGoodAlphabet, INFO);

			bool isWrongAlphabet = true;
			for (int index = 0; wrongAlphabet[index] != 0; index++)
			{
				if (!LFString::IsAbcLetter(wrongAlphabet[index]))
				{
					isWrongAlphabet = false;
					break;
				}
			}
			LFTest::AssertOk(isWrongAlphabet == false, INFO);

			bool isWrongAlphabet2 = true;
			for (int index = 0; wrongAlphabet2[index] != 0; index++)
			{
				if (!LFString::IsAbcLetter(wrongAlphabet2[index]))
				{
					isWrongAlphabet2 = false;
					break;
				}
			}
			LFTest::AssertOk(isWrongAlphabet2 == false, INFO);

			bool isDigitChecker = true;
			for (int i = 0; i < 256; i++)
			{
				if (i < 10)
				{
					if (!LFString::IsNumberDigit(i + '0'))
					{
						isDigitChecker = false;
						break;
					}
				}
				else if (LFString::IsNumberDigit(i + '0'))
				{
					isDigitChecker = false;
					break;
				}
			}
			LFTest::AssertOk(isDigitChecker, INFO);

			LFString text("test 123  ");
			LFTest::AssertOk(text.GetTextLength() == 10 && text.GetTextLenghtWithoutSpace() == 7, INFO);

			LFString empty;

			LFTest::AssertOk(empty.IsEmpty(), INFO);
			LFTest::AssertOk(empty == LFString(""), INFO);

			LFString empty2("");
			LFTest::AssertOk(empty2.IsEmpty(), INFO);

			empty += "hohoh";
			LFTest::AssertOk(!empty.IsEmpty(), INFO);

			empty.Clear();
			LFTest::AssertOk(empty.IsEmpty(), INFO);

			empty += 'h';
			LFTest::AssertOk(!empty.IsEmpty(), INFO);
		};
		StringTestGet();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestIs = []()
		{
			LFString example("X-Ample123_123B");
			LFString example2("arvizturo tukorfurogep");

			LFTest::AssertOk(example.IsExist(LFString("X-Ample123")) == true, INFO);
			LFTest::AssertOk(example.IsExist(LFString("X-Ample")) == true, INFO);
			LFTest::AssertOk(example.IsExist(LFString("Ample")) == true, INFO);
			LFTest::AssertOk(example.IsExist(LFString("X-Am")) == true, INFO);
			LFTest::AssertOk(example.IsExist(LFString("e12")) == true, INFO);
			LFTest::AssertOk(example.IsExist(LFString("23")) == true, INFO);
			LFTest::AssertOk(example.IsExist(LFString("3B")) == true, INFO);
			LFTest::AssertOk(example.IsExist(LFString("123")) == true, INFO);
			LFTest::AssertOk(example.IsExist(LFString("123B")) == true, INFO);
			LFTest::AssertOk(example.IsExist(LFString("X-Ample124")) == false, INFO);
			LFTest::AssertOk(example.IsExist(LFString("1234")) == false, INFO);
			LFTest::AssertOk(example.IsExist(LFString("X-ample123")) == false, INFO);
			LFTest::AssertOk(example2.IsExist(LFString("o ")) == true, INFO);
			LFTest::AssertOk(example2.IsExist(LFString("or")) == true, INFO);
			LFTest::AssertOk(example2.IsExist(LFString("og")) == true, INFO);
			LFTest::AssertOk(example2.IsExist(LFString("roe")) == false, INFO);
			LFTest::AssertOk(example2.IsExist(LFString("ogepp")) == false, INFO);

			LFTest::AssertOk(example.IsExist(LFString('_')) == true, INFO);
			LFTest::AssertOk(example2.IsExist(LFString('o')) == true, INFO);
			LFTest::AssertOk(example2.IsExist(LFString(' ')) == true, INFO);
			LFTest::AssertOk(example2.IsExist(LFString('x')) == false, INFO);

			LFTest::AssertOk(2 == example2.GetExistCount(LFString("tu")), INFO);
			LFTest::AssertOk(1 == example2.GetExistCount(LFString("o t")), INFO);

			LFTest::AssertOk(3 == example2.GetExistCount(LFString('o')), INFO);
			LFTest::AssertOk(1 == example2.GetExistCount(LFString(' ')), INFO);
			LFTest::AssertOk(3 == example2.GetExistCount(LFString('u')), INFO);

			LFTest::AssertOk(example.IsStartsWith(LFString("X-Ample123")) == true, INFO);
			LFTest::AssertOk(example.IsStartsWith(LFString("X-Ample")) == true, INFO);
			LFTest::AssertOk(example.IsStartsWith(LFString("X-Am")) == true, INFO);
			LFTest::AssertOk(example.IsStartsWith(LFString("Ample")) == false, INFO);

			LFTest::AssertOk(example.IsStartsWith(LFString('X')) == true, INFO);
			LFTest::AssertOk(example.IsStartsWith(LFString('-')) == false, INFO);

			LFTest::AssertOk(example.IsEndsWith(LFString("123_123B")) == true, INFO);
			LFTest::AssertOk(example.IsEndsWith(LFString("_123B")) == true, INFO);
			LFTest::AssertOk(example.IsEndsWith(LFString("123B")) == true, INFO);
			LFTest::AssertOk(example.IsEndsWith(LFString("1234")) == false, INFO);

			LFTest::AssertOk(example.IsEndsWith(LFString('B')) == true, INFO);
			LFTest::AssertOk(example.IsEndsWith(LFString('b')) == false, INFO);
		};
		StringTestIs();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestCopyArray = []()
		{
			char text[20];
			LFString::CopyToArray("hello123", text);
			LFTest::AssertOk(LFString(text) == LFString("hello123"), INFO);
		};
		StringTestCopyArray();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestReplaceRemove = []()
		{
			LFString text("X-Ample123_123B");

			text.Replace(LFString("X-"), LFString("Y+"));
			LFTest::AssertOk(text == LFString("Y+Ample123_123B"), INFO);
			text.Replace(LFString("X"), LFString("Z"));
			LFTest::AssertOk(text == LFString("Y+Ample123_123B"), INFO);

			text.Replace('1', '2');
			LFTest::AssertOk(text == LFString("Y+Ample223_223B"), INFO);
			text.Replace('1', '3');
			LFTest::AssertOk(text == LFString("Y+Ample223_223B"), INFO);
			text.Replace('+', ':');
			LFTest::AssertOk(text == LFString("Y:Ample223_223B"), INFO);

			text.Replace('4', 1);
			LFTest::AssertOk(text == LFString("Y4Ample223_223B"), INFO);

			text.Replace(123, 5);
			LFTest::AssertOk(text == LFString("00123"), INFO);

			text = "X-Ample123_123B";

			text.Remove(10, 5);
			LFTest::AssertOk(text == LFString("X-Ample123"), INFO);

			text.Remove(LFString(123));
			LFTest::AssertOk(text == LFString("X-Ample"), INFO);

			text = "arvizturo tukorfurogep";
			text.Remove('o');
			LFTest::AssertOk(text == LFString("arviztur tukrfurgep"), INFO);

			text.Trim();
			LFTest::AssertOk(text == LFString("arvizturtukrfurgep"), INFO);

			text.Clear();
			LFTest::AssertOk(text == LFString(""), INFO);
		};
		StringTestReplaceRemove();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestLarge = []()
		{
			LFString text;
			const int textSize = 1200;

			char largeText[textSize];
			for (int index = 0; index < textSize - 1; index++)
				largeText[index] = 'A';
			largeText[textSize - 1] = '\0';

			text = largeText;
			LFTest::AssertOk(textSize - 1 == text.GetTextLength(), INFO);
			LFTest::AssertOk(textSize * 2 == text.GetDataSize(), INFO);
			
			text += "hoho";
			LFTest::AssertOk(text.IsEndsWith(LFString("hoho")), INFO);

			text += largeText;
			LFTest::AssertOk((textSize * 4) + ((LFString::GetTextLength("hoho") - 1) * 2) == text.GetDataSize(), INFO);
		};
		StringTestLarge();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestCopy = []() { return LFString("hoho1234!"); };
		LFTest::AssertOk(StringTestCopy() == LFString("hoho1234!"), INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestSplit = []()
		{
			LFString text;

			text = "one#two#three#four";
			auto numbers = text.Split('#');
			LFTest::AssertOk(numbers[0] == LFString("one") && numbers[1] == LFString("two") && numbers[2] == LFString("three") && numbers[3] == LFString("four"), INFO);
		};
		StringTestSplit();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestSplit2 = []()
		{
			LFString text;

			text = "onesplittwosplitthreesplitfour";
			auto numbers = text.Split(LFString("split"));
			LFTest::AssertOk(numbers[0] == LFString("one") && numbers[1] == LFString("two") && numbers[2] == LFString("three") && numbers[3] == LFString("four"), INFO);
		};
		StringTestSplit2();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto StringTestSplit3 = []()
		{
			LFString text;
			auto empty = text.Split(LFString('#'));
			LFTest::AssertOk(empty.GetLength() == 0, INFO);

			LFString text2("#");
			auto empty2 = text2.Split(LFString('#'));
			LFTest::AssertOk(empty2[0].IsEmpty(), INFO);
		};
		StringTestSplit3();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);
	}

	void LFCommonTest::LFVFSManagerTest()
	{
		LFIoc<LFVFSManager *>::Register<LFVFSManager>();
		LFIoc<LFVFSManager *>::Create();

		LFString nothing(LFIoc<LFVFSManager *>::Get()->GetPath(LFVFSPath::No));
		LFString dataReadFile(LFIoc<LFVFSManager *>::Get()->GetPath(LFVFSPath::DataRead));
		LFString dataReadWriteFile(LFIoc<LFVFSManager *>::Get()->GetPath(LFVFSPath::DataReadWrite));
		LFString imageFile(LFIoc<LFVFSManager *>::Get()->GetPath(LFVFSPath::Image));
		LFString effectFile(LFIoc<LFVFSManager *>::Get()->GetPath(LFVFSPath::ShaderEffect));
		LFString soundFile(LFIoc<LFVFSManager *>::Get()->GetPath(LFVFSPath::Sound));
		
		LFTest::AssertOk(nothing.IsEmpty() && !dataReadFile.IsEmpty() && !dataReadWriteFile.IsEmpty() && !imageFile.IsEmpty() && !effectFile.IsEmpty() && !soundFile.IsEmpty(), INFO);

		LFIoc<LFVFSManager *>::Release();
	}

	void LFCommonTest::LFGameComponentTest()
	{
		LFTestSprite::componentUpdate = 0;
		LFTestLayer *gameLayer = LFMemoryManager::New<LFTestLayer>(INFO, LFString("GameLayer")); //LFGameCompositeComponent

		LFTestSprite *sprite1 = LFMemoryManager::New<LFTestSprite>(INFO, LFString("Sprite1")); //LFGameComponent
		LFTestSprite *sprite2 = LFMemoryManager::New<LFTestSprite>(INFO, LFString("Sprite2")); //LFGameComponent

		gameLayer->Add(sprite1);
		gameLayer->Add(sprite1);
		gameLayer->Add(sprite2);
		gameLayer->Update(1.23); //componentUpdate = 2.46

		sprite1->SetIsAlive(false);
		sprite2->SetIsAlive(false);
		gameLayer->Update(1.23);
		LFMemoryManager::Delete(gameLayer);

		LFTest::AssertOk(LFTestSprite::componentUpdate == 2.46, INFO);
	}

	void LFCommonTest::LFGameCompositeComponentTest()
	{
		LFTestSprite::componentUpdate = 0;
		LFTestLayer *gameLayer = LFMemoryManager::New<LFTestLayer>(INFO, LFString("GameLayer")); //LFGameCompositeComponent

		LFTestSprite *sprite1 = LFMemoryManager::New<LFTestSprite>(INFO, LFString("Sprite1")); //LFGameComponent
		LFTestSprite *sprite2 = LFMemoryManager::New<LFTestSprite>(INFO, LFString("Sprite2")); //LFGameComponent

		gameLayer->Add(sprite1);
		gameLayer->Add(sprite2);
		gameLayer->Add(sprite2);
		LFTest::AssertOk(gameLayer->GetComponentsLength() == 2, INFO);

		gameLayer->Update(1.23); //componentUpdate = 2.46
		sprite1->SetIsAlive(false);
		sprite2->SetIsAlive(false); //gameLayer->Remove(sprite2);
		gameLayer->Update(1.23);

		LFTest::AssertOk(gameLayer->GetComponentsLength() == 0, INFO);
		LFTest::AssertOk(LFTestSprite::componentUpdate == 2.46, INFO);

		LFMemoryManager::Delete(gameLayer);
	}

	void LFCommonTest::LFTimerTest()
	{
		LFTimer timer;
		timer.Reset();

		double time = 0;
		for (; ;)
		{
			time += timer.DeltaTime();

			if (time > 1)
				break;
		}

		LFTest::AssertOk(time > 0, INFO);
	}

	void LFCommonTest::LFWatchTest()
	{
		bool isAlarm = false;
		auto OnAlarm = [&isAlarm]() { isAlarm = true; };

		LFWatch watch(LFTime(1, 0), LFTime(0, 0), LFTime(2, 0));
		watch.SetAlarmEvent(OnAlarm);

		for (int i = 0; i < 60; i++, watch++)
			;

		LFTest::AssertOk(isAlarm, INFO);
	}

	void LFCommonTest::LFEventTest()
	{
		LFTestObjectB *obj = LFMemoryManager::New<LFTestObjectB>(INFO);
		
		int x = 100;
		Args eventArgs{ 5 };

		std::function<void(const Args &args)> func1 = [&x](const Args &args) { x += args.x; };
		obj->TestEvent += func1;
		std::function<void(const Args &args)> func2 = [&x](const Args &args) { x += (args.x * 2); };
		obj->TestEvent += func2;
		
		obj->TestEvent(eventArgs);

		LFTest::AssertOk(x == 115, INFO);

		obj->TestEvent -= func1;
		obj->TestEvent -= func2;

		LFMemoryManager::Delete(obj);
	}

	void LFCommonTest::RunAllTests()
	{
		LFTupleTest();
		LFMemoryManagerTest();
		LFStringTest();
		LFVFSManagerTest();
		LFGameComponentTest();
		LFGameCompositeComponentTest();
		LFTimerTest();
		LFWatchTest();
		LFEventTest();
	}
}}}}
