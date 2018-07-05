#include "SMNumberLabelControl.h"
#include "SMFontSprite.h"

namespace SMEngine { namespace Gui
{
	SMNumberLabelControl::SMNumberLabelControl(const SMString &name, int value, int digits, const SMVector2D &position, int height)
		: SMLabelControl(name, SMString().AppendStr(value, digits), position, height), value(value), digits(digits)
	{ }

	SMNumberLabelControl::~SMNumberLabelControl()
	{ }

	void SMNumberLabelControl::Value(int value)
	{
		valueText.Clear();
		valueText.Append(value, digits);

		int index = 0;
		for (componentList.First(); componentList.IsDone(); componentList.Next())
			dynamic_cast<SMFontSprite *>(componentList.Current())->Character(valueText[index++]);
	}
};};
