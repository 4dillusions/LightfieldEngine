/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "CollectionsTest.h"
#include "..\Test.h"
#include "..\..\Core\Collections\LFDictionary.h"
#include "..\..\Core\Collections\LFList.h"

using namespace LFCore::Common;
using namespace LFCore::Collections;

namespace UnitTest
{
	void CollectionsTest::DictionaryTest()
	{
		LFDictionary<int, int *> dictionary;

		int *n2 = LFNew<int>(AT, 2);
		int *n7 = LFNew<int>(AT, 7);
		int *n5 = LFNew<int>(AT, 5);
		int *n6 = LFNew<int>(AT, 6);
		int *n9 = LFNew<int>(AT, 9);
		int *n11 = LFNew<int>(AT, 11);
		int *n4 = LFNew<int>(AT, 4);

		dictionary.Add(2, n2);
		dictionary.Add(7, n7);
		dictionary.Add(5, n5);
		bool x2 = dictionary.Add(2, n2); //false
		dictionary.Add(6, n6);
		dictionary.Add(9, n9);
		bool x5 = dictionary.Add(5, n5); //false
		dictionary.Add(11, n11);
		dictionary.Add(4, n4);

		Test::AssertOk((x2 == false && x5 == false), "LFCore::Collections::LFDictionary::Add");

		bool isFounded11 = (*dictionary.FindItem(11) == 11);
		dictionary.Delete(5);
		bool isNotFounded5 = (dictionary.FindItem(5) == nullptr);
		
		Test::AssertOk((isFounded11 && isNotFounded5), "LFCore::Collections::LFDictionary::FindItem, Delete");

		int allNumbers = 0;
		for (dictionary.First(); dictionary.IsDone(); dictionary.Next())
			allNumbers += *dictionary.Current();

		Test::AssertOk((allNumbers == (2 + 7 + 6 + 9 + 11 + 4)), "LFCore::Collections::LFDictionary iterator pattern");
	}
	
	void CollectionsTest::ListTest()
	{
		LFList<int *> list;

		int *n2 = LFNew<int>(AT, 2);
		int *n7 = LFNew<int>(AT, 7);
		int *n5 = LFNew<int>(AT, 5);
		int *n6 = LFNew<int>(AT, 6);
		int *n9 = LFNew<int>(AT, 9);
		int *n11 = LFNew<int>(AT, 11);
		int *n4 = LFNew<int>(AT, 4);

		list.Add(n2);
		list.Add(n7);
		list.Add(n5);
		list.Add(n6);
		list.Add(n9);
		list.Add(n11);
		list.Add(n4);

		for (list.First(); list.IsDone(); list.Next())
			if (*list.Current() == 5)
				list.DeleteCurrent();

		int allNumbers = 0;
		for (list.First(); list.IsDone(); list.Next())
			allNumbers += *list.Current();

		Test::AssertOk((allNumbers == (2 + 7 + 6 + 9 + 11 + 4)), "LFCore::Collections::LFList iterator pattern, Delete");
	}
};
