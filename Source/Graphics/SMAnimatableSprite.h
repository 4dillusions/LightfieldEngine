#pragma once

#include "..\\Graphics\\SMSprite.h"
#include "..\\Core\\SMTimer.h"

using namespace SMEngine::Graphics;
using namespace SMEngine::Core;

namespace SMEngine { namespace Gui
{
	/*
	Mozgathat�, anim�lhat� sprite

	Haszn�lat:
	SMAnimatableSprite *animSprite;
	...
	animSprite = new SMAnimatableSprite(SMVector2D(80, 80), SMVector2D(256, 512), SMVector2D(100, 50), "ships.png", SMVector2D(10, 16));
	animSprite->SpeedTime(20); //anim sebess�g milisecundumban
	animSprite->IsLoop(true); //ism�tl�d� anim e
	animSprite->IsForward(true); //az anim�ci� ir�nya el�re/h�tra
	animSprite->IsKillMe(false); //anim, ut�n t�r�lje e mag�t

	spriteLayer->Add(animSprite);


	animSprite->IsLoop(false); //ism�tl�d� anim e
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
		int vertexIndex; //a quad m�trixban a vertex indexe
		int frameCout; //�sszesen h�ny r�szb�l �ll a m�trix
		int vertexCout; //�sszesen h�ny vertex van
		SMTimer timer;
		double time;
		double speedTime;
		bool isLoop; //ism�tl�d� anim�
		bool isKillMe; //az anim�ci� v�g�n megsemmis�ti e mag�t
		bool isForward; //el�re, vagy visszafel� anim�l�dik
		bool isAnimating; //�ppen most anim�ci� alatt van e
		bool isFirstUse; //egyszeri flag, kezdetben m�g ne anim�l�djon semmi

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
