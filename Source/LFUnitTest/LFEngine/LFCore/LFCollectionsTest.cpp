/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFCollectionsTest.h"
#include "..\..\LFTest.h"
#include "..\..\LFTestObjectA.h"
#include "..\..\..\LFEngine\LFCore\LFCore.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFMemoryManager.h"
#include "..\..\..\LFEngine\LFCore\LFCollections\LFLinkedListNode.h"
#include "..\..\..\LFEngine\LFCore\LFCollections\LFLinkedList.h"
#include "..\..\..\LFEngine\LFCore\LFCollections\LFListNode.h"
#include "..\..\..\LFEngine\LFCore\LFCollections\LFList.h"
#include "..\..\..\LFEngine\LFCore\LFCollections\LFDictionary.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFString.h"

using namespace LF3Engine::LFEngine::LFCore::LFCollections;
using namespace LF3Engine::LFUnitTest;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore
{
	void LFCollectionsTest::LFLinkedListNodeTest()
	{
		int memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();
		LFTestObjectA::SetReferenceCounter(0);

		auto LinkedListObjectNode = []()
		{
			LFLinkedListNode<LFTestObjectA> linkedListNode;
			linkedListNode.item = LFTestObjectA();
			linkedListNode.Release();
		};
		LinkedListObjectNode();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);
		LFTest::AssertOk(LFTestObjectA::GetReferenceCounter() == 0, INFO);

		LFLinkedListNode<LFTestObjectA *> linkedListNode2;
		linkedListNode2.item = LFMemoryManager::New<LFTestObjectA>(INFO);
		linkedListNode2.isDelete = true;
		linkedListNode2.Release();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);
		LFTest::AssertOk(LFTestObjectA::GetReferenceCounter() == 0, INFO);
	}
	
	void LFCollectionsTest::LFLinkedListTest()
	{
		int memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();

		//object list
		auto LinkedListObject = []()
		{
			LFLinkedList<int> list;
		};
		LinkedListObject();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		LFLinkedList<int> list;

		list.Add(2);
		list.Add(7);
		list.Add(5);
		list.Add(6);
		list.Add(9);
		list.Add(11);
		list.Add(4);

		for (list.First(); list.IsDone(); list.Next())
			if (list.GetCurrent() == 5)
				list.RemoveCurrent();

		int allNumbers = 0;
		for (list.First(); list.IsDone(); list.Next())
			allNumbers += list.GetCurrent();

		list.RemoveAll();

		list.Add(4);
		list.Add(5);
		list.Add(6);

		int allNumbers2 = 0;
		for (list.First(); list.IsDone(); list.Next())
			allNumbers2 += list.GetCurrent();

		LFTest::AssertOk((allNumbers2 == (4 + 5 + 6)), INFO);
		LFTest::AssertOk((allNumbers == (2 + 7 + 6 + 9 + 11 + 4)), INFO);

		list.RemoveAll();

		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		//dynamic list
		auto LinkedListDynamic = []()
		{
			LFLinkedList<int *> list2;
		};
		LinkedListDynamic();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		LFLinkedList<int *> list2;

		list2.Add(LFMemoryManager::New<int>(INFO, 2));
		list2.Add(LFMemoryManager::New<int>(INFO, 7));
		list2.Add(LFMemoryManager::New<int>(INFO, 5));
		list2.Add(LFMemoryManager::New<int>(INFO, 6));
		list2.Add(LFMemoryManager::New<int>(INFO, 9));
		list2.Add(LFMemoryManager::New<int>(INFO, 11));
		list2.Add(LFMemoryManager::New<int>(INFO, 4));

		for (list2.First(); list2.IsDone(); list2.Next())
			if (*list2.GetCurrent() == 5)
				list2.DeleteCurrent();

		allNumbers = 0;
		for (list2.First(); list2.IsDone(); list2.Next())
			allNumbers += *list2.GetCurrent();

		list2.DeleteAll();

		list2.Add(LFMemoryManager::New<int>(INFO, 4));
		list2.Add(LFMemoryManager::New<int>(INFO, 5));
		list2.Add(LFMemoryManager::New<int>(INFO, 6));

		allNumbers2 = 0;
		for (list2.First(); list2.IsDone(); list2.Next())
			allNumbers2 += *list2.GetCurrent();

		LFTest::AssertOk((allNumbers2 == (4 + 5 + 6)), INFO);
		LFTest::AssertOk((allNumbers == (2 + 7 + 6 + 9 + 11 + 4)), INFO);

		list2.DeleteAll();

		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);
	}

	void LFCollectionsTest::LFListNodeTest()
	{
		int memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();
		LFTestObjectA::SetReferenceCounter(0);

		auto LinkedListObjectNode = []()
		{
			LFListNode<LFTestObjectA> linkedListNode;
			linkedListNode.item = LFTestObjectA();
		};
		LinkedListObjectNode();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);
		LFTest::AssertOk(LFTestObjectA::GetReferenceCounter() == 0, INFO);

		LFListNode<LFTestObjectA *> linkedListNode2;
		linkedListNode2.item = LFMemoryManager::New<LFTestObjectA>(INFO);
		linkedListNode2.Release();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);
		LFTest::AssertOk(LFTestObjectA::GetReferenceCounter() == 0, INFO);
	}

	void LFCollectionsTest::LFListTest()
	{
		//object list
		int memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();

		auto ListObject = []()
		{
			LFList<int> list;
		};
		ListObject();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		auto ListObjTestReturn = []()
		{
			LFList<LFString> result;
			
			LFString temp;
			temp += "one";
			result.Add(temp);

			temp.Clear();
			temp += "two";
			result.Add(temp);

			return result;
		};
		LFTest::AssertOk(ListObjTestReturn()[0] == LFString("one") && ListObjTestReturn()[1] == LFString("two"), INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		LFList<int> list;

		list.Add(2);
		list.Add(7);
		list.Add(5);
		list.Add(6);
		list.Add(9);
		list.Add(11);
		list.Add(4);

		for (list.First(); list.IsDone(); list.Next())
			if (list.GetCurrent() == 5)
				list.RemoveCurrent();

		int allNumbers = 0;
		for (list.First(); list.IsDone(); list.Next())
			allNumbers += list.GetCurrent();

		list.RemoveAll();

		LFTest::AssertOk((allNumbers == (2 + 7 + 6 + 9 + 11 + 4)), INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 1, INFO);

		list.Add(2);
		list.Add(7);
		list.Add(5);
		list.Add(6);
		list.Add(9);
		list.Add(11);
		list.Add(4);

		list.RemoveAt(8);
		list.RemoveAt(2);

		allNumbers = 0;
		for (list.First(); list.IsDone(); list.Next())
			allNumbers += list.GetCurrent();

		list.RemoveAll();

		LFTest::AssertOk((allNumbers == (2 + 7 + 6 + 9 + 11 + 4)), INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 1, INFO);

		LFList<int> list2(3);
		list2.Add(1);
		list2.Add(2);
		list2.Add(3);
		list2.Add(4);
		list2.Add(5);
		allNumbers = 0;
		for (list2.First(); list2.IsDone(); list2.Next())
			allNumbers += list2.GetCurrent();

		list2.RemoveAll();

		list2.Add(1);
		list2.Add(2);
		list2.Add(3);
		list2[0] = 10;
		int allNumbers2 = 0;
		for (int i = 0; i < list2.GetLength(); allNumbers2 += list2[i++])
			;

		list2.RemoveAll();

		LFTest::AssertOk((allNumbers == (1 + 2 + 3 + 4 + 5)), INFO);
		LFTest::AssertOk((allNumbers2 == (10 + 2 + 3)), INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 2, INFO);

		//dynamic list
		auto ListDynamic = []()
		{
			LFList<int *> listD;
		};
		ListDynamic();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 2, INFO);

		auto ListDynamicTestReturn = []()
		{
			LFList<int *> result;
			result.Add(LFMemoryManager::New<int>(INFO, 1));
			result.Add(LFMemoryManager::New<int>(INFO, 2));

			return result;
		};
		auto dList = ListDynamicTestReturn();
		LFTest::AssertOk(*dList[0] == 1 && *dList[1] == 2, INFO);
		dList.DeleteAll();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 3, INFO);

		LFList<int *> listD;

		listD.Add(LFMemoryManager::New<int>(INFO, 2));
		listD.Add(LFMemoryManager::New<int>(INFO, 7));
		listD.Add(LFMemoryManager::New<int>(INFO, 5));
		listD.Add(LFMemoryManager::New<int>(INFO, 6));
		listD.Add(LFMemoryManager::New<int>(INFO, 9));
		listD.Add(LFMemoryManager::New<int>(INFO, 11));
		listD.Add(LFMemoryManager::New<int>(INFO, 4));

		for (listD.First(); listD.IsDone(); listD.Next())
			if (*listD.GetCurrent() == 5)
				listD.DeleteCurrent();

		allNumbers = 0;
		for (listD.First(); listD.IsDone(); listD.Next())
			allNumbers += *listD.GetCurrent();

		listD.DeleteAll();

		LFTest::AssertOk((allNumbers == (2 + 7 + 6 + 9 + 11 + 4)), INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 4, INFO);

		listD.Add(LFMemoryManager::New<int>(INFO, 2));
		listD.Add(LFMemoryManager::New<int>(INFO, 7));
		listD.Add(LFMemoryManager::New<int>(INFO, 5));
		listD.Add(LFMemoryManager::New<int>(INFO, 6));
		listD.Add(LFMemoryManager::New<int>(INFO, 9));
		listD.Add(LFMemoryManager::New<int>(INFO, 11));
		listD.Add(LFMemoryManager::New<int>(INFO, 4));

		listD.DeleteAt(8);
		listD.DeleteAt(2);

		allNumbers = 0;
		for (listD.First(); listD.IsDone(); listD.Next())
			allNumbers += *listD.GetCurrent();

		listD.DeleteAll();

		LFTest::AssertOk((allNumbers == (2 + 7 + 6 + 9 + 11 + 4)), INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 4, INFO);

		LFList<int *> listD2(true, 3);
		listD2.Add(LFMemoryManager::New<int>(INFO, 1));
		listD2.Add(LFMemoryManager::New<int>(INFO, 2));
		listD2.Add(LFMemoryManager::New<int>(INFO, 3));
		listD2.Add(LFMemoryManager::New<int>(INFO, 4));
		listD2.Add(LFMemoryManager::New<int>(INFO, 5));
		allNumbers = 0;
		for (listD2.First(); listD2.IsDone(); listD2.Next())
			allNumbers += *listD2.GetCurrent();

		listD2.DeleteAll();

		listD2.Add(LFMemoryManager::New<int>(INFO, 1));
		listD2.Add(LFMemoryManager::New<int>(INFO, 2));
		listD2.Add(LFMemoryManager::New<int>(INFO, 3));
		*listD2[0] = 10;
		allNumbers2 = 0;
		for (int i = 0; i < listD2.GetLength(); allNumbers2 += *listD2[i++])
			;

		listD2.DeleteAll();

		LFTest::AssertOk((allNumbers == (1 + 2 + 3 + 4 + 5)), INFO);
		LFTest::AssertOk((allNumbers2 == (10 + 2 + 3)), INFO);
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 5, INFO);

		//dynamic list remove
		LFList<int *> listD3;
		int *a = LFMemoryManager::New<int>(INFO, 3);
		int *b = LFMemoryManager::New<int>(INFO, 3);
		int *c = LFMemoryManager::New<int>(INFO, 3);
		listD3.Add(a);
		listD3.Add(b);
		listD3.Add(c);

		listD3.RemoveAll();

		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 9, INFO);

		LFMemoryManager::Delete(a);
		LFMemoryManager::Delete(b);
		LFMemoryManager::Delete(c);

		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount + 6, INFO);
	}
	
	void LFCollectionsTest::LFDictionaryNodeTest()
	{
		int memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();
		LFTestObjectA::SetReferenceCounter(0);

		auto DictionaryObjectNode = []()
		{
			LFDictionaryNode<int, LFTestObjectA> dictionaryNode(1, LFTestObjectA());
		};
		DictionaryObjectNode();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);
		LFTest::AssertOk(LFTestObjectA::GetReferenceCounter() == 0, INFO);

		LFTestObjectA::SetReferenceCounter(0);
		memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();
		auto DictionaryDynamicNode = []()
		{
			LFDictionaryNode<int, LFTestObjectA *> linkedListNode2(1, LFMemoryManager::New<LFTestObjectA>(INFO));
		};
		DictionaryDynamicNode();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);
		LFTest::AssertOk(LFTestObjectA::GetReferenceCounter() == 0, INFO);
	}
	
	void LFCollectionsTest::LFDictionaryTest()
	{
		//object dictionary
		int memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();
		auto DictionaryObj = []()
		{
			LFDictionary<LFString, int> dictionary;
		};
		DictionaryObj();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		LFDictionary<LFString, int> dictionary;
		dictionary.Add(LFString("one"), 1);
		dictionary.Add(LFString("two"), 2);
		dictionary.Add(LFString("three"), 3);
		dictionary.Add(LFString("one"), 4);

		int numbers = 0;
		for (dictionary.First(); dictionary.IsDone(); dictionary.Next())
			numbers += dictionary.GetCurrentItem();

		LFTest::AssertOk(dictionary.GetLength() == 3, INFO);
		LFTest::AssertOk(numbers == (1 + 2 + 3), INFO);
		LFTest::AssertOk(dictionary.GetItem(LFString("two")) == 2, INFO);
		LFTest::AssertOk(dictionary.GetItem(LFString("ten")) == 0, INFO);

		dictionary.RemoveAt(LFString("one"));
		numbers = 0;
		for (dictionary.First(); dictionary.IsDone(); dictionary.Next())
			numbers += dictionary.GetCurrentItem();

		LFTest::AssertOk(numbers == (2 + 3), INFO);

		numbers = 0;
		dictionary.RemoveAll();
		for (dictionary.First(); dictionary.IsDone(); dictionary.Next())
			numbers += dictionary.GetCurrentItem();

		LFTest::AssertOk(numbers == 0, INFO);

		dictionary.Add(LFString("seven"), 7);
		dictionary.Add(LFString("five"), 5);
		dictionary.Add(LFString("eight"), 8);
		dictionary.Add(LFString("six"), 6);
		numbers = 0;
		for (dictionary.First(); dictionary.IsDone(); dictionary.Next())
			numbers += dictionary.GetCurrentItem();

		LFTest::AssertOk(numbers == (5 + 6 + 7 + 8), INFO);

		LFDictionary<LFString, int> dictionary2(1);
		dictionary2.Add(LFString("seven"), 7);
		dictionary2.Add(LFString("five"), 5);
		dictionary2.Add(LFString("eight"), 8);
		dictionary2.Add(LFString("six"), 6);
		numbers = 0;
		for (dictionary2.First(); dictionary2.IsDone(); dictionary2.Next())
			numbers += dictionary2.GetCurrentItem();

		LFTest::AssertOk(numbers == (5 + 6 + 7 + 8), INFO);

		//dynamic dictionary
		memoryLeakCount = LFMemoryManager::GetMemoryLeakCount();
		auto DictionaryDynamic = []()
		{
			LFDictionary<LFString, int *> dictionaryD;
		};
		DictionaryDynamic();
		LFTest::AssertOk(LFMemoryManager::GetMemoryLeakCount() == memoryLeakCount, INFO);

		LFDictionary<LFString, int *> dictionaryD;
		auto num4 = LFMemoryManager::New<int>(INFO, 4);
		dictionaryD.Add(LFString("one"), LFMemoryManager::New<int>(INFO, 1));
		dictionaryD.Add(LFString("two"), LFMemoryManager::New<int>(INFO, 2));
		dictionaryD.Add(LFString("three"), LFMemoryManager::New<int>(INFO, 3));
		dictionaryD.Add(LFString("one"), num4);

		numbers = 0;
		for (dictionaryD.First(); dictionaryD.IsDone(); dictionaryD.Next())
			numbers += *dictionaryD.GetCurrentItem();

		LFTest::AssertOk(dictionaryD.GetLength() == 3, INFO);
		LFTest::AssertOk(numbers == (1 + 2 + 3), INFO);
		LFTest::AssertOk(*dictionaryD.GetItem(LFString("two")) == 2, INFO);
		LFTest::AssertOk(dictionaryD.GetItem(LFString("ten")) == nullptr, INFO);
		LFMemoryManager::Delete(num4);

		dictionaryD.DeleteAt(LFString("one"));
		numbers = 0;
		for (dictionaryD.First(); dictionaryD.IsDone(); dictionaryD.Next())
			numbers += *dictionaryD.GetCurrentItem();

		LFTest::AssertOk(numbers == (2 + 3), INFO);

		numbers = 0;
		dictionaryD.DeleteAll();
		for (dictionaryD.First(); dictionaryD.IsDone(); dictionaryD.Next())
			numbers += *dictionaryD.GetCurrentItem();

		LFTest::AssertOk(numbers == 0, INFO);

		dictionaryD.Add(LFString("seven"), LFMemoryManager::New<int>(INFO, 7));
		dictionaryD.Add(LFString("five"), LFMemoryManager::New<int>(INFO, 5));
		dictionaryD.Add(LFString("eight"), LFMemoryManager::New<int>(INFO, 8));
		dictionaryD.Add(LFString("six"), LFMemoryManager::New<int>(INFO, 6));
		numbers = 0;
		for (dictionary.First(); dictionary.IsDone(); dictionary.Next())
			numbers += dictionary.GetCurrentItem();

		LFTest::AssertOk(numbers == (5 + 6 + 7 + 8), INFO);

		LFDictionary<LFString, int *> dictionaryD2(1);
		dictionaryD2.Add(LFString("seven"), LFMemoryManager::New<int>(INFO, 7));
		dictionaryD2.Add(LFString("five"), LFMemoryManager::New<int>(INFO, 5));
		dictionaryD2.Add(LFString("eight"), LFMemoryManager::New<int>(INFO, 8));
		dictionaryD2.Add(LFString("six"), LFMemoryManager::New<int>(INFO, 6));
		numbers = 0;
		for (dictionaryD2.First(); dictionaryD2.IsDone(); dictionaryD2.Next())
			numbers += *dictionaryD2.GetCurrentItem();

		LFTest::AssertOk(numbers == (5 + 6 + 7 + 8), INFO);
	}

	void LFCollectionsTest::RunAllTests()
	{
		LFLinkedListNodeTest();
		LFLinkedListTest();
		LFListNodeTest();
		LFListTest();
		LFDictionaryNodeTest();
		LFDictionaryTest();
	}
}}}}