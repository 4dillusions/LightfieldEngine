#include "SMImageControl.h"

namespace SMEngine { namespace Gui
{
	SMImageControl::SMImageControl(const SMString &name, const SMRectangle &rectangle, const SMString &imageName, bool imageIsAlpha)
		: SMControl(name, rectangle)
	{
		imageSprite = new SMSprite(SMVector2D(rectangle.width, rectangle.height), rectangle.position, imageName, imageIsAlpha);
		componentList.Add(imageSprite);
	}

	SMImageControl::~SMImageControl()
	{ }

	void SMImageControl::Position(const SMVector2D &position)
	{
		imageSprite->Position(position);
	}

	void SMImageControl::PositionOffset(const SMVector2D &position)
	{
		imageSprite->PositionOffset(position);
	}
};};
