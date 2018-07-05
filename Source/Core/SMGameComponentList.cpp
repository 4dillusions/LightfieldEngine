#include "SMGameComponentList.h"

#include "../IO/SMLogger.h"
using namespace SMEngine::IO;

namespace SMEngine { namespace Core
{
	SMGameComponentList::SMGameComponentList()
	{ }

	SMGameComponentList::SMGameComponentList(int size)
	{
		data.reserve(size);
	}

	SMGameComponentList::~SMGameComponentList()
	{
		RemoveAll();
	}

	void SMGameComponentList::First()
	{
		gcIterator = data.begin();
	}

	bool SMGameComponentList::IsDone()
	{
		return (gcIterator != data.end());
	}

	void SMGameComponentList::Next()
	{
		++gcIterator;
	}

	SMGameComponent *SMGameComponentList::Current()
	{
		return *gcIterator;
	}

	void SMGameComponentList::Add(SMGameComponent *item)
	{
		data.push_back(item);
	}

	void SMGameComponentList::Remove(SMGameComponent *item)
	{
		for (iterator i = data.begin(); i != data.end(); ++i)
			if (*i == item)
			{
				delete *i;
				data.erase(i);

				return;
			}
	}

	void SMGameComponentList::Update(double deltaTime)
	{
		for (iterator i = data.begin(); i != data.end(); ++i)
		{
			if (!(*i)->IsAlive()) //ha ez az elem halott, akkor törlés és ugrás a következõ elemre, majd az élõ elem kirajzolása
			{
				delete *i;

				if (i == --data.end()) //utolsó elem törölve, vége
				{
					data.erase(i);
					return;
				}

				i = data.erase(i);

				if (!(*i)->IsAlive())
					continue;
			}

			if ((*i)->IsVisible())
				(*i)->Update(deltaTime);
		}
	}

	void SMGameComponentList::WriteReport()
	{
		for (iterator i = data.begin(); i != data.end(); ++i)
			(*i)->WriteReport();
	}

	void SMGameComponentList::RemoveAll()
	{
		/*for (iterator i = data.begin(); i != data.end();)
		{
			SMString text;
			text.Append("Remove: ");
			text.Append((*i)->Name().ToBadaString());
			SMLogger::Instance().WriteOutput(text);

			delete *i;
			*i = nullptr;

			i = data.erase(i);
		}*/
	}
};};
