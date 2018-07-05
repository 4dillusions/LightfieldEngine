/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFSpriteControl.h"

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFMath
{
	class LFVector4D;
}}}}

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFAnimatedSpriteControl final : public LFSpriteControl
	{
		const double animTime; //msec
		const bool isReleaseAfterAnim;
		const bool isRepeat;
		const int frameCount;
		const LFCore::LFMath::LFVector2D startVertexPos;

		bool isAnim = true;
		double time = 0;
		int frames = 0;

	public:
		LFAnimatedSpriteControl(const LFCore::LFCommon::LFString &name, const LFCore::LFMath::LFRectangle &posVertexSize, const LFCore::LFMath::LFVector4D &posStartEndAtlas, double animTime, bool isReleaseAfterAnim, bool isRepeat);
		~LFAnimatedSpriteControl() = default;

		//LFControl functions
		void Update(double deltaTime) override;
	};
}}} 
