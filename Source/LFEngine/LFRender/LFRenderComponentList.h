/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFRenderComponent.h"
//#include <type_traits>
#include "..\LFCore\LFCollections\LFDictionary.h"

namespace LF3Engine { namespace LFEngine { namespace LFRender
{
	/**
		@brief
		static singleton Dictionary for LFRenderComponent items
	*/
	class LFRenderComponentList final
	{
		LFRenderComponentList(const LFRenderComponentList&) = delete;
		LFRenderComponentList(LFRenderComponentList &&) = delete;
		LFRenderComponentList &operator=(const LFRenderComponentList &) = delete;
		LFRenderComponentList &operator=(LFRenderComponentList &&) = delete;

		LFCore::LFCollections::LFDictionary<LFCore::LFCommon::LFString, LFRenderComponent *> dataList;

	public:
		LFRenderComponentList()
		{
			//static_assert(std::is_base_of<LFRenderComponent, TRenderComponent>::value, "Type parameter of LFRenderComponentList must derive from LFRenderComponent class!"); //Compile-time check
		}

		~LFRenderComponentList() = default;

		void Add(LFCore::LFCommon::LFString name, LFRenderComponent *component)
		{
			dataList.Add(name, component);
		}

		LFRenderComponent *GetItem(LFCore::LFCommon::LFString name)
		{
			return dataList.GetItem(name);
		}

		void ReleaseAt(LFCore::LFCommon::LFString name)
		{
			if (LFRenderComponent *component = dataList.GetItem(name))
			{
				component->Release();
				dataList.DeleteAt(name);
			}
		}

		void ReleaseAll()
		{
			for (dataList.First(); dataList.IsDone(); dataList.Next())
				dataList.GetCurrentItem()->Release();

			dataList.DeleteAll();
		}
	};
}}}
