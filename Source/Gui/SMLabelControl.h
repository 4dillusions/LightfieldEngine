#pragma once

#include "SMControl.h"

namespace SMEngine { namespace Gui
{
	/*
	LabelControl: Szöveget jelenít meg.

	Használat:
	SMLabelControl *label = new SMLabelControl("label1", "ABCD", SMVector2D(), 30);
	guiLayer->Add(label);

	A kattintási esemény kezelés au, mint az ImageControl-nál, bár nem valószínû, hogy ez itt kell.
	*/
	class SMLabelControl : public SMControl
	{
	public:
		SMLabelControl(const SMString &name, const SMString &text, const SMVector2D &position, int height);
		virtual ~SMLabelControl();

		void OffsetPositionCenter(); //a magasság felével felfelé a szélesség felével balra mozgatja magához képest középre
	};
};};
