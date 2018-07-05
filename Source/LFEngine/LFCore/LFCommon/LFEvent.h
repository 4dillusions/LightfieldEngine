/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCollections\LFList.h"
#include <functional>

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	template <typename TArgs> class LFEvent final
	{
		LFEvent(const LFEvent&) = delete;
		LFEvent(LFEvent &&) = delete;
		LFEvent &operator=(const LFEvent &) = delete;
		LFEvent &operator=(LFEvent &&) = delete;

		LFCollections::LFList<std::function<void (const TArgs &args)>> functionList;

	public:
		LFEvent()
		{ }

        void operator += (std::function<void (const TArgs &args)> function)
		{
			functionList.Add(function);
		}

        void operator -= (std::function<void (const TArgs &args)> function)
		{
			for (functionList.First(); functionList.IsDone(); functionList.Next())
                if (functionList.GetCurrent().template target<void (const TArgs &args)>() == function.template target<void (const TArgs &args)>())
					functionList.RemoveCurrent();
		}

		void operator () (const TArgs &args)
		{
			for (functionList.First(); functionList.IsDone(); functionList.Next())
				(functionList.GetCurrent())(args);
		}
	};
}}}}
