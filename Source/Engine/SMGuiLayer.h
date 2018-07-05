#pragma once

#include "..\\Core\\SMGameCompositComponent.h"
#include "..\\Graphics\\SMSprite.h"
#include "..\\Graphics\\SMSpriteGroup.h"

using namespace SMEngine::Core;
using namespace SMEngine::Graphics;

namespace SMEngine { namespace Engine
{
	/*
	Használat:

	SMGuiLayer *guiLayer = new SMGuiLayer("guiLayer");
	mainScreen->Add(guiLayer);
	 */
	class SMGuiLayer : public SMGameCompositComponent
	{
	public:
		SMGuiLayer(const SMString &name);
		override ~SMGuiLayer();

		override void Add(SMGameComponent *gameComponent); //Control-t vár
		override void WriteReport();
	};
};};
