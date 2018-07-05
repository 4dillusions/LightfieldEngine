#pragma once

#include "SMControl.h"

namespace SMEngine { namespace Gui
{
	/*
	CheckButtonControl:
	Két állapotú check box tulajdonképpen.

	Használat:
	class Game : public SMIClickedEventHandler<SMCheckButtonControl *>
	{
		SMCheckButtonControl *checkButton;
		...
		override void Clicked(const SMObserverEventArgs<SMCheckButtonControl *> &args);
	};
		...
		void Game::CreateSceneGraph()
		{
			...
			checkButton = new SMCheckButtonControl("checkButton1", SMRectangle(0, 0, 100, 100), "True.jpg", "False.jpg");
			checkButton->ClickedEvent += this;
			guiLayer->Add(checkButton);
		}

		Game::~Game()
		{
			checkButton->ClickedEvent -= this;
		}

		...
		void Game::Clicked(const SMObserverEventArgs<SMCheckButtonControl *> &args)
		{
			SMString text;
			//text.Append(args.subject->Name().ToChar());
			text.Append(" ");

			if (args.subject)->IsChecked())
				text.Append("checked");
			else
				text.Append("unchecked");

			SMLogger::Instance().WriteOutput(text);
		}
	*/
	class SMCheckButtonControl : public SMControl
	{
	private:
		bool isChecked;
		SMSprite *trueSprite, *falseSprite;

		SMObserverEventArgs<SMCheckButtonControl *> controlArgs;

	public:
		SMCheckButtonControl(const SMString &name, const SMRectangle &rectangle, const SMString &trueTextureName, const SMString &falseTextureName, bool trueTextureIsAlpha = false, bool falseTextureIsAlpha = false);
		virtual ~SMCheckButtonControl();

		override void TouchPressed(const SMTouchEventArgs &args);
		SMEventArgs<SMIClickedEventHandler<SMCheckButtonControl *>, SMObserverEventArgs<SMCheckButtonControl *> > ClickedEvent;

		bool isEnabled;

		bool IsChecked();
		void IsChecked(bool isChecked, bool isCheckEnable = false); //isCheckEnable: ha a kontrol nem látható, de mégis be kell állítani az értékét
	};
};};
