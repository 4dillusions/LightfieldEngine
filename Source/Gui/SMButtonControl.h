#pragma once

#include "SMLabelControl.h"

#include "..\\Engine\\SMGuiLayer.h"

using namespace SMEngine::Engine;

namespace SMEngine { namespace Gui
{
/*
	ButtonControl:
	Sima nyomógomb felirattal.

	Használat:
	class Game : public SMIClickedEventHandler<SMControl *>
	{
		SMButtonControl *button;
		...
		override void Clicked(const SMObserverEventArgs<SMControl *> &args);
	};
		...
		void Game::CreateSceneGraph()
		{
			...
			button = new SMButtonControl("button1", "BTN1", 30, SMRectangle(50, 50, 300, 60), "Button.jpg");
			button->ClickedEvent += this;
			guiLayer->Add(button);
		}

		Game::~Game()
		{
			checkButton->ClickedEvent -= this;
		}

		...
		void Game::Clicked(const SMObserverEventArgs<SMControl *> &args)
		{
			SMLogger::Instance().WriteOutput(args.subject->Name().ToChar());
		}
	*/
	class SMButtonControl : public SMControl
	{
	private:
		SMString text;
		SMSprite *buttonSprite;
		SMLabelControl *label;

	public:
		SMButtonControl(const SMString &name, const SMString &text, int fontHeight, const SMRectangle &rectangle, const SMString &buttonTextureName, bool buttonTextureIsAlpha = false);
		virtual ~SMButtonControl();
	};
};};
