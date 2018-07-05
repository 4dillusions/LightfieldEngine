#pragma once

#include <map>

namespace SMEngine { namespace Core
{
	/*
	Szótár lista, ami nem támogatja a menet közbeni törlést.

	Deklaráció:
	SMDictionary<SMString, int> dic;

	Bejáró:
	for (dic.First(); dic.IsDone(); dic.Next())
		dic.Current()...

	vagy:
	for (dic.First(); dic.IsDone(); dic.Next())
		dic.CurrentKey()...

    smarPtr-el:
    SMDictionary<SMString, SMSmartPtr<Test> > dic;
    dic.Add("test", SMSmartPtr<Test>(new Test()));
	*/
	template <typename TKey, typename TValue> class SMDictionary
	{
	protected:
		std::map<TKey, TValue> data;
		typename std::map<TKey, TValue>::iterator iterator;

	public:
		SMDictionary()
		{ }

		SMDictionary(int size)
		{ }

		~SMDictionary()
		{
			RemoveAll();
		}

		int Lenght() const
		{
			return data.size();
		}

		//int a = dictionary["egy"];
		TValue operator[] (const TKey &key) const
		{
			return data[key];
		}

		//dictionary["huszonketto"] = 22;
		TValue &operator[] (const TKey &key)
		{
			return data[key];
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

		TValue Current()
		{
			return (*iterator).second;
		}

		TKey CurrentKey()
		{
			return (*iterator).first;
		}

		//Benne van e ez a kulcsú elem
		bool IsExist(const TKey &key)
		{
			return (data.find(key) != data.end());
		}

		void Add(const TKey &key, const TValue &value)
		{
			data.insert(std::make_pair(key, value));
		}

		void Remove(const TKey &item)
		{
			for (iterator = data.begin(); iterator != data.end(); ++iterator)
				if ((*iterator).first == item)
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
