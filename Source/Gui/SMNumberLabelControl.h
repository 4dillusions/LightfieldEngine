#pragma once

#include "SMLabelControl.h"

namespace SMEngine { namespace Gui
{
	/*
	NumberLabelControl: Kizárólag számokat jelenít meg. Meghatározható adott digit szám, melynél az üres mezõket nullával tölti ki.
	Egyelõre adott digits mérettel dolgozik.

	Használat:
	SMNumberLabelControl *numLabel = new SMNumberLabelControl("numLabel1", 2561, 6, SMVector2D(), 30);
	guiLayer->Add(numLabel);
	...
	numLabel->Value(593); //000593

	A kattintási esemény kezelés au, mint az ImageControl-nál, bár nem valószínû, hogy ez itt kell.
	*/
	class SMNumberLabelControl : public SMLabelControl
	{
	private:
		SMString valueText;
		int value, digits;

	public:
		SMNumberLabelControl(const SMString &name, int value, int digits, const SMVector2D &position, int height);
		virtual ~SMNumberLabelControl();

		int Value() { return value; }
		void Value(int value);
		int Digits() { return digits; }
	};
};};
