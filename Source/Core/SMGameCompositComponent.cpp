#include "SMGameCompositComponent.h"

namespace SMEngine { namespace Core
{
	SMGameCompositComponent::SMGameCompositComponent(const SMString &name) : SMGameComponent(name), isAliveChanged(false), isVisibleChanged(false)
	{ }

	SMGameCompositComponent::~SMGameCompositComponent()
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			componentList.Current()->IsAlive(false);
	}

	SMGameComponent *SMGameCompositComponent::Find(const SMString &name)
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (componentList.Current()->Name() == name)
				return componentList.Current();

		return nullptr;
	}

	void SMGameCompositComponent::Add(SMGameComponent *gameComponent)
	{
		componentList.Add(gameComponent);
	}

	void SMGameCompositComponent::Update(double deltaTime)
	{
		//ez azért kell, hogyha nem a composit component frissíti a listáját, csak tárol
		//ilyenkor muszáj ezeket a beállításokat így külön is érvényesíteni, hogy a másik lista le tudja kezelni frissítésnél
		if (isAliveChanged || isVisibleChanged)
		{
			isAliveChanged = false;
			isVisibleChanged = false;

			for (componentList.First(); componentList.IsDone(); componentList.Next())
			{
				componentList.Current()->IsAlive(isAlive);
				componentList.Current()->IsVisible(isVisible);
			}
		}

		componentList.Update(deltaTime);
	}

	void SMGameCompositComponent::IsAlive(bool isAlive)
	{
		this->isAlive = isAlive;
		isAliveChanged = true;
	}

	void SMGameCompositComponent::IsVisible(bool isVisible)
	{
		SMGameComponent::IsVisible(isVisible);
		this->isVisible = isVisible;

		isVisibleChanged = true;

		for (componentList.First(); componentList.IsDone(); componentList.Next())
			componentList.Current()->IsVisible(isVisible);
	}

	void SMGameCompositComponent::WriteReport()
	{
		componentList.WriteReport();
	}
};};
