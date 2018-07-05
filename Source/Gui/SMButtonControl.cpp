#include "SMButtonControl.h"

namespace SMEngine { namespace Gui
{
	SMButtonControl::SMButtonControl(const SMString &name, const SMString &text, int fontHeight, const SMRectangle &rectangle, const SMString &buttonTextureName, bool buttonTextureIsAlpha)
		//: SMLabelControl(SMString(name).AppendStr("_label1"), text, rectangle.Center(), 30), text(text)
		: SMControl(name, rectangle)
	{
		buttonSprite = new SMSprite(SMVector2D(rectangle.width, rectangle.height), rectangle.position, buttonTextureName, buttonTextureIsAlpha);
		componentList.Add(buttonSprite);

		label = new SMLabelControl("label1", text, rectangle.Center(), fontHeight);
		SMList<SMSprite *> spriteList;
		label->GetSprites(spriteList);

		for (spriteList.First(); spriteList.IsDone(); spriteList.Next())
			componentList.Add(spriteList.Current());

		label->OffsetPositionCenter();
	}

	SMButtonControl::~SMButtonControl()
	{ }
};};
