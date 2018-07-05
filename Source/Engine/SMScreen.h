#pragma once

#include "..\\Core\\SMGameCompositComponent.h"

using namespace SMEngine::Core;

namespace SMEngine { namespace Engine
{
	/*
	Használat:

	SMScreen *mainScreen = new SMScreen("mainScreen");
	SMSceneGraph::Instance()->Add(mainScreen);
	*/
	class SMScreen : public SMGameCompositComponent
	{
	public:
		SMScreen(const SMString &name);
		override ~SMScreen();
	};
};};
