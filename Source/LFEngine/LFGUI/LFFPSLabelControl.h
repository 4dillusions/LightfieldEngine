/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFLabelControl.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFFPSLabelControl final : public LFLabelControl
	{
		double time;
		int fpsCounter;

	public:
		LFFPSLabelControl(const LFCore::LFMath::LFRectangle &posTileSize, const LFCore::LFMath::LFColor &color);
		~LFFPSLabelControl() = default;

		//LFControl functions
		void Update(double deltaTime) override;
	};
}}}
