#pragma once

#include "SMNumberLabelControl.h"
#include "..\\Core\\SMTimer.h"

using namespace SMEngine::Core;

namespace SMEngine { namespace Gui
{
	/*
	NumberLabelControl: Kiz�r�lag sz�mokat jelen�t meg. Meghat�rozhat� adott digit sz�m, melyn�l az �res mez�ket null�val t�lti ki.
	Egyel�re adott digits m�rettel dolgozik.

	Haszn�lat:
	SMNumberLabelFpsControl *numLabelFps = new SMNumberLabelFpsControl("numLabelFps1", 0, 3, SMVector2D(390, 0), 30);
	guiLayer->Add(numLabelFps);

	A kattint�si esem�ny kezel�s au, mint az ImageControl-n�l, b�r nem val�sz�n�, hogy ez itt kell.
	*/
	class SMNumberLabelFpsControl : public SMNumberLabelControl
	{
	private:
		SMTimer timer;
		double time;
		int fpsCounter;

	public:
		SMNumberLabelFpsControl(const SMString &name, int value, int digits, const SMVector2D &position, int height);
		virtual ~SMNumberLabelFpsControl();

		override void Update(double deltaTime);
	};
};};
