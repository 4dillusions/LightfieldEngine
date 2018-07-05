/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFAnimatedSpriteControl.h"
#include "..\LFCore\LFCommon\LFSystemData.h"
#include "..\LFCore\LFMath\LFVector4D.h"

using namespace LF3Engine::LFEngine::LFData;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFMath;

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	LFAnimatedSpriteControl::LFAnimatedSpriteControl(const LFString &name, const LFRectangle &posVertexSize, const LFVector4D &posStartEndAtlas, 
		double animTime, bool isReleaseAfterAnim, bool isRepeat)
			: LFSpriteControl(name, posVertexSize, LFVector2D(posStartEndAtlas.x, posStartEndAtlas.y)),
				animTime(animTime), isReleaseAfterAnim(isReleaseAfterAnim), isRepeat(isRepeat), frameCount(posStartEndAtlas.z - posStartEndAtlas.x),
				startVertexPos(posAtlasSize.position)
	{ }

	void LFAnimatedSpriteControl::Update(double deltaTime)
	{
		if (isAnim)
		{
			time += deltaTime;

			if (time > animTime)
			{
				posAtlasSize.position.x = startVertexPos.x + frames;
				SetStartVertex();

				time = 0;
				frames++;

				if (frames > frameCount)
				{
					if (isReleaseAfterAnim)
						SetIsAlive(false);

					frames = 0;

					if (!isRepeat)
						isAnim = false;
				}
			}
		}

		LFControl::Update(deltaTime);
	}
}}} 
