#pragma once

#include "SMLabelControl.h"

namespace SMEngine { namespace Gui
{
	/*
	NumberLabelControl: Kiz�r�lag sz�mokat jelen�t meg. Meghat�rozhat� adott digit sz�m, melyn�l az �res mez�ket null�val t�lti ki.
	Egyel�re adott digits m�rettel dolgozik.

	Haszn�lat:
	SMNumberLabelControl *numLabel = new SMNumberLabelControl("numLabel1", 2561, 6, SMVector2D(), 30);
	guiLayer->Add(numLabel);
	...
	numLabel->Value(593); //000593

	A kattint�si esem�ny kezel�s au, mint az ImageControl-n�l, b�r nem val�sz�n�, hogy ez itt kell.
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
