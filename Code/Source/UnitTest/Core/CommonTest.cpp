/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "CommonTest.h"
#include "..\Test.h"
#include "..\..\Core\Common\LFVFSManager.h"
#include "..\..\Core\Common\LFEvent.h"
#include "..\..\Core\Common\LFEventArgs.h"
#include "..\..\Core\Common\LFGameCompositComponent.h"
#include "..\..\Core\Common\LFMemoryManager.h"
#include "..\..\Core\Common\LFTimer.h"
#include "..\..\Core\Common\LFWatch.h"

using namespace LFCore::Common;

namespace UnitTest
{
	void CommonTest::VFSManagerTest()
	{
		LFVFSManager::CreateInstance();

		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_SOUND, "/Home/Media/Sounds/");
		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_IMAGE, "/Home/Media/Images/");
		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_DATA, "/Home/Media/Data/");
		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_LEVEL, "/Home/Media/Levels/");
		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_SCRIPT, "/Home/Script/");

		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_SOUND, "/Home/Media/Sounds2/");
		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_IMAGE, "/Home/Media/Images2/");
		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_DATA, "/Home2/Media/Data2");
		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_SCRIPT, "/Home/Script2/");

		LFString soundFile(LFVFSManager::Instance()->Path(LFVFSManager::CP_SOUND));
		LFString imageFile(LFVFSManager::Instance()->Path(LFVFSManager::CP_IMAGE));
		LFString otherFile(LFVFSManager::Instance()->Path(LFVFSManager::CP_DATA));
		LFString levelFile(LFVFSManager::Instance()->Path(LFVFSManager::CP_LEVEL));
		LFString scriptFile(LFVFSManager::Instance()->Path(LFVFSManager::CP_SCRIPT));

		LFString sound("/Home/Media/Sounds/");
		LFString image("/Home/Media/Images/");
		LFString other("/Home/Media/Data/");
		LFString level("/Home/Media/Levels/");
		LFString script("/Home/Script/");

		bool isOk = (soundFile == sound && imageFile == image && otherFile == other && levelFile == level && scriptFile == script);
		Test::AssertOk(isOk, "LFCore::Common::LFVFSManager");

		LFVFSManager::ReleaseInstance();
	}

	class IUpdateEventHandler
	{
	public:
		virtual void OnUpdate() = 0;
		virtual ~IUpdateEventHandler() { }
	};

	class Object
    {
    public:
        LFEvent<IUpdateEventHandler> UpdateEvent;

        Object() : UpdateEvent(&IUpdateEventHandler::OnUpdate)
        { }

        void OnUpdate()
        {
            UpdateEvent();
        }
    };

    class TestObject : public IUpdateEventHandler
    {
    public:
        static int touch;

        virtual void OnUpdate()
        {
            touch++;
        }
    };

    int TestObject::touch = 0;

	void CommonTest::EventTest()
	{
		 Object obj;

		TestObject *to1 = LFNew<TestObject>(AT);
        TestObject *to2 = LFNew<TestObject>(AT);

        obj.UpdateEvent += to1;
        obj.UpdateEvent += to2;

        obj.OnUpdate();
        obj.UpdateEvent -= to1;
        obj.UpdateEvent -= to2;
        Test::AssertOk(TestObject::touch == 2, "LFCore::Common::LFEvent");

		LFDelete(to1);
		LFDelete(to2);
	}

	class LFTouchEventArgs
	{
	public:
		int x, y;
	};

	class LFITouchPressedEventHandler
	{
	public:
		virtual void OnTouchPressed(const LFTouchEventArgs &args) = 0;
		virtual ~LFITouchPressedEventHandler() { };
	};


	class Object2
    {
    private:
        LFTouchEventArgs touchArgs;

    public:
        LFEventArgs<LFITouchPressedEventHandler, LFTouchEventArgs> TouchEvent;

        Object2() : TouchEvent(&LFITouchPressedEventHandler::OnTouchPressed)
        { }

        void TouchPressed()
        {
            touchArgs.x = 1;
            touchArgs.y = 2;

            TouchEvent(touchArgs);
        }
    };

    class TestObject2 : public LFITouchPressedEventHandler
    {
    public:
        static int touchX, touchY;

        virtual void OnTouchPressed(const LFTouchEventArgs &args)
        {
            touchX += args.x;
            touchY += args.y;
        }
    };

    int TestObject2::touchX = 0;
    int TestObject2::touchY = 0;

    void CommonTest::EventArgsTest()
    {
        Object2 obj;

        TestObject2 *to1 = LFNew<TestObject2>(AT);
        TestObject2 *to2 = LFNew<TestObject2>(AT);

        obj.TouchEvent += to1;
        obj.TouchEvent += to2;

        obj.TouchPressed();
        obj.TouchEvent -= to1;
        obj.TouchEvent -= to2;
        Test::AssertOk(TestObject2::touchX == 2 && TestObject2::touchY == 4, "LFCore::Common::SMEventArgs");

		LFDelete(to1);
		LFDelete(to2);
    }

	double componentUpdate = 0;
	class Sprite : public LFGameComponent
    {
    public:
        Sprite(const LFString &name) : LFGameComponent(name)
        { }

        virtual void Update(double deltaTime)
        {
            componentUpdate += deltaTime;
        }

        virtual ~Sprite() { };
    };

    class Layer : public LFGameCompositComponent
    {
    public:
       Layer(const LFString &name) : LFGameCompositComponent(name)
       { }

       virtual ~Layer()
       { }
    };

	void CommonTest::GameComponentTest()
    {
		Layer *gameLayer = LFNew<Layer>(AT, LFString("GameLayer")); //LFGameCompositComponent

		Sprite *sprite1 = LFNew<Sprite>(AT, LFString("Sprite1")); //LFGameComponent
		Sprite *sprite2 = LFNew<Sprite>(AT, LFString("Sprite2")); //LFGameComponent
		
		gameLayer->Add(sprite1);
		gameLayer->Add(sprite1);
		gameLayer->Add(sprite2);
		gameLayer->Update(1.23); //componentUpdate = 2.46
		
		sprite1->SetIsAlive(false);
		sprite2->SetIsAlive(false);
		gameLayer->Update(1.23);
		LFDelete(gameLayer);

		Test::AssertOk(componentUpdate == 2.46, "LFCore::Common::LFGameComponent, LFCore::Common::LFGameComponent");
    }

	void CommonTest::GameCompositComponentTest()
	{
		componentUpdate = 0;
		Layer *gameLayer = LFNew<Layer>(AT, LFString("GameLayer")); //LFGameCompositComponent

		Sprite *sprite1 = LFNew<Sprite>(AT, LFString("Sprite1")); //LFGameComponent
		Sprite *sprite2 = LFNew<Sprite>(AT, LFString("Sprite2")); //LFGameComponent

		gameLayer->Add(sprite1);
		gameLayer->Add(sprite2);
		gameLayer->Add(sprite2);
		Test::AssertOk(gameLayer->GetComponetsLength() == 2, "LFCore::Common::LFGameComponent, LFCore::Common::LFGameComponent::GetComponetsLength");

		gameLayer->Update(1.23); //componentUpdate = 2.46
		sprite1->SetIsAlive(false);
		sprite2->SetIsAlive(false); //gameLayer->Remove(sprite2);
		gameLayer->Update(1.23);

		Test::AssertOk(gameLayer->GetComponetsLength() == 0, "LFCore::Common::LFGameComponent::GetComponetsLength");
		Test::AssertOk(componentUpdate == 2.46, "LFCore::Common::LFGameCompositComponent::Update");

		LFDelete(gameLayer);
	}

	void CommonTest::MemoryTest()
    {
		int memoryLeakCount = LFMemoryManager::Instance().MemoryLeakCount();

		int *x = LFNew<int>(AT, 0);
		int *y = LFNewArray<int>(AT, 10);

		LFDelete(x);
		LFDeleteArray(y);

		Test::AssertOk((LFMemoryManager::Instance().MemoryLeakCount() == memoryLeakCount && x == nullptr && y == nullptr), "LFCore::Common::LFMemoryManager");
	}

	void CommonTest::StringTest()
	{
		LFString text("test123");
		
		LFString text2;
		text2.Append("test");
		text2.Append("123");

		Test::AssertOk((text == text2), "LFCore::Common::LFString::Append, operator==");

		LFString text3("test 123  ");
		Test::AssertOk((text3.Length() == 10 && text3.LengthNoSpace() == 7), "LFCore::Common::LFString::Length, Common::LFString::LengthNoSpace");

		text3.Clear();
		text3.Append(1979);
		Test::AssertOk((text3 == LFString("1979")), "LFCore::Common::LFString::Append(int number)");

		text3.Clear();
		text3.Append(123, 5);
		Test::AssertOk((text3 == LFString("00123")), "LFCore::Common::LFString::Append(int number, int digits)");

		text3 += LFString("hoho");
		Test::AssertOk((text3 == LFString("00123hoho")), "LFCore::Common::LFString::operator+=");

		LFString text4 = text2 + text3;
		Test::AssertOk((text4 == LFString("test12300123hoho")), "LFCore::Common::LFString::operator+");

		text3.Clear();
		for (int i = 1; i < 7; text3.Append(i++))
			;
		Test::AssertOk((text3 == LFString("123456")), "LFCore::Common::LFString::Append(int)");

		text3.Clear();
		text3.Append(3.1435f);
		Test::AssertOk((text3 == LFString("3.1435")), "LFCore::Common::LFString::Append(float)");

		LFString text5(6);
		text5.Append("123456");
		Test::AssertOk((text5 == LFString("123456")), "LFCore::Common::LFString::LFString(int size), LFCore::Common::LFString::Append(const char *)");

		char textArray[1600];
		for (int i = 0; i < 1600; i++)
		{
			textArray[i] = 'a';
		}

		LFString text6(textArray);
		LFString text7(text6);
		Test::AssertOk((text6 == text7), "LFCore::Common::LFString::LFString(const char *text), LFCore::Common::LFString::LFString(const LFString &value)");

		bool isDigitChecker = true;
		for (int i = 0; i < 256; i++)
		{
			if (i < 10)
			{
				if (!LFString::IsDigitFromChar((char)i))
				{
					isDigitChecker = false;
					break;
				}
			}
			else if (LFString::IsDigitFromChar((char)i))
			{
				isDigitChecker = false;
				break;
			}
		}
		Test::AssertOk(isDigitChecker, "LFCore::Common::LFString::IsDigitFromChar(char character)");

		LFString text8;
		for (int i = 1; i < 7; text8.Append(i++))
			;
		Test::AssertOk(text8.ToInt() == 123456, "LFCore::Common::LFString::ToInt()");

		const char *goodAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const char *wrongAlphabet = "abcd}";
		const char *wrongAlphabet2 = "abcd0";

		bool isGoodAlphabet = true;
		for (int index = 0; goodAlphabet[index] != 0; index++)
		{
			if (!LFString::IsAlphabetChar(goodAlphabet[index]))
			{
				isGoodAlphabet = false;
				break;
			}
		}
		Test::AssertOk(isGoodAlphabet, "LFCore::Common::LFString::IsAlphabetChar - isGoodAlphabet");

		bool isWrongAlphabet = true;
		for (int index = 0; wrongAlphabet[index] != 0; index++)
		{
			if (!LFString::IsAlphabetChar(wrongAlphabet[index]))
			{
				isWrongAlphabet = false;
				break;
			}
		}
		Test::AssertOk(isWrongAlphabet == false, "LFCore::Common::LFString::IsAlphabetChar - isGoodAlphabet");

		bool isWrongAlphabet2 = true;
		for (int index = 0; wrongAlphabet2[index] != 0; index++)
		{
			if (!LFString::IsAlphabetChar(wrongAlphabet2[index]))
			{
				isWrongAlphabet2 = false;
				break;
			}
		}
		Test::AssertOk(isWrongAlphabet2 == false, "LFCore::Common::LFString::IsAlphabetChar - isGoodAlphabet2");

		const char *test = "test";
		const char *arviz = "arvizturo tukorfurogep";
		const char *test2 = "test";

		Test::AssertOk(LFString::IsEqual(arviz, test) == false, "LFCore::Common::LFString::IsEqual - not equal");
		Test::AssertOk(LFString::IsEqual(test, arviz) == false, "LFCore::Common::LFString::IsEqual - not equa2");
		Test::AssertOk(LFString::IsEqual(test, test2) == true, "LFCore::Common::LFString::IsEqual - equal");

		LFString example("X-Ample123_123B");
		Test::AssertOk(example.Search("X-Ample123") == true, "LFCore::Common::LFString::Search - equal1");
		Test::AssertOk(example.Search("X-Ample") == true, "LFCore::Common::LFString::Search - equal2");
		Test::AssertOk(example.Search("Ample") == true, "LFCore::Common::LFString::Search - equal3");
		Test::AssertOk(example.Search(LFString("X-Am")) == true, "LFCore::Common::LFString::Search - equal4");
		Test::AssertOk(example.Search("e12") == true, "LFCore::Common::LFString::Search - equal5");
		Test::AssertOk(example.Search("23") == true, "LFCore::Common::LFString::Search - equal6");
		Test::AssertOk(example.Search("3B") == true, "LFCore::Common::LFString::Search - equal7");
		Test::AssertOk(example.Search(LFString("123")) == true, "LFCore::Common::LFString::Search - equal8");
		Test::AssertOk(example.Search(LFString("123B")) == true, "LFCore::Common::LFString::Search - equal9");
		Test::AssertOk(example.Search("X-Ample124") == false, "LFCore::Common::LFString::Search - not equal1");
		Test::AssertOk(example.Search("1234") == false, "LFCore::Common::LFString::Search - not equal2");
		Test::AssertOk(example.Search(LFString("X-ample123")) == false, "LFCore::Common::LFString::Search - not equal3");

		LFString example2("arvizturo tukorfurogep");
		Test::AssertOk(example2.Search("o ") == true, "LFCore::Common::LFString::Search 2 - equal1");
		Test::AssertOk(example2.Search("or") == true, "LFCore::Common::LFString::Search 2 - equal2");
		Test::AssertOk(example2.Search(LFString("og")) == true, "LFCore::Common::LFString::Search 2 - equal3");
		Test::AssertOk(example2.Search("roe") == false, "LFCore::Common::LFString::Search 2 - not equal1");
		Test::AssertOk(example2.Search(LFString("ogepp")) == false, "LFCore::Common::LFString::Search 2 - not equal2");

		LFString empty;
		Test::AssertOk(empty.IsEmpty(), "LFCore::Common::LFString::IsEmpty - default");
		Test::AssertOk(empty == LFString(""), "LFCore::Common::LFString::IsEmpty - default2");
		LFString empty2("");
		Test::AssertOk(empty2.IsEmpty(), "LFCore::Common::LFString::IsEmpty - default3");
		empty.Append("hohoh");
		Test::AssertOk(!empty.IsEmpty(), "LFCore::Common::LFString::IsEmpty - not empty");
		empty.Clear();
		Test::AssertOk(empty.IsEmpty(), "LFCore::Common::LFString::IsEmpty - cleared");
		empty.Append("h");
		Test::AssertOk(!empty.IsEmpty(), "LFCore::Common::LFString::IsEmpty - not empty2");
	}

	void CommonTest::TimerTest()
	{
		LFTimer timer;
		timer.Reset();

        double time = 0;
        for (; ;)
        {
            time += timer.DeltaTime();

            if (time > 300)
                break;
        }

        Test::AssertOk(time > 0, "LFCore::Common::LFTimer::Reset(), LFCore::Common::LFTimer::DeltaTime()");
	}

	bool isAlarm = false;
	class WatchTestObject : public LFIWatchAlarmEventHandler
	{
	public:
		WatchTestObject(LFWatch &watch)
		{
			watch.AlarmEvent += this;
		}

		virtual void OnAlarm()
		{
			isAlarm = true;
		}

		virtual ~WatchTestObject() { };
	};

	void CommonTest::WatchTest()
	{
		LFWatch watch(LFTime(1, 0), LFTime(0, 0), LFTime(2, 0));
		WatchTestObject watchTestObj(watch);

		for (int i = 0; i < 60; i++, watch++)
			;

		Test::AssertOk(isAlarm, "LFCore::Common::LFWatch::Alarm()");
	}
};
