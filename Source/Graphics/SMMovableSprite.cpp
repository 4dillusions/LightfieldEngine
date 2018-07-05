#include "SMMovableSprite.h"

namespace SMEngine { namespace Graphics
{
	SMMovableSprite::SMMovableSprite(const SMRectangle &rectangle, SMString textureName, const SMVector2D &velocity, bool isMove, bool isAlpha, bool isVisible , bool isFont)
		: SMSprite(rectangle.position, rectangle.Size(), textureName, isAlpha, isVisible, isFont), rectangle(rectangle), velocity(velocity), isMove(isMove)
	{ }

	SMMovableSprite::~SMMovableSprite()
	{ }

	void SMMovableSprite::Update(double deltaTime)
	{
		if (isMove)
			PositionOffset(velocity * (deltaTime / 1000.0));

		SMSprite::Update(deltaTime);
	}
};};
