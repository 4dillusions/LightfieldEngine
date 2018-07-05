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
		//ez az�rt kell, hogyha nem a composit component friss�ti a list�j�t, csak t�rol
		//ilyenkor musz�j ezeket a be�ll�t�sokat �gy k�l�n is �rv�nyes�teni, hogy a m�sik lista le tudja kezelni friss�t�sn�l
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
