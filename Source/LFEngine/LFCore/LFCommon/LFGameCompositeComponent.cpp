/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFGameCompositeComponent.h"
#include "..\LFIO\LFLogger.h"
#include "..\LFPatterns\LFIoc.h"

using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon 
{
	LFGameCompositeComponent::LFGameCompositeComponent(const LFString &name, bool isChildrenDestructDelete) : LFGameComponent(name), componentList(isChildrenDestructDelete)
	{ }

	LFGameCompositeComponent::~LFGameCompositeComponent()
	{ }

	LFGameComponent *LFGameCompositeComponent::Find(const LFString &name)
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (componentList.Current()->GetName() == name)
				return componentList.Current();

		return nullptr;
	}

	LFGameComponent *LFGameCompositeComponent::Find(const LFGameComponent *gameComponent)
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (componentList.Current() == gameComponent)
				return componentList.Current();

		return nullptr;
	}

	bool LFGameCompositeComponent::IsLastVisible(const LFString &name)
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

	int LFGameCompositeComponent::GetComponentsLength() const
	{
		return componentList.Length();
	}

	void LFGameCompositeComponent::WriteOutputComponentNames()
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			LFIoc<LFLogger>::Get().WriteOutput(componentList.Current()->GetName());
	}

	void LFGameCompositeComponent::Add(LFGameComponent *gameComponent)
	{
		if (Find(gameComponent) == nullptr)
			componentList.Add(gameComponent);
		else
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Warning, LFString("This component is already exist: ") + gameComponent->GetName());
	}

	void LFGameCompositeComponent::Remove(LFGameComponent *gameComponent)
	{
		componentList.Delete(gameComponent);
	}

	void LFGameCompositeComponent::Update(double deltaTime)
	{
		componentList.Update(deltaTime);
	}

	void LFGameCompositeComponent::SetIsAlive(bool isAlive)
	{
		this->isAlive = isAlive;

		for (componentList.First(); componentList.IsDone(); componentList.Next())
			componentList.Current()->SetIsAlive(isAlive);
	}

	void LFGameCompositeComponent::SetIsVisible(bool isVisible)
	{
		this->isVisible = isVisible;

		for (componentList.First(); componentList.IsDone(); componentList.Next())
			componentList.Current()->SetIsVisible(isVisible);
	}
}}}}