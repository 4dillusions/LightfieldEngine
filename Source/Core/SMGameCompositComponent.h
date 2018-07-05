#pragma once

#include "SMGameComponentList.h"

namespace SMEngine { namespace Core
{
	/*
	Compositor pattern.
	GameComponent-ek listáját tartalmazza.

	Példa:
	class Sprite : public SMGameComponent
    {
    public:
        Sprite(const SMString &name) : SMGameComponent(name)
        { }

        override void Update(double deltaTime)
        {
            componentUpdate++;
        }
    };

    class Layer : public SMGameCompositComponent
    {
    public:
       Layer(const SMString &name) : SMGameCompositComponent(name)
       { }

       override ~Layer()
       { }
    };

    class Screen ua, mint a layer
    ...
	Screen *mainScreen = new Screen(); //SMGameCompositComponent

	Layer *gameLayer = new Layer(); //SMGameCompositComponent
	mainScreen->Add(gameLayer);

	Sprite *sprite1 = new Sprite(text); //SMGameComponent
	Sprite *sprite2 = new Sprite(text2); //SMGameComponent
	gameLayer->Add(sprite1);
	gameLayer->Add(sprite2);

	mainScreen->Update(1.23);
	*/
	class SMGameCompositComponent : public SMGameComponent
	{
	private:
		bool isAliveChanged, isVisibleChanged;

	protected:
		SMGameComponentList componentList;

	public:
		SMGameCompositComponent(const SMString &name);
		override ~SMGameCompositComponent();

		SMGameComponent *Find(const SMString &name); //nullptr, ha nincs ilyen a listában

		virtual void Add(SMGameComponent *gameComponent);
		override void Update(double deltaTime);
		override void IsAlive(bool isAlive);
		override void IsVisible(bool isVisible);
		override void WriteReport();
	};
};};
