#pragma once

#include "..\LFCommon\LFMemoryManager.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCollections
{
	template<typename T> struct LFLinkedListNode final
	{
		LFLinkedListNode<T>() = default;
		LFLinkedListNode<T>(const LFLinkedListNode<T>&) = delete;
		LFLinkedListNode(LFLinkedListNode<T> &&) = delete;
		LFLinkedListNode<T> &operator=(const LFLinkedListNode<T> &) = delete;
		LFLinkedListNode<T> &operator=(LFLinkedListNode<T> &&) = delete;

		T item;
		LFLinkedListNode *prev = nullptr, *next = nullptr;
		bool isAlive = true;
	
		void Release()
		{
			if (prev != nullptr)
				prev->next = next;

			if (next != nullptr)
				next->prev = prev;
		}
	};

	template<typename T> struct LFLinkedListNode<T *> final
	{
		LFLinkedListNode<T *>() = default;
		LFLinkedListNode<T *>(const LFLinkedListNode<T *> &) = delete;
		LFLinkedListNode<T *>(LFLinkedListNode<T *> &&) = delete;
		LFLinkedListNode<T *> &operator=(const LFLinkedListNode<T *> &) = delete;
		LFLinkedListNode<T *> &operator=(LFLinkedListNode<T *> &&) = delete;

		T *item = nullptr;
		LFLinkedListNode *prev = nullptr, *next = nullptr;
		bool isAlive = true, isDelete = false;

		void Release()
		{
			if (prev != nullptr)
				prev->next = next;

			if (next != nullptr)
				next->prev = prev;
		
			if (isDelete && item != nullptr)
				 LFCommon::LFMemoryManager::Delete(item);
		}
	};
}}}}