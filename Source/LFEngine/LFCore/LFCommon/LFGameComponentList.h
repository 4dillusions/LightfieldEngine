/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFCollections\LFLinkedList.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	class LFGameComponent;

	class LFGameComponentList final
	{
		LFGameComponentList(const LFGameComponentList&) = delete;
		LFGameComponentList(LFGameComponentList &&) = delete;
		LFGameComponentList &operator=(const LFGameComponentList &) = delete;
		LFGameComponentList &operator=(LFGameComponentList &&) = delete;

		LFCollections::LFLinkedList<LFGameComponent *> data;

		void DeleteCurrent();

	public:
		explicit LFGameComponentList(bool isChildrenDestructDelete = true);

		void First();
		bool IsDone();
		void Next();
		LFGameComponent *Current();
		int Length() const;
		LFGameComponent *GetFirst();

		void Add(LFGameComponent *item);
		void Delete(LFGameComponent *item); //After render only
		void Update(double deltaTime); //If List item alive is false, item will be deleted
		void DeleteAll(); //After render only
	};
}}}}