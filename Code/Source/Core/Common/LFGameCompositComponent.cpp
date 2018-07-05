/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameCompositComponent.h"
#include "..\IO\LFLogger.h"

using namespace LFCore::IO;

namespace LFCore { namespace Common
{
	LFGameCompositComponent::LFGameCompositComponent(const LFString &name, bool isChildrenDestructDelete) : LFGameComponent(name), componentList(isChildrenDestructDelete)
	{ }

	LFGameCompositComponent::~LFGameCompositComponent()
	{ }

	LFGameComponent *LFGameCompositComponent::Find(const LFString &name)
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (componentList.Current()->GetName() == name)
				return componentList.Current();

		return nullptr;
	}

	bool LFGameCompositComponent::IsLastVisible(const LFString &name)
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (componentList.Current()->GetName() == name && componentList.Current()->GetIsVisible())
			{
				while (componentList.Current() != nullptr)
				{
					componentList.Next();

					if (componentList.Current() == nullptr)
						return true;

					if (componentList.Current()->GetIsVisible())
						return false;
				}
			}

		return false;
	}

	int LFGameCompositComponent::GetComponetsLength()
	{
		return componentList.Length();
	}

	void LFGameCompositComponent::WriteOutputComponentNames()
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			LFLogger::Instance().WriteOutput(componentList.Current()->GetName());
	}

	void LFGameCompositComponent::Add(LFGameComponent *gameComponent)
	{
		if (Find(gameComponent->GetName()) == nullptr)
			componentList.Add(gameComponent);
	}

	void LFGameCompositComponent::Remove(LFGameComponent *gameComponent)
	{
		componentList.Delete(gameComponent);
	}

	void LFGameCompositComponent::Update(double deltaTime)
	{
		componentList.Update(deltaTime);
	}

	void LFGameCompositComponent::SetIsAlive(bool isAlive)
	{
		this->isAlive = isAlive;

		for (componentList.First(); componentList.IsDone(); componentList.Next())
			componentList.Current()->SetIsAlive(isAlive);
	}

	void LFGameCompositComponent::SetIsVisible(bool isVisible)
	{
		this->isVisible = isVisible;

		for (componentList.First(); componentList.IsDone(); componentList.Next())
			componentList.Current()->SetIsVisible(isVisible);
	}
}}
