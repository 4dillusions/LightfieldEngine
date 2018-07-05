/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFSpriteControl.h"
#include "..\LFCore\LFMath\LFCircle.h"
#include "..\LFCore\LFCommon\LFEvent.h"

namespace LF3Engine { namespace LFEngine { namespace LFGUI
{
	class LFMovableSpriteControl;

	struct SpriteTouchEventArgs { LFMovableSpriteControl *anotherSprite; };

	class LFMovableSpriteControl : public LFSpriteControl
	{
	protected:
		static LFCore::LFMath::LFRectangle walls;
		static LFCore::LFCollections::LFLinkedList<LFMovableSpriteControl *> movableSpriteList;

		LFCore::LFMath::LFCircle boundingCircle;
		LFCore::LFMath::LFVector2D move = LFCore::LFMath::LFVector2D();
		double refreshSpeed = 1000.0;
		double time = 0;

		void CCDCorrection(const LFMovableSpriteControl *anotherSprite = nullptr);
		//void BoundingCircleCorrection();

	public:
		LFMovableSpriteControl(const LFCore::LFCommon::LFString &name, const LFCore::LFMath::LFRectangle &posVertexSize, const LFCore::LFMath::LFVector2D &posAtlas, float boundingRadius, const LFCore::LFMath::LFColor &color = LFCore::LFMath::LFColor(LFCore::LFMath::LFColor::White));
		virtual ~LFMovableSpriteControl();

		static void SetWalls(const LFCore::LFMath::LFRectangle &walls);
		void SetMove(const LFCore::LFMath::LFVector2D &move);
		void SetRefreshSpeed(double refreshSpeed);

		LFCore::LFCommon::LFEvent<SpriteTouchEventArgs> OnSpriteTouch;

		//LFControl functions
		void SetPosition(const LFCore::LFMath::LFVector2D &position) override;
		void Update(double deltaTime) override;
	};
}}}
