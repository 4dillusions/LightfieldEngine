#pragma once

#include "SMList.h"
#include "SMEventHandlers.h"

namespace SMEngine { namespace Core
{
	/*
	Esemény típus paraméter nélküli eseményekhez.
	Az eseményezõ objektumokra mutató pointer tárolódik és ennek az osztálynak nem feladata az objektum felszabadítása még véletlenül sem!

	Példa:
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
    ...
    Object obj;

    TestObject *to1 = new TestObject();
    TestObject *to2 = new TestObject();

    obj.UpdateEvent += to1;
    obj.UpdateEvent += to2;

    obj.Update();
    obj.UpdateEvent -= to1; //fel kell szabadítani, ha késõbb megszûnnek ezek
    obj.UpdateEvent -= to2;
	*/
	template <typename TReceiver> class SMEvent
	{
	private:
		SMList<TReceiver *> receiverList;
		void (TReceiver::*receiverFunction)();

	public:
		SMEvent(void (TReceiver::*receiverFunction)()) : receiverFunction(receiverFunction)
		{ }

		void operator += (TReceiver *receiver)
		{
			receiverList.Add(receiver);
		}

		void operator -= (TReceiver *receiver)
		{
			receiverList.Remove(receiver);
		}

		void operator () ()
		{
			for (receiverList.First(); receiverList.IsDone(); receiverList.Next())
				(receiverList.Current()->*receiverFunction)();
		}
	};
};};
