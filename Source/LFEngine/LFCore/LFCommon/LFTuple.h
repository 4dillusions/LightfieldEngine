/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	template <typename T1> class LFTuple1 final
	{
	public:
		T1 item1;

		LFTuple1(T1 item1) : item1(item1)
		{ }
	};

	template <typename T1, typename T2> class LFTuple2 final
	{
	public:
		T1 item1;
		T2 item2;

		LFTuple2(T1 item1, T2 item2) : item1(item1), item2(item2)
		{ }
	};

	template <typename T1, typename T2, typename T3> class LFTuple3 final
	{
	public:
		T1 item1;
		T2 item2;
		T3 item3;

		LFTuple3(T1 item1, T2 item2, T3 item3) : item1(item1), item2(item2), item3(item3)
		{ }
	};

	template <typename T1, typename T2, typename T3, typename T4> class LFTuple4 final
	{
	public:
		T1 item1;
		T2 item2;
		T3 item3;
		T4 item4;

		LFTuple4(T1 item1, T2 item2, T3 item3, T4 item4) : item1(item1), item2(item2), item3(item3), item4(item4)
		{ }
	};

	template <typename T1, typename T2, typename T3, typename T4, typename T5> class LFTuple5 final
	{
	public:
		T1 item1;
		T2 item2;
		T3 item3;
		T4 item4;
		T5 item5;

		LFTuple5(T1 item1, T2 item2, T3 item3, T4 item4, T5 item5) : item1(item1), item2(item2), item3(item3), item4(item4), item5(item5)
		{ }
	};

	class LFTuple final
    {
		LFTuple() = delete;
		LFTuple(const LFTuple&) = delete;
		LFTuple(LFTuple &&) = delete;
		LFTuple &operator=(const LFTuple &) = delete;
		LFTuple &operator=(LFTuple &&) = delete;
		~LFTuple() = delete;

	public:
        template <typename T1> static LFTuple1<T1> Create(T1 item1)
        {
            return LFTuple1<T1>(item1);
        }

        template <typename T1, typename T2> static LFTuple2<T1, T2> Create(T1 item1, T2 item2)
        {
            return LFTuple2<T1, T2>(item1, item2);
        }

        template <typename T1, typename T2, typename T3> static LFTuple3<T1, T2, T3> Create(T1 item1, T2 item2, T3 item3)
        {
            return LFTuple3<T1, T2, T3>(item1, item2, item3);
        }

        template <typename T1, typename T2, typename T3, typename T4> static LFTuple4<T1, T2, T3, T4> Create(T1 item1, T2 item2, T3 item3, T4 item4)
        {
            return LFTuple4<T1, T2, T3, T4>(item1, item2, item3, item4);
        }

        template <typename T1, typename T2, typename T3, typename T4, typename T5> static LFTuple5<T1, T2, T3, T4, T5> Create(T1 item1, T2 item2, T3 item3, T4 item4, T5 item5)
        {
            return LFTuple5<T1, T2, T3, T4, T5>(item1, item2, item3, item4, item5);
        }
    };
}}}}