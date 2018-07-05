#pragma once

#include "SMControl.h"

namespace SMEngine { namespace Gui
{
	/*
	ImageControl:
	Kép, mely tud kattintási eseményt is kezelni.

	Használat:
	class Game : public SMIClickedEventHandler<SMControl *>
	{
		SMImageControl *image;
		...
		override void Clicked(const SMObserverEventArgs<SMControl *> &args);
	};
		...
		void Game::CreateSceneGraph()
		{
			...
			image = new SMImageControl("image1", SMRectangle(0, 0, 100, 100), "BadaLogo.jpg");
			image->ClickedEvent += this;
			guiLayer->Add(image);
		}

		Game::~Game()
		{
			image->ClickedEvent -= this;
		}

		...
		void Game::Clicked(const SMObserverEventArgs<SMControl *> &args)
		{
			SMLogger::Instance().WriteOutput(args.subject->Name());
		}
	*/
	class SMImageControl : public SMControl
	{
	private:
		SMSprite *imageSprite;

	public:
		SMImageControl(const SMString &name, const SMRectangle &rectangle, const SMString &imageName, bool imageIsAlpha = false);
		virtual ~SMImageControl();

		void Position(const SMVector2D &position);
		void PositionOffset(const SMVector2D &position);
	};
};};
