/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFFPSLabelControl.h"
#include "..\LFCore\LFMath\LFRectangle.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFFPSLabelControl::LFFPSLabelControl(const LFRectangle &posTileSize, const LFColor &color) : 
		LFLabelControl(LFString("FPS"), LFString("00000"), posTileSize)
	{
		LFLabelControl::SetColor(color);
	}

	void LFFPSLabelControl::Update(double deltaTime)
	{
		time += deltaTime;
		++fpsCounter;

		if (time > 1000) //one second
		{
			SetText(LFString(fpsCounter));
			fpsCounter = time = 0;
		}

		LFControl::Update(deltaTime);
	}
}}}
