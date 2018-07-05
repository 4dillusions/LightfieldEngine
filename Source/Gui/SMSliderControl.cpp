#include "SMSliderControl.h"

namespace SMEngine { namespace Gui
{
	SMSliderControl::SMSliderControl(const SMString &name, SMGuiLayer *guiLayer, const SMVector2D &position, int slideValueMin, int slideValueMax, int slideStep) :
		ClickedEvent(&SMIClickedEventHandler<SMSliderControl *>::Clicked), name(name), position(position), slideValue(0),
			slideValueMin(slideValueMin), slideValueMax(slideValueMax), slideStep(slideStep), commaStartPos(64 + position.x, 0 + position.y), isEnabled(true)
	{
		imgPlus = new SMImageControl(SMString(name).AppendStr("imgPlus"), SMRectangle(320 + position.x, 0 + position.y, 64, 64), "SliderPlus.png", true);
		imgPlus->ClickedEvent += this;
		guiLayer->Add(imgPlus);

		imgMinus = new SMImageControl(SMString(name).AppendStr("imgMinus"), SMRectangle(0 + position.x, 0 + position.y, 64, 64), "SliderMinus.png", true);
		imgMinus->ClickedEvent += this;
		guiLayer->Add(imgMinus);

		imgBar = new SMImageControl(SMString(name).AppendStr("imgBar"), SMRectangle(64 + position.x, 24 + position.y, 256, 16), "SliderBar.png", true);
		guiLayer->Add(imgBar);

		imgComma = new SMImageControl(SMString(name).AppendStr("imgComma"), SMRectangle(commaStartPos.x, commaStartPos.y, 16, 64), "SliderComma.png", true);
		guiLayer->Add(imgComma);

		stepOffset = (imgBar->Rectangle().width - imgComma->Rectangle().width) / (float)slideValueMax;
	}

	void SMSliderControl::SlideValue(int value, bool isSlideEnable)
	{
		if (imgPlus->IsVisibleControl() || isSlideEnable)
		{
			slideValue = value;

			if (value < slideValueMin) slideValue = slideValueMin;
			if (value > slideValueMax) slideValue = slideValueMax;

			//csúszka beállítása
			imgComma->Position(SMVector2D(commaStartPos.x, commaStartPos.y)); //nullára állítás
			imgComma->PositionOffset(SMVector2D(stepOffset * slideValue, 0)); //mozgatás adott helyre a skálán
		}
	}

	void SMSliderControl::Clicked(const SMObserverEventArgs<SMControl *> &args)
	{
		if (isEnabled)
		{
			if (args.subject->Name() == imgPlus->Name()) SlideValue(slideValue + slideStep);
			if (args.subject->Name() == imgMinus->Name()) SlideValue(slideValue - slideStep);

			controlArgs.subject = this;
			ClickedEvent(controlArgs);
		}
	}
};};
