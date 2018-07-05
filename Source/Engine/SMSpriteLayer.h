#pragma once

#include "..\\Core\\SMGameCompositComponent.h"
#include "..\\Graphics\\SMSprite.h"
#include "..\\Graphics\\SMSpriteGroup.h"

using namespace SMEngine::Core;
using namespace SMEngine::Graphics;

namespace SMEngine { namespace Engine
{
	/*
	Haszn�lat:

	SMSpriteLayer *spriteLayer = new SMSpriteLayer("spriteLayer");
	mainScreen->Add(spriteLayer);
	*/
	class SMSpriteLayer : public SMGameCompositComponent
	{
	public:
		SMSpriteLayer(const SMString &name);
		override ~SMSpriteLayer();

		override void Add(SMGameComponent *gameComponent); //Sprite-ot v�r
		override void WriteReport();
	};
};};
