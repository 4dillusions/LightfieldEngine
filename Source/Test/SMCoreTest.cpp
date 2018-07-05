#include "SMCoreTest.h"

#include <stdio.h>
#include <stdlib.h>

#include "..\\IO\\SMLogger.h"
#include "..\\Core\\SMString.h"

#include "..\\Test\\SMTest.h"

#include "..\\Math\\SMRectangle.h"

#include "..\\Core\\SMSmartPtr.h"
#include "..\\Core\\SMArray.h"
#include "..\\Core\\SMArray2D.h"
#include "..\\Core\\SMTuple.h"
#include "..\\Core\\SMParams.h"
#include "..\\Core\\SMTimer.h"
#include "..\\Core\\SMList.h"
#include "..\\Core\\SMDictionary.h"
#include "..\\Core\\SMEventHandlers.h"
#include "..\\Core\\SMEvent.h"
#include "..\\Core\\SMEventArgs.h"
#include "..\\Core\\SMGameCompositComponent.h"

using namespace SMEngine::Math;

using namespace SMEngine::IO;
using namespace SMEngine::Core;
using namespace SMEngine::Test;

namespace SMEngine { namespace Test
{
	void SMCoreTest::SMStringTest()
    {
		SMString s("teszt");
		SMTest::AssertOk(s == "teszt", "SMString::SMString(const char *text)");

		SMString s2(SMString("hoho"));
		SMTest::AssertOk(s2 == "hoho", "SMString::SMString(const SMString &value)");

		SMString s3;
		s3.Append("hoho");
		s3.Append(" haha");
		s3.Append("_hihi");
		SMTest::AssertOk(s3 == "hoho haha_hihi", "SMString::Append(const char *text)");

		SMString s4;
		s4.Append(123, 6);
		SMTest::AssertOk(s4 == "000123", "SMString::Append(int number, int digits)");

		SMString s5;
		s5.Append(1234);
		s5.Append(567);
		s5.Append("huhu");
		s5.Append(12);
		SMTest::AssertOk(s5 == "1234567huhu12", "SMString::Append(int number), SMString::Append(const char *text)");

		SMString s6("hoho");
		SMString s7;
		s7.Append("ho");
		s7.Append("ho");
		SMTest::AssertOk(s6.HashCode() == s7.HashCode(), "SMString::HashCode() /char */");

		SMString s8;
		s8.Append("texture");
		s8.Append(22);
		SMTest::AssertOk(s8 == "texture22", "SMString::Append(const char *text), SMString::Append(int number)");

		SMString s9 = "texture42";
		SMString s10;
		s10.Append("texture");
		s10.Append("_");
		s10.Append("128");
		s10.Append("_");
		s10.Append("256");
		s10.Append(s9);
		SMTest::AssertOk(s10 == "texture_128_256texture42", "SMString::Append(int number), SMString::Append(const char *text), SMString::Append(const SMString &value)");
    }

    int testObjectCounter = 0;

    class Test
    {
    public:
		Test(int a) : a(a)
        {
            testObjectCounter++;
        }

        Test()
        {
            testObjectCounter++;
        }

		Test(const Test &value)
		{
			testObjectCounter++;
			a = value.a;
		}

        ~Test()
        {
            testObjectCounter--;
        }

		bool operator == (const Test &value) const
        {
            return (a == value.a);
        }

        int a;
    };

    void TestSmartPtrMethod()
    {
        SMSmartPtr<Test> test(new Test());
        test->a = 20;

        Test *test2 = test;
        SMTest::AssertOk(test2->a == test->a, "SMSmartPtr::operator T * ()");
    }

    void SMCoreTest::SMSmartPtrTest()
    {
        TestSmartPtrMethod();
        SMTest::AssertOk(testObjectCounter == 0, "SMSmartPtr::~SMSmartPtr()");
    }

    void TestArray()
    {
        testObjectCounter = 0;
        SMArray<SMSmartPtr<Test> > arrayTest(3);
        arrayTest[0] = SMSmartPtr<Test>(new Test(1));
        arrayTest[1] = SMSmartPtr<Test>(new Test(2));
        arrayTest[2] = SMSmartPtr<Test>(new Test(3));
    }

    void SMCoreTest::SMArrayTest()
    {
        SMArray<int> array(3);
        array[0] = 1;
        array[1] = 2;
        array[2] = 3;

        int x = 0;
        for (int i = 0; i < array.Lenght(); ++i)
            x += array[i];

        SMTest::AssertOk(x == 6, "SMArray::SMArray(int size), SMArray:: T operator[] (int index), SMArray:: T &operator[] (int index)");

        array.SetAll(0);

        int y = 0;
        for (int i = 0; i < array.Lenght(); ++i)
            y += array[i];

        SMTest::AssertOk(y == 0, "SMArray::SetAll(T value, T *array, int size)");

        SMArray<int> array2(3);
        array2[0] = 2;
        array2[1] = 3;
        array2[2] = 4;

        array.Copy(array2);

        int z = 0;
        for (int i = 0; i < array.Lenght(); ++i)
            z += array[i];

        SMTest::AssertOk(z == 9, "SMArray::Copy(const SMArray &array)");

        TestArray();
        SMTest::AssertOk(testObjectCounter == 0, "SMArray<Test> arrayTest(2)");
    }

