#pragma once

#include "..\\Core\\SMGameCompositComponent.h"
#include "..\\Core\\SMEventArgs.h"
#include "..\\Core\\SMEventHandlers.h"
#include "..\\Core\\SMList.h"
#include "..\\Graphics\\SMSprite.h"
#include "..\\Math\\SMRectangle.h"
#include "..\\Input\\SMInput.h"

using namespace SMEngine::Core;
using namespace SMEngine::Graphics;
using namespace SMEngine::Math;
using namespace SMEngine::Input;

namespace SMEngine { namespace Gui
{
	/*
	F� control oszt�ly:
	Lekezeli k�zpontilag a kattint�si esem�ny, tov�bbadja a gyerek t�pusoknak. �s egyebek.
	*/
	class SMControl : public SMGameCompositComponent, public SMITouchPressedEventHandler
	{
	protected:
		SMObserverEventArgs<SMControl *> controlArgs;

		SMRectangle rectangle;
		bool isUpdatable; //a GetControls akkor adja a param�terben kapott lis�hoz a control-t, ha isUpdatable == true

		SMList<SMControl *> controls;

	public:
		int tag; //b�rmire haszn�lhat� jel�l�s

		SMControl(const SMString &name, const SMRectangle &rectangle = SMRectangle());
		SMControl(const SMControl &value);
		virtual ~SMControl();

		SMEventArgs<SMIClickedEventHandler<SMControl *>, SMObserverEventArgs<SMControl *> > ClickedEvent;

		override void TouchPressed(const SMTouchEventArgs &args);
		void GetSprites(SMList<SMSprite *> &spriteList); //a compocitComponent �soszt�ly list�j�ban t�rolt sprite-okat adja vissza rekurz�van
		void GetControls(SMList<SMControl *> &controlList); //a controls list�ban t�rolt controlokat adja vissza rekurz�van
		SMRectangle &Rectangle() { return rectangle; }
		bool IsVisibleControl() { return isVisible; };
	};
};};
