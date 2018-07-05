/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFListNode.h"
#include "..\LFCore.h"
#include <algorithm>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCollections
{
	/**
		@brief
		Dynamic array data structure with objects. <br><br>

		Mainly use for indexing <br><br>
	
		best/worst<br>
		search: O(n) O(n) <br>
		insert: O(1) O(1) <br>
		delete: O(n) O(n) <br>
		index:  O(1) O(1) <br>
		static remove/delete: yes <br>
		continuously remove/delete: yes <br>
	*/
	template<typename T> class LFList final
	{
		static const int MinDataSize = 100;
		int dataSize;
		int length = 0;
		int currentIndex = 0;

		LFListNode<T> **data = nullptr;
		LFListNode<T> *current = nullptr;
		
		void ReleaseAll()
		{
			if (data != nullptr)
				for (First(); IsDone(); Next())
					if (data[currentIndex] != nullptr)
						LFCommon::LFMemoryManager::Delete(data[currentIndex]);

			length = 0;
		}

		void NextToEnd()
		{
			currentIndex++;

			if (currentIndex < dataSize)
				current = data[currentIndex];
			else
				current = nullptr;
		}

	public:
		explicit LFList(int minDataSize = MinDataSize) : dataSize(minDataSize)
		{
			data = LFCommon::LFMemoryManager::NewPointerArray<LFListNode<T>>(INFO, dataSize);
			
			for (int i = 0; i < dataSize; i++)
				data[i] = nullptr;
		}

		LFList<T>(const LFList<T> &value)
		{
			*this = value;
		}

        LFList(LFList<T> &&value)
        {
			*this = std::move(value);
        }

		~LFList()
		{
			ReleaseAll();
			LFCommon::LFMemoryManager::DeletePointerArray(data);
		}

		LFList<T> &operator=(const LFList<T> &value)
		{
			if (this != &value)
			{
				ReleaseAll();
				LFCommon::LFMemoryManager::DeletePointerArray(data);

				dataSize = value.dataSize;
				length = value.length;
				currentIndex = value.currentIndex;

				data = LFCommon::LFMemoryManager::NewPointerArray<LFListNode<T>>(INFO, dataSize);
				for (int i = 0; i < length; i++)
					data[i] = value.data[i];
			}

			return *this;
		}

		LFList<T> &operator=(LFList<T> &&value)
		{
			if (this != &value)
			{
				ReleaseAll();
				LFCommon::LFMemoryManager::DeletePointerArray(data);

				dataSize = value.dataSize;
				length = value.length;
				currentIndex = value.currentIndex;
				data = value.data;

				value.dataSize = MinDataSize;
				value.length = 0;
				value.currentIndex = 0;
				value.data = nullptr;
			}

			return *this;
		}

		int GetLength() const
		{
			return length;
		}

		void First()
		{
			currentIndex = 0;
			current = data[0];
		}

		bool IsDone()
		{
			return (current != nullptr);
		}

		void Next()
		{
			currentIndex++;

			if (currentIndex < length)
				current = data[currentIndex];
			else
				current = nullptr;
		}

		T &GetCurrent()
		{
			if (current != nullptr)
				return current->item;

			static T currentItem;
			return currentItem;
		}

		//T operator [] (int index) const
		//{
		//	return data[index]->item;
		//}

		T &operator [] (int index)
		{
			return data[index]->item;
		}

		void Add(const T &item)
		{
			if (length == dataSize)
			{
				dataSize *= 2;
				LFListNode<T> **tempData = LFCommon::LFMemoryManager::NewPointerArray<LFListNode<T>>(INFO, dataSize);
				for (int i = 0; i < length; i++)
					tempData[i] = data[i];

				LFCommon::LFMemoryManager::DeletePointerArray(data);
				data = tempData;
			}

			auto temp = LFCommon::LFMemoryManager::New<LFListNode<T>>(INFO);
			temp->item = item;

			data[length] = temp;
			length++;
		}

		void RemoveAt(int index)
		{
			if (length > 0 && index >= 0 && index < length)
			{
				length--;
				LFCommon::LFMemoryManager::Delete(data[index]);

				for (int i = index; i < length; i++)
					data[i] = data[i + 1];
			}
		}

		void RemoveCurrent()
		{
			RemoveAt(currentIndex);
		}

		void RemoveAll()
		{
			ReleaseAll();
		}
	};

	/**
	@brief
	Dynamic array data structure with pointers. <br><br>

	Mainly use for indexing <br><br>

	best/worst<br>
	search: O(n) O(n) <br>
	insert: O(1) O(1) <br>
	delete: O(n) O(n) <br>
	index:  O(1) O(1) <br>
	static remove/delete: yes <br>
	continuously remove/delete: yes <br>
	*/
	template<typename T> class LFList<T *> final
	{
		static const int MinDataSize = 100;
		int dataSize;
		int length = 0;
		int currentIndex = 0;
		bool isDestructDelete; //release all in destructor

		LFListNode<T *> **data = nullptr;
		LFListNode<T *> *current = nullptr;
		
		void ReleaseAll(bool isDelete)
		{
			if (data != nullptr)
				for (First(); IsDone(); Next())
				{
					if (isDelete)
						data[currentIndex]->Release();

					LFCommon::LFMemoryManager::Delete(data[currentIndex]);
				}

			length = 0;
		}

		void ReleaseAt(int index, bool isDelete)
		{
			if (length > 0 && index >= 0 && index < length)
			{
				length--;

				if (isDelete)
					data[index]->Release();

				LFCommon::LFMemoryManager::Delete(data[index]);

				for (int i = index; i < length; i++)
					data[i] = data[i + 1];
			}
		}

		void NextToEnd()
		{
			currentIndex++;

			if (currentIndex < dataSize)
				current = data[currentIndex];
			else
				current = nullptr;
		}

	public:
		explicit LFList(bool isDestructDelete = true, int minDataSize = MinDataSize) : dataSize(minDataSize), isDestructDelete(isDestructDelete)
		{
			data = LFCommon::LFMemoryManager::NewPointerArray<LFListNode<T *>>(INFO, dataSize);

			for (int i = 0; i < dataSize; i++)
				data[i] = nullptr;
		}

		LFList(const LFList<T *> &value)
		{
			*this = value;
		}

        LFList(LFList<T *> &&value)
        {
			*this = std::move(value);
        }

		~LFList()
		{
			ReleaseAll(isDestructDelete);
			LFCommon::LFMemoryManager::DeletePointerArray(data);
		}

		LFList<T *> &operator=(const LFList<T *> &value)
		{
			if (this != &value)
			{
				ReleaseAll(isDestructDelete);
				LFCommon::LFMemoryManager::DeletePointerArray(data);

				dataSize = value.dataSize;
				length = value.length;
				currentIndex = value.currentIndex;
				isDestructDelete = value.isDestructDelete;

				data = LFCommon::LFMemoryManager::NewPointerArray<LFListNode<T *>>(INFO, dataSize);
				for (int i = 0; i < length; i++)
					data[i] = value.data[i];
			}

			return *this;
		}

		LFList<T *> &operator=(LFList<T *> &&value)
		{
			if (this != &value)
			{
				ReleaseAll(isDestructDelete);
				LFCommon::LFMemoryManager::DeletePointerArray(data);

				dataSize = value.dataSize;
				length = value.length;
				currentIndex = value.currentIndex;
				isDestructDelete = value.isDestructDelete;
				data = value.data;

				value.dataSize = MinDataSize;
				value.length = 0;
				value.currentIndex = 0;
				value.isDestructDelete = false;
				value.data = nullptr;
			}

			return *this;
		}

		int GetLength() const
		{
			return length;
		}

		void First()
		{
			currentIndex = 0;
			current = data[0];
		}

		bool IsDone()
		{
			return (current != nullptr);
		}

		void Next()
		{
			currentIndex++;

			if (currentIndex < length)
				current = data[currentIndex];
			else
				current = nullptr;
		}

		T *GetCurrent()
		{
			if (current != nullptr)
				return current->item;

			return nullptr;
		}

		/*T operator [] (int index) const
		{
			return data[index]->item;
		}*/

		T *operator [] (int index)
		{
			return data[index]->item;
		}

		void Add(T *item)
		{
			if (length == dataSize)
			{
				dataSize *= 2;
				LFListNode<T *> **tempData = LFCommon::LFMemoryManager::NewPointerArray<LFListNode<T *>>(INFO, dataSize);
				for (int i = 0; i < length; i++)
					tempData[i] = data[i];

				LFCommon::LFMemoryManager::DeletePointerArray(data);
				data = tempData;
			}

			auto temp = LFCommon::LFMemoryManager::New<LFListNode<T *>>(INFO);
			temp->item = item;

			data[length] = temp;
			length++;
		}

		/** @brief Remove at item from list, but not delete */
		void RemoveAt(int index)
		{
			ReleaseAt(index, false);
		}

		/** @brief Remove at item from list, and delete */
		void DeleteAt(int index)
		{
			ReleaseAt(index, true);
		}

		/** @brief Remove current item from list, but not delete (when it is iterating) */
		void RemoveCurrent()
		{
			ReleaseAt(currentIndex, false);
		}

		/** @brief Remove current item from list, and delete (when it is iterating) */
		void DeleteCurrent()
		{
			ReleaseAt(currentIndex, true);
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
