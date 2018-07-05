#pragma once

#include "SMImageControl.h"
#include "SMButtonControl.h"
#include "SMLabelControl.h"

namespace SMEngine { namespace Gui
{
	/*
	SMMessageWindow:
	A GUI layerre fölteszi a komponenseit és ott is kell hagyni.
	Igen/nem kattintás után az agész layer visible false lesz. Újabb kérdésnél csak annyi, hogy visible true.
	Ez most ilyen suszter megoldás, újra kell tervezni a gui-t majd.

	Használat:
	class Game : public SMIClickedEventHandler<SMMessageWindow *>
	{
		SMGuiLayer *guiLayer;
		SMMessageWindow *message;
		...
		override void Clicked(const SMObserverEventArgs<SMMessageWindow *> &args);
	};

		...
		void Game::CreateSceneGraph()
		{
			...
			message = new SMMessageWindow("message1", guiLayer, "ARE YOU SURE WANT TO QUIT");
			message->ClickedEvent += this;
		}

		Game::~Game()
		{
			message->ClickedEvent -= this;
		}

		...
		void Game::Clicked(const SMObserverEventArgs<SMMessageWindow *> &args)
		{
			if (args.subject->isOk)
				SMLogger::Instance().WriteOutput("Yes");
			else
				SMLogger::Instance().WriteOutput("No");
		}

		...
		guiLayer->IsVisible(true); //show message box
	*/
	class SMMessageWindow : public SMIClickedEventHandler<SMControl *>
	{
	private:
		SMString name;

		SMGuiLayer *guiLayer;
		SMImageControl *imgBackground;
		SMButtonControl *btnYes, *btnNo;
		SMLabelControl *lblMessage;

		SMObserverEventArgs<SMMessageWindow *> controlArgs;

	public:
		SMMessageWindow(const SMString &name, SMGuiLayer *guiLayer, const SMString &message);

		SMString &Name() { return name; }
		bool isOk, isVisible;

		bool IsVisible() { return isVisible; }

		void Show();
		void Hide();

		SMEventArgs<SMIClickedEventHandler<SMMessageWindow *>, SMObserverEventArgs<SMMessageWindow *> > ClickedEvent;
		override void Clicked(const SMObserverEventArgs<SMControl *> &args);
	};
};};
