/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFList.h"

namespace LFCore { namespace Collections
{
	/*
	Linked list data structure
	Works with object key and pointer data.
	Keys are compared by using < > = operators

	current speed
	search: O(n)
	insert: O(1)
	delete: O(1)

	needed speed
	search: O(log n)
	insert: O(log n)
	delete: O(log n)
	*/
	template<typename TKey, typename TItem> class LFDictionary
	{
	private:
		struct LFNode
		{
			TKey key;
			TItem item;

			LFNode(const TKey &key, TItem item) : key(key), item(item)
			{ }

			void Release(bool isDelete)
			{
				if (isDelete && item != nullptr)
					LFCore::Common::LFDelete(item);
			}
		};

		bool isDestructDelete; //release all in destructor
		LFList<LFNode *> nodeList;
		
		bool Release(const TKey &key, bool isDelete)
		{
			bool result = false;

			for (nodeList.First(); nodeList.IsDone(); nodeList.Next())
			{
				if (nodeList.Current()->key == key)
				{
					nodeList.Current()->Release(isDelete);

					if (isDelete)
						nodeList.DeleteCurrent();
					else
						nodeList.RemoveCurrent();
					
					result = true;
				}
			}

			return result;
		}

		void ReleaseAll(bool isDelete)
		{
			for (nodeList.First(); nodeList.IsDone(); nodeList.Next())
			{
				nodeList.Current()->Release(isDelete);

				if (isDelete)
					nodeList.DeleteCurrent();
				else
					nodeList.RemoveCurrent();
			}
		}

	public:
		explicit LFDictionary(bool isDestructDelete = true) : isDestructDelete(isDestructDelete), nodeList(isDestructDelete)
		{ }

		~LFDictionary()
		{
			ReleaseAll(isDestructDelete);
		}

		int Length()
		{
			return nodeList.Length();
		}

		void First()
		{
			nodeList.First();
		}
    
		void Next()
		{
			nodeList.Next();
		}
    
		TItem Current()
		{
			return nodeList.Current()->item;		
		}
    
		bool IsDone()
		{
			return nodeList.IsDone();
		}

		TItem FindItem(const TKey &key)
		{
			for (nodeList.First(); nodeList.IsDone(); nodeList.Next())
				if (nodeList.Current()->key == key)
					return nodeList.Current()->item;

			return nullptr;
		}

		bool Add(const TKey &key, TItem item)
		{
			if (item == nullptr)
				return false;

			if (FindItem(key) != nullptr)
				return false;

			nodeList.Add(new LFNode(key, item));

			return true;
		}

		//Remove current item from list, but not delete
		void Remove(const TKey &key)
		{
			Release(key, false);
		}

		//Remove current item from list and delete
		void Delete(const TKey &key)
		{
			Release(key, true);
		}

		//Remove all items from list, but not, delete
		void RemoveAll()
		{
			ReleaseAll(false);
		}

		//Remove all items from list, and delete
		void DeleteAll()
		{
			ReleaseAll(true);
		}
	};
}}
