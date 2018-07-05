/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameComponentList.h"
#include "LFGameComponent.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
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
		return data.GetCurrent();
	}

	int LFGameComponentList::Length() const
	{
		return data.GetLength();
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
			if (data.GetCurrent() == item)
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
			if (data.GetCurrent()->GetIsAlive())
				data.GetCurrent()->Update(deltaTime);
			else
				DeleteCurrent();
		}
	}

	void LFGameComponentList::DeleteAll()
	{
		for (data.First(); data.IsDone(); data.Next())
			DeleteCurrent();
	}
}}}}