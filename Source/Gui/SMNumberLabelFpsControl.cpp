#include "SMNumberLabelFpsControl.h"

namespace SMEngine { namespace Gui
{
	SMNumberLabelFpsControl::SMNumberLabelFpsControl(const SMString &name, int value, int digits, const SMVector2D &position, int height)
		: SMNumberLabelControl(name, value, digits, position, height), time(0), fpsCounter(0)
	{
		this->isUpdatable = true;
	}

	SMNumberLabelFpsControl::~SMNumberLabelFpsControl()
	{ }

	void SMNumberLabelFpsControl::Update(double deltaTime)
	{
		time += timer.DeltaTime();
		++fpsCounter;

		if (time > 1000) //másodpercenként
		{
			Value(fpsCounter);
			fpsCounter = time = 0;
		}
	}
};};
