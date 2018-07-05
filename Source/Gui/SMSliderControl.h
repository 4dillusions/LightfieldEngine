#pragma once

#include "SMImageControl.h"
#include "..\\Engine\\SMGuiLayer.h"

using namespace SMEngine::Engine;

namespace SMEngine { namespace Gui
{
	/*
	bug: ha kettõ ilyet kirakok, akkor össze-vissza rajzol mindefélét.

	SMSliderControl:
	A GUI layerre fölteszi a komponenseit és ott is kell hagyni.
	Ez most ilyen suszter megoldás, újra kell tervezni a gui-t majd.

	Használat:
	class Game : public SMIClickedEventHandler<SMSliderControl *>
	{
		SMSliderControl *slider;
		override void Clicked(const SMObserverEventArgs<SMSliderControl *> &args);
	};

		...
		void Game::CreateSceneGraph()
		{
			...
			slider = new SMSliderControl("slider", guiLayer, SMVector2D(48, 128), 0, 10, 1);
			slider->ClickedEvent += this;
		}

		Game::~Game()
		{
			slider->ClickedEvent -= this;
		}

		...
		void Game::Clicked(const SMObserverEventArgs<SMSliderControl *> &args)
		{
			SMString text;
			text.Append(args.subject->Name());
			text.Append(": ");
			text.Append(args.subject->SlideValue());

			SMLogger::Instance().WriteOutput(text);
		}
	*/
	class SMSliderControl : public SMIClickedEventHandler<SMControl *>
	{
	private:
		SMImageControl *imgPlus, *imgMinus, *imgBar, *imgComma;
		SMString name;
		SMVector2D position;
		int slideValue, slideValueMin, slideValueMax, slideStep;
		float stepOffset;
		SMVector2D commaStartPos;

		SMObserverEventArgs<SMSliderControl *> controlArgs;

	public:
		SMSliderControl(const SMString &name, SMGuiLayer *guiLayer, const SMVector2D &position, int slideValueMin, int slideValueMax, int slideStep);

		void SlideValue(int value, bool isSlideEnable = false);
		int SlideValue() { return slideValue; }
		SMString &Name() { return name; }

		bool isEnabled;

		SMEventArgs<SMIClickedEventHandler<SMSliderControl *>, SMObserverEventArgs<SMSliderControl *> > ClickedEvent;
		override void Clicked(const SMObserverEventArgs<SMControl *> &args);
	};
};};
