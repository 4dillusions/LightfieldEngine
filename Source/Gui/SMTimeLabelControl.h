#pragma once

#include "SMLabelControl.h"
#include "SMTimerControl.h"
#include "..\\Core\\SMWatch.h"

namespace SMEngine { namespace Gui
{
	/*
	TimeLabelControl: Percet másodpercet jelenít meg és számlálni tud másodperces léptetéssel.
	Értesítést küld, ha a megadott alsó, vagy felõ határt elérte az idõ.

	Használat:
	class Game : public SMITickMinEventHandler<SMTimeLabelControl *>
	{
		SMTimeLabelControl *lblTimer;
		...
		override void Tick(const SMObserverEventArgs<SMTimeLabelControl *> &args);
	};
		...
		void Game::CreateSceneGraph()
		{
			...
			lblTimer = new SMTimeLabelControl("lblTimer", SMWatch(SMTime(0, 10), SMTime(), SMTime(0, 20)), false, SMVector2D(46, 750), 25);
			lblTimer->TickMinEvent += this;
			levelGuiLayer->Add(lblTimer);
		}

		Game::~Game()
		{
			lblTimer->TickMinEvent -= this;
		}

		...
		void Level::Tick(const SMObserverEventArgs<SMTimeLabelControl *> &args)
		{
			GameOver();
		}

	...
	//lblTimer->Value(593); //000593

	A kattintási esemény kezelés au, mint az ImageControl-nál, bár nem valószínû, hogy ez itt kell.
	*/
	class SMTimeLabelControl : public SMLabelControl, public SMITickEventHandler<SMTimerControl *>, public SMIWatchAlarmEventHandler
	{
	private:
		SMWatch watch;
		SMTimerControl *timerControl;
		SMString minuteText, secondText;
		bool isForward;

		SMObserverEventArgs<SMTimeLabelControl *> timerLabelArgs;

		void SetTimerTexts();

	public:
		SMTimeLabelControl(const SMString &name, const SMWatch &watch, bool isForward, const SMVector2D &position, int height);
		virtual ~SMTimeLabelControl();

		override void Tick(const SMObserverEventArgs<SMTimerControl *> &args);
		override void Alarm();

		SMEventArgs<SMITickMinEventHandler<SMTimeLabelControl *>, SMObserverEventArgs<SMTimeLabelControl *> > TickMinEvent;
		SMEventArgs<SMITickMaxEventHandler<SMTimeLabelControl *>, SMObserverEventArgs<SMTimeLabelControl *> > TickMaxEvent;

		SMTime &Time() { return watch.time; }
		void Time(const SMTime &time);
		void Start();
		void Stop();
	};
};};
