/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLinkedListNode.h"
#include  "..\LFCore.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCollections
{
	/**
		@brief
		Linked list data structure with objects. <br>
		It can delete items while iterate, except RemoveAll/DeleteAll functions <br><br>

		Mainly use for iterating <br><br>

		best/worst<br>
		search: O(n) O(n) <br>
		insert: O(1) O(1) <br>
		delete: O(1) O(1) <br>
		index: no <br>
		static remove/delete: no <br>
		continuously remove/delete: yes <br>
	*/
	template<typename T> class LFLinkedList final
	{
	public:
		LFLinkedList<T>() = default;

	private:
		LFLinkedList<T>(const LFLinkedList<T> &) = delete;
		LFLinkedList(LFLinkedList<T> &&) = delete;
		LFLinkedList<T> &operator=(const LFLinkedList<T> &) = delete;
		LFLinkedList<T> &operator=(LFLinkedList<T> &&) = delete;

		LFLinkedListNode<T> *first = nullptr, *last = nullptr, *current = nullptr;
		int length = 0;

		void ReleaseCurrent()
		{
			if (current != nullptr)
			{
				length--;
				current->isAlive = false;
			}
		}

		void ReleaseAll()
		{
			for (First(); IsDone(); Next())
				ReleaseCurrent();
		}

	public:
		~LFLinkedList()
		{
			ReleaseAll();
		}

		int GetLength() const
		{
			return length;
		}

		T &GetFirst()
		{
			if (first != nullptr)
				return first->item;

			static T item;
			return item;
		}

		T &GetLast()
		{
			if (last != nullptr)
				return last->item;

			static T item;
			return item;
		}

		void First()
		{
			current = first;
		}
    
		void Next()
		{
			if (current != nullptr)
			{
				LFLinkedListNode<T> *temp = current;
				current = current->next;

				if (temp->isAlive == false)
				{
					temp->Release();

					if (temp->prev == nullptr)
						first = temp->next;

					if (temp->next == nullptr)
						last = temp->prev;

					LFCommon::LFMemoryManager::Delete(temp);
				}
			}
		}
    
		T &GetCurrent()
		{
			if (current != nullptr)
				return current->item;

			static T currentItem;
			return currentItem;
		}
    
		bool IsDone()
		{
			return (current != nullptr);
		}

		void Add(const T &item)
		{
			length++;

			LFLinkedListNode<T> *node = LFCommon::LFMemoryManager::New<LFLinkedListNode<T>>(INFO);
			node->item = item;

			if (first == nullptr)
			{
				first = node;
			}
			else
			{
				if (last == nullptr)
				{
					last = node;
					first->next = node;
					node->prev = first;
				}
				else
				{
					last->next = node;
					node->prev = last;
					last = node;
				}
			}
		}

		void RemoveCurrent()
		{
			ReleaseCurrent();
		}

		void RemoveAll()
		{
			length = 0;

			ReleaseAll();
		}
	};

	/**
	@brief
	Linked list data structure with pointers. <br>
	It can delete items while iterate, except RemoveAll/DeleteAll functions <br><br>

	Mainly use for iterating <br><br>

	best/worst<br>
	search: O(n) O(n) <br>
	insert: O(1) O(1) <br>
	delete: O(1) O(1) <br>
	index: no <br>
	static remove/delete: no <br>
	continuously remove/delete: yes <br>
	*/
	template<typename T> class LFLinkedList<T *> final
	{
		LFLinkedList<T *>(const LFLinkedList<T *>&) = delete;
		LFLinkedList(LFLinkedList<T *> &&) = delete;
		LFLinkedList<T *> &operator=(const LFLinkedList<T *> &) = delete;
		LFLinkedList<T *> &operator=(LFLinkedList<T *> &&) = delete;

		LFLinkedListNode<T *> *first = nullptr, *last = nullptr, *current = nullptr;
		bool isDestructDelete; //release all in destructor
		int length = 0;

		void ReleaseCurrent(bool isDelete)
		{
			if (current != nullptr)
			{
				length--;

				current->isAlive = false;
				current->isDelete = isDelete;

				if (current->next == nullptr)
					Next();
			}
		}

		void ReleaseAll(bool isDelete)
		{
			for (First(); IsDone(); Next())
				ReleaseCurrent(isDelete);

			length = 0;
		}

	public:
		explicit LFLinkedList(bool isDestructDelete = true) : isDestructDelete(isDestructDelete)
		{ }

		~LFLinkedList()
		{
			ReleaseAll(isDestructDelete);
		}

		int GetLength() const
		{
			return length;
		}

		T *GetFirst()
		{
			if (first != nullptr)
				return first->item;

			return nullptr;
		}

		T *GetLast()
		{
			if (last != nullptr)
				return last->item;

			return nullptr;
		}

		void First()
		{
			current = first;
		}

		void Next()
		{
			if (current != nullptr)
			{
				LFLinkedListNode<T *> *temp = current;
				current = current->next;

				if (temp->isAlive == false)
				{
					temp->Release();

					if (temp->prev == nullptr)
						first = temp->next;

					if (temp->next == nullptr)
						last = temp->prev;

					LFCommon::LFMemoryManager::Delete(temp);
				}
			}
		}

		T *GetCurrent()
		{
			if (current != nullptr)
				return current->item;

			return nullptr;
		}

		bool IsDone()
		{
			return (current != nullptr);
		}

		void Add(T *item)
		{
			if (item == nullptr)
				return;

			length++;

			LFLinkedListNode<T *> *node = LFCommon::LFMemoryManager::New<LFLinkedListNode<T *>>(INFO);
			node->item = item;

			if (first == nullptr)
			{
				first = node;
			}
			else
			{
				if (last == nullptr)
				{
					last = node;
					first->next = node;
					node->prev = first;
				}
				else
				{
					last->next = node;
					node->prev = last;
					last = node;
				}
			}
		}

		/** @brief Remove current item from list, but not delete (when it is iterating) */
		void RemoveCurrent()
		{
			ReleaseCurrent(false);
		}

		/** @brief Remove current item from list, and delete (when it is iterating) */
		void DeleteCurrent()
		{
			ReleaseCurrent(true);
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
