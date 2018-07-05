/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFDictionaryNode.h"
#include "LFLinkedList.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCollections
{
	/**
		@brief
		Hash table data structure <br>
		Items are objects <br>
		Keys are compared by using (explicit casted) integer <br><br>
		
		Mainly use for search <br><br>

		best/worst<br>
		search: O(1) O(n/10) <br>
		insert: O(1) O(n/10) <br>
		delete: O(1) O(n/10) <br>
		index:  O(1) O(n/10) <br>
		static remove/delete: yes <br>
		continuously remove/delete: no<br>
	*/
	template<typename TKey, typename TItem> class LFDictionary final
	{
		LFDictionary<TKey, TItem>(const LFDictionary<TKey, TItem> &) = delete;
		LFDictionary(LFDictionary<TKey, TItem> &&) = delete;
		LFDictionary<TKey, TItem> &operator=(const LFDictionary<TKey, TItem> &) = delete;
		LFDictionary<TKey, TItem> &operator=(LFDictionary<TKey, TItem> &&) = delete;

		static const int MinHashSize = 10;
		int hashSize;
		int length = 0;
		int currentHashIndex = 0;
		int currentItemIndex = 0;

		LFLinkedList<LFDictionaryNode<TKey, TItem> *> **data = nullptr;
		LFDictionaryNode<TKey, TItem> *current = nullptr;

	public:
		explicit LFDictionary(int minHashSize = MinHashSize) : hashSize(minHashSize)
		{
			data = LFCommon::LFMemoryManager::NewPointerArray<LFLinkedList<LFDictionaryNode<TKey, TItem> *>>(INFO, hashSize);

			for (int i = 0; i < hashSize; i++)
				data[i] = LFCommon::LFMemoryManager::New<LFLinkedList<LFDictionaryNode<TKey, TItem> *>>(INFO);
		}

		~LFDictionary()
		{
			for (int i = 0; i < hashSize; i++)
				LFCommon::LFMemoryManager::Delete(data[i]);

			LFCommon::LFMemoryManager::DeletePointerArray(data);
		}

		int GetLength() const
		{
			return length;
		}

		void First()
		{
			if (length > 0)
			{
				bool isMatch = false;
				for (int i = 0; i < hashSize; i++)
				{
					data[i]->First();
					if (data[i]->IsDone() && !isMatch)
					{
						isMatch = true;
						currentHashIndex = i;
					}
				}

				if (isMatch)
				{
					current = data[currentHashIndex]->GetCurrent();
					currentItemIndex = 0;
					data[currentHashIndex]->Next();
				}
				else 
					current = nullptr;
			}
			else
				current = nullptr;
		}

		bool IsDone()
		{
			return (current != nullptr);
		}

		void Next()
		{
			while (currentItemIndex < length && currentHashIndex < hashSize)
			{
				if (data[currentHashIndex]->IsDone())
				{
					current = data[currentHashIndex]->GetCurrent();
					currentItemIndex++;
					data[currentHashIndex]->Next();

					return;
				}
				
				currentHashIndex++;
			}

			current = nullptr;
		}
		
		TItem &GetCurrentItem()
		{
			if (current != nullptr)
				return current->item;

			static TItem currentItem;
			return currentItem;
		}

		TKey &GetCurrentKey()
		{
			if (current != nullptr)
				return current->key;

			static TKey currentKey;
			return currentKey;
		}

		TItem &GetItem(const TKey &key)
		{
			if (length > 0)
			{
				int hashCode = static_cast<int>(key);
				int hashIndex = static_cast<int>(key) % hashSize;

				for (data[hashIndex]->First(); data[hashIndex]->IsDone(); data[hashIndex]->Next())
					if (static_cast<int>(data[hashIndex]->GetCurrent()->key) == hashCode)
						return data[hashIndex]->GetCurrent()->item;
			}

			static TItem currentItem;
			return currentItem;
		}

		void Add(const TKey &key, const TItem &item)
		{
			int hashIndex = static_cast<int>(key) % hashSize;
			if (length > 0)
			{
				int hashCode = static_cast<int>(key);

				for (data[hashIndex]->First(); data[hashIndex]->IsDone(); data[hashIndex]->Next())
					if (static_cast<int>(data[hashIndex]->GetCurrent()->key) == hashCode)
						return;
			}

			data[hashIndex]->Add(LFCommon::LFMemoryManager::New<LFDictionaryNode<TKey, TItem>>(INFO, key, item));
			length++;
		}

		void RemoveAt(const TKey &key)
		{
			if (length > 0)
			{
				int hashCode = static_cast<int>(key);
				int hashIndex = static_cast<int>(key) % hashSize;

				for (data[hashIndex]->First(); data[hashIndex]->IsDone(); data[hashIndex]->Next())
					if (static_cast<int>(data[hashIndex]->GetCurrent()->key) == hashCode)
					{
						data[hashIndex]->DeleteCurrent();
						length--;
					}
			}
		}

		void RemoveAll()
		{
			for (int i = 0; i < hashSize; i++)
				data[i]->DeleteAll();

			length = 0;
		}
	};

	/**
	@brief
	Hash table data structure <br>
	Items are pointers <br>
	Keys are compared by using (explicit casted) integer <br><br>

	Mainly use for search <br><br>

	best/worst<br>
	search: O(1) O(n/10) <br>
	insert: O(1) O(n/10) <br>
	delete: O(1) O(n/10) <br>
	index:  O(1) O(n/10) <br>
	static remove/delete: yes <br>
	continuously remove/delete: no<br>
	*/
	template<typename TKey, typename TItem> class LFDictionary<TKey, TItem *> final
	{
		LFDictionary<TKey, TItem *>(const LFDictionary<TKey, TItem *> &) = delete;
		LFDictionary(LFDictionary<TKey, TItem *> &&) = delete;
		LFDictionary<TKey, TItem *> &operator=(const LFDictionary<TKey, TItem *> &) = delete;
		LFDictionary<TKey, TItem *> &operator=(LFDictionary<TKey, TItem *> &&) = delete;

		static const int MinHashSize = 10;
		int hashSize;
		int length = 0;
		int currentHashIndex = 0;
		int currentItemIndex = 0;
		bool isDestructDelete;

		LFLinkedList<LFDictionaryNode<TKey, TItem *> *> **data = nullptr;
		LFDictionaryNode<TKey, TItem *> *current = nullptr;

		void ReleaseAt(const TKey &key, bool isDelete)
		{
			if (length > 0)
			{
				int hashCode = static_cast<int>(key);
				int hashIndex = static_cast<int>(key) % hashSize;

				for (data[hashIndex]->First(); data[hashIndex]->IsDone(); data[hashIndex]->Next())
					if (static_cast<int>(data[hashIndex]->GetCurrent()->key) == hashCode)
					{
						if (isDelete)
							data[hashIndex]->DeleteCurrent();
						else
							data[hashIndex]->RemoveCurrent();

						length--;
					}
			}
		}

		void ReleaseAll(bool isDelete)
		{
			for (int i = 0; i < hashSize; i++)
				if (isDelete)
					data[i]->DeleteAll();
				else
					data[i]->RemoveAll();

			length = 0;
		}

	public:
		explicit LFDictionary(int minHashSize = MinHashSize, bool isDestructDelete = true) : hashSize(minHashSize), isDestructDelete(isDestructDelete)
		{
			data = LFCommon::LFMemoryManager::NewPointerArray<LFLinkedList<LFDictionaryNode<TKey, TItem *> *>>(INFO, hashSize);

			for (int i = 0; i < hashSize; i++)
				data[i] = LFCommon::LFMemoryManager::New<LFLinkedList<LFDictionaryNode<TKey, TItem *> *>>(INFO, isDestructDelete);
		}

		~LFDictionary()
		{
			for (int i = 0; i < hashSize; i++)
				LFCommon::LFMemoryManager::Delete(data[i]);

			LFCommon::LFMemoryManager::DeletePointerArray(data);
		}

		int GetLength() const
		{
			return length;
		}

		void First()
		{
			if (length > 0)
			{
				bool isMatch = false;
				for (int i = 0; i < hashSize; i++)
				{
					data[i]->First();
					if (data[i]->IsDone() && !isMatch)
					{
						isMatch = true;
						currentHashIndex = i;
					}
				}

				if (isMatch)
				{
					current = data[currentHashIndex]->GetCurrent();
					currentItemIndex = 0;
					data[currentHashIndex]->Next();
				}
				else
					current = nullptr;
			}
			else
				current = nullptr;
		}

		bool IsDone()
		{
			return (current != nullptr);
		}

		void Next()
		{
			while (currentItemIndex < length && currentHashIndex < hashSize)
			{
				if (data[currentHashIndex]->IsDone())
				{
					current = data[currentHashIndex]->GetCurrent();
					currentItemIndex++;
					data[currentHashIndex]->Next();

					return;
				}

				currentHashIndex++;
			}

			current = nullptr;
		}

		TItem *GetCurrentItem()
		{
			if (current != nullptr)
				return current->item;

			return nullptr;
		}

		TKey *GetCurrentKey()
		{
			if (current != nullptr)
				return current->key;

			return nullptr;
		}

		TItem *GetItem(const TKey &key)
		{
			if (length > 0)
			{
				int hashCode = static_cast<int>(key);
				int hashIndex = static_cast<int>(key) % hashSize;

				for (data[hashIndex]->First(); data[hashIndex]->IsDone(); data[hashIndex]->Next())
					if (static_cast<int>(data[hashIndex]->GetCurrent()->key) == hashCode)
						return data[hashIndex]->GetCurrent()->item;
			}

			return nullptr;
		}

		void Add(const TKey &key, TItem *item)
		{
			int hashIndex = static_cast<int>(key) % hashSize;
			if (length > 0)
			{
				int hashCode = static_cast<int>(key);

				for (data[hashIndex]->First(); data[hashIndex]->IsDone(); data[hashIndex]->Next())
					if (static_cast<int>(data[hashIndex]->GetCurrent()->key) == hashCode)
						return;
			}

			data[hashIndex]->Add(LFCommon::LFMemoryManager::New<LFDictionaryNode<TKey, TItem *>>(INFO, key, item));
			length++;
		}

		/** @brief Remove this item from list, but not delete */
		void RemoveAt(const TKey &key)
		{
			ReleaseAt(key, false);
		}

		/** @brief Remove this item from list, and delete */
		void DeleteAt(const TKey &key)
		{
			ReleaseAt(key, true);
		}

		/** @brief Remove all items from list, but not delete */
		void RemoveAll()
		{
			ReleaseAll(false);
		}

		/** @brief Remove all items from list, and delete */
		void DeleteAll()
		{
			ReleaseAll(true);
		}
	};
}}}}
