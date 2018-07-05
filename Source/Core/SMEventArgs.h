#pragma once

#include "SMList.h"
#include "SMEventHandlers.h"

namespace SMEngine { namespace Core
{
	/*
	Esemény típus paraméteres eseményekhez.
	Az eseményezõ objektumokra mutató pointer tárolódik és ennek az osztálynak nem feladata az objektum felszabadítása még véletlenül sem!

	Példa:
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
    ...
    Object2 obj;

    TestObject2 *to1 = new TestObject2();
    TestObject2 *to2 = new TestObject2();

    obj.TouchEvent += to1;
    obj.TouchEvent += to2;

    obj.TouchPressed();
    obj.TouchEvent -= to1; //fel kell szabadítani, ha késõbb megszûnnek ezek
    obj.TouchEvent -= to2;
	*/
	template <typename TReceiver, typename TArgs> class SMEventArgs
	{
	private:
		bool isAction;

		SMList<TReceiver *> receiverList;
		void (TReceiver::*receiverFunctionWithArgs)(const TArgs &args);

	public:
		SMEventArgs(void (TReceiver::*receiverFunctionWithArgs)(const TArgs &args)) : receiverFunctionWithArgs(receiverFunctionWithArgs)
		{ }

		void operator += (TReceiver *receiver)
		{
			receiverList.Add(receiver);
		}

		void operator -= (TReceiver *receiver)
		{
			receiverList.Remove(receiver);
		}

		void operator () (const TArgs &args)
		{
			for (receiverList.First(); receiverList.IsDone(); receiverList.Next())
				(receiverList.Current()->*receiverFunctionWithArgs)(args);
		}
	};
};};
