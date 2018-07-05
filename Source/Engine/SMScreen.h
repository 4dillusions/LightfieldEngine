#pragma once

#include "..\\Core\\SMGameCompositComponent.h"

using namespace SMEngine::Core;

namespace SMEngine { namespace Engine
{
	/*
	Haszn�lat:

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
