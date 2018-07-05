#pragma once

#include "..\LFCommon\LFMemoryManager.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCollections
{
	template<typename T> struct LFListNode final
	{
		LFListNode<T>() = default;
		LFListNode<T>(const LFListNode<T> &) = delete;
		LFListNode(LFListNode<T> &&) = delete;
		LFListNode<T> &operator=(const LFListNode<T> &) = delete;
		LFListNode<T> &operator=(LFListNode<T> &&) = delete;

		T item;
	};

	template<typename T> struct LFListNode<T *> final
	{
		LFListNode<T *>() = default;
		LFListNode<T *>(const LFListNode<T *> &) = delete;
		LFListNode<T *>(LFListNode<T *> &&) = delete;
		LFListNode<T *> &operator=(const LFListNode<T *> &) = delete;
		LFListNode<T *> &operator=(LFListNode<T *> &&) = delete;

		T *item = nullptr;
		
		void Release()
		{
			LFCommon::LFMemoryManager::Delete(item);
		}
	};
}}}}