    void TestArray2D()
    {
        testObjectCounter = 0;
        SMArray2D<SMSmartPtr<Test> > arrayTest(2, 3);

        for(int x = 0; x < arrayTest.LenghtX(); ++x)
            for(int y = 0; y < arrayTest.LenghtY(); ++y)
                arrayTest(x, y) = SMSmartPtr<Test>(new Test(x + y));
    }

    void SMCoreTest::SMArray2DTest()
    {
        SMArray2D<int> array(2, 2);
        array(0, 0) = 1;
        array(0, 1) = 2;
        array(1, 0) = 3;
        array(1, 1) = 4;

        int x1 = 0;
        for(int x = 0; x < array.LenghtX(); ++x)
            for(int y = 0; y < array.LenghtY(); ++y)
                x1 += array(x, y);

        SMTest::AssertOk(x1 == 10, "SMArray::SMArray2D(int sizeX, int sizeY), SMArray:: T operator() (int indexX, int indexY), SMArray:: T &operator() (int indexX, int indexY)");

        array.SetAll(0);

        int y1 = 0;
        for(int x = 0; x < array.LenghtX(); ++x)
            for(int y = 0; y < array.LenghtY(); ++y)
                y1 += array(x, y);

        SMTest::AssertOk(y1 == 0, "SMArray::Setall(T value)");

        SMArray2D<int> array2(2, 2);
        array2(0, 0) = 2;
        array2(0, 1) = 3;
        array2(1, 0) = 4;
        array2(1, 1) = 5;

        array.Copy(array2);

        int z1 = 0;
        for(int x = 0; x < array.LenghtX(); ++x)
            for(int y = 0; y < array.LenghtY(); ++y)
                z1 += array(x, y);

        SMTest::AssertOk(z1 == 14, "SMArray::Copy(const SMArray2D &array)");

        TestArray2D();
        SMTest::AssertOk(testObjectCounter == 0, "SMArray2D<Test> arrayTest(2, 3)");
    }

    void SMCoreTest::SMTupleTest()
    {
        SMTuple1<int> t1 = SMTuple::Create(1);
        SMTuple2<int, int> t2 = SMTuple::Create(1, 2);
        SMTuple3<int, int, int> t3 = SMTuple::Create(1, 2, 3);
        SMTuple4<int, int, int, int> t4 = SMTuple::Create(1, 2, 3, 4);
        SMTuple5<int, int, int, int, int> t5 = SMTuple::Create(1, 2, 3, 4, 5);

        SMTest::AssertOk((t1.item1) == 1, "SMTuple1, SMTuple::Create");
        SMTest::AssertOk((t2.item1 + t2.item2) == (1 + 2), "SMTuple2, SMTuple::Create");
        SMTest::AssertOk((t3.item1 + t3.item2 + t3.item3) == (1 + 2 + 3), "SMTuple3, SMTuple::Create");
        SMTest::AssertOk((t4.item1 + t4.item2 + t4.item3 + t4.item4) == (1 + 2 + 3 + 4), "SMTuple4, SMTuple::Create");
        SMTest::AssertOk((t5.item1 + t5.item2 + t5.item3 + t5.item4 + t5.item5) == (1 + 2 + 3 + 4 + 5), "SMTuple5, SMTuple::Create");
    }

    void SMCoreTest::SMParamsTest()
    {
        SMParams<int> params = SMParams<int>(1, 2, 3, 4, 5, nullptr);

        int num = 0;
        for (int i = 0; i < params.Lenght(); num += params[i], ++i);
        SMTest::AssertOk(num == (1 + 2 + 3 + 4 + 5), "SMParams");
    }

    void SMCoreTest::SMTimerTest()
    {
        SMTimer timer;

        double time = 0;
        for(; ;)
        {
            time += timer.DeltaTime();

            if (time > 100)
                break;
        }

        SMTest::AssertOk(time > 0, "SMTimer::Reset(), SMTimer::DeltaTime()");
    }

    Test *t;

    void SMListTestHelper()
    {
        SMSmartPtr<Test> smart(new Test(10));
        t = smart;

        SMList<SMSmartPtr<Test> > list;
        list.Add(smart);
    }

