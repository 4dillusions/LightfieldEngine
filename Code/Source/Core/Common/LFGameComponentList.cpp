/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameComponentList.h"
#include "LFMemoryManager.h"
#include "LFGameComponent.h"

namespace LFCore { namespace Common
{
	LFGameComponentList::LFGameComponentList(bool isDestructDelete) : data(isDestructDelete)
	{ }

	void LFGameComponentList::DeleteCurrent()
	{
		data.DeleteCurrent();
	}

	void LFGameComponentList::First()
	{
		data.First();
	}

	bool LFGameComponentList::IsDone()
	{
		return data.IsDone();
	}

	void LFGameComponentList::Next()
	{
		data.Next();
	}

	LFGameComponent *LFGameComponentList::Current()
	{
		return data.Current();
	}

	int LFGameComponentList::Length()
	{
		return data.Length();
	}

	LFGameComponent *LFGameComponentList::GetFirst()
	{
		return data.GetFirst();
	}

	void LFGameComponentList::Add(LFGameComponent *item)
	{
		data.Add(item);
	}

	void LFGameComponentList::Delete(LFGameComponent *item)
	{
		for (data.First(); data.IsDone(); data.Next())
		{
			if (data.Current() == item)
			{
				data.DeleteCurrent();
				return;
			}
		}
	}

	void LFGameComponentList::Update(double deltaTime)
	{
		for (data.First(); data.IsDone(); data.Next())
		{
			if (data.Current()->GetIsAlive())
				data.Current()->Update(deltaTime);
			else
				DeleteCurrent();
		}
	}

	void LFGameComponentList::DeleteAll()
	{
		for (data.First(); data.IsDone(); data.Next())
			DeleteCurrent();
	}
}}
