/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\Common\LFMemoryManager.h"

namespace LFCore { namespace Collections
{
	/*
	Linked list data structure with pointers.
	It can delete items while iterate, except RemoveAll/DeleteAll functions

	search: O(n)
	insert: O(1)
	delete: O(1)
	*/
	template<typename T> class LFList
	{
	private:
		struct Node
		{
			T item;
			Node *prev, *next;
			bool isAlive, isDelete;

			Node() : item(nullptr), prev(nullptr), next(nullptr), isAlive(true), isDelete(false)
			{ }

			void Release()
			{
				if (prev != nullptr)
					prev->next = next;

				if (next != nullptr)
					next->prev = prev;

				if (isDelete && item != nullptr)
					LFCore::Common::LFDelete(item);
			}
		};

		Node *first, *last, *current;
		bool isDestructDelete; //release all in destructor
		int length;

		void ReleaseCurrent(bool isDelete)
		{
			if (current != nullptr)
			{
				current->isAlive = false;
				current->isDelete = isDelete;
			}
		}

		void ReleaseAll(bool isDelete)
		{
			for (First(); IsDone(); Next())
				ReleaseCurrent(isDelete);
		}

	public:
		explicit LFList(bool isDestructDelete = true) : first(nullptr), last(nullptr), current(nullptr), isDestructDelete(isDestructDelete), length(0)
		{ }

		~LFList()
		{
			ReleaseAll(isDestructDelete);
		}

		int Length()
		{
			return length;
		}

		T GetFirst()
		{
			First();

			return Current();
		}

		void First()
		{
			current = first;
		}
    
		void Next()
		{
			if (current != nullptr)
			{
				Node *temp = current;
				current = current->next;

				if (temp->isAlive == false)
				{
					temp->Release();

					if (temp->prev == nullptr)
						first = temp->next;

					if (temp->next == nullptr)
						last = temp->prev;

					delete temp;
				}
			}
		}
    
		T Current()
		{
			if (current != nullptr)
				return current->item;

			return T();
		}
    
		bool IsDone()
		{
			return (current != nullptr);
		}

		void Add(T item)
		{
			if (item == nullptr)
				return;

			length++;

			Node *node = new Node;
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

		//Remove current item from list, but not delete (when it is iterating)
		void RemoveCurrent()
		{
			length--;

			ReleaseCurrent(false);
		}

		//Remove current item from list, and delete (when it is iterating)
		void DeleteCurrent()
		{
			length--;

			ReleaseCurrent(true);
		}

		//Remove all items from list, but not delete
		void RemoveAll()
		{
			length = 0;

			ReleaseAll(false);
		}

		//Remove all items from list, and delete
		void DeleteAll()
		{
			length = 0;

			ReleaseAll(true);
		}
	};
}}
