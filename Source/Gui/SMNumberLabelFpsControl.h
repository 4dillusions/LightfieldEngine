#pragma once

#include "SMNumberLabelControl.h"
#include "..\\Core\\SMTimer.h"

using namespace SMEngine::Core;

namespace SMEngine { namespace Gui
{
	/*
	NumberLabelControl: Kizárólag számokat jelenít meg. Meghatározható adott digit szám, melynél az üres mezõket nullával tölti ki.
	Egyelõre adott digits mérettel dolgozik.

	Használat:
	SMNumberLabelFpsControl *numLabelFps = new SMNumberLabelFpsControl("numLabelFps1", 0, 3, SMVector2D(390, 0), 30);
	guiLayer->Add(numLabelFps);

	A kattintási esemény kezelés au, mint az ImageControl-nál, bár nem valószínû, hogy ez itt kell.
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
