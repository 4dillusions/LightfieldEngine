/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\Collections\LFList.h"

namespace LFCore { namespace Common
{
	class LFGameComponent;

	class LFCORE_LIBRARY LFGameComponentList
	{
	private:
		LFCore::Collections::LFList<LFGameComponent *> data;

		void DeleteCurrent();

	public:
		LFGameComponentList(bool isChildrenDestructDelete = true);

		void First();
		bool IsDone();
		void Next();
		LFGameComponent *Current();
		int Length();
		LFGameComponent *GetFirst();

		void Add(LFGameComponent *item);
		void Delete(LFGameComponent *item); //After render only
		void Update(double deltaTime); //If List item alive is false, item will be deleted
		void DeleteAll(); //After render only
	};
}}
