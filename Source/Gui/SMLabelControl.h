#pragma once

#include "SMControl.h"

namespace SMEngine { namespace Gui
{
	/*
	LabelControl: Sz�veget jelen�t meg.

	Haszn�lat:
	SMLabelControl *label = new SMLabelControl("label1", "ABCD", SMVector2D(), 30);
	guiLayer->Add(label);

	A kattint�si esem�ny kezel�s au, mint az ImageControl-n�l, b�r nem val�sz�n�, hogy ez itt kell.
	*/
	class SMLabelControl : public SMControl
	{
	public:
		SMLabelControl(const SMString &name, const SMString &text, const SMVector2D &position, int height);
		virtual ~SMLabelControl();

		void OffsetPositionCenter(); //a magass�g fel�vel felfel� a sz�less�g fel�vel balra mozgatja mag�hoz k�pest k�z�pre
	};
};};
