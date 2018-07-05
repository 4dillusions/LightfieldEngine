#include "SMLabelControl.h"
#include "SMFontSprite.h"

namespace SMEngine { namespace Gui
{
	SMLabelControl::SMLabelControl(const SMString &name, const SMString &text, const SMVector2D &position, int height)
		: SMControl(name, SMRectangle(position.x, position.y, 0, height))
	{
		for (int i = 0; i < text.Lenght(); ++i)
		{
			SMFontSprite *font = new SMFontSprite(text[i], height, SMVector2D(position.x + rectangle.width, position.y), "Font.png");
			rectangle.width += (font->CharWidth() * height / 14);

			componentList.Add(font);
		}
	}

	SMLabelControl::~SMLabelControl()
	{ }

	void SMLabelControl::OffsetPositionCenter()
	{
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			if (SMFontSprite *font = dynamic_cast<SMFontSprite *>(componentList.Current()))
				font->PositionOffset(SMVector2D(-rectangle.width / 2, -rectangle.height / 2));
	}
};};