    void SMCoreTest::SMListTest()
    {
        SMListTestHelper();
        SMTest::AssertOk(t->a != 10, "SMList->SmartPtr");

        SMList<int> list;
        list.Add(1);
        list.Add(2);
        list.Add(3);

        list.Remove(2);

        int x = 0;
        for (list.First(); list.IsDone(); list.Next())
            x += list.Current();
        SMTest::AssertOk(x == 4, "SMList->Remove, First, IsDone, Next");
    }

    Test *d;

    void SMDictionaryTestHelper()
    {
        SMSmartPtr<Test> smart(new Test(10));
        d = smart;

        SMDictionary<SMString, SMSmartPtr<Test> > dic;
        dic.Add("test", smart);
        dic.Add("test2", SMSmartPtr<Test>(new Test()));
        SMTest::AssertOk(dic.IsExist("test2"), "SMDictionary::IsExist(const TKey &key)");
        dic.Remove("test2");
        SMTest::AssertOk(!dic.IsExist("test2"), "SMDictionary::IsExist(const TKey &key) remove utan");
    }

    void SMCoreTest::SMDictionaryTest()
    {
        SMDictionaryTestHelper();
        SMTest::AssertOk(d->a != 10, "SMDictionary->SmartPtr");

        SMDictionary<int, int> dic;
        dic.Add(1, 1);
        dic.Add(2, 2);
        dic.Add(3, 3);

        dic.Remove(2);

        int x = 0;
        for (dic.First(); dic.IsDone(); dic.Next())
            x += dic.Current();
        SMTest::AssertOk(x == 4, "SMDictionary->Remove, First, IsDone, Next");
    }

    class Object
    {
    public:
        SMEvent<SMIUpdateEventHandler> UpdateEvent;

        Object() : UpdateEvent(&SMIUpdateEventHandler::Update)
        { }

        void Update()
        {
            UpdateEvent();
        }
    };

    class TestObject : public SMIUpdateEventHandler
    {
    public:
        static int touch;

        override void Update()
        {
            touch++;
        }
    };

    int TestObject::touch = 0;

    void SMCoreTest::SMEventTest()
    {
        Object obj;

        TestObject *to1 = new TestObject();
        TestObject *to2 = new TestObject();

        obj.UpdateEvent += to1;
        obj.UpdateEvent += to2;

        obj.Update();
        obj.UpdateEvent -= to1; //fel kell szabadítani, ha késõbb megszûnnek ezek
        obj.UpdateEvent -= to2;
        SMTest::AssertOk(TestObject::touch == 2, "SMEvent");
    }

    class Object2
    {
    private:
        SMTouchEventArgs touchArgs;

    public:
        SMEventArgs<SMITouchPressedEventHandler, SMTouchEventArgs> TouchEvent;

        Object2() : TouchEvent(&SMITouchPressedEventHandler::TouchPressed)
        { }

        void TouchPressed()
        {
            touchArgs.x = 1;
            touchArgs.y = 2;

            TouchEvent(touchArgs);
        }
    };

    class TestObject2 : public SMITouchPressedEventHandler
    {
    public:
        static int touchX, touchY;

        override void TouchPressed(const SMTouchEventArgs &args)
        {
            touchX += args.x;
            touchY += args.y;
        }
    };

    int TestObject2::touchX = 0;
    int TestObject2::touchY = 0;

    void SMCoreTest::SMEventArgsTest()
    {
        Object2 obj;

        TestObject2 *to1 = new TestObject2();
        TestObject2 *to2 = new TestObject2();

        obj.TouchEvent += to1;
        obj.TouchEvent += to2;

        obj.TouchPressed();
        obj.TouchEvent -= to1; //fel kell szabadítani, ha késõbb megszûnnek ezek
        obj.TouchEvent -= to2;
        SMTest::AssertOk(TestObject2::touchX == 2 && TestObject2::touchY == 4, "SMEventArgs");
    }

    int componentUpdate = 0;

    class Sprite : public SMGameComponent
    {
    public:
        Sprite(const SMString &name) : SMGameComponent(name)
        { }

        override void Update(double deltaTime)
        {
            componentUpdate++;
        }
    };

    class Layer : public SMGameCompositComponent
    {
    public:
       Layer(const SMString &name) : SMGameCompositComponent(name)
       { }

       override ~Layer()
       { }
    };

    void SMCoreTest::SMGameComponentTest()
    {
        SMSmartPtr<Layer> layer(new Layer("layer")); //a fõ componens lehet smart ptr. Õ magával húz minden pointert.
        Sprite *s1 = new Sprite("s1");
        Sprite *s2 = new Sprite("s2");

        layer->Add(s1);
        layer->Add(s2);

        layer->Update(0.0);
        s1->IsAlive(false);
        layer->Update(0.0);

        SMTest::AssertOk(componentUpdate == 3, "SMGameComponent");
    }
};};
