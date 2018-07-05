#pragma once

#include "SMList.h"
#include "SMEventHandlers.h"

namespace SMEngine { namespace Core
{
	/*
	Esem�ny t�pus param�ter n�lk�li esem�nyekhez.
	Az esem�nyez� objektumokra mutat� pointer t�rol�dik �s ennek az oszt�lynak nem feladata az objektum felszabad�t�sa m�g v�letlen�l sem!

	P�lda:
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
    obj.UpdateEvent -= to1; //fel kell szabad�tani, ha k�s�bb megsz�nnek ezek
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
