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
	Fõ control osztály:
	Lekezeli központilag a kattintási esemény, továbbadja a gyerek típusoknak. És egyebek.
	*/
	class SMControl : public SMGameCompositComponent, public SMITouchPressedEventHandler
	{
	protected:
		SMObserverEventArgs<SMControl *> controlArgs;

		SMRectangle rectangle;
		bool isUpdatable; //a GetControls akkor adja a paraméterben kapott lisához a control-t, ha isUpdatable == true

		SMList<SMControl *> controls;

	public:
		int tag; //bármire használható jelölés

		SMControl(const SMString &name, const SMRectangle &rectangle = SMRectangle());
		SMControl(const SMControl &value);
		virtual ~SMControl();

		SMEventArgs<SMIClickedEventHandler<SMControl *>, SMObserverEventArgs<SMControl *> > ClickedEvent;

		override void TouchPressed(const SMTouchEventArgs &args);
		void GetSprites(SMList<SMSprite *> &spriteList); //a compocitComponent õsosztály listájában tárolt sprite-okat adja vissza rekurzívan
		void GetControls(SMList<SMControl *> &controlList); //a controls listában tárolt controlokat adja vissza rekurzívan
		SMRectangle &Rectangle() { return rectangle; }
		bool IsVisibleControl() { return isVisible; };
	};
};};
