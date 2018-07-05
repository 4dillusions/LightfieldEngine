#pragma once

#include "..\\Graphics\\SMSprite.h"
#include "..\\Core\\SMTimer.h"

using namespace SMEngine::Graphics;
using namespace SMEngine::Core;

namespace SMEngine { namespace Gui
{
	/*
	Mozgatható, animálható sprite

	Használat:
	SMAnimatableSprite *animSprite;
	...
	animSprite = new SMAnimatableSprite(SMVector2D(80, 80), SMVector2D(256, 512), SMVector2D(100, 50), "ships.png", SMVector2D(10, 16));
	animSprite->SpeedTime(20); //anim sebesség milisecundumban
	animSprite->IsLoop(true); //ismétlõdõ anim e
	animSprite->IsForward(true); //az animáció iránya elõre/hátra
	animSprite->IsKillMe(false); //anim, után törölje e magát

	spriteLayer->Add(animSprite);


	animSprite->IsLoop(false); //ismétlõdõ anim e
	...
	if (!animSprite->IsAnimating())
	{
		animSprite->IsForward(false);
		animSprite->PlayAnim();
	}
	*/
	class SMAnimatableSprite : public SMSprite
	{
	private:
		int vertexIndex; //a quad mátrixban a vertex indexe
		int frameCout; //összesen hány részbõl áll a mátrix
		int vertexCout; //összesen hány vertex van
		SMTimer timer;
		double time;
		double speedTime;
		bool isLoop; //ismétlõdõ animû
		bool isKillMe; //az animáció végén megsemmisíti e magát
		bool isForward; //elõre, vagy visszafelé animálódik
		bool isAnimating; //éppen most animáció alatt van e
		bool isFirstUse; //egyszeri flag, kezdetben még ne animálódjon semmi

	public:

		SMAnimatableSprite(const SMVector2D &frameSize, const SMVector2D &textureSize, const SMVector2D &position, const SMString &textureName, const SMVector2D &matrixSize,
				bool isVisible = true);

		override void Update(double deltaTime);

		void SpeedTime(double speedTime) { this->speedTime = speedTime; }
		void IsLoop(bool isLoop) { this->isLoop = isLoop; }
		void IsKillMe(bool isKillMe);
		void IsForward(bool isForward);
		bool IsAnimating() { return isAnimating; }

		void PlayAnim();
	};
};};
