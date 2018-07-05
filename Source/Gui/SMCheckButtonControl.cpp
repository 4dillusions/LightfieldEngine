#include "SMCheckButtonControl.h"

namespace SMEngine { namespace Gui
{
	SMCheckButtonControl::SMCheckButtonControl(const SMString &name, const SMRectangle &rectangle, const SMString &trueTextureName, const SMString &falseTextureName,
	    bool trueTextureIsAlpha, bool falseTextureIsAlpha) :
			SMControl(name, rectangle), isChecked(false), isEnabled(true),
				ClickedEvent(&SMIClickedEventHandler<SMCheckButtonControl *>::Clicked)
	{
		trueSprite = new SMSprite(SMVector2D(rectangle.width, rectangle.height), rectangle.position, trueTextureName, trueTextureIsAlpha);
		componentList.Add(trueSprite);

		falseSprite = new SMSprite(SMVector2D(rectangle.width, rectangle.height), rectangle.position, falseTextureName, falseTextureIsAlpha);
		componentList.Add(falseSprite);

		IsChecked(isChecked);
	}

	SMCheckButtonControl::~SMCheckButtonControl()
	{ }

	void SMCheckButtonControl::TouchPressed(const SMTouchEventArgs &args)
	{
		if (rectangle.Contains(args.x, args.y))
		{
			IsChecked(!isChecked);

			controlArgs.subject = this;
			ClickedEvent(controlArgs);
		}
	}

	bool SMCheckButtonControl::IsChecked()
	{
		return isChecked;
	}

	void SMCheckButtonControl::IsChecked(bool isChecked, bool isCheckEnable)
	{
		if ((isVisible && isAlive && isEnabled) || isCheckEnable)
		{
			this->isChecked = isChecked;

			trueSprite->IsVisible(isChecked);
			falseSprite->IsVisible(!isChecked);
		}
	}
};};
