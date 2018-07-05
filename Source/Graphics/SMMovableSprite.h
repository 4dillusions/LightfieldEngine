#pragma once

#include "SMSprite.h"
#include "..\\Math\\SMRectangle.h"

namespace SMEngine { namespace Graphics
{
	/*
	Használat:

	SMMovableSprite *badaLogo = new SMMovableSprite(SMRectangle(128, 128, 40, 100), "BadaLogo.jpg", SMVector2D(0, 30));
	spriteLayer->Add(badaLogo);
	badaLogo->IsMove(true);
	*/
	class SMMovableSprite : public SMSprite
	{
	protected:
		SMRectangle rectangle;
		bool isMove;
		SMVector2D velocity;

	public:
		SMMovableSprite(const SMRectangle &rectangle, SMString textureName, const SMVector2D &velocity, bool isMove = false, bool isAlpha = false, bool isVisible = true, bool isFont = false);
		override ~SMMovableSprite();

		override void Update(double deltaTime);

		bool IsMove(bool isMove)
		{
			this->isMove = isMove;
		}
	};
};};
