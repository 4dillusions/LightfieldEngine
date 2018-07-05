#include "LFLabelFPSControl.h"
#include "LFNumberLabelControl.h"
#include "..\..\..\Script\LFLuaType.h"
#include "..\..\..\Script\Engine\Graphics\LF2D\GUI\LFLabelFPSControlLua.h"

using namespace LFEngine::Script;
using namespace LFEngine::GameEngine;

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI {
	LFLabelFPSControl::LFLabelFPSControl(const LFFontMaterial &fontMaterial, const LFLabelData &labelData) : 
		LFNumberLabelControl(fontMaterial, labelData),
		time(0), fpsCounter(0)
	{
		controlType = LFLuaType().SetObject(this, LFLabelFPSControlName, sizeof(LFLabelFPSControl));
	}

	LFLabelFPSControl::~LFLabelFPSControl()
	{ }

	void LFLabelFPSControl::Update(double deltaTime)
	{
		time += timer.DeltaTime();
		++fpsCounter;

		if (time > 1000) //one second
		{
			Value(fpsCounter);
			fpsCounter = time = 0;
		}

		LFGameCompositComponent::Update(deltaTime);
	}
}}}}
