#pragma once

#include <vector>

namespace SMEngine { namespace Core
{
	/*
	Hagyom�nyos objektum lista, ami nem t�mogatja a menet k�zbeni t�rl�st.

	Deklar�ci�:
	//pointer burkol�sa objektumk�nt
	SMList<Test> list; //SMList<Test> list(100); //size 100
    Test *t = new Test();
    list.Add(*t);

    //vagy
    SMList<Test> list;
    list.Add(1);
    list.Add(2);

	Bej�r�:
	for (list.First(); list.IsDone(); list.Next())
	    list.Current()...

    SmartPtr:
    SMList<SMSmartPtr<Test> > list;
    list.Add(SmartPtr<Test>(new Test()));

    for (list.First(); list.IsDone(); list.Next())
	    list.Current()->...
	*/
	template <typename T> class SMList
	{
	protected:
		std::vector<T> data;
		typename std::vector<T>::iterator iterator;

	public:
		SMList()
		{ }

		SMList(int size)
		{
			data.reserve(size); //vector::capacity
		}

		~SMList()
		{
			RemoveAll();
		}

		int Lenght() const
		{
			return data.size();
		}

		void First()
		{
			iterator = data.begin();
		}

		bool IsDone()
		{
			return (iterator != data.end());
		}

		void Next()
		{
			++iterator;
		}

		T Current()
		{
			return *iterator;
		}

		void Add(const T &item)
		{
			data.push_back(item);
		}

		void Remove(const T &item)
		{
			for (iterator = data.begin(); iterator != data.end(); ++iterator)
				if (*iterator == item)
				{
					data.erase(iterator);
					return;
				}
		}

		void RemoveAll()
		{
			data.clear();
		}
	};
};};
