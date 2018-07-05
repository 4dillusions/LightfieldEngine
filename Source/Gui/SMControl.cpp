#include "SMControl.h"

namespace SMEngine { namespace Gui
{
	SMControl::SMControl(const SMString &name, const SMRectangle &rectangle)
		: SMGameCompositComponent(name), rectangle(rectangle), isUpdatable(false), ClickedEvent(&SMIClickedEventHandler<SMControl *>::Clicked)
	{
		SMInput::Instance()->TouchPressedEvent += this;
	}

	SMControl::SMControl(const SMControl &value)
		: SMGameCompositComponent(name), ClickedEvent(&SMIClickedEventHandler<SMControl *>::Clicked)
	{
		*this = value;
		SMInput::Instance()->TouchPressedEvent += this;
	}

	SMControl::~SMControl()
	{
		SMInput::Instance()->TouchPressedEvent -= this;
	}

	void SMControl::TouchPressed(const SMTouchEventArgs &args)
	{
		if (isVisible && rectangle.Contains(args.x, args.y))
		{
			controlArgs.subject = this;
			ClickedEvent(controlArgs);
		}
	}

	void SMControl::GetSprites(SMList<SMSprite *> &spriteList)
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (SMSprite *current = dynamic_cast<SMSprite *>(componentList.Current()))
				spriteList.Add(current);

		for (controls.First(); controls.IsDone(); controls.Next())
			controls.Current()->GetSprites(spriteList);
	}

	void SMControl::GetControls(SMList<SMControl *> &controlList)
	{
		if (isUpdatable) //sajnos ezzel akkor nem minden control kerül fel, így nem lehet késõbb lekezelni sem
			controlList.Add(this);

		for (controls.First(); controls.IsDone(); controls.Next())
			controls.Current()->GetControls(controlList);
	}
};};
