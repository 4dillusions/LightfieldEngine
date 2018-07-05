#pragma once

#include "SMCore.h"

namespace SMEngine { namespace Core
{
    /*
    Burkol� oszt�ly pointerhez. (pointert tartalmaz� t�pusn�l az operator= �s a m�sol� konstruktort meg kell �rni, ahogy itt is!

    Haszn�lat:
    SMSmartPtr<Test> test(new Test());

    test->a = 20;
    Test *test2 = test;
    */
    template <typename T> class SMSmartPtr
    {
    private:
        T *pointer;

    public:
		SMSmartPtr() : pointer(nullptr)
		{ }

        SMSmartPtr(T *pointer) { this->pointer = pointer; }

		SMSmartPtr(const SMSmartPtr &value) : pointer(nullptr)
		{
			pointer = new T(*value.pointer);
		}

        ~SMSmartPtr() { delete pointer; }

		SMSmartPtr<T> &operator= (const SMSmartPtr<T> &value) //m�ly m�sol�s
		{
			if (this == &value)
				return *this;

			if (pointer != nullptr)
				delete pointer;

			if (value.pointer == nullptr)
				pointer = nullptr;
			else
				pointer = new T(*value.pointer);

			return *this;
		}

		bool operator == (const SMSmartPtr<T> &value) const
        {
            return (pointer == value.pointer);
        }

        T *operator -> () { return pointer; }
        operator T * () { return pointer; }
    };
};};
