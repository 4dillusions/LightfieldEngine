#pragma once

#include "LFNumberLabelControl.h"
#include "..\..\..\..\Core\Common\LFTimer.h"

namespace LFEngine { namespace Graphics { namespace LF2D { namespace GUI {
	class LFENGINE_LIBRARY LFLabelFPSControl : public LFNumberLabelControl
	{
	private:
		LFCore::Common::LFTimer timer;
		double time;
		int fpsCounter;

	public:
		LFLabelFPSControl(const LFEngine::GameEngine::LFFontMaterial &fontMaterial, const LFLabelData &labelData);
		virtual ~LFLabelFPSControl();

		//LFGameCompositComponent
		virtual void Update(double deltaTime);
	};
}}}}
