#pragma once

#include "..\LFCommon\LFMemoryManager.h"                                 

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCollections
{
	template<typename TKey, typename TItem> struct LFDictionaryNode final
	{
		LFDictionaryNode<TKey, TItem>(const LFDictionaryNode<TKey, TItem> &) = delete;
		LFDictionaryNode(LFDictionaryNode<TKey, TItem> &&) = delete;
		LFDictionaryNode<TKey, TItem> &operator=(const LFDictionaryNode<TKey, TItem> &) = delete;
		LFDictionaryNode<TKey, TItem> &operator=(LFDictionaryNode<TKey, TItem> &&) = delete;

		TKey key;
		TItem item;

		LFDictionaryNode(const TKey &key, const TItem &item) : key(key), item(item)
		{ }
	};

	template<typename TKey, typename TItem> struct LFDictionaryNode<TKey, TItem *> final
	{
		LFDictionaryNode<TKey, TItem *>(const LFDictionaryNode<TKey, TItem *> &) = delete;
		LFDictionaryNode(LFDictionaryNode<TKey, TItem *> &&) = delete;
		LFDictionaryNode<TKey, TItem *> &operator=(const LFDictionaryNode<TKey, TItem *> &) = delete;
		LFDictionaryNode<TKey, TItem *> &operator=(LFDictionaryNode<TKey, TItem *> &&) = delete;

		TKey key;
		TItem *item = nullptr;

		LFDictionaryNode(const TKey &key, TItem *item) : key(key), item(item)
		{ }

		~LFDictionaryNode()
		{
			LFCommon::LFMemoryManager::Delete(item);
		}
	};
}}}}
