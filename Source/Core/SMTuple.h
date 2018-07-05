#pragma once

namespace SMEngine { namespace Core
{
	/*
	Tuple típus.

	Deklaráció:
	SMTuple1<int> t = SMTuple::Create(12);
	SMTuple2<int, int> t2 = SMTuple::Create(12, 34);

	SMTuple2<int, int> TestTuple()
    {
        return SMTuple::Create(12, 34);
    }
	*/

	template <typename T1> class SMTuple1
	{
	public:
		T1 item1;

		SMTuple1(T1 item1) : item1(item1)
		{ }
	};

	template <typename T1, typename T2> class SMTuple2
	{
	public:
		T1 item1;
		T2 item2;

		SMTuple2(T1 item1, T2 item2) : item1(item1), item2(item2)
		{ }
	};

	template <typename T1, typename T2, typename T3> class SMTuple3
	{
	public:
		T1 item1;
		T2 item2;
		T3 item3;

		SMTuple3(T1 item1, T2 item2, T3 item3) : item1(item1), item2(item2), item3(item3)
		{ }
	};

	template <typename T1, typename T2, typename T3, typename T4> class SMTuple4
	{
	public:
		T1 item1;
		T2 item2;
		T3 item3;
		T4 item4;

		SMTuple4(T1 item1, T2 item2, T3 item3, T4 item4) : item1(item1), item2(item2), item3(item3), item4(item4)
		{ }
	};

	template <typename T1, typename T2, typename T3, typename T4, typename T5> class SMTuple5
	{
	public:
		T1 item1;
		T2 item2;
		T3 item3;
		T4 item4;
		T5 item5;

		SMTuple5(T1 item1, T2 item2, T3 item3, T4 item4, T5 item5) : item1(item1), item2(item2), item3(item3), item4(item4), item5(item5)
		{ }
	};

	class SMTuple
    {
    public:
        template <typename T1> static SMTuple1<T1> Create(T1 item1)
        {
            return SMTuple1<T1>(item1);
        }

        template <typename T1, typename T2> static SMTuple2<T1, T2> Create(T1 item1, T2 item2)
        {
            return SMTuple2<T1, T2>(item1, item2);
        }

        template <typename T1, typename T2, typename T3> static SMTuple3<T1, T2, T3> Create(T1 item1, T2 item2, T3 item3)
        {
            return SMTuple3<T1, T2, T3>(item1, item2, item3);
        }

        template <typename T1, typename T2, typename T3, typename T4> static SMTuple4<T1, T2, T3, T4> Create(T1 item1, T2 item2, T3 item3, T4 item4)
        {
            return SMTuple4<T1, T2, T3, T4>(item1, item2, item3, item4);
        }

        template <typename T1, typename T2, typename T3, typename T4, typename T5> static SMTuple5<T1, T2, T3, T4, T5> Create(T1 item1, T2 item2, T3 item3, T4 item4, T5 item5)
        {
            return SMTuple5<T1, T2, T3, T4, T5>(item1, item2, item3, item4, item5);
        }
    };
};};